#include "../src/mathutil.h"

int main() {

    // test with small numbers

    if(expmod(432, 18, 765) != 729)
        goto error;

    if(expmod(98765432456, 21345654321, 1234567654325432) != 531932833467048)
        goto error;

    // test with big numbers

    if(expmod(1234567654326545432, 0x84b603a249dbac18, 4611686094970622477) != 4208510699096144003)
        goto error;

    return 0;


    error:
        return 1;

}
