#include<stdint.h>
#include<stdlib.h>
#include<rte_mbuf.h>
#include<usocket.h>
#include<udp.h>
#include<simple-queue.h>

int maxfd=0;
struct socket_info sockets[1024];
int udp_socket(uint32_t ip_addr,uint32_t port)
{	
	int i=0;
	struct socket_info * sockptr = NULL;
	for (i=0;i<maxfd;i++)
	{
		sockptr =&sockets[i];
		if(sockptr->port==port)
		{
			return -1;
		}
	}
	sockptr =&sockets[maxfd];
	sockptr->ip_addr=ip_addr;
	sockptr->port=port;
	maxfd++;
	return maxfd-1;
}

int udp_send(int sockfd, void * buffer, uint16_t buf_len, uint32_t dst_addr, uint32_t port)
{
	struct rte_mbuf pkt;
	struct socket_info * sockptr = NULL;
	sockptr =&sockets[sockfd];
	struct udp_conn_t dummy;
	dummy.src_port=sockptr->port;
	dummy.dst_port=port;
	dummy.src_ip=sockptr->ip_addr;
	dummy.dst_ip=dst_addr;
	pkt.buf_addr=buffer;
	pkt.buf_len=buf_len;
	udp_packet_create(&pkt,&dummy);
	return 0;
}

void add_packet_to_queue(int i,struct rte_mbuf *pkt, uint32_t src_ip, uint32_t dst_ip,uint16_t dst_port,uint16_t src_port){
	struct udp_conn_t dummy;
	dummy.src_port=src_port;
	dummy.dst_port=dst_port;
	dummy.src_ip=src_ip;
	dummy.dst_ip=dst_ip;
	sq_push(i,soft_q,pkt->buf_addr,pkt->buf_len,dummy);	
}
/*
int udp_recv(int sockfd, void * buffer, uint16_t buf_len)
{
	
}*/
