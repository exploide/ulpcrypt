#include <stdlib.h>
#include <string.h>

#include "../src/crypt.h"
#include "../src/keygen.h"

int main() {

    size_t n = 192;
    size_t l = 96;
    uint64_t sk = 83914;
    uint64_t se = 19596479;
    uint64_t q = 6144351827159131;

    ulp_public_key* pub_key;
    ulp_private_key* priv_key;
    ulp_generate_key_pair(n, l, sk, se, q, &pub_key, &priv_key);

    uint8_t msg[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
    ulp_ciphertext* ciphertext;

    // encrypt message and check whether the decrypted data matches the original message

    if(ulp_encrypt(msg, pub_key, &ciphertext) != 0)
        goto error;

    uint8_t* decrypted;
    if(ulp_decrypt(ciphertext, priv_key, &decrypted) != 0)
        goto error;

    if(memcmp(msg, decrypted, l/8) != 0)
        goto error;

    ulp_free_public_key(pub_key);
    ulp_free_private_key(priv_key);
    ulp_free_ciphertext(ciphertext);
    free(decrypted);
    return 0;


    error:
        ulp_free_public_key(pub_key);
        ulp_free_private_key(priv_key);
        ulp_free_ciphertext(ciphertext);
        free(decrypted);
        return 1;

}
