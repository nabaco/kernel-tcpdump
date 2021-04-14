#!/bin/bash

rmmod tcp_dump
rmmod L3_IP4
rmmod L3_IP6
rmmod L3_ARP
rmmod layer2
rmmod link_list

insmod /home/test/Documents/link_list.ko
insmod /home/test/Documents/layer2.ko
insmod /home/test/Documents/L3_IP4.ko
insmod /home/test/Documents/L3_IP6.ko
insmod /home/test/Documents/L3_ARP.ko
insmod /home/test/Documents/tcp_dump.ko
