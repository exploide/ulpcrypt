#include "../src/structs.h"

int main() {

    ulp_public_key* pub = NULL;
    ulp_private_key* priv = NULL;
    ulp_ciphertext* c = NULL;

    // test struct allocation with reasonable n and l

    pub = ulp_alloc_public_key(512, 256);
    if(pub == NULL)
        goto error;

    priv = ulp_alloc_private_key(512, 256);
    if(priv == NULL)
        goto error;

    c = ulp_alloc_ciphertext(512, 256);
    if(c == NULL)
        goto error;

    ulp_free_public_key(pub);
    ulp_free_private_key(priv);
    ulp_free_ciphertext(c);

    // test struct allocation with odd n and l

    pub = ulp_alloc_public_key(119, 59);
    if(pub == NULL)
        goto error;

    priv = ulp_alloc_private_key(119, 59);
    if(priv == NULL)
        goto error;

    c = ulp_alloc_ciphertext(119, 59);
    if(c == NULL)
        goto error;

    // test buffer access

    pub->A[21] = 42;
    pub->P[5] = 666;
    priv->S[7] = 99;
    c->c1[0] = 15;
    c->c2[58] = 69;

    ulp_free_public_key(pub);
    ulp_free_private_key(priv);
    ulp_free_ciphertext(c);
    return 0;


    error:
        ulp_free_public_key(pub);
        ulp_free_private_key(priv);
        ulp_free_ciphertext(c);
        return 1;

}
