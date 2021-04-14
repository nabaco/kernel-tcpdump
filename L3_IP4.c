#include "L3_IP4_inter.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nachum Barcohen <nachum.barcohen@gmail.com>");

static u_short hex = 0x0800;
static char name[4] = "IP4";

static int __init md_init(void) {
    bool b;
    printk("+ module L3_IP4 started!\n");
    b = l2_add_l3_proto(name, hex, (void*)proc_l3);
    if(!b) {
        return -1;
    }
    return 0;
}
static void __exit md_exit(void) {
    bool b = l2_del_l3_proto(1, &hex);
    if(!b) {
        printk("+ WARNING: L3_IP4 not removed from L3 protocols database in L2 module\n");
    }
    printk("+ module L3_IP4 unloaded!\n");
}

void proc_l3(struct sk_buff* skb) {
    /* Implementation taken from the internet - for reference
    struct iphdr* test_hdr;
    char* sip;
    char* dip;
    test_hdr = ip_hdr(skb);s
    sip = (char*)&test_hdr->saddr;
    dip = (char*)&test_hdr->daddr;
    //From > to. protocol. message. length.
    printk(" -- IP4 (reference): %u.%u.%u.%u > %u.%u.%u.%u. ", sip[0]&0xff, sip[1]&0xff, sip[2]&0xff, sip[3]&0xff, dip[0]&0xff, dip[1]&0xff, dip[2]&0xff, dip[3]&0xff);
    printk("Protocol: %u, %d bytes.\n", test_hdr->protocol, ntohs(test_hdr->tot_len));
    */

    struct ip4_hdr* hdr;
    //Offset MAC header
    hdr = (struct ip4_hdr*)(skb->head+skb->network_header);
    printk("\n-- IP4: %u.%u.%u.%u", hdr->h_source.char_address[0],
                                    hdr->h_source.char_address[1],
                                    hdr->h_source.char_address[2],
                                    hdr->h_source.char_address[3]);
    printk(" > %u.%u.%u.%u.\n", hdr->h_dest.char_address[0],
                                hdr->h_dest.char_address[1],
                                hdr->h_dest.char_address[2],
                                hdr->h_dest.char_address[3]);
    printk("-- Version: %u\n-- IHL: %u \n-- DSCP: %u\n-- ECN: %u\n-- Total Length: %u\n-- ID: %u\n", hdr->version,
                                                                                                        hdr->ihl,
                                                                                                        hdr->dscp,
                                                                                                        hdr->ecn,
                                                                                                        hdr->total_length,
                                                                                                        hdr->id);
    printk("-- Flags: %u\n-- Fragment Offset: %u\n-- Time to Live: %u\n-- Protocol: %u\n-- Checksum: %u\n", hdr->flags,
                                                                                                        hdr->frag_offset,
                                                                                                        hdr->TTL,
                                                                                                        hdr->h_proto,
                                                                                                        hdr->h_chksum);
    if(hdr->ihl > 5) {
        printk(" -- Options - Copy: %u\n-- Class: %u\n-- Number %u\n-- Length: %u.\n", hdr->opt_copy,
                                                                                        hdr->opt_class,
                                                                                        hdr->opt_num,
                                                                                        hdr->opt_len);
    }
}

module_init(md_init);
module_exit(md_exit);