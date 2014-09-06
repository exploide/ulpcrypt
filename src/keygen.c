#include <stdlib.h>
#include <math.h>

#include "keygen.h"
#include "random.h"
#include "mathutil.h"


#define C 17.5920386346335


/**
 * Generate the parameters for the U-LP cryptosystem dependent on n and l.
 * @param size_t n - security parameter
 * @param size_t l - message length
 * @param uint64_t* sk - pointer to error bound for key generation (will be generated)
 * @param uint64_t* se - pointer to error bound for encryption (will be generated)
 * @param uint64_t* q - pointer to modulus (will be generated)
 * @return int - 0 on success, a negative value otherwise
 */
int ulp_generate_parameters(size_t n, size_t l, uint64_t* sk, uint64_t* se, uint64_t* q) {

    if(n == 0 || l == 0 || sk == NULL || se == NULL || q == NULL)
        return -2;

    if(n % 8 != 0)
        return -8;

    // compute parameters
    *sk = ceil(pow(2*C*n, 9.0/7.0));
    *se = ceil(pow(C*(2*n+l), 9.0/7.0 + 8.0/7.0 * (double)l/(double)n));
    *q = max(powl(4*(*se), 2), 8*n*(*se)*(*sk) + 4*(*se) + 4);
    // search next prime number
    if(*q % 2 == 0)
        (*q)++;
    while(!is_prime(*q))
        (*q)+=2;

    if(*q >= 0x8000000000000000) // 2^63
        return -63;

    return 0;

}


/**
 * Generate a keypair for the U-LP cryptosystem.
 * @param size_t n - security parameter
 * @param size_t l - message length
 * @param uint64_t sk - error bound for key generation
 * @param uint64_t se - error bound for encryption
 * @param uint64_t q - modulus, must be less than 2^63 due to possible overflow problems
 * @param ulp_public_key** pub_key_p - pointer to a public key pointer (will be generated)
 * @param ulp_private_key** priv_key_p - pointer to a private key pointer (will be generated)
 * @return int - 0 on success, a negative value otherwise
 */
int ulp_generate_key_pair(size_t n, size_t l, uint64_t sk, uint64_t se, uint64_t q, ulp_public_key** pub_key_p, ulp_private_key** priv_key_p) {

    if(n == 0 || l == 0 || sk == 0 || se == 0 || q == 0 || pub_key_p == NULL || priv_key_p == NULL || q >= 0x8000000000000000)
        return -2;

    // allocate memory for keys
    ulp_public_key* pub_key = ulp_alloc_public_key(n, l);
    ulp_private_key* priv_key = ulp_alloc_private_key(n, l);
    uint64_t* SA = calloc(l*n, sizeof(q));
    if(pub_key == NULL || priv_key == NULL || SA == NULL)
        goto fail;

    // store parameters in key structs
    pub_key->se = se;
    pub_key->q = q;
    priv_key->q = q;

    // sample random data
    int err = 0;
    err += get_random_numbers(pub_key->A, n*n, q);
    err += get_random_numbers(pub_key->P, l*n, sk);
    err += get_random_numbers(priv_key->S, l*n, sk);
    if(err != 0)
        goto fail;

    // S*A
    for(size_t i = 0; i < l; i++) {
        for(size_t j = 0; j < n; j++) {
            for(size_t k = 0; k < n; k++) {
                SA[i*n+j] = (SA[i*n+j] + mulmod(priv_key->S[i*n+k], pub_key->A[k*n+j], q)) % q;
            }
        }
    }

    // P = E - S*A
    for(size_t i = 0; i < l*n; i++) {
        pub_key->P[i] = (pub_key->P[i] + q - SA[i]) % q;
    }

    // exit properly
    free(SA);
    *pub_key_p = pub_key;
    *priv_key_p = priv_key;
    return 0;


    // on failure, do cleanup
    fail:
        ulp_free_public_key(pub_key);
        ulp_free_private_key(priv_key);
        free(SA);
        return -1;

}
