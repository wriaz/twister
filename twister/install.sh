#!/bin/sh
make clean
make
sudo mkdir -p /home/twister
sudo chmod 777 -R /home/twister
cp ./build/libtwister.a /home/twister/.
cp $RTE_SDK/$RTE_TARGET/x86_64-native-linuxapp-gcc/lib/* /home/twister/
echo 'install all twister headers'
mkdir -p /home/twister/include/.
cp  ./include/*.h /home/twister/include
cp $RTE_SDK/$RTE_TARGET/x86_64-native-linuxapp-gcc/include/*.h /home/twister/
mkdir -p /home/twister/generic/.
mkdir -p /home/twister/exec-env/.
cp $RTE_SDK/$RTE_TARGET/x86_64-native-linuxapp-gcc/include/generic/*.h /home/twister/generic/
cp $RTE_SDK/$RTE_TARGET/x86_64-native-linuxapp-gcc/include/exec-env/*.h /home/twister/exec-env/
echo "transfering twister.mk"
sudo cp ./mk/twister.mk /usr/include
echo "DONE........."
