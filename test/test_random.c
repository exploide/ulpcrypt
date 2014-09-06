#include <stdlib.h>
#include <string.h>

#include "../src/random.h"

int main() {

    uint64_t q = 765432354334562449;
    size_t count = 100;
    uint64_t* b1 = calloc(count, sizeof(uint64_t));
    uint64_t* b2 = calloc(count, sizeof(uint64_t));

    // try to gather random data

    if(get_random_numbers(b1, count, q) != 0)
        goto error;

    if(get_random_numbers(b2, count, q) != 0)
        goto error;

    // ensure that the two calls haven't returned the same data

    if(memcmp(b1, b2, count*sizeof(uint64_t)) == 0)
        goto error;

    free(b1);
    free(b2);
    return 0;


    error:
        free(b1);
        free(b2);
        return 1;

}
