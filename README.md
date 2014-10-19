ulpcrypt
========

Implementation of the U-LP Cryptosystem

This library is an implementation of the U-LP cryptosystem as described by Cabarcas, Göpfert, and Weiden in *Provably Secure LWE Encryption with Smallish Uniform Noise and Secret*. The library provides functions for key generation, encryption, and decryption, for the standard variant of U-LP, as well as for the ring-LWE variant.

U-LP is a provably secure (post-quantum) encryption scheme, based on the *learning with errors* problem.

Warning: Note that this cryptosystem is very young and not very extensively researched, yet. The purpose of this library is mainly for academic purposes. So take care when considering this for use in practice.


##Building ulpcrypt

ulpcrypt is built using the CMake build system. Primarily it's configured for the use with the gcc compiler, but should also work with clang. ulpcrypt should compile on Linux, Windows, and Mac OS X. The following shows the steps required for compilation, exemplary on Linux:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```
This should build both, a static and a shared version of ulpcrypt.


##Testing ulpcrypt

This library comes with a test suite, powered by CTest, the testing tool which is shipped with CMake. To run the test suite, just execute in the build folder:
```
$ make test
```
All the test should pass before continuing using the library.


##Using ulpcrypt

ulpcrypt compiles to a shared and a static library. To make the function definitions available, just include the
header `ulpcrypt.h`. Most functions return the value 0 on success and a negative value, otherwise. Exceptions
are the functions for allocating structures, which return a pointer, and the functions for deallocating structures,
which return nothing.

An API documentation including structures and functions is available in the `doc/` directory.

Exemplary usage:
```
#include <stdlib.h>

#include "ulpcrypt.h"

int main() {

    size_t n = 192;
    size_t l = 96;
    uint64_t sk;
    uint64_t se;
    uint64_t q;

    ulp_generate_parameters(n, l, &sk, &se, &q);

    ulp_public_key* pub_key;
    ulp_private_key* priv_key;
    ulp_generate_key_pair(n, l, sk, se, q, &pub_key, &priv_key);

    uint8_t msg[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};

    ulp_ciphertext* ciphertext;
    ulp_encrypt(msg, pub_key, &ciphertext);

    uint8_t* decrypted;
    ulp_decrypt(ciphertext, priv_key, &decrypted);

    ulp_free_public_key(pub_key);
    ulp_free_private_key(priv_key);
    ulp_free_ciphertext(ciphertext);
    free(decrypted);
    return 0;

}
```
