#include <stdlib.h>

#include "ring_crypt.h"
#include "encoding.h"
#include "random.h"
#include "mathutil.h"


/**
 * Encrypt a message with the U-LP cryptosystem (ring variant).
 * @param uint8_t msg[] - the bytes to encrypt (number of bits has to match the n parameter in the key)
 * @param ulp_ring_public_key* pub_key - the public key used for encryption
 * @param ulp_ring_ciphertext** ciphertext_p - pointer to the ciphertext pointer (will be generated)
 * @return int - 0 on success, a negative value otherwise
 */
int ulp_ring_encrypt(uint8_t msg[], ulp_ring_public_key* pub_key, ulp_ring_ciphertext** ciphertext_p) {

    if(msg == NULL || pub_key == NULL)
        return -1;

    // allocate memory for ciphertext and other buffers
    ulp_ring_ciphertext* ciphertext = ulp_ring_alloc_ciphertext(pub_key->n);
    uint64_t* e1 = malloc(pub_key->n * sizeof(pub_key->se));
    uint64_t* mul_tmp = malloc(pub_key->n * sizeof(pub_key->q));
    uint64_t* encoded = malloc(pub_key->n * sizeof(pub_key->q));
    if(ciphertext == NULL || e1 == NULL || mul_tmp == NULL || encoded == NULL)
        goto fail;

    // gather random data for e1, e2 and e3
    int err = 0;
    err += get_random_numbers(e1, pub_key->n, pub_key->se);
    err += get_random_numbers(ciphertext->c1, pub_key->n, pub_key->se);
    err += get_random_numbers(ciphertext->c2, pub_key->n, pub_key->se);
    if(err != 0)
        goto fail;

    // encode input
    encode(msg, encoded, pub_key->n, pub_key->q);

    // c1 = a*e1 + e2
    if(poly_mulmod(pub_key->a, e1, pub_key->n, pub_key->q, mul_tmp) != 0)
        goto fail;
    for(size_t i = 0; i < pub_key->n; i++) {
        ciphertext->c1[i] = (ciphertext->c1[i] + mul_tmp[i]) % pub_key->q;
    }

    // c2 = p*e1 + e3 + encoded(msg)
    if(poly_mulmod(pub_key->p, e1, pub_key->n, pub_key->q, mul_tmp) != 0)
        goto fail;
    for(size_t i = 0; i < pub_key->n; i++) {
        ciphertext->c2[i] = (ciphertext->c2[i] + mul_tmp[i] + encoded[i]) % pub_key->q;
    }

    // exit properly
    free(e1);
    free(mul_tmp);
    free(encoded);
    *ciphertext_p = ciphertext;
    return 0;


    fail:
        ulp_ring_free_ciphertext(ciphertext);
        free(e1);
        free(mul_tmp);
        free(encoded);
        return -1;

}


/**
 * Decrypt a ciphertext with the U-LP cryptosystem (ring variant).
 * @param ulp_ring_ciphertext* ciphertext - pointer to the ciphertext to decrypt
 * @param ulp_ring_private_key* priv_key - the private key used for decryption
 * @param uint8_t** msg_p - pointer to the message buffer pointer (will be generated)
 * @return int - 0 on success, a negative value otherwise
 */
int ulp_ring_decrypt(ulp_ring_ciphertext* ciphertext, ulp_ring_private_key* priv_key, uint8_t** msg_p) {

    if(ciphertext == NULL || priv_key == NULL)
        return -1;

    if(ciphertext->n != priv_key->n)
        return -2;

    // compute number of bytes needed for storing the decrypted plaintext
    size_t num_bytes = priv_key->n / 8;
    if(num_bytes * 8 != priv_key->n)
        num_bytes++;

    // allocate memory
    uint64_t* tmp = malloc(priv_key->n * sizeof(priv_key->q));
    uint8_t* msg = malloc(num_bytes);
    if(tmp == NULL || msg == NULL)
        goto fail;

    // s * c1 + c2
    if(poly_mulmod(priv_key->s, ciphertext->c1, priv_key->n, priv_key->q, tmp) != 0)
        goto fail;
    for(size_t i = 0; i < priv_key->n; i++) {
        tmp[i] = (tmp[i] + ciphertext->c2[i]) % priv_key->q;
    }

    // decode decrypted message
    decode(tmp, msg, priv_key->n, priv_key->q);

    // exit properly
    free(tmp);
    *msg_p = msg;
    return 0;


    fail:
        free(tmp);
        free(msg);
        return -1;

}
