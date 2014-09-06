#include "../src/keygen.h"

int main() {

    uint64_t se = 0;
    uint64_t sk = 0;
    uint64_t q = 0;

    // test what happens when n is not a multiple of 8
    if(ulp_generate_parameters(12, 6, &sk, &se, &q) == 0)
        goto error;

    // perform some tests

    if(ulp_generate_parameters(64, 32, &sk, &se, &q) != 0 || sk != 20436 || se != 2547392 || q != 103827296026637)
        goto error;

    if(ulp_generate_parameters(256, 128, &sk, &se, &q) != 0 || sk != 121470 || se != 33435447 || q != 17886865857437077)
        goto error;

    if(ulp_generate_parameters(512, 256, &sk, &se, &q) != 0 || sk != 296147 || se != 121133100 || q != 234771646649760029)
        goto error;

    if(ulp_generate_parameters(888, 256, &sk, &se, &q) != 0 || sk != 601141 || se != 22611642 || q != 96563145323786923)
        goto error;

    return 0;


    error:
        return 1;

}
