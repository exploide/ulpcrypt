#ifndef _ULP_RING_STRUCTS_H_
#define _ULP_RING_STRUCTS_H_


#include <stddef.h>
#include <stdint.h>


/**
 * Public key for U-LP ring variant.
 * n - security parameter
 * q - modulus
 * se - error bound for encryption
 * a - part of the public key
 * p - part of the public key
 */
typedef struct {
    size_t n;
    uint64_t q;
    uint64_t se;
    uint64_t* a;
    uint64_t* p;
} ulp_ring_public_key;


/**
 * Private key for U-LP ring variant.
 * n - security parameter
 * q - modulus
 * s - secret vector
 */
typedef struct {
    size_t n;
    uint64_t q;
    uint64_t* s;
} ulp_ring_private_key;


/**
 * Ciphertext for U-LP ring variant.
 * n - security parameter
 * c1 - first part of the ciphertext
 * c2 - second part of the ciphertext
 */
typedef struct {
    size_t n;
    uint64_t* c1;
    uint64_t* c2;
} ulp_ring_ciphertext;


ulp_ring_public_key* ulp_ring_alloc_public_key(size_t n);
ulp_ring_private_key* ulp_ring_alloc_private_key(size_t n);
ulp_ring_ciphertext* ulp_ring_alloc_ciphertext(size_t n);


void ulp_ring_free_public_key(ulp_ring_public_key* pub_key);
void ulp_ring_free_private_key(ulp_ring_private_key* priv_key);
void ulp_ring_free_ciphertext(ulp_ring_ciphertext* ciphertext);


#endif
