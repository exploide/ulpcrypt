#ifndef _ULP_RING_CRYPT_H_
#define _ULP_RING_CRYPT_H_


#include "ring_structs.h"


int ulp_ring_encrypt(uint8_t msg[], ulp_ring_public_key* pub_key, ulp_ring_ciphertext** ciphertext_p);


int ulp_ring_decrypt(ulp_ring_ciphertext* ciphertext, ulp_ring_private_key* priv_key, uint8_t** msg_p);


#endif
