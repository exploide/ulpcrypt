#include "encoding.h"


/**
 * Encode a bitstream to an array of 64 bit integers.
 * 0 will be mapped to 0, 1 will be mapped to q/2.
 * @param uint8_t in[] - input bitstream to encode
 * @param uint64_t out[] - output array which will hold the encoded data
 * @param size_t l - number of bits to encode
 * @param uint64_t q - modulus q needed for encoding
 * @return int - 0 on success, a negative value otherwise
 */
int encode(uint8_t in[], uint64_t out[], size_t l, uint64_t q) {
    if(in == NULL || out == NULL)
        return -1;

    // define possible encoding values
    uint64_t low = 0;
    uint64_t high = q/2;

    // calculate number of bytes
    size_t num_bytes = l/8;
    if(num_bytes * 8 != l)
        num_bytes++;

    // iterate over bytes and bits and encode input
    for(size_t by = 0; by < num_bytes; by++) {
        uint8_t byte = in[by];
        for(size_t bi = 0; bi < 8 && l > 0; bi++) {
            out[by*8+bi] = (byte & 0x80) ? high : low;
            byte <<= 1;
            l--;
        }
    }

    return 0;
}


/**
 * Decode an array of 64 bit integers to a bitstream.
 * A value in range [q/4, q-q/4] will be mapped to 1, 0 otherwise.
 * @param uint64_t in[] - input array to decode
 * @param uint8_t out[] - output array which will hold the decoded data
 * @param size_t l - number of integers to decode
 * @param uint64_t q - modulus q needed for decoding
 * @return int - 0 on success, a negative value otherwise
 */
int decode(uint64_t in[], uint8_t out[], size_t l, uint64_t q) {
    if(in == NULL || out == NULL)
        return -1;

    // define thresholds
    uint64_t t1 = q/4;
    uint64_t t2 = q - q/4;

    // compute number of bytes
    size_t num_bytes = l/8;
    if(num_bytes * 8 != l)
        num_bytes++;

    // iterate over bytes and bits and decode input
    for(size_t by = 0; by < num_bytes; by++) {
        out[by] = 0;
        for(size_t bi = 0; bi < 8 && l > 0; bi++) {
            uint8_t val = (in[by*8+bi] < t1 || in[by*8+bi] > t2) ? 0 : 1;
            out[by] |= val << (7-bi);
            l--;
        }
    }

    return 0;
}
