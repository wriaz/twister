#ifndef _UDP_H_
#define _UDP_H_

#define UDP_PROTO_ID	17
#define TCP_PROTO_ID 06
struct udp_conn_t
{
	uint16_t src_port;
	uint16_t dst_port;
	uint32_t src_ip;
	uint32_t dst_ip;

};

extern void udp_packet_parser(struct rte_mbuf *pkt, uint32_t src_ip, uint32_t dst_ip);
extern void udp_packet_create(struct rte_mbuf *pkt, struct udp_conn_t *udp_conn);
extern uint8_t udp_hdr_size;
extern uint8_t tcp_hdr_size; 

#endif
