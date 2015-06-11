#include <rte_ether.h>
#include <portconf.h>
#include <vlan.h>
#include <eth.h>
#include <rte_ether.h>
#include <arplogic.h>
#include <ip.h>
#include <queued_pkts.h>
#include <vlan.h>

//static struct ether_addr eth_port_mac[MAX_ETH_PORTS];
int eth_pkt_ctor(struct rte_mbuf* m, uint8_t port_id, uint16_t eth_type, uint32_t dst_ip ) {

    
    //uint8_t socket_id = rte_eth_dev_socket_id(port_id);
    //struct rte_mbuf * m = rte_pktmbuf_alloc ( tx_mempool[socket_id] );
    rte_pktmbuf_prepend( m, sizeof ( struct ether_hdr )  );
    struct ether_hdr* eth = rte_pktmbuf_mtod(m, struct ether_hdr *);
    eth->ether_type = eth_type;
    ether_addr_copy(port_info[port_id].eth_mac, &(eth->s_addr));
    
    if ( eth_type == ETHER_TYPE_VLAN ) {
        vlan_ctor(m, port_id, ETHER_TYPE_IPv4); //TODO make it generic
    }
        
    struct arp_table * arp_table_ptr = search_arp_table(dst_ip);
    if ( arp_table_ptr == NULL ) {
        
        construct_arp_packet(dst_ip, port_id);
        add_pkt_to_queue(m, dst_ip);

        }
    else {
        ether_addr_copy(&(arp_table_ptr->eth_mac), &(eth->d_addr));
        }
    
    add_pkt_to_tx_queue(m, port_id); 
    return 0;   

}

int eth_pkt_parser(struct rte_mbuf * pkt, uint8_t port_id) {
	struct ether_hdr * eth = rte_pktmbuf_mtod(pkt, struct ether_hdr *);
	uint8_t accept_brdcast = is_broadcast_ether_addr(&(eth->d_addr)) & ACCEPT_BRDCAST;
	if(is_same_ether_addr(&(eth->d_addr), port_info[port_id].eth_mac) || accept_brdcast) {
		switch(eth->ether_type) {
		case ETHER_TYPE_ARP:
			arp_parser(eth, port_id);
			break;
		case ETHER_TYPE_VLAN:
			vlan_parser(pkt, port_id);
			break;
		case ETHER_TYPE_IPv4:
			ip4_packet_parser(pkt, port_id);	//--!TODO implement ipv6
			break;
		default:
			rte_pktmbuf_free(pkt);
			break;
		}
	}
	else
		rte_pktmbuf_free(pkt);
	return 0;
}


