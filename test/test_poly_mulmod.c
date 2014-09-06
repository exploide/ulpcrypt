#include <string.h>

#include "../src/mathutil.h"

int main() {

    size_t n = 5;
    uint64_t q = 13;
    uint64_t p1[] = {2, 6, 1, 0, 11};
    uint64_t p2[] = {0, 2, 12, 3, 4};
    uint64_t result[5];
    uint64_t result_cmp[] = {3, 11, 3, 10, 12};
    if(poly_mulmod(p1, p2, n, q, result) != 0 || memcmp(result, result_cmp, n*sizeof(uint64_t)) != 0)
        goto error;

    n = 10;
    q = 124567890987697;
    uint64_t p3[] = {56789098, 12456, 0, 0, 7697, 7697, 56789098, 987697, 21345678, 524353245};
    uint64_t p4[] = {76456544, 32454365, 5234532, 643545, 5646435, 0, 0, 0, 43243245, 676576887};
    uint64_t result2[10];
    uint64_t result2_cmp[] = {87089358200106, 76491873611365, 88499648609750, 59973954620151, 102521999917615, 27484570724615, 10385314663838, 54600194504447, 61320648958789, 22308415167513};
    if(poly_mulmod(p3, p4, n, q, result2) != 0 || memcmp(result2, result2_cmp, n*sizeof(uint64_t)) != 0)
        goto error;

    return 0;


    error:
        return 1;

}
