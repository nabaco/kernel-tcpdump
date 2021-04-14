#include "L3_IP6_inter.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nachum Barcohen <nachum.barcohen@gmail.com>");

static u_short hex = 0x86DD;
static char name[4] = "IP6";

static int __init md_init(void) {
    bool b;
    printk("+ module L3_IP6 started!\n");
    b = l2_add_l3_proto(name, hex, (void*)proc_l3);
    if(!b) {
        return -1;
    }
    return 0;
}
static void __exit md_exit(void) {
    bool b = l2_del_l3_proto(1, &hex);
    if(!b) {
        printk("+ WARNING: L3_IP6 not removed from L3 protocols database in L2 module\n");
    }
    printk("+ module L3_IP6 unloaded!\n");
}

void proc_l3(struct sk_buff* skb) {
    struct ip6_hdr* hdr;
    //Offset MAC header
    hdr = (struct ip6_hdr*)(skb->head+skb->network_header);
    printk("\n-- IP6: %04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x", hdr->h_source.char_address[0],
                                                                hdr->h_source.char_address[1],
                                                                hdr->h_source.char_address[2],
                                                                hdr->h_source.char_address[3],
                                                                hdr->h_source.char_address[4],
                                                                hdr->h_source.char_address[5],
                                                                hdr->h_source.char_address[6],
                                                                hdr->h_source.char_address[7]);
    printk(" > %04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x\n", hdr->h_dest.char_address[0],
                                                            hdr->h_dest.char_address[1],
                                                            hdr->h_dest.char_address[2],
                                                            hdr->h_dest.char_address[3],
                                                            hdr->h_dest.char_address[4],
                                                            hdr->h_dest.char_address[5],
                                                            hdr->h_dest.char_address[6],
                                                            hdr->h_dest.char_address[7]);
    printk("-- Version: %u\n-- Traffic Class: %u(DS), %u(ECN)\n", hdr->version,
                                                hdr->traffic_class_ds, hdr->traffic_class_ecn);
    printk("-- Flow Label: %u\n-- Next Header: %u\n-- Hop Limit: %u\n", hdr->flow_label,
                                                            hdr->next_header, hdr->hop_limit);
}

module_init(md_init);
module_exit(md_exit);
