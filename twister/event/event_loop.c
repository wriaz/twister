#include <unistd.h>
#include <rte_lcore.h>
#include <event_loop.h>
#include <eth.h>
#include <rx.h>
#include <tx.h>
#include <queued_pkts.h>

int tw_loop_init(tw_loop_t * event_loop) { //TODO secs_to_run for  event loop
	event_loop->data = NULL;
	int core_id = rte_lcore_id();
	if(global_pps_limit[core_id])
		global_pps_delay[core_id] = 10000000000/global_pps_limit[core_id];
	else
		global_pps_delay[core_id] = 0;
	return 0;
}

int tw_stop(tw_loop_t * event_loop) {
	event_loop->stop_flag = 0;
	return 0;
}

tw_loop_t * tw_default_loop(uint16_t time_to_run) {
	tw_loop_t * loop = rte_malloc("tw_loop_t *", sizeof(tw_loop_t), RTE_CACHE_LINE_SIZE);
	loop->secs_to_run = time_to_run;
	return loop;
}

//int tw_udp_init(tw_loop_t * loop, tw_udp_t * udp_handle) {
tw_udp_t * tw_udp_init(tw_loop_t * loop) {
	tw_udp_t * temp_udp_handle = loop->rx_handle_queue;
	//udp_handle = loop->rx_handle_queue;
	
	if(temp_udp_handle == NULL) {
			temp_udp_handle = rte_malloc("tw_udp_t *", sizeof(tw_udp_t), RTE_CACHE_LINE_SIZE);
			loop->rx_handle_queue = temp_udp_handle;
	}
	else {
			while(temp_udp_handle->next != NULL)
					temp_udp_handle = temp_udp_handle->next;
			temp_udp_handle->next = rte_malloc("tw_udp_t *", sizeof(tw_udp_t), RTE_CACHE_LINE_SIZE);
			temp_udp_handle = temp_udp_handle->next;
	}
	
	//TODO populate tw_loop_t entries if needed
	//udp_handle = temp_udp_handle;
	temp_udp_handle->handle_type = TW_UDP_HANDLE;
	loop->active_handles++;
	//udp_handle = temp_udp_handle;
	//udp_handle->flags = 0;
	//return 0;
	return temp_udp_handle;
}

tw_timer_t * tw_timer_init(tw_loop_t * loop) {
		
	tw_timer_t * temp_handle = loop->timer_handle_queue;
	if(temp_handle == NULL) {
			temp_handle = rte_malloc("tw_timer_t *", sizeof(tw_timer_t), RTE_CACHE_LINE_SIZE);
			loop->timer_handle_queue = temp_handle;
	}
	else {
			while(temp_handle->next != NULL)
					temp_handle = temp_handle->next;
			temp_handle->next = rte_malloc("tw_timer_t *", sizeof(tw_timer_t), RTE_CACHE_LINE_SIZE);
			temp_handle = temp_handle->next;
	}
	
	//TODO populate tw_loop_t entries if needed
	//timer_handle = (tw_timer_t *) temp_handle;
	temp_handle->handle_type = TW_TIMER_HANDLE;
	loop->active_handles++;
	return temp_handle;
}

tw_tx_t * tw_udp_tx_init(tw_loop_t * loop) {
	tw_tx_t * temp_handle = loop->tx_handle_queue;
	if(temp_handle == NULL) {
			temp_handle = rte_malloc("tw_tx_t *", sizeof(tw_tx_t), RTE_CACHE_LINE_SIZE);
			loop->tx_handle_queue = temp_handle;
	}
	else {
			while(temp_handle->next != NULL)
					temp_handle = temp_handle->next;
			temp_handle->next = rte_malloc("tw_tx_t *", sizeof(tw_tx_t), RTE_CACHE_LINE_SIZE);
			temp_handle = temp_handle->next;
	}
	
	//tx_handle = (tw_tx_t *) temp_handle;
	temp_handle->handle_type = TW_UDP_TX_HANDLE;
	loop->active_handles++;
	return temp_handle;
}

int tw_timer_start(tw_timer_t* timer_handle, tw_timer_cb timer_cb, uint64_t timeout, uint64_t repeat) {
	if(timer_handle == NULL)
		return -1;
	timer_handle->timer_cb = timer_cb;
	timer_handle->timeout = timeout;
	timer_handle->repeat = repeat;
	return 0;
}

int tw_udp_bind(tw_udp_t * udp_handle, struct tw_sockaddr_in * addr, uint8_t flags) {
	//if(udp_handle == NULL)
	udp_handle->addr = NULL;
	udp_handle->sock_fd = udp_socket(addr->sock_ip, addr->sock_port);
	udp_sockets[udp_handle->sock_fd].type = TW_SOCK_DGRAM;
	udp_sockets[udp_handle->sock_fd].proto = TW_IPPROTO_UDP;

	udp_handle->flags = flags;
	return 0;
}

int tw_udp_tx_bind(tw_tx_t * tx_handle, struct tw_sockaddr_in * addr, int sock_fd, uint8_t flags) {
	tx_handle->flags = flags;
	tx_handle->sock_fd = sock_fd;
	tx_handle->dst_addr = addr;
	return 0;
}

int tw_timer_bind(tw_timer_t * timer_handle, struct tw_sockaddr_in * addr, int sock_fd, uint8_t flags) {
	timer_handle->flags = flags;
	timer_handle->sock_fd = sock_fd;
	timer_handle->dst_addr = addr;
	return 0;

}

struct tw_sockaddr_in * tw_ip4_addr(char * ip_str, uint16_t l4_port) {
	struct tw_sockaddr_in * addr = rte_malloc("struct tw_sockaddr_in *", sizeof(struct tw_sockaddr_in), RTE_CACHE_LINE_SIZE);
	uint32_t ip_addr = 0;
	if(ip_str != NULL)
		ip_addr = convert_ip_str_to_dec(ip_str);
	addr->sock_ip = ip_addr;
	addr->sock_port = l4_port;
	return addr;
}

int tw_udp_recv_start(tw_udp_t * udp_handle, void * alloc_cb, void * recv_cb) {
	if(udp_handle == NULL)
		return -1;
	char * temp_ip = NULL;
	udp_handle->addr = tw_ip4_addr(temp_ip, 0);
	udp_handle->alloc_cb = alloc_cb;
	udp_handle->recv_cb = recv_cb;
	return 0;
}

int tw_udp_tx_start(tw_tx_t * tx_handle, void * tx_cb) {
	if(tx_handle == NULL)
		return -1;

	tx_handle->tx_cb = tx_cb;
	return 0;
}

int tw_run(tw_loop_t * event_loop) {
	
	uint8_t infinite_loop = 0, continue_loop = 1;
	if (event_loop->secs_to_run == INFINITE_LOOP)
		infinite_loop = 1;
	int num_rx_pkts = 0, pkt_count = 0, i;
	uint64_t curr_time_cycle = 0, prev_queued_pkts_cycle = 0, prev_stats_calc = 0, time_diff = 0;
	uint64_t loop_start_time = tw_get_current_timer_cycles();
	struct lcore_conf *qconf = &lcore_conf[rte_lcore_id()];
	struct mbuf_table m[qconf->num_queues];
	struct rte_mbuf * pkt;
	tw_buf_t temp_buffer;
	int payload_size;
	
	//tw_handle_t * temp_handle_queue;
	tw_udp_t * temp_udp_handle;
	tw_tx_t * temp_tx_handle;
	tw_timer_t * temp_timer_handle;
	
	void (*tw_udp_recv_cb) (tw_udp_t *, uint16_t, tw_buf_t *, struct tw_sockaddr_in *, uint8_t);
	void (*tw_tx_cb) (tw_tx_t *);
	void (*tw_timer_cb) (tw_timer_t *);

	do {
		if(event_loop->stop_flag)
			return 0;
		curr_time_cycle = tw_get_current_timer_cycles();
		time_diff = get_time_diff(curr_time_cycle, prev_queued_pkts_cycle, one_msec);
		if(unlikely(time_diff > queue_update_limit)) {
			update_queued_pkts(curr_time_cycle);
			prev_queued_pkts_cycle = curr_time_cycle;
		}
		
		time_diff = get_time_diff(curr_time_cycle, prev_stats_calc, one_msec);
		if(unlikely(time_diff > stats_calc_limit)) {
			calc_global_stats();
			print_global_stats();
			prev_stats_calc = curr_time_cycle;
		}

		twister_timely_burst();
		
		temp_udp_handle = event_loop->rx_handle_queue;
		if(temp_udp_handle != NULL)
			num_rx_pkts = rx_for_each_queue(m);

		if(num_rx_pkts > 0) {
			//printf("pkts rx %d\n", num_rx_pkts);
			for(i=0;i<qconf->num_queues;i++) {
				for(pkt_count = 0;pkt_count < m[i].len;pkt_count++) {
					pkt = m[i].m_table[pkt_count];
					eth_pkt_parser(pkt, m[i].portid, LOOP_PROCESS, NULL);
				}
			}
		}
		
		if(event_loop->active_handles > 0) {
			while(temp_udp_handle != NULL) {
				switch(temp_udp_handle->handle_type) {
					case(TW_UDP_HANDLE):
						//temp_udp_handle = (tw_udp_t *) temp_handle_queue;
						while(udp_sock_queue[temp_udp_handle->sock_fd].n_pkts > 0) {
							tw_udp_recv_cb = temp_udp_handle->recv_cb;
							payload_size = udp_queue_pop(temp_udp_handle->sock_fd, temp_udp_handle->addr, &temp_buffer);
							tw_udp_recv_cb(temp_udp_handle, payload_size, &temp_buffer, temp_udp_handle->addr, 0);
						}
						break;
					default:
						break;
				}
				temp_udp_handle = temp_udp_handle->next;
			}

			temp_tx_handle = event_loop->tx_handle_queue;
			while(temp_tx_handle != NULL) {
				//temp_tx_handle = (tw_tx_t *) temp_handle_queue;
				tw_tx_cb = temp_tx_handle->tx_cb;
				tw_tx_cb(temp_tx_handle);
				temp_tx_handle = temp_tx_handle->next;
			}

			temp_timer_handle = event_loop->timer_handle_queue;
			while(temp_timer_handle != NULL) {
				//temp_timer_handle = (tw_timer_t *) temp_handle_queue;
				time_diff = get_time_diff(curr_time_cycle, temp_timer_handle->last_run_time, one_msec);
				if(unlikely(time_diff > temp_timer_handle->timeout)) {
					tw_timer_cb = temp_timer_handle->timer_cb;
					tw_timer_cb(temp_timer_handle);  //TODO add time logic
					temp_timer_handle->last_run_time = curr_time_cycle;
				}
				temp_timer_handle = temp_timer_handle->next;
			}
		}

		if(!infinite_loop) {
			if(get_time_diff(curr_time_cycle, loop_start_time, one_sec) >= event_loop->secs_to_run)
				continue_loop = 0;
		}
	} while(continue_loop);

	return 0;
}
