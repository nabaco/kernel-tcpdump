# Kernel tcpdump

## About

This is a small project I have done when I just begun developing to learn C, linux kernel, and networking all at once.
The is to catch all network traffic and print some basic networking info about the packets, breaking the different protocols into separate modules.
This was done for educational puposes only, don't expect a lot :)

## Run

**Dependencies: ** linux-headers-generic

To compile run (in Linux): `make`

To re/load the modules into the kernel run: `sudo ./start.sh`

To stop the modules from running: `sudo ./stop.sh`

To see modules output, run: `tail -n20 -f /var/log/kern.log`

**Note: ** If running in WSL2, run the following command:

```sudo -rf /usr/lib/modules/(uname -r) && sudo ln -s /usr/lib/modules/*-generic /usr/lib/modules/$(uname -r)```
