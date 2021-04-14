#include <linux/init.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/ip.h>
#include "link_list.h"
#include "layer2.h"

void proc_l3(struct sk_buff* skb);
