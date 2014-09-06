#ifndef _ULP_CRYPT_H_
#define _ULP_CRYPT_H_


#include "structs.h"


int ulp_encrypt(uint8_t msg[], ulp_public_key* pub_key, ulp_ciphertext** ciphertext_p);


int ulp_decrypt(ulp_ciphertext* ciphertext, ulp_private_key* priv_key, uint8_t** msg_p);


#endif
