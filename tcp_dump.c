#include <linux/init.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include "layer2.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nachum Barcohen <nachum.barcohen@gmail.com>");

//Initialisation routine
static struct packet_type hook;

//Functions definition
void handler_add(void);
void handler_remove(void);
void print_mac_hdr(struct ethhdr *eth);
static int hook_func(struct sk_buff *skb);

static int __init md_init(void) {
    printk("+ module tcp_dump started!\n");
    handler_add();   
    return 0;
}
static void __exit md_exit(void) {
    printk("+ module tcp_dump unloaded!\n");
    handler_remove();
}

void handler_add(void) {
    hook.type = htons(ETH_P_ALL);
    hook.func = (void *)hook_func;
    hook.dev = NULL;
    dev_add_pack(&hook);
    printk("+ Handler protocol added\n");
}

void handler_remove(void) {
    dev_remove_pack(&hook);
    printk("+ Handler protocol removed\n");
    synchronize_net();
}

static int hook_func(struct sk_buff *skb) {
    proc_l2(skb);
    return 0;
    
}

module_init(md_init);
module_exit(md_exit);
