#ifndef _ULP_ENCODING_H_
#define _ULP_ENCODING_H_


#include <stddef.h>
#include <stdint.h>


int encode(uint8_t in[], uint64_t out[], size_t l, uint64_t q);

int decode(uint64_t in[], uint8_t out[], size_t l, uint64_t q);


#endif
