#include "layer2_inter.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nachum Barcohen <nachum.barcohen@gmail.com>");

static proto_db_element* head = NULL;

static int __init md_init(void) {
    printk("+ module layer2 started!\n");
    head = proto_db_create();
    if(!head) {
        printk("+ failed to create L3 protocls database!\n");
        return -1;
    }
    return 0;
}

static void __exit md_exit(void) {
    printk("+ module layer2 unloaded!\n");
    proto_db_purge(head);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
| Preamble | Start of frame delimiter | MAC destination |  MAC source |802.1Q tag (optional) | Ethertype (Ethernet II) or length (IEEE 802.3) |	Payload        | Frame check sequence (32‑bit CRC) | Interpacket gap
| 7 octets |1 octet                   | 6 octets        | 6 octets    | (4 octets)           | 2 octets                                       |	46‑1500 octets | 4 octets                          | 12 octets
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

extern void proc_l2(struct sk_buff* skb) {
    struct eth_hdr* hdr;
    u_short proto_hex;
    proto_db_element* l3_proto;

    //TODO: Check why "+skb->mac_header" sometimes is 64 and sometimes 2.
    //printk("+ mac_header: %d, network_header: %d\n", skb->mac_header, skb->network_header);
    //Offset layer 1 header (preamble).
    hdr = (struct eth_hdr*)(skb->head+skb->mac_header);
    printk("+ MAC: %02x:%02x:%02x:%02x:%02x:%02x", hdr->h_dest[0], hdr->h_dest[1], hdr->h_dest[2],
                                                    hdr->h_dest[3], hdr->h_dest[4], hdr->h_dest[5]);
    printk(" > %02x:%02x:%02x:%02x:%02x:%02x.", hdr->h_source[0], hdr->h_source[1], hdr->h_source[2],
                                                hdr->h_source[3], hdr->h_source[4], hdr->h_source[5]);

    if(hdr->h_proto == 0x8100) {
        struct eth_vtag_hdr* vtag_hdr = (struct eth_vtag_hdr*)hdr;
        printk(" VLAN! TPID: %u, PCP: %03x, DEI: %1x, VID: %012x.", vtag_hdr->vlan_tipd, vtag_hdr->vtci.vlan_pcp, vtag_hdr->vtci.vlan_dei, vtag_hdr->vtci.vlan_vid);
        proto_hex = ntohs(vtag_hdr->h_proto);
    } else {
        proto_hex = ntohs(hdr->h_proto);
    }
 
    l3_proto = proto_db_find(head, 1, &proto_hex);
    
    if(!l3_proto) {
        printk(" Unknown L3 protocol! Hex: %04x.\n", proto_hex);
    } else {
//        printk("P: %s\n", l3_proto->proto_name);
//        skb->head = skb->data++;
        (*l3_proto->proc_hdr_func)(skb);
    }
}
EXPORT_SYMBOL(proc_l2);

extern bool l2_add_l3_proto(char* name, u_short hex, proc_func_ptr func) {
    if (!proto_db_add(head, name, hex, func)) {
        return false;
    }
    printk("+ L3 protocol %s added to L3 database with hex code %04x\n", name, hex);
    return true;
}
EXPORT_SYMBOL(l2_add_l3_proto);

extern bool l2_del_l3_proto(int type, void* param) {
    if (!proto_db_del(head, type, param)) {
        return false;
    }
    if(type == 0) {
        printk("+ L3 protocol %s deleted from L3 database\n", (char*)param);
    } else {
        printk("+ L3 protocol %04x deleted from L3 database\n", *((u_short*)param));
    }
    return true;
}
EXPORT_SYMBOL(l2_del_l3_proto);

module_init(md_init);
module_exit(md_exit);