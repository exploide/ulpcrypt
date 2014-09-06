#include <stdlib.h>
#include <string.h>

#include "../src/ring_crypt.h"
#include "../src/ring_keygen.h"

int main() {

    size_t n = 96;
    uint64_t sk = 34419;
    uint64_t se = 5409067;
    uint64_t q = 468128092967831;

    ulp_ring_public_key* pub_key;
    ulp_ring_private_key* priv_key;
    ulp_ring_generate_key_pair(n, sk, se, q, &pub_key, &priv_key);

    uint8_t msg[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
    ulp_ring_ciphertext* ciphertext;

    // encrypt message and check whether the decrypted data matches the original message

    if(ulp_ring_encrypt(msg, pub_key, &ciphertext) != 0)
        goto error;

    uint8_t* decrypted;
    if(ulp_ring_decrypt(ciphertext, priv_key, &decrypted) != 0)
        goto error;

    if(memcmp(msg, decrypted, n/8) != 0)
        goto error;

    ulp_ring_free_public_key(pub_key);
    ulp_ring_free_private_key(priv_key);
    ulp_ring_free_ciphertext(ciphertext);
    free(decrypted);
    return 0;


    error:
        ulp_ring_free_public_key(pub_key);
        ulp_ring_free_private_key(priv_key);
        ulp_ring_free_ciphertext(ciphertext);
        free(decrypted);
        return 1;

}
