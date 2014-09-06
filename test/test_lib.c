#include <stdlib.h>
#include <string.h>

#include "../src/ulpcrypt.h"

int main() {

    // test U-LP functions for normal variant

    size_t n = 192;
    size_t l = 96;
    uint64_t sk;
    uint64_t se;
    uint64_t q;

    ulp_generate_parameters(n, l, &sk, &se, &q);

    ulp_public_key* pub_key;
    ulp_private_key* priv_key;
    ulp_generate_key_pair(n, l, sk, se, q, &pub_key, &priv_key);

    uint8_t msg[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};

    ulp_ciphertext* ciphertext;
    ulp_encrypt(msg, pub_key, &ciphertext);

    uint8_t* decrypted;
    ulp_decrypt(ciphertext, priv_key, &decrypted);

    if(memcmp(msg, decrypted, l/8) != 0)
        goto error;


    // test U-LP functions for ring variant

    n = 96;
    sk = 34419;
    se = 5409067;
    q = 468128092967831;

    ulp_ring_public_key* r_pub_key;
    ulp_ring_private_key* r_priv_key;
    ulp_ring_generate_key_pair(n, sk, se, q, &r_pub_key, &r_priv_key);

    ulp_ring_ciphertext* r_ciphertext;
    ulp_ring_encrypt(msg, r_pub_key, &r_ciphertext);

    uint8_t* r_decrypted;
    ulp_ring_decrypt(r_ciphertext, r_priv_key, &r_decrypted);

    if(memcmp(msg, r_decrypted, n/8) != 0)
        goto error;


    // do cleanup

    ulp_free_public_key(pub_key);
    ulp_free_private_key(priv_key);
    ulp_free_ciphertext(ciphertext);
    free(decrypted);
    ulp_ring_free_public_key(r_pub_key);
    ulp_ring_free_private_key(r_priv_key);
    ulp_ring_free_ciphertext(r_ciphertext);
    free(r_decrypted);
    return 0;


    error:
        ulp_free_public_key(pub_key);
        ulp_free_private_key(priv_key);
        ulp_free_ciphertext(ciphertext);
        free(decrypted);
        ulp_ring_free_public_key(r_pub_key);
        ulp_ring_free_private_key(r_priv_key);
        ulp_ring_free_ciphertext(r_ciphertext);
        free(r_decrypted);
        return 1;

}
