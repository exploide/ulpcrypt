#include "../src/ring_structs.h"

int main() {

    ulp_ring_public_key* pub = NULL;
    ulp_ring_private_key* priv = NULL;
    ulp_ring_ciphertext* c = NULL;

    // test struct allocation with reasonable n

    pub = ulp_ring_alloc_public_key(512);
    if(pub == NULL)
        goto error;

    priv = ulp_ring_alloc_private_key(512);
    if(priv == NULL)
        goto error;

    c = ulp_ring_alloc_ciphertext(512);
    if(c == NULL)
        goto error;

    ulp_ring_free_public_key(pub);
    ulp_ring_free_private_key(priv);
    ulp_ring_free_ciphertext(c);

    // test struct allocation with odd n

    pub = ulp_ring_alloc_public_key(119);
    if(pub == NULL)
        goto error;

    priv = ulp_ring_alloc_private_key(119);
    if(priv == NULL)
        goto error;

    c = ulp_ring_alloc_ciphertext(119);
    if(c == NULL)
        goto error;

    // test buffer access

    pub->a[21] = 42;
    pub->p[5] = 666;
    priv->s[7] = 99;
    c->c1[0] = 15;
    c->c2[58] = 69;

    ulp_ring_free_public_key(pub);
    ulp_ring_free_private_key(priv);
    ulp_ring_free_ciphertext(c);
    return 0;


    error:
        ulp_ring_free_public_key(pub);
        ulp_ring_free_private_key(priv);
        ulp_ring_free_ciphertext(c);
        return 1;

}
