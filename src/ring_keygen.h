#ifndef _ULP_RING_KEYGEN_H_
#define _ULP_RING_KEYGEN_H_


#include "ring_structs.h"


int ulp_ring_generate_key_pair(size_t n, uint64_t sk, uint64_t se, uint64_t q, ulp_ring_public_key** pub_key_p, ulp_ring_private_key** priv_key_p);


#endif
