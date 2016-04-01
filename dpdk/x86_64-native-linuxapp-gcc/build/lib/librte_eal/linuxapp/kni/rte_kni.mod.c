#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x9412fa01, __VMLINUX_SYMBOL_STR(module_layout) },
	{        0, __VMLINUX_SYMBOL_STR(alloc_pages_current) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x58df1fc2, __VMLINUX_SYMBOL_STR(device_remove_file) },
	{ 0xd50b5609, __VMLINUX_SYMBOL_STR(netdev_info) },
	{ 0x6d0fc37d, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xc1d295b1, __VMLINUX_SYMBOL_STR(pci_bus_read_config_byte) },
	{ 0xd2b09ce5, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x31ad0fe1, __VMLINUX_SYMBOL_STR(__pm_runtime_idle) },
	{ 0xf5893abf, __VMLINUX_SYMBOL_STR(up_read) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0xb9318f63, __VMLINUX_SYMBOL_STR(skb_pad) },
	{ 0xbd100793, __VMLINUX_SYMBOL_STR(cpu_online_mask) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0x5dcfc657, __VMLINUX_SYMBOL_STR(dev_mc_add_excl) },
	{ 0x92e4bd19, __VMLINUX_SYMBOL_STR(napi_complete) },
	{ 0x4272d0d4, __VMLINUX_SYMBOL_STR(pci_disable_device) },
	{ 0xf64536d1, __VMLINUX_SYMBOL_STR(dev_uc_add_excl) },
	{ 0x23787eb, __VMLINUX_SYMBOL_STR(pci_disable_msix) },
	{ 0x41721113, __VMLINUX_SYMBOL_STR(hwmon_device_unregister) },
	{ 0x4ea25709, __VMLINUX_SYMBOL_STR(dql_reset) },
	{ 0xb54533f7, __VMLINUX_SYMBOL_STR(usecs_to_jiffies) },
	{ 0x12cccec8, __VMLINUX_SYMBOL_STR(netif_carrier_on) },
	{ 0x1ab49e22, __VMLINUX_SYMBOL_STR(pci_disable_sriov) },
	{ 0xc0a3d105, __VMLINUX_SYMBOL_STR(find_next_bit) },
	{ 0xb7b8eefb, __VMLINUX_SYMBOL_STR(netif_carrier_off) },
	{ 0x273cc021, __VMLINUX_SYMBOL_STR(x86_dma_fallback_dev) },
	{ 0xeae3dfd6, __VMLINUX_SYMBOL_STR(__const_udelay) },
	{ 0x1eecf3fc, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x417e6f5b, __VMLINUX_SYMBOL_STR(__pm_runtime_resume) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x6b2f8ded, __VMLINUX_SYMBOL_STR(pci_bus_write_config_word) },
	{ 0x4629334c, __VMLINUX_SYMBOL_STR(__preempt_count) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x31dbaebf, __VMLINUX_SYMBOL_STR(__put_net) },
	{ 0x5be8aa36, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x91745d5d, __VMLINUX_SYMBOL_STR(netif_napi_del) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x57a6ccd0, __VMLINUX_SYMBOL_STR(down_read) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x2ef20384, __VMLINUX_SYMBOL_STR(kthread_bind) },
	{ 0xe1cd38ee, __VMLINUX_SYMBOL_STR(__netdev_alloc_skb) },
	{ 0x27c33efe, __VMLINUX_SYMBOL_STR(csum_ipv6_magic) },
	{ 0x1a0eb5b4, __VMLINUX_SYMBOL_STR(netif_rx) },
	{ 0x946e6fba, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0xf432dd3d, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x5d41c87c, __VMLINUX_SYMBOL_STR(param_ops_charp) },
	{ 0x774f6678, __VMLINUX_SYMBOL_STR(misc_register) },
	{ 0xd5f2172f, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0xfb578fc5, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x92dbaaa0, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0x57a6ac32, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xe94c016a, __VMLINUX_SYMBOL_STR(current_task) },
	{ 0xac7f6dfd, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x2edf7983, __VMLINUX_SYMBOL_STR(ethtool_op_get_link) },
	{ 0xee54fb05, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0x449ad0a7, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xa00aca2a, __VMLINUX_SYMBOL_STR(dql_completed) },
	{ 0x4c9d28b0, __VMLINUX_SYMBOL_STR(phys_base) },
	{ 0xcd279169, __VMLINUX_SYMBOL_STR(nla_find) },
	{ 0x3f41bc3a, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x9166fada, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x157b2d79, __VMLINUX_SYMBOL_STR(register_netdev) },
	{ 0x5a921311, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0x5792f848, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x843dd2d2, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x91e14f04, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xcaea5f14, __VMLINUX_SYMBOL_STR(dev_close) },
	{ 0x51e8ea04, __VMLINUX_SYMBOL_STR(netif_set_real_num_rx_queues) },
	{ 0x8834396c, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0xb8ac11ed, __VMLINUX_SYMBOL_STR(netif_set_real_num_tx_queues) },
	{ 0xa0669fdb, __VMLINUX_SYMBOL_STR(netif_napi_add) },
	{ 0x2072ee9b, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x6632ef59, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x3b4ceb4a, __VMLINUX_SYMBOL_STR(up_write) },
	{ 0xe6e3b875, __VMLINUX_SYMBOL_STR(down_write) },
	{ 0x94be4a5c, __VMLINUX_SYMBOL_STR(__get_page_tail) },
	{ 0xfa06b394, __VMLINUX_SYMBOL_STR(dev_kfree_skb_any) },
	{ 0x9f46ced8, __VMLINUX_SYMBOL_STR(__sw_hweight64) },
	{ 0xcf961140, __VMLINUX_SYMBOL_STR(dev_open) },
	{ 0xe523ad75, __VMLINUX_SYMBOL_STR(synchronize_irq) },
	{ 0x6536f54d, __VMLINUX_SYMBOL_STR(pci_find_capability) },
	{ 0x39a1e906, __VMLINUX_SYMBOL_STR(device_create_file) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0xc190e3ee, __VMLINUX_SYMBOL_STR(napi_gro_receive) },
	{ 0x853eb0f0, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x40a9b349, __VMLINUX_SYMBOL_STR(vzalloc) },
	{ 0x59881371, __VMLINUX_SYMBOL_STR(__free_pages) },
	{ 0x618911fc, __VMLINUX_SYMBOL_STR(numa_node) },
	{ 0xb3540a75, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x42c8de35, __VMLINUX_SYMBOL_STR(ioremap_nocache) },
	{ 0x12a38747, __VMLINUX_SYMBOL_STR(usleep_range) },
	{ 0x2d35215f, __VMLINUX_SYMBOL_STR(pci_bus_read_config_word) },
	{ 0x372a4e9d, __VMLINUX_SYMBOL_STR(__napi_schedule) },
	{ 0xf0fdf6cb, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0xb9249d16, __VMLINUX_SYMBOL_STR(cpu_possible_mask) },
	{        0, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x41792f22, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xc141bd48, __VMLINUX_SYMBOL_STR(alloc_netdev_mqs) },
	{ 0x52bf4f78, __VMLINUX_SYMBOL_STR(eth_type_trans) },
	{ 0x8603ad8d, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0x892f3c69, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0xc6a841dc, __VMLINUX_SYMBOL_STR(pskb_expand_head) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
	{ 0xa1eab74c, __VMLINUX_SYMBOL_STR(netdev_err) },
	{ 0xbfddb49f, __VMLINUX_SYMBOL_STR(ether_setup) },
	{ 0xcc5005fe, __VMLINUX_SYMBOL_STR(msleep_interruptible) },
	{ 0x6e938e79, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xcf21d241, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0xa70a6dbd, __VMLINUX_SYMBOL_STR(netdev_warn) },
	{ 0x34f22f94, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0xb67bfba8, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0x9c55cec, __VMLINUX_SYMBOL_STR(schedule_timeout_interruptible) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x69acdf38, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x2ed4cb1f, __VMLINUX_SYMBOL_STR(___pskb_trim) },
	{ 0x20b2bb2d, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0x2d144e5f, __VMLINUX_SYMBOL_STR(pci_disable_msi) },
	{ 0xf5a47480, __VMLINUX_SYMBOL_STR(skb_add_rx_frag) },
	{ 0xedc03953, __VMLINUX_SYMBOL_STR(iounmap) },
	{ 0x238502b7, __VMLINUX_SYMBOL_STR(put_page) },
	{ 0xb352177e, __VMLINUX_SYMBOL_STR(find_first_bit) },
	{ 0x7193f296, __VMLINUX_SYMBOL_STR(pci_get_device) },
	{ 0xfa66f77c, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x4cbbd171, __VMLINUX_SYMBOL_STR(__bitmap_weight) },
	{ 0x324961c0, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0x20f7caff, __VMLINUX_SYMBOL_STR(unregister_netdev) },
	{ 0x61d743eb, __VMLINUX_SYMBOL_STR(ndo_dflt_bridge_getlink) },
	{ 0xcf016db5, __VMLINUX_SYMBOL_STR(pci_dev_put) },
	{ 0x2e0d2f7f, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x6bbb9cc6, __VMLINUX_SYMBOL_STR(pci_vfs_assigned) },
	{ 0x9e0c711d, __VMLINUX_SYMBOL_STR(vzalloc_node) },
	{ 0x28318305, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xffb48f6b, __VMLINUX_SYMBOL_STR(pci_enable_msi_block) },
	{ 0x68819f76, __VMLINUX_SYMBOL_STR(__netif_schedule) },
	{ 0x28e871c1, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x628a0d61, __VMLINUX_SYMBOL_STR(pci_enable_device_mem) },
	{ 0x323d36c8, __VMLINUX_SYMBOL_STR(skb_tstamp_tx) },
	{ 0xb7e42fb6, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x4f6b400b, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0x831b08e1, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0x5d66d8c9, __VMLINUX_SYMBOL_STR(hwmon_device_register) },
	{ 0x24598c4e, __VMLINUX_SYMBOL_STR(misc_deregister) },
	{ 0x2a6e6109, __VMLINUX_SYMBOL_STR(__init_rwsem) },
	{ 0x9e7d6bd0, __VMLINUX_SYMBOL_STR(__udelay) },
	{ 0x84a4ff6d, __VMLINUX_SYMBOL_STR(dma_ops) },
	{ 0x84db6f5f, __VMLINUX_SYMBOL_STR(device_set_wakeup_enable) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0xa1c18d9a, __VMLINUX_SYMBOL_STR(pci_save_state) },
	{ 0x33d6a5da, __VMLINUX_SYMBOL_STR(alloc_etherdev_mqs) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "A4124DD503E459BD18634A2");