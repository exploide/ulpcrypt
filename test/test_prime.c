#include "../src/mathutil.h"

int main() {

    if(is_prime(0) == 1)
        goto error;

    if(is_prime(1) == 1)
        goto error;

    if(is_prime(2) == 0)
        goto error;

    if(is_prime(3) == 0)
        goto error;

    if(is_prime(4) == 1)
        goto error;

    if(is_prime(38183) == 0)
        goto error;

    if(is_prime(1234321237) == 0)
        goto error;

    if(is_prime(1234321232134323) == 1)
        goto error;

    if(is_prime(1234321232134387) == 0)
        goto error;

    if(is_prime(1234321287765432169) == 0)
        goto error;

    return 0;


    error:
        return 1;

}
