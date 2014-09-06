#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#include "mathutil.h"


/**
 * Compute the maximum of two given unsigned 64 bit integers.
 * @param uint64_t a - one number to compare
 * @param uint64_t b - another number to compare
 * @return uint64_t - the greater of the two numbers.
 */
uint64_t max(uint64_t a, uint64_t b) {
    return a > b ? a : b;
}


/**
 * Compute (a * b) mod q.
 * @param uint64_t a - one factor
 * @param uint64_t b - the other factor
 * @param uint64_t q - the modulus, must be less than 2^63 due to possible overflow problems
 * @return uint64_t - the result of (a * b) mod q
 */
uint64_t mulmod(uint64_t a, uint64_t b, uint64_t q) {

    #ifdef __SIZEOF_INT128__

        // make use of the inofficial but efficient 128-bit integer type
        unsigned __int128 tmp = (unsigned __int128) a * (unsigned __int128) b;
        return (uint64_t) (tmp % q);

    #else

        // this is a rather inefficient fallback implementation
        // in case that there is no 128-bit integer type available
        // attention: this only works with q < 2^63 due to possible overflow problems

        // a = a1 * 2^32 + a2 ; b = b1 * 2^32 + b2
        uint64_t a1 = a >> 32;
        uint64_t a2 = a & 0x00000000FFFFFFFF;
        uint64_t b1 = b >> 32;
        uint64_t b2 = b & 0x00000000FFFFFFFF;

        uint64_t a1b1 = (a1 * b1) % q;
        uint64_t a1b2 = (a1 * b2) % q;
        uint64_t a2b1 = (a2 * b1) % q;
        uint64_t a2b2 = (a2 * b2) % q;

        for(size_t i = 0; i < 64; i++) {
            if(i < 32) {
                a1b2 <<= 1;
                a1b2 %= q;
                a2b1 <<= 1;
                a2b1 %= q;
            }
            a1b1 <<= 1;
            a1b1 %= q;
        }

        uint64_t tmp = (a1b1 + a1b2) % q;
        tmp = (tmp + a2b1) % q;
        tmp = (tmp + a2b2) % q;

        return tmp;

    #endif

}


/**
 * Compute b^x mod n
 * @param uint64_t b - the basis
 * @param uint64_t x - the exponent
 * @param uint64_t n - the modulus
 * @return uint64_t - the result of b^x mod n
 */
uint64_t expmod(uint64_t b, uint64_t x, uint64_t n) {
    // perform an efficient exponentiation by squaring
    uint64_t res = 1;
    while(x > 0) {
        if(x & 0x0000000000000001) {
            res = mulmod(res, b, n);
        }
        b = mulmod(b, b, n);
        x >>= 1;
    }
    return res;
}


/**
 * Check if a number is prime.
 * @param uint64_t n - the number to check if it's prime
 * @return int - 1 if n is prime, 0 otherwise
 */
int is_prime(uint64_t n) {
    if(n % 2 == 0 || n == 1)
        return n == 2 ? 1 : 0;

    // perform (deterministic) Miller-Rabin primality test

    uint64_t s = 1;
    uint64_t t = 2;
    while((n-1) % (t<<1) == 0) {
        s++;
        t <<= 1;
    }
    uint64_t d = (n-1) / t;

    // these bases should be sufficient to test all n < 2^64
    uint64_t bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

    for(size_t i = 0; i < 7; i++) {
        uint64_t a = bases[i];
        if(a >= n)
            break;

        uint64_t tmp = expmod(a, d, n);
        if(tmp != 1 && tmp != n-1) {
            size_t cnt = 0;
            for(uint64_t r = 1; r < s; r++) {
                tmp = mulmod(tmp, tmp, n);
                if(tmp != n-1)
                    cnt++;
            }
            if(cnt == s-1)
                return 0;
        }

    }

    return 1;
}


/**
 * Compute p1*p2 where p1, p2 are polynomials over Z_q[x]/<x^n + 1>.
 * Polynomials are represented by their coefficient vectors [a_0, ..., a_{n-1}]
 * @param uint64_t p1[] - first polynomial
 * @param uint64_t p2[] - second polynomial
 * @param size_t n - length of coefficient vectors
 * @param uint64_t q - modulus for coefficients
 * @param uint64_t result[] - result vector (must be sufficiently large to hold n coefficients)
 * @return int - 0 on success, a negative value otherwise
 */
int poly_mulmod(uint64_t p1[], uint64_t p2[], size_t n, uint64_t q, uint64_t result[]) {

    uint64_t* tmp = calloc(2*n-1, sizeof(uint64_t));
    if(tmp == NULL)
        goto fail;

    // p1 * p2
    for(size_t i = 0; i < n; i++) {
        for(size_t j = 0; j < n; j++) {
            tmp[i+j] = (tmp[i+j] + mulmod(p1[i], p2[j], q)) % q;
        }
    }

    // tmp mod (x^n + 1)
    while(1) {
        size_t deg;
        for(deg = 2*n-2; deg >= n; deg--) {
            if(tmp[deg] != 0)
                break;
        }
        if(deg < n)
            break;

        tmp[deg-n] = (tmp[deg-n] + q - tmp[deg]) % q;
        tmp[deg] = 0;
    }

    memcpy(result, tmp, n*sizeof(uint64_t));
    free(tmp);

    return 0;


    fail:
        return -1;

}
