cmake_minimum_required(VERSION 2.6)

project(U-LP_Library)

set(lib_name_shared ulpcrypt)
set(lib_name_static ulpcrypt-static)
set(lib_files src/ulpcrypt.h src/structs.h src/structs.c src/keygen.h src/keygen.c src/crypt.h src/crypt.c src/encoding.h src/encoding.c src/random.h src/random.c src/mathutil.h src/mathutil.c src/ring_structs.h src/ring_structs.c src/ring_keygen.h src/ring_keygen.c src/ring_crypt.h src/ring_crypt.c)

add_library(${lib_name_shared} SHARED ${lib_files})
add_library(${lib_name_static} STATIC ${lib_files})

set(CMAKE_C_FLAGS "-Wall -Wextra -std=c11 -lm")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

set(CMAKE_BUILD_TYPE Release)



### testing ###

enable_testing()

add_executable(test_structs test/test_structs.c src/structs.h src/structs.c)
add_test(test_structs test_structs)

add_executable(test_random test/test_random.c src/random.h src/random.c)
add_test(test_random test_random)

add_executable(test_max test/test_max.c src/mathutil.h src/mathutil.c)
add_test(test_max test_max)

add_executable(test_mulmod test/test_mulmod.c src/mathutil.h src/mathutil.c)
add_test(test_mulmod test_mulmod)

add_executable(test_expmod test/test_expmod.c src/mathutil.h src/mathutil.c)
add_test(test_expmod test_expmod)

add_executable(test_prime test/test_prime.c src/mathutil.h src/mathutil.c)
add_test(test_prime test_prime)

add_executable(test_gen_params test/test_gen_params.c src/keygen.h src/keygen.c src/mathutil.h src/mathutil.c src/structs.h src/structs.c src/random.h src/random.c)
add_test(test_gen_params test_gen_params)

add_executable(test_gen_keys test/test_gen_keys.c src/keygen.h src/keygen.c src/mathutil.h src/mathutil.c src/structs.h src/structs.c src/random.h src/random.c)
add_test(test_gen_keys test_gen_keys)

add_executable(test_coding test/test_coding.c src/encoding.h src/encoding.c)
add_test(test_coding test_coding)

add_executable(test_crypt test/test_crypt.c src/crypt.h src/crypt.c src/encoding.h src/encoding.c src/structs.h src/structs.c src/random.h src/random.c src/mathutil.h src/mathutil.c src/keygen.h src/keygen.c)
add_test(test_crypt test_crypt)

add_executable(test_ring_structs test/test_ring_structs.c src/ring_structs.h src/ring_structs.c)
add_test(test_ring_structs test_ring_structs)

add_executable(test_poly_mulmod test/test_poly_mulmod.c src/mathutil.h src/mathutil.c)
add_test(test_poly_mulmod test_poly_mulmod)

add_executable(test_ring_gen_keys test/test_ring_gen_keys.c src/ring_keygen.h src/ring_keygen.c src/mathutil.h src/mathutil.c src/random.h src/random.c src/ring_structs.h src/ring_structs.c)
add_test(test_ring_gen_keys test_ring_gen_keys)

add_executable(test_ring_crypt test/test_ring_crypt.c src/ring_crypt.h src/ring_crypt.c src/ring_keygen.h src/ring_keygen.c src/mathutil.h src/mathutil.c src/random.h src/random.c src/ring_structs.h src/ring_structs.c src/encoding.h src/encoding.c)
add_test(test_ring_crypt test_ring_crypt)

add_executable(test_lib_shared test/test_lib.c src/ulpcrypt.h)
target_link_libraries(test_lib_shared ${lib_name_shared})
add_test(test_lib_shared test_lib_shared)

add_executable(test_lib_static test/test_lib.c src/ulpcrypt.h)
target_link_libraries(test_lib_static ${lib_name_static})
add_test(test_lib_static test_lib_static)
