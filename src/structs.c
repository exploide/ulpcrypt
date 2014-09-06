#include <stdlib.h>

#include "structs.h"


/**
 * Allocate heap memory for storing an U-LP public key.
 * @param size_t n - security parameter
 * @param size_t l - message length
 * @return ulp_public_key* - pointer to the allocated heap memory
 */
ulp_public_key* ulp_alloc_public_key(size_t n, size_t l) {
    ulp_public_key* key = malloc(sizeof(ulp_public_key));
    if(key == NULL)
        return NULL;
    key->n = n;
    key->l = l;
    key->A = malloc(n*n*sizeof(key->q));
    key->P = malloc(l*n*sizeof(key->q));
    if(key->A == NULL || key->P == NULL) {
        free(key->A);
        free(key->P);
        free(key);
        return NULL;
    }
    return key;
}


/**
 * Allocate heap memory for storing an U-LP private key.
 * @param size_t n - security parameter
 * @param size_t l - message length
 * @return ulp_private_key* - pointer to the allocated heap memory
 */
ulp_private_key* ulp_alloc_private_key(size_t n, size_t l) {
    ulp_private_key* key = malloc(sizeof(ulp_private_key));
    if(key == NULL)
        return NULL;
    key->n = n;
    key->l = l;
    key->S = malloc(l*n*sizeof(key->q));
    if(key->S == NULL) {
        free(key);
        return NULL;
    }
    return key;
}


/**
 * Allocate heap memory for storing an U-LP ciphertext.
 * @param size_t n - security parameter
 * @param size_t l - message length
 * @return ulp_ciphertext* - pointer to the allocated heap memory
 */
ulp_ciphertext* ulp_alloc_ciphertext(size_t n, size_t l) {
    ulp_ciphertext* ciphertext = malloc(sizeof(ulp_ciphertext));
    if(ciphertext == NULL)
        return NULL;
    ciphertext->n = n;
    ciphertext->l = l;
    ciphertext->c1 = malloc(n*sizeof(uint64_t));
    ciphertext->c2 = malloc(l*sizeof(uint64_t));
    if(ciphertext->c1 == NULL || ciphertext->c2 == NULL) {
        free(ciphertext->c1);
        free(ciphertext->c2);
        free(ciphertext);
        return NULL;
    }
    return ciphertext;
}


/**
 * Deallocate heap memory for an U-LP public key.
 * @param ulp_public_key* pub_key - pointer to the memory to free
 */
void ulp_free_public_key(ulp_public_key* pub_key) {
    if(pub_key != NULL) {
        free(pub_key->A);
        free(pub_key->P);
        free(pub_key);
    }
}


/**
 * Deallocate heap memory for an U-LP private key.
 * @param ulp_private_key* priv_key - pointer to the memory to free
 */
void ulp_free_private_key(ulp_private_key* priv_key) {
    if(priv_key != NULL) {
        free(priv_key->S);
        free(priv_key);
    }
}


/**
 * Deallocate heap memory for an U-LP ciphertext.
 * @param ulp_ciphertext* ciphertext - pointer to the memory to free
 */
void ulp_free_ciphertext(ulp_ciphertext* ciphertext) {
    if(ciphertext != NULL) {
        free(ciphertext->c1);
        free(ciphertext->c2);
        free(ciphertext);
    }
}
