#include <string.h>

#include "../src/encoding.h"

int main() {

    uint64_t q = 3133737123486443;
    uint64_t q_half = 1566868561743221;
    size_t l = 3*8;
    uint8_t msg[3];
    uint64_t encoded[l];
    uint8_t decoded[3];

    // test encode / decode with 3 byte message

    msg[0] = 0x63;
    msg[1] = 0xA7;
    msg[2] = 0xD4;
    uint64_t encoded_cmp[] = {0, q_half, q_half, 0, 0, 0, q_half, q_half, q_half, 0, q_half, 0, 0, q_half, q_half, q_half, q_half, q_half ,0, q_half, 0, q_half, 0, 0};

    if(encode(msg, encoded, l, q) != 0)
        goto error;

    if(memcmp(encoded, encoded_cmp, l * sizeof(uint64_t)) != 0)
        goto error;

    if(decode(encoded, decoded, l, q) != 0)
        goto error;

    if(memcmp(decoded, msg, 3) != 0)
        goto error;

    // now test with an odd number of bits

    memset(encoded, 0, l * sizeof(uint64_t));
    memset(decoded, 0, 3);

    if(encode(msg, encoded, 15, q) != 0)
        goto error;

    if(memcmp(encoded, encoded_cmp, 15 * sizeof(uint64_t)) != 0 || encoded[16] != 0)
        goto error;

    if(decode(encoded, decoded, 15, q) != 0)
        goto error;

    msg[1] &= 0xFE;
    if(memcmp(decoded, msg, 2) != 0)
        goto error;

    return 0;


    error:
        return 1;

}
