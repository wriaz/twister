#include <stdio.h>
#include <stdint.h>
#include <getopt.h>
#include <tw_common.h>
#include <tw_api.h>
#include <stats.h>
#include "twiperf.h"
#define PacketLimit 0
#define UDP_PROTO_ID    17


tw_buf_t * tx_buf; //global memory buffer variable, equal the payload user given in arguments.
tw_loop_t * tw_loop; // event loop, used for client and server.                           

int i_errno; // variable used to store error number
int main(int, char **);


/**** temporary variables for udp server i.e reply_udp_payload ****/
struct ether_hdr * eth; //ethernet header 14 bytes
struct ipv4_hdr * ipHdr_d; // ip header 20 bytes
struct udp_hdr * udp_hdr_d; //udp header 8 bytes
uint32_t dst_ip,src_ip;    // ips in decimal
uint16_t eth_type;
uint16_t src_port, dst_port;


/*** stats variables ***/
struct iperf_test test;
struct iperf_stats test_stats;

/**** prototypes ****/
void print_perf_stats();
int udp_app_server(void *);
void reply_udp_payload(tw_rx_t *, tw_buf_t *);
void reply_ether_payload(tw_rx_t *, tw_buf_t *);
void pkt_rx(tw_rx_t *, tw_buf_t *);
void pkt_tx(tw_tx_t *);
void tw_udp_connect();

void sig_handler(int signo) /*On presseing Ctrl-C*/
{
    if (signo == SIGINT){
        twiprintf(&test, summary_dot_line);
        twiprintf(&test, summary_head);
        twiprintf(&test, summary_stats_number, 0.0, test_stats.interval_window, test_stats.total_transfered_bytes, test_stats.bandwidth, test_stats.datagrams_sent);
	printf("\n\n");
        exit(1);
  }
}

int twiperf_parse_arguments(struct iperf_test *test, int argc, char **argv) /*parsing user given arguments*/
{
    int server_flag, client_flag, udp_flag, ethernet_flag;
    static struct option longopts[] =
    {
        {"udp", no_argument, NULL, 'u'},
        {"ethernet", no_argument, NULL, 'e'},
        {"server", no_argument, NULL, 's'},
        {"client", required_argument, NULL, 'c'},
        {"help", no_argument, NULL, 'h'},
        {"port", required_argument, NULL, 'p'},
        {"bytes", required_argument, NULL, 'n'},
        {NULL, 0, NULL, 0}
    };
    int flag;
    server_flag = client_flag = udp_flag = ethernet_flag = 0;
    test->packet_size = 64; //initialized to default value of 64 bytes pcket size
    test->server_port = 5001;  //initialized to default port of 5001
    test->client_port = 7777;  //initialized to default port of 5001
    test->test_runtime = 0;  //initialized to default infinite runtime

	udp_flag = 1;
    test->protocol_id = 2;

    while ((flag = getopt_long(argc, argv, "n:p:ue:cs:h:", longopts, NULL)) != -1) {
        switch (flag) {
            case 'p':
                test->server_port = atoi(optarg);
                break;
            case 'n':
                test->packet_size =atoi(optarg);
                break;
            case 'c':
                client_flag = 1;
                test->role = 2;
                test->client_mac = tw_get_ether_addr("tw0");
                test->server_ip =tw_cpu_to_be_32( tw_convert_ip_str_to_dec(strdup(optarg)));
                test->client_ip = tw_cpu_to_be_32(tw_get_ip_addr("tw0"));
                break;
            case 's':
                server_flag = 1;
                test->role = 1;
                test->server_mac = tw_get_ether_addr("tw0");
                test->server_ip = tw_cpu_to_be_32(tw_get_ip_addr("tw0"));
                break;
            case 'e':
                ethernet_flag = 1;
		        udp_flag = 0;
                test->protocol_id = 1;
                break;
            case 'u':
                udp_flag = 1;
                test->protocol_id = 2;
                break;
            case 'h':
                twiperf_usage();
                exit(1);
                break;
            default:
                twiperf_usage();
                exit(1);
        }
	}
	if(server_flag == 1 && client_flag == 1 || udp_flag == 1 && ethernet_flag == 1 )
	{
		twiperf_usage();
        exit(1);
	}
	if(server_flag == 0 && client_flag == 0 || udp_flag == 0 && ethernet_flag == 0 )
	{
		twiperf_usage();
        exit(1);
	}
    if ((test->role != 1) && (test->role != 2)) {
        i_errno = IENOROLE;
        return -1;
    }
    if (udp_flag == 1 && test->packet_size > MAX_UDP_BLOCKSIZE) {
        i_errno = IEUDPBLOCKSIZE;
        return -1;
    }
	return 0;
}

/* reply_udp_payload acts as udp server; switches the IP and ports, mac addresses and echoes back the packet to sender*/
void reply_udp_payload(tw_rx_t * handle, tw_buf_t * buffer) {
     eth = buffer->data;
     eth_type = tw_be_to_cpu_16(eth->ether_type);
     ipHdr_d = buffer->data + sizeof(struct ether_hdr);
     dst_ip  = (ipHdr_d->dst_addr);
     src_ip = (ipHdr_d->src_addr);
     ipHdr_d->dst_addr = (src_ip);
     ipHdr_d->src_addr = (dst_ip);
     ipHdr_d->hdr_checksum = tw_ipv4_cksum(ipHdr_d);
     udp_hdr_d = (struct udp_hdr *)ipHdr_d + sizeof(struct ipv4_hdr);
     dst_port = (udp_hdr_d->dst_port);
     src_port = (udp_hdr_d->src_port);
     udp_hdr_d->dst_port = (src_port);
     udp_hdr_d->src_port = (dst_port);
     udp_hdr_d->dgram_cksum = 0;
     tw_copy_ether_addr(&(eth->s_addr), &(eth->d_addr));
     tw_copy_ether_addr(test.server_mac, &(eth->s_addr));
     test_stats.datagrams_recv++;
     tw_send_pkt(buffer, "tw0");
                 
}

/*initializing the udp app server with event loops and packet processing functions */
int udp_app_server(__attribute__((unused)) void * app_params) { 

    tw_rx_t * server;
    int status;
    tw_loop_t * tw_loop = tw_default_loop(INFINITE_LOOP);

    server = tw_rx_init(tw_loop);
    if (server == NULL) {
        printf("Error in RX init\n");
        exit(1);
    }

    status = tw_rx_start(server, reply_udp_payload);
    if (status) {
        printf("Error in receive start\n");
        exit(1);
    }
    tw_timer_t * timer_handle;
    timer_handle = tw_timer_init(tw_loop);
    tw_timer_start(timer_handle, print_perf_stats, 1000);
    twiprintf(&test, stats_head);
    tw_run(tw_loop);
    return 0;
}

/* reply_ether_payload acts as ethernet packet server at layer-2; switches the mac addresses and echoes back the packet to sender*/
void reply_ether_payload(tw_rx_t * handle, tw_buf_t * buffer) {
    struct ether_hdr * eth = buffer->data;
    tw_copy_ether_addr(&(eth->s_addr), &(eth->d_addr));
	tw_copy_ether_addr(test.server_mac, &(eth->s_addr));
	tw_send_pkt(buffer, "tw0");
}
/*initializing the ethernet packet server with event loops and packet processing functions */
int ether_app_server(__attribute__((unused)) void * app_params) {

    tw_rx_t * server;
    int status;
    struct tw_sockaddr_in * addr;
    tw_loop_t * tw_loop = tw_default_loop(INFINITE_LOOP);

    server = tw_rx_init(tw_loop);
    if (server == NULL) {
        printf("Error in RX init\n");
        exit(1);
    }

    status = tw_rx_start(server, reply_ether_payload);
    if (status) {
        printf("Error in receive start\n");
        exit(1);
    }
    tw_timer_t * timer_handle;
    timer_handle = tw_timer_init(tw_loop);
    tw_timer_start(timer_handle, print_perf_stats, 1000);
    twiprintf(&test, stats_head);
    tw_run(tw_loop);
    return 0;
}


/*packet receive callbacks, receives the packet , increment the counter and free the buffer*/
void pkt_rx(tw_rx_t * handle, tw_buf_t * buffer) { 
    eth = buffer->data;
    test_stats.datagrams_recv++;
    tw_free_pkt(buffer);
    return;
}
/*print the test stats, registerd as timer callback (1 second) at udp_app_client event loop, called every second*/
void print_perf_stats(){

    test_stats.interval_window = test_stats.interval_window + 1.0;
    uint64_t bytes = (   (  (tw_stats.rx_pps + tw_stats.tx_pps )*(test.packet_size)  ) /1000   ); //KBytes
    float bandwidth = (bytes *8*1000 )/ (float)(1048576.0) ; // Mbit / sec 
    twiprintf(&test, stats_number, test_stats.interval_window-1.0, test_stats.interval_window, tw_stats.rx_pps,tw_stats.tx_pps, bytes, bandwidth, test_stats.datagrams_sent, test_stats.datagrams_recv);

    test_stats.total_transfered_bytes += bytes;
    test_stats.bandwidth += bandwidth;
}

/*send udp packet, used in udp_app_client event loop*/
void pkt_tx(tw_tx_t * handle)
{
    test.eth = test.tx_buf->data;
    test.ip  = (test.tx_buf->data + sizeof(struct ether_hdr));
    test.udp = test.tx_buf->data + sizeof(struct ether_hdr) + sizeof(struct ipv4_hdr);
    test.udp->src_port = tw_cpu_to_be_16(test.client_port);
    test.udp->dst_port = tw_cpu_to_be_16(test.server_port);
    test.udp->dgram_len = tw_cpu_to_be_16(test.tx_buf->size - sizeof(struct ether_hdr) - sizeof(struct ipv4_hdr));
    test.udp->dgram_cksum = 0;
    test.ip->total_length = tw_cpu_to_be_16(test.tx_buf->size - sizeof(struct ether_hdr));
    test.ip->next_proto_id = UDP_PROTO_ID;
    test.ip->src_addr = test.client_ip;
    test.ip->dst_addr = test.server_ip;
    test.ip->version_ihl = 0x45;
    test.ip->time_to_live = 63;
    test.ip->hdr_checksum =tw_ipv4_cksum(test.ip);
    test.eth->ether_type = tw_cpu_to_be_16(ETHER_TYPE_IPv4);
    tw_copy_ether_addr(test.server_mac, &(test.eth->d_addr));
    tw_copy_ether_addr(test.client_mac, &(test.eth->s_addr));
    tw_send_pkt(test.tx_buf, "tw0");
    test_stats.datagrams_sent++;
}

int udp_app_client(__attribute__((unused)) void * app_params) {
    tw_rx_t * rx_handle;
    tw_timer_t * timer_handle;
    int status;
    tw_loop = tw_default_loop(INFINITE_LOOP); //udp app client event loop
    rx_handle = tw_rx_init(tw_loop);
    if (rx_handle == NULL) {
        printf("Error in RX initn");
        exit(1);
    }
    status = tw_rx_start(rx_handle, pkt_rx); //registering receive callback in event loop
    if (status) {
        printf("Error in receive startn");
        exit(1);
    }
    timer_handle = tw_timer_init(tw_loop); //registering timer callback i.e., void tw_udp_connect() 
    tw_timer_start(timer_handle, tw_udp_connect, 1000);
    tw_run(tw_loop); //start the event-loop
    return 0;
}
/*tw_udp_connect is called every second by udp_app_client event loop untill the Address of server is reloved. After that 
this callback is unregisterd and pkt_tx function is registerd as transmitt packets. */
void tw_udp_connect(){ 
    static arpCount=0;
    struct arp_table* temp_arp_entry=NULL;
    if (arpCount < 4){
        temp_arp_entry = tw_search_arp_table(test.server_ip);
        if(temp_arp_entry == NULL )  {
             tw_send_arp_request(tw_cpu_to_be_32(test.server_ip), "tw0");                                                                    
             arpCount++;
             return;
         }
        else {

             test.server_mac = &temp_arp_entry->eth_mac;
             struct in_addr server_ip; server_ip.s_addr = test.server_ip;
             struct in_addr client_ip; client_ip.s_addr = test.client_ip;
             printf("local %s, port %u ", inet_ntoa(client_ip), test.client_port);
             printf("connected to %s port %u\n", inet_ntoa(server_ip), test.server_port);
             tw_loop->timer_handle_queue=NULL; //TODO write unregister the tw_udp_connect() callback function.
             tw_loop->active_handles--;
             tw_tx_t * tx_handle = tw_tx_init(tw_loop); //registering the tx event for client, ready to send packets
             if (tx_handle == NULL) {
                 printf("Error in TX initn");
                 exit(1);
             }
             int status = tw_tx_start(tx_handle, pkt_tx);
             if (status) {
                  printf("Error in transmit startn");
                  exit(1);
             }
             tw_timer_t * timer_handle;
             timer_handle = tw_timer_init(tw_loop);
             tw_timer_start(timer_handle, print_perf_stats, 1000);
             twiprintf(&test, stats_head);
        }
    }
    else if (arpCount>=4 && temp_arp_entry == NULL ){
        printf("unable to find the ip on network.\n");
        exit(1);
    }

}

// MAIN
int main(int argc, char **argv) {
    tw_init_global();
    if (twiperf_parse_arguments(&test, argc, argv) < 0) {
        iperf_err(&test, "parameter error - %s", iperf_strerror(i_errno));
        fprintf(stderr, "\n");
        twiperf_usage();
        exit(1); 
    }
    
    if (signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");
    
    Printing_Enable = 1; //disable the real-time printing of Tx/Rx,
    tw_map_port_to_engine("tw0", "engine0");
    if(test.protocol_id == 1 && test.role == 1)
    {
	    ether_app_server(NULL);
    }
    else if (test.protocol_id == 2 && test.role == 1)
    {
        udp_app_server(NULL);
    }
    else if (test.protocol_id == 1 && test.role == 2)
    {
        printf("Functionality not supported yet\n");
    }
    if (test.protocol_id == 2 && test.role == 2)
	{
	    test.tx_buf = tw_new_buffer(test.packet_size);
	    tw_stats.secs_passed=0;
        struct in_addr server_ip; server_ip.s_addr = (test.server_ip);
        twiprintf(&test, on_host_conn, inet_ntoa(server_ip), test.server_port);
        udp_app_client(NULL);
	}
    
    return 0;
}

    




