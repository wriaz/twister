#ifndef _PORTCONF_H_
#define _PORTCONF_H_

#define MAX_ETH_PORTS 16
#define MAX_RX_QUEUES_PER_PORT 4
#define MAX_TX_QUEUES_PER_PORT 4
#define MAX_PKT_BURST 32
#define ACCEPT_BRDCAST	1		//If the ports should accept the broadcast packets or not

uint8_t num_ports = 0;

enum {
	REPLY_ARP		= 0x00000001,
	REPLY_ICMPv4	= 0x00000002	//--!TODO add support for icmpv4 and v6
} __attribute__((__packed__));

struct mbuf_table {
	unsigned len;
	struct rte_mbuf *m_table[MAX_PKT_BURST];
} __attribute__((__packed__));

struct port_info {
	union {
		uint32_t	ip_addr;
		uint8_t		ip[4];
	};
	uint8_t	flags;
	struct ether_addr * eth_mac;		//--!TODO initialize eth_mac in init func
	uint16_t vlan_tag;
	uint8_t socket_id;
	uint8_t num_rx_queues;			//--!TODO init the values of rx and tx queues
	uint8_t num_tx_queues;
	struct mbuf_table tx_pkt_array[MAX_TX_QUEUES_PER_PORT];
	//struct port_stats;	//--! add stats info
} __attribute__((__packed__));

struct port_info port_info[MAX_ETH_PORTS];

/*int eth_port_init() {
	num_ports = rte_eth_dev_count();
	return 0;
}*/

#endif