CURRENT = $(shell uname -r)
KDIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)
TARGET1 = link_list
TARGET2 = layer2
TARGET3 = L3_IP4
TARGET4 = L3_IP6
TARGET5 = L3_ARP
TARGET6 = tcp_dump

obj-m := $(TARGET1).o $(TARGET2).o $(TARGET3).o $(TARGET4).o $(TARGET5).o $(TARGET6).o 
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	@rm -f *.o .*.cmd .*.flags *.mod.c *.order *.mod
	@rm -f *.*.cmd *~ *.*~ TODO.*
	@rm -fR .tmp*
	@rm -rf .tmp_versions
disclean: clean
	@rm *.ko *.symvers
