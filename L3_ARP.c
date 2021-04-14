#include "L3_ARP_inter.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nachum Barcohen <nachum.barcohen@gmail.com>");

static u_short hex = 0x0806;
static char name[4] = "ARP";

static int __init md_init(void) {
    bool b;
    printk("+ module L3_ARP started!\n");
    b = l2_add_l3_proto(name, hex, (void*)proc_l3);
    if(!b) {
        return -1;
    }
    return 0;
}
static void __exit md_exit(void) {
    bool b = l2_del_l3_proto(1, &hex);
    if(!b) {
        printk("+ WARNING: L3_ARP not removed from L3 protocols database in L2 module\n");
    }
    printk("+ module L3_ARP unloaded!\n");
}

void proc_l3(struct sk_buff* skb) {
    struct arp_hdr* hdr;
    //Offset MAC header
    hdr = (struct arp_hdr*)(skb->head+skb->network_header);
    printk("\n-- ARP - Hardware type: %u\n-- Protocol type: %u\n", hdr->htype, hdr->ptype);
    printk("--Hardware Address Length: %u\n--Protocol Address Length: %u\n-- Operation: %u\n", hdr->hlen,
                                                                                hdr->plen, hdr->oper);
    printk("-- MAC: %02x:%02x:%02x:%02x:%02x:%02x", hdr->sha.char_address[0], hdr->sha.char_address[1],
                                        hdr->sha.char_address[2], hdr->sha.char_address[3],
                                        hdr->sha.char_address[4], hdr->sha.char_address[5]);
    printk(" > %02x:%02x:%02x:%02x:%02x:%02x\n", hdr->tha.char_address[0], hdr->tha.char_address[1],
                                        hdr->tha.char_address[2], hdr->tha.char_address[3],
                                        hdr->tha.char_address[4], hdr->tha.char_address[5]);
    printk("-- IP: %u.%u.%u.%u", hdr->spa.char_address[0], hdr->spa.char_address[1],
                                    hdr->spa.char_address[2], hdr->spa.char_address[3]);
    printk(" > %u.%u.%u.%u\n", hdr->tpa.char_address[0], hdr->tpa.char_address[1],
                                    hdr->tpa.char_address[2], hdr->tpa.char_address[3]);
}

module_init(md_init);
module_exit(md_exit);
