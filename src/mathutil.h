#ifndef _ULP_MATHUTIL_H_
#define _ULP_MATHUTIL_H_


#include <stddef.h>
#include <stdint.h>


uint64_t max(uint64_t a, uint64_t b);


uint64_t mulmod(uint64_t a, uint64_t b, uint64_t q);


uint64_t expmod(uint64_t b, uint64_t x, uint64_t n);


int is_prime(uint64_t n);


int poly_mulmod(uint64_t p1[], uint64_t p2[], size_t n, uint64_t q, uint64_t result[]);


#endif
