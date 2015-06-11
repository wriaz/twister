#ifndef _TX_H_
#define _TX_H_

#include <stdint.h>
#include <rte_config.h>
#include <rte_common.h>
#include <rte_cycles.h>
#include <rte_ethdev.h>
#include <lcoreconf.h>
#include <timerdefs.h>


int add_pkt_to_tx_queue(struct rte_mbuf *, uint8_t);
int twister_timely_burst(void);


#endif
