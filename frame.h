#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>
#include <stddef.h>


#define FRAME_HEADER_SIZE  17
#define FRAME_MAX_PAYLOAD  1500
#define FRAME_MAX_TOTAL    (FRAME_HEADER_SIZE + FRAME_MAX_PAYLOAD)
#define MAC_LEN            6

typedef struct {
    uint16_t length;          /* host byte order */
    uint8_t  src[MAC_LEN];
    uint8_t  dst[MAC_LEN];
    uint16_t vlan;            /* host byte order */
    uint8_t  pri;
} frame_header_t;


int  frame_header_serialize  (const frame_header_t *hdr,
                              uint8_t out[FRAME_HEADER_SIZE]);
int  frame_header_deserialize(const uint8_t in[FRAME_HEADER_SIZE],
                              frame_header_t *hdr);

//it will have 18 17+ NUll too 
void mac_to_str  (const uint8_t mac[MAC_LEN], char out[18]);
int  mac_from_str(const char *s, uint8_t out[MAC_LEN]);

#endif 