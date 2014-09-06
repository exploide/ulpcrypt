#ifndef _ULP_KEYGEN_H_
#define _ULP_KEYGEN_H_


#include "structs.h"


int ulp_generate_parameters(size_t n, size_t l, uint64_t* sk, uint64_t* se, uint64_t* q);


int ulp_generate_key_pair(size_t n, size_t l, uint64_t sk, uint64_t se, uint64_t q, ulp_public_key** pub_key_p, ulp_private_key** priv_key_p);


#endif
