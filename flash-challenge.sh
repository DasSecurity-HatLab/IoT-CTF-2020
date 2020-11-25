#!/bin/bash
# Usage ./flash-challenge.sh CHALLENGE/adv_sign.squashfs
SELFDIR=`dirname \`realpath ${0}\``
cd ${SELFDIR}
echo -n "Waiting for DFU Device";
while [ -z "`dfu-util -l | grep 'Found DFU'`" ]
do
    echo -n ".";
done
echo "Gotcha!";
dfu-util -R -a vendor -D ${1}

