#include "../src/mathutil.h"

int main() {

    // test with small numbers

    if(mulmod(123, 456, 7) != 4)
        goto error;

    if(mulmod(987654, 54321, 43650352937) != 9999999997)
        goto error;

    // test with 64 bit numbers

    if(mulmod(0xffffffffffffffff, 0xffffffffffffffff, 1152921504606847009) != 279841)
        goto error;

    return 0;


    error:
        return 1;

}
