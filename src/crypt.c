#include <stdlib.h>

#include "crypt.h"
#include "encoding.h"
#include "random.h"
#include "mathutil.h"


/**
 * Encrypt a message with the U-LP cryptosystem.
 * @param uint8_t msg[] - the bytes to encrypt (number of bits has to match the l parameter in the key)
 * @param ulp_public_key* pub_key - the public key used for encryption
 * @param ulp_ciphertext** ciphertext_p - pointer to the ciphertext pointer (will be generated)
 * @return int - 0 on success, a negative value otherwise
 */
int ulp_encrypt(uint8_t msg[], ulp_public_key* pub_key, ulp_ciphertext** ciphertext_p) {

    if(msg == NULL || pub_key == NULL)
        return -1;

    // allocate memory for ciphertext and other buffers
    ulp_ciphertext* ciphertext = ulp_alloc_ciphertext(pub_key->n, pub_key->l);
    uint64_t* e1 = malloc(pub_key->n * sizeof(pub_key->se));
    uint64_t* encoded = malloc(pub_key->l * sizeof(pub_key->q));
    if(ciphertext == NULL || e1 == NULL || encoded == NULL)
        goto fail;

    // gather random data for e1, e2 and e3
    int err = 0;
    err += get_random_numbers(e1, pub_key->n, pub_key->se);
    err += get_random_numbers(ciphertext->c1, pub_key->n, pub_key->se);
    err += get_random_numbers(ciphertext->c2, pub_key->l, pub_key->se);
    if(err != 0)
        goto fail;

    // encode input
    encode(msg, encoded, pub_key->l, pub_key->q);

    // c1 = A*e1 + e2
    for(size_t i = 0; i < pub_key->n; i++) {
        for(size_t j = 0; j < pub_key->n; j++) {
            ciphertext->c1[i] = (ciphertext->c1[i] + mulmod(pub_key->A[i*pub_key->n + j], e1[j], pub_key->q)) % pub_key->q;
        }
    }

    // c2 = P*e1 + e3 + encoded(msg)
    for(size_t i = 0; i < pub_key->l; i++) {
        ciphertext->c2[i] = (ciphertext->c2[i] + encoded[i]) % pub_key->q;
        for(size_t j = 0; j < pub_key->n; j++) {
            ciphertext->c2[i] = (ciphertext->c2[i] + mulmod(pub_key->P[i*pub_key->n + j], e1[j], pub_key->q)) % pub_key->q;
        }
    }

    // exit properly
    free(e1);
    free(encoded);
    *ciphertext_p = ciphertext;
    return 0;


    fail:
        ulp_free_ciphertext(ciphertext);
        free(e1);
        free(encoded);
        return -1;

}


/**
 * Decrypt a ciphertext with the U-LP cryptosystem.
 * @param ulp_ciphertext* ciphertext - pointer to the ciphertext to decrypt
 * @param ulp_private_key* priv_key - the private key used for decryption
 * @param uint8_t** msg_p - pointer to the message buffer pointer (will be generated)
 * @return int - 0 on success, a negative value otherwise
 */
int ulp_decrypt(ulp_ciphertext* ciphertext, ulp_private_key* priv_key, uint8_t** msg_p) {

    if(ciphertext == NULL || priv_key == NULL)
        return -1;

    if(ciphertext->n != priv_key->n || ciphertext->l != priv_key->l)
        return -2;

    // compute number of bytes needed for storing the decrypted plaintext
    size_t num_bytes = priv_key->l / 8;
    if(num_bytes * 8 != priv_key->l)
        num_bytes++;

    // allocate memory
    uint64_t* tmp = malloc(priv_key->l * sizeof(priv_key->q));
    uint8_t* msg = malloc(num_bytes);
    if(tmp == NULL || msg == NULL) {
        free(tmp);
        free(msg);
        return -1;
    }

    // S * c1 + c2
    for(size_t i = 0; i < priv_key->l; i++) {
        tmp[i] = ciphertext->c2[i];
        for(size_t j = 0; j < priv_key->n; j++) {
            tmp[i] = (tmp[i] + mulmod(priv_key->S[i*priv_key->n + j], ciphertext->c1[j], priv_key->q)) % priv_key->q;
        }
    }

    // decode decrypted message
    decode(tmp, msg, priv_key->l, priv_key->q);

    // exit properly
    free(tmp);
    *msg_p = msg;
    return 0;

}
