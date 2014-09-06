#include "../src/keygen.h"

int main() {

    ulp_public_key* pub_key = NULL;
    ulp_private_key* priv_key = NULL;

    size_t n = 256;
    size_t l = 128;
    uint64_t sk = 121470;
    uint64_t se = 33435447;
    uint64_t q = 17886865857437077;

    // generate key pair and do sanity checks

    if(ulp_generate_key_pair(n, l, sk, se, q, &pub_key, &priv_key) != 0)
        goto error;

    if(pub_key == NULL || pub_key->n != n || pub_key->l != l || pub_key->q != q || pub_key->se != se || pub_key->A == NULL || pub_key->P == NULL)
        goto error;

    if(priv_key == NULL || priv_key->n != n || priv_key->l != l || priv_key->q != q || priv_key->S == NULL)
        goto error;

    // check if values are below thresholds

    for(size_t i = 0; i < n*n; i++) {
        if(pub_key->A[i] >= q)
            goto error;
    }

    for(size_t i = 0; i < l*n; i++) {
        if(pub_key->P[i] >= q)
            goto error;
        if(priv_key->S[i] >= sk)
            goto error;
    }

    ulp_free_public_key(pub_key);
    ulp_free_private_key(priv_key);
    return 0;


    error:
        ulp_free_public_key(pub_key);
        ulp_free_private_key(priv_key);
        return 1;

}
