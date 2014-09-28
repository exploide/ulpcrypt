#include <stdlib.h>

#include "ring_structs.h"


/**
 * Allocate heap memory for storing a U-LP public key (ring variant).
 * @param size_t n - security parameter and message length
 * @return ulp_ring_public_key* - pointer to the allocated heap memory
 */
ulp_ring_public_key* ulp_ring_alloc_public_key(size_t n) {
    ulp_ring_public_key* key = malloc(sizeof(ulp_ring_public_key));
    if(key == NULL)
        return NULL;
    key->n = n;
    key->a = malloc(n*sizeof(key->q));
    key->p = malloc(n*sizeof(key->q));
    if(key->a == NULL || key->p == NULL) {
        free(key->a);
        free(key->p);
        free(key);
        return NULL;
    }
    return key;
}


/**
 * Allocate heap memory for storing a U-LP private key (ring variant).
 * @param size_t n - security parameter and message length
 * @return ulp_ring_private_key* - pointer to the allocated heap memory
 */
ulp_ring_private_key* ulp_ring_alloc_private_key(size_t n) {
    ulp_ring_private_key* key = malloc(sizeof(ulp_ring_private_key));
    if(key == NULL)
        return NULL;
    key->n = n;
    key->s = malloc(n*sizeof(key->q));
    if(key->s == NULL) {
        free(key);
        return NULL;
    }
    return key;
}


/**
 * Allocate heap memory for storing a U-LP ciphertext (ring variant).
 * @param size_t n - security parameter and message length
 * @return ulp_ring_ciphertext* - pointer to the allocated heap memory
 */
ulp_ring_ciphertext* ulp_ring_alloc_ciphertext(size_t n) {
    ulp_ring_ciphertext* ciphertext = malloc(sizeof(ulp_ring_ciphertext));
    if(ciphertext == NULL)
        return NULL;
    ciphertext->n = n;
    ciphertext->c1 = malloc(n*sizeof(uint64_t));
    ciphertext->c2 = malloc(n*sizeof(uint64_t));
    if(ciphertext->c1 == NULL || ciphertext->c2 == NULL) {
        free(ciphertext->c1);
        free(ciphertext->c2);
        free(ciphertext);
        return NULL;
    }
    return ciphertext;
}


/**
 * Deallocate heap memory for a U-LP public key (ring variant).
 * @param ulp_ring_public_key* pub_key - pointer to the memory to free
 */
void ulp_ring_free_public_key(ulp_ring_public_key* pub_key) {
    if(pub_key != NULL) {
        free(pub_key->a);
        free(pub_key->p);
        free(pub_key);
    }
}


/**
 * Deallocate heap memory for a U-LP private key (ring variant).
 * @param ulp_ring_private_key* priv_key - pointer to the memory to free
 */
void ulp_ring_free_private_key(ulp_ring_private_key* priv_key) {
    if(priv_key != NULL) {
        free(priv_key->s);
        free(priv_key);
    }
}


/**
 * Deallocate heap memory for a U-LP ciphertext (ring variant).
 * @param ulp_ring_ciphertext* ciphertext - pointer to the memory to free
 */
void ulp_ring_free_ciphertext(ulp_ring_ciphertext* ciphertext) {
    if(ciphertext != NULL) {
        free(ciphertext->c1);
        free(ciphertext->c2);
        free(ciphertext);
    }
}
