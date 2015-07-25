#ifndef _RX_H_
#define _RX_H_
/**
 * @file
 *
 * RX modules Helpers in Twister
 */
#include <stdint.h>
#include <rte_config.h>
#include <rte_common.h>
#include <rte_cycles.h>
#include <rte_ethdev.h>
#include <lcoreconf.h>
#include <stats.h>

int get_pkt_from_rx_queue(struct mbuf_table * m, uint8_t port, uint8_t queue_id); /**< get_pkt_from_rx_queue - This function gets the packets from each RX queue. Arguments include: The pointer to the packets, The port and queue ID from which the function has to RX the packets. */
int rx_for_each_queue(struct mbuf_table *); /**< rx_for_each_queue - This function RX for each queue managed by the logical core. */


#endif
