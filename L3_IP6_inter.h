#include "layer3_inter.h"

#pragma pack(1)

union ip_addr {   
    struct
    {
        uint64_t int1_address;
        uint64_t int2_address;
    } int_address;  
    uint16_t char_address[8];
};

struct ip6_hdr {
    uint32_t version:4,
                traffic_class_ds:6,
                traffic_class_ecn:2,
                flow_label:20;
    uint16_t payload_length;
    uint8_t next_header;
    uint8_t hop_limit;
    union ip_addr h_source;
    union ip_addr h_dest;
};

#pragma pack()