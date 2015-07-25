#ifndef _PKTPARSER_H_
#define _PKTPARSER_H_
/**
 * @file
 *
 * Packet Parser Helpers in Twister
 */
#include <eth.h>

int parse_pkt(struct rte_mbuf *, uint8_t); /**< parse_pkt - This function parse the packet after receiving the packet from the Rx queue. */
 
#endif