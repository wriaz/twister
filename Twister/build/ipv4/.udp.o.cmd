cmd_ipv4/udp.o = gcc -Wp,-MD,ipv4/.udp.o.d.tmp -m64 -pthread  -march=native -DRTE_MACHINE_CPUFLAG_SSE -DRTE_MACHINE_CPUFLAG_SSE2 -DRTE_MACHINE_CPUFLAG_SSE3 -DRTE_MACHINE_CPUFLAG_SSSE3 -DRTE_COMPILE_TIME_CPUFLAGS=RTE_CPUFLAG_SSE,RTE_CPUFLAG_SSE2,RTE_CPUFLAG_SSE3,RTE_CPUFLAG_SSSE3  -I/home/mininet/xflow/HVC2/Twister/build/include -I/home/mininet/xflow/HVC2/Twister/../dpdk/x86_64-native-linuxapp-gcc/include -include /home/mininet/xflow/HVC2/Twister/../dpdk/x86_64-native-linuxapp-gcc/include/rte_config.h -O3 -W -Wall -Werror -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wpointer-arith -Wcast-align -Wnested-externs -Wcast-qual -Wformat-nonliteral -Wformat-security -Wundef -Wwrite-strings -I/home/mininet/xflow/HVC2/Twister/include -I/home/mininet/xflow/HVC2/Twister/../dpdk/x86_64-native-linuxapp-gcc/include   -o ipv4/udp.o -c /home/mininet/xflow/HVC2/Twister/ipv4/udp.c 