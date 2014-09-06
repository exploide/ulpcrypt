#include "../src/mathutil.h"

int main() {

    // test with small numbers

    if(max(1337, 42) != 1337)
        goto error;

    if(max(69, 666) != 666)
        goto error;

    // test with big numbers

    if(max(1099511627776, 0xFFFFFFFFFFFFFFFF) != 0xFFFFFFFFFFFFFFFF)
        goto error;

    // test with one bigger and one smaller number

    if(max(4294967296, 327576) != 4294967296)
        goto error;

    // test with zero

    if(max(0, 6543) != 6543)
        goto error;

    if(max(1125900252520278, 0) != 1125900252520278)
        goto error;

    // test with equal numbers

    if(max(1125900252520278, 1125900252520278) != 1125900252520278)
        goto error;

    return 0;


    error:
        return 1;

}
