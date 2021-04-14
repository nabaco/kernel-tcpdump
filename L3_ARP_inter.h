#include "layer3_inter.h"

#pragma pack(1)

union mac_addr {
    struct {
        uint32_t int1_address;
        uint16_t int2_address;
    } int_address;
    uint8_t char_address[6];
};

union ip_addr {
    uint32_t int_address;
    uint8_t char_address[4];
};

struct arp_hdr {
    uint16_t htype;
    uint16_t ptype;
    uint8_t hlen;
    uint8_t plen;
    uint16_t oper;
    union mac_addr sha;
    union ip_addr spa;
    union mac_addr tha;
    union ip_addr tpa;
};

#pragma pack()