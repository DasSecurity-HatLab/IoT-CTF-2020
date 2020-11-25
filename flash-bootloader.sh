#!/bin/bash
set -e
./fel-uboot.sh
echo -n "Waiting for DFU Device";
while [ -z "`dfu-util -l | grep 'Found DFU'`" ]
do
    echo -n ".";
done
echo "Gotcha!";
dfu-util -a u-boot -D IMAGE/u-boot-sunxi-with-nand-spl.bin

