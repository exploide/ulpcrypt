#include "../src/ring_keygen.h"

int main() {

    ulp_ring_public_key* pub_key = NULL;
    ulp_ring_private_key* priv_key = NULL;

    size_t n = 256;
    uint64_t sk = 121470;
    uint64_t se = 33435447;
    uint64_t q = 17886865857437077;

    // generate key pair and do sanity checks

    if(ulp_ring_generate_key_pair(n, sk, se, q, &pub_key, &priv_key) != 0)
        goto error;

    if(pub_key == NULL || pub_key->n != n || pub_key->q != q || pub_key->se != se || pub_key->a == NULL || pub_key->p == NULL)
        goto error;

    if(priv_key == NULL || priv_key->n != n || priv_key->q != q || priv_key->s == NULL)
        goto error;

    // check if values are below thresholds

    for(size_t i = 0; i < n; i++) {
        if(pub_key->a[i] >= q || pub_key->p[i] >= q || priv_key->s[i] >= sk)
            goto error;
    }

    ulp_ring_free_public_key(pub_key);
    ulp_ring_free_private_key(priv_key);
    return 0;


    error:
        ulp_ring_free_public_key(pub_key);
        ulp_ring_free_private_key(priv_key);
        return 1;

}
