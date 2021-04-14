#include "layer3_inter.h"

//TODO: Add #DEFINE to all IP4 protocols

#pragma pack(1)

union ip_addr {
    uint32_t int_address;
    uint8_t char_address[4];
};

struct ip4_hdr {
    uint8_t version:4,
            ihl:4;
    uint8_t dscp:6,
            ecn:2;
    uint16_t total_length;
    uint16_t id; 
    uint16_t flags:3,
            frag_offset:13;
    uint8_t TTL;
    uint8_t h_proto;
    uint16_t h_chksum;
    union ip_addr h_source; //4 bytes
    union ip_addr h_dest; //4 bytes
    uint8_t opt_copy:1,
            opt_class:2,
            opt_num:5;
    uint8_t opt_len;
};

#pragma pack()