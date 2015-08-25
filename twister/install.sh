#!/bin/sh
cd ../dpdk/
#make install T=x86_64-native-linuxapp-gcc
cd ../twister/
make clean
make
sudo mkdir -p /usr/lib/twister
sudo cp ../dpdk/x86_64-native-linuxapp-gcc/lib/* /usr/lib/twister/.
sudo cp build/libtwister.a /usr/lib/twister/.

echo 'install all twister headers'
sudo cp  include/*.h /usr/include/.
sudo cp ../dpdk/x86_64-native-linuxapp-gcc/include/*.h /usr/include/.
sudo mkdir -p /usr/include/generic/.
sudo mkdir -p /usr/include/exec-env/.
sudo cp ../dpdk/x86_64-native-linuxapp-gcc/include/generic/*.h /usr/include/generic/.
sudo cp ../dpdk/x86_64-native-linuxapp-gcc/include/exec-env/*.h /usr/include/exec-env/.

echo "transfering twister.mk"
sudo cp twister.mk /usr/include
 
echo "DONE........."
