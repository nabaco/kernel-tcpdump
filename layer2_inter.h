#include <linux/init.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include "layer2.h"
#include "link_list.h"

//TODO: Add #DEFINE to all the protocols that are not implemented.

#pragma pack(1)

struct VTCI {
    unsigned int vlan_pcp:3;
    unsigned int vlan_dei:1;
    unsigned int vlan_vid:12;
};

struct eth_hdr {
    unsigned char h_dest[6];
    unsigned char h_source[6];
    uint16_t h_proto;
};

struct eth_vtag_hdr {
    unsigned char h_dest[6];
    unsigned char h_source[6];
    uint16_t vlan_tipd;
    struct VTCI vtci;
    uint16_t h_proto;
};

#pragma pack()