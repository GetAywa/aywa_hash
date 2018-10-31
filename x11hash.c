#include "x11hash.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

//#include <boost/multiprecision/cpp_int.hpp>

//#include "yespower/sph_yespower.h"
#include "yespower/yespower.h"

#include "sha3/sph_blake.h"
#include "sha3/sph_bmw.h"
#include "sha3/sph_groestl.h"
#include "sha3/sph_jh.h"
#include "sha3/sph_keccak.h"
#include "sha3/sph_skein.h"
#include "sha3/sph_luffa.h"
#include "sha3/sph_cubehash.h"
#include "sha3/sph_shavite.h"
#include "sha3/sph_simd.h"
#include "sha3/sph_echo.h"

//int yespower_hash(const char *input, char *output)
//{
//	yespower_params_t params = {YESPOWER_1_0, 2048, 32, NULL, 0};
//	return yespower_tls(input, 80, &params, (yespower_binary_t *) output);
//}

//void yespowerhash(const char* input, char* output)
//{
//    char * yespower_output;
//    uint32_t groestlkeccak_input[16];
////    yespower_hash ((const char*)input, yespower_output);

//    yespower_params_t params = {YESPOWER_1_0, 2048, 32, NULL, 0};
//    yespower_tls(input, 80, &params, (yespower_binary_t *) yespower_output);

//    memcpy(output, yespower_output, 32);

//    //groestlkeccak_hash (groestlkeccak_input,output);

//}


void x11_hash(const char* input, char* output)
{
    sph_groestl512_context   ctx_groestl;
    sph_keccak512_context    ctx_keccak;

    //these uint512 in the c++ source of the client are backed by an array of uint32
    uint32_t hashA[16], hashB[16];
    uint32_t yespower_input[32], yespower_output[32];

    memcpy(yespower_input, input, 80);
    yespower_hash(yespower_input, yespower_output);


    //memcpy(hashA, yespower_output, 32);

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, yespower_input, 64);
    sph_groestl512_close(&ctx_groestl, hashA);

    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, hashA, 64);
    sph_keccak512_close(&ctx_keccak, hashB);

    memcpy(output, hashB, 32);

/* trying 2
 *  uint32_t hash1[16], hash2[16], hash3[16];
    char* result;

    yespower_hash(input, result);

//    sph_groestl_big_context ctx_groestl;
//    sph_groestl512_init(&ctx_groestl);
//    sph_groestl512(&ctx_groestl, &result, 64);
//    sph_groestl512_close(&ctx_groestl, &result);

//    sph_keccak512_context    ctx_keccak;
//    sph_keccak512_init(&ctx_keccak);
//    sph_keccak512 (&ctx_keccak, (const void*)(&hash2), 64);
//    sph_keccak512_close(&ctx_keccak, (void*)(&hash3));

    memcpy(output, result, 32);
    */
}

