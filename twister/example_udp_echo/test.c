#include <stdio.h>
#include <stdint.h>
#include <rx.h>
#include <initfuncs.h>
#include <event_loop.h>
#include <timestamp.h>

//int PIPELINE=0;

struct timestamp_option * pkt_timestamp;

int main (int, char **);
int launch_one_lcore(__attribute__((unused)) void *);
void reply_payload(int, void *, uint16_t, struct sock_conn_t);

void reply_payload(int sock_fd, void * payload_data, uint16_t payload_size, struct sock_conn_t conn) {
	pkt_timestamp = (struct timestamp_option *) payload_data;
	//printf("rx rcvd %lu echo %lu\n", pkt_timestamp->timestamp, pkt_timestamp->echo_timestamp);
	//uint64_t curr_time = get_current_timer_cycles();
	//parse_timestamp(pkt_timestamp, curr_time);
	//add_timestamp(pkt_timestamp, curr_time);
	pkt_timestamp->echo_timestamp = pkt_timestamp->timestamp;
	//printf("tx rcvd %lu echo %lu\n", pkt_timestamp->timestamp, pkt_timestamp->echo_timestamp);
	udp_send(sock_fd,(void *) pkt_timestamp,sizeof(struct timestamp_option), payload_size, conn.dst_ip, conn.dst_port);
	rte_free(payload_data);
	return;
}

int main(int argc, char **argv )
{
	init_global(argc, argv);
	rte_eal_mp_remote_launch(launch_one_lcore, NULL, CALL_MASTER);
	return 0;
}

int launch_one_lcore(__attribute__((unused)) void *dummy)
{
	void (*rx_cb_func) (int, void *, uint16_t, struct sock_conn_t) = reply_payload;
	int sockfd = udp_socket(port_info[0].start_ip_addr, 7777);
	event_flags_global = NO_FLAG_SET;
	struct event_io * io_event_rx = reg_io_event(sockfd, rx_cb_func, REPEAT_EVENT, event_flags_global, RX_CALLBACK);
	//struct event_io * io_event_tx = reg_io_event(sockfd, tx_cb_func, REPEAT_EVENT, NO_FLAG_SET, TX_CALLBACK);
	start_io_events(INFINITE_LOOP);
        return 0;
}

