ulpcrypt
========

Implementation of the U-LP Cryptosystem

This library is an implementation of the U-LP cryptosystem as described by Cabarcas, Göpfert, and Weiden in *Provably Secure LWE Encryption with Smallish Uniform Noise and Secret*. The library provides functions for key generation, encryption, and decryption, for the standard variant of U-LP, as well as for the Ring-LWE variant.

U-LP is a provably secure (post-quantum) encryption scheme, based on the *Learning with Errors* problem.

Warning: Note that this cryptosystem is very young and not very extensively researched, yet. The purpose of this library is mainly for academic purposes. So take care when considering this for use in practice.


##Building ulpcrypt

ulpcrypt is built using the CMake build system. Primarily it's configured for the use with the gcc compiler. ulpcrypt should compile on Linux and Windows. The following shows the steps required for compilation, exemplary on Linux:
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
