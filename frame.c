#include "frame.h"

#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

int frame_header_serialize(const frame_header_t *hdr,
                           uint8_t out[FRAME_HEADER_SIZE])
{

    if(hdr == NULL || out == NULL)
        return -1;
    
    if(hdr->length > FRAME_MAX_PAYLOAD)
        return -1;

    uint16_t net_len = htons(hdr->length);
    uint16_t net_vlan = htons(hdr->vlan);

    memcpy(out, &net_len, 2);
    memcpy(out+2, hdr->src, MAC_LEN);
    memcpy(out+8, hdr->dst, MAC_LEN);
    memcpy(out+14, &net_vlan, 2);
    out[16] = hdr->pri;
    out[17] = '\0'; // Null-terminate the output for safety
  
    return 0;
}

int frame_header_deserialize(const uint8_t in[FRAME_HEADER_SIZE],
                             frame_header_t *hdr)
{

    if(in == NULL || hdr == NULL)
        return -1;

    uint16_t net_len, net_vlan;
    memcpy(&net_len, in+0, 2);
    memcpy(&net_vlan, in+14, 2);
    hdr->length = ntohs(net_len);
    hdr->vlan = ntohs(net_vlan);
    memcpy(hdr->src, in+2, MAC_LEN);
    memcpy(hdr->dst, in+8, MAC_LEN);
    hdr->pri = in[16];

    if (hdr->length > FRAME_MAX_PAYLOAD) return -1;
    return 0;

}

void mac_to_str(const uint8_t mac[MAC_LEN], char out[18])
{
    snprintf(out, 18, "%02x:%02x:%02x:%02x:%02x:%02x",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

int mac_from_str(const char *s, uint8_t out[MAC_LEN])
{
    if (!s || !out) return -1;

    unsigned int b[MAC_LEN];

    if (sscanf(s, "%x:%x:%x:%x:%x:%x",
               &b[0], &b[1], &b[2], &b[3], &b[4], &b[5]) != MAC_LEN)
        return -1;

    for (int i = 0; i < MAC_LEN; i++) {
        if (b[i] > 0xFFu) 
        return -1;
        out[i] = (uint8_t)b[i];
    }
    return 0;
}

