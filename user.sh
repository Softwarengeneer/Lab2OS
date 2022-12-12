#! /bin/bash
echo $1 > /sys/kernel/debug/lab2_OS_2/info
dmesg | tail -n 20 | cut -c16-