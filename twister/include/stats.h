/** @file Gathers stats and displays them
 *
 */

#ifndef _STATS_H_
#define _STATS_H_

#include <rte_memcpy.h>
#include <rte_byteorder.h>
#include <rte_mbuf.h>
#include <rte_udp.h>
#include <rte_malloc.h>
#include <portconf.h>
#include <lcoreconf.h>
#include <eth.h>
#include <rte_ethdev.h>
#include <rte_ether.h>
#include <portconf.h>
#include <rte_cycles.h>
#include <timerfuncs.h>
#include <common.h>

#define stats_port 0 		//Use port stats_port to send stats packets
#define stats_update_limit 1000	// send stats pkt after stats_update_limit msec
#define stats_calc_limit 1	//calc stats parameters every 1000 millisecs

struct rte_timer stats_timer;

uint64_t stats_time_period;
int stats_fd;
uint32_t stats_server_ip;
uint16_t l4_stats_port;

uint64_t global_pps_limit;
uint64_t global_pps_delay;

/** To calculate RTT
 *
 */
struct average_filter
{
        float timestamp;
        struct average_filter* next;
}__attribute__ ((__packed__));

/** Contains all stats
 *
 */
struct stats_option
{
        uint64_t secs_passed;
        uint64_t payload_size;
        uint64_t timestamp;
        uint64_t rx_pps;
        uint64_t tx_pps;
        uint64_t pkts_rx;
        uint64_t pkts_tx;
        uint64_t pkts_dropped;
        uint64_t rtt;
}__attribute__ ((__packed__));
struct average_filter *root_rtt_average;
struct average_filter *end_rtt_average;
const uint8_t average_filter_len;

uint8_t average_list_size;
struct stats_option tw_stats;
extern uint64_t prev_pkts_rx, prev_pkts_tx;

/** Clears screen
 *
 */
void tw_clear_scr(void);

/** Prints all the global stats, essentially prints the stats struct
 *
 */
void tw_print_global_stats(void);

/** Calculates RTT
 *
 * @param time_clk :Current time
 */
void tw_calc_average_rtt(uint64_t time_clk);

/** Populates the stats structure
 *
 * @return 0(TRUE)
 */
int tw_calc_global_stats(void);

/** Only calculates stats for a specific port.
 *
 * @param portname :Name of port in string form
 *
 * @return
 */
int tw_get_port_stats (char * portname);
float average_rtt;
uint64_t data_pkt_recvd;
uint64_t data_pkt_sent;
uint32_t seconds_passed;

uint32_t test_runtime;

#endif
