#ifndef _ULP_STRUCTS_H_
#define _ULP_STRUCTS_H_


#include <stddef.h>
#include <stdint.h>


/**
 * Public key for U-LP.
 * n - security parameter
 * l - message length
 * q - modulus
 * se - error bound for encryption
 * A - part of the public key
 * P - part of the public key
 */
typedef struct {
    size_t n;
    size_t l;
    uint64_t q;
    uint64_t se;
    uint64_t* A;
    uint64_t* P;
} ulp_public_key;


/**
 * Private key for U-LP.
 * n - security parameter
 * l - message length
 * q - modulus
 * S - secret
 */
typedef struct {
    size_t n;
    size_t l;
    uint64_t q;
    uint64_t* S;
} ulp_private_key;


/**
 * Ciphertext for U-LP.
 * n - security parameter
 * l - message length
 * c1 - first part of the ciphertext
 * c2 - second part of the ciphertext
 */
typedef struct {
    size_t n;
    size_t l;
    uint64_t* c1;
    uint64_t* c2;
} ulp_ciphertext;


ulp_public_key* ulp_alloc_public_key(size_t n, size_t l);
ulp_private_key* ulp_alloc_private_key(size_t n, size_t l);
ulp_ciphertext* ulp_alloc_ciphertext(size_t n, size_t l);


void ulp_free_public_key(ulp_public_key* pub_key);
void ulp_free_private_key(ulp_private_key* priv_key);
void ulp_free_ciphertext(ulp_ciphertext* ciphertext);


#endif
