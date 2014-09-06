#include <stdlib.h>

#include "ring_keygen.h"
#include "random.h"
#include "mathutil.h"


/**
 * Generate a keypair for the U-LP cryptosystem (ring variant).
 * @param size_t n - security parameter and message length
 * @param uint64_t sk - error bound for key generation
 * @param uint64_t se - error bound for encryption
 * @param uint64_t q - modulus, must be less than 2^63 due to possible overflow problems
 * @param ulp_ring_public_key** pub_key_p - pointer to a public key pointer (will be generated)
 * @param ulp_ring_private_key** priv_key_p - pointer to a private key pointer (will be generated)
 * @return int - 0 on success, a negative value otherwise
 */
int ulp_ring_generate_key_pair(size_t n, uint64_t sk, uint64_t se, uint64_t q, ulp_ring_public_key** pub_key_p, ulp_ring_private_key** priv_key_p) {

    if(n == 0 || sk == 0 || se == 0 || q == 0 || pub_key_p == NULL || priv_key_p == NULL || q >= 0x8000000000000000)
        return -2;

    // allocate memory for keys
    ulp_ring_public_key* pub_key = ulp_ring_alloc_public_key(n);
    ulp_ring_private_key* priv_key = ulp_ring_alloc_private_key(n);
    uint64_t* sa = malloc(n*sizeof(uint64_t));
    if(pub_key == NULL || priv_key == NULL || sa == NULL)
        goto fail;

    // store parameters in key structs
    pub_key->se = se;
    pub_key->q = q;
    priv_key->q = q;

    // sample random data
    int err = 0;
    err += get_random_numbers(pub_key->a, n, q);
    err += get_random_numbers(pub_key->p, n, sk);
    err += get_random_numbers(priv_key->s, n, sk);
    if(err != 0)
        goto fail;

    // s*a
    if(poly_mulmod(priv_key->s, pub_key->a, n, q, sa) != 0)
        goto fail;

    // p = e - s*a
    for(size_t i = 0; i < n; i++) {
        pub_key->p[i] = (pub_key->p[i] + q - sa[i]) % q;
    }

    // exit properly
    free(sa);
    *pub_key_p = pub_key;
    *priv_key_p = priv_key;
    return 0;


    // on failure, do cleanup
    fail:
        ulp_ring_free_public_key(pub_key);
        ulp_ring_free_private_key(priv_key);
        free(sa);
        return -1;

}
