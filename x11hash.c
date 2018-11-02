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


void x11_hash(const char* input, char* output)
{
    sph_blake512_context     ctx_blake;
    sph_bmw512_context       ctx_bmw;
    sph_groestl512_context   ctx_groestl;
    sph_skein512_context     ctx_skein;
    sph_jh512_context        ctx_jh;
    sph_keccak512_context    ctx_keccak;

    sph_luffa512_context		ctx_luffa1;
    sph_cubehash512_context		ctx_cubehash1;
    sph_shavite512_context		ctx_shavite1;
    sph_simd512_context		ctx_simd1;
    sph_echo512_context		ctx_echo1;

    //these uint512 in the c++ source of the client are backed by an array of uint32
    uint32_t hashA[16], hashB[16], yespower_result[32], yespower_outputs[32];

    yespower_hash(input, yespower_outputs);
    //memcpy(yespower_result, yespower_outputs, 32);


//    sph_blake512_init(&ctx_blake);
//    sph_blake512 (&ctx_blake, input, 80);
//    sph_blake512_close (&ctx_blake, hashA);

//    sph_bmw512_init(&ctx_bmw);
//    sph_bmw512 (&ctx_bmw, hashA, 64);
//    sph_bmw512_close(&ctx_bmw, hashB);

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, yespower_outputs, 64);
    sph_groestl512_close(&ctx_groestl, hashA);

//    sph_skein512_init(&ctx_skein);
//    sph_skein512 (&ctx_skein, hashA, 64);
//    sph_skein512_close (&ctx_skein, hashB);

//    sph_jh512_init(&ctx_jh);
//    sph_jh512 (&ctx_jh, hashB, 64);
//    sph_jh512_close(&ctx_jh, hashA);

    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, hashA, 64);
    sph_keccak512_close(&ctx_keccak, hashB);

//    sph_luffa512_init (&ctx_luffa1);
//    sph_luffa512 (&ctx_luffa1, hashB, 64);
//    sph_luffa512_close (&ctx_luffa1, hashA);

//    sph_cubehash512_init (&ctx_cubehash1);
//    sph_cubehash512 (&ctx_cubehash1, hashA, 64);
//    sph_cubehash512_close(&ctx_cubehash1, hashB);

//    sph_shavite512_init (&ctx_shavite1);
//    sph_shavite512 (&ctx_shavite1, hashB, 64);
//    sph_shavite512_close(&ctx_shavite1, hashA);

//    sph_simd512_init (&ctx_simd1);
//    sph_simd512 (&ctx_simd1, hashA, 64);
//    sph_simd512_close(&ctx_simd1, hashB);

//    sph_echo512_init (&ctx_echo1);
//    sph_echo512 (&ctx_echo1, hashB, 64);
//    sph_echo512_close(&ctx_echo1, hashA);

    //memcpy(output, hashB, 32);
    memcpy(output, hashB, 32);
}

/*
//void x11_hash(const char* input, char* output)
//{
////    char * yespower_output;
////    uint32_t groestlkeccak_input[16];
////    yespower_hash ((const char*)input, yespower_output);


//        uint32_t yespower_input[64], yespower_output[1024], groestlkeccak_output[32];

//        memcpy(yespower_input, input, 80);
//        yespower_hash(yespower_input, yespower_output);



////    yespower_params_t params = {YESPOWER_1_0, 2048, 32, NULL, 0};
////    yespower_tls(input, 80, &params, (yespower_binary_t *) yespower_output);

//    memcpy(yespower_input, yespower_output, 32);

//    groestlkeccak_hash (yespower_output,groestlkeccak_output);
//    memcpy(output, groestlkeccak_hash, 32);

//}


void x11_hash2(const char* input, char* output)
{

    uint32_t x11Data[16];

    //yespower_hash(input, (char*) &x11Data);

    sph_groestl_big_context ctx_groestl;
    sph_groestl512_init(&ctx_groestl);
    sph_groestl512(&ctx_groestl, &input, 64);
    sph_groestl512_close(&ctx_groestl, &x11Data);

//    uint16_t rData [32];

//    sph_keccak_context ctx_keccak;
//    sph_keccak512_init(&ctx_keccak);
//    sph_keccak512(&ctx_keccak, &x11Data, 64);
//    sph_keccak512_close(&ctx_keccak, &rData);

    memcpy(output, x11Data, 32);


    /* version1
    sph_groestl512_context   ctx_groestl;
    sph_keccak512_context    ctx_keccak;

    //these uint512 in the c++ source of the client are backed by an array of uint32
    uint32_t hashA[16], hashB[16];
    uint32_t yespower_input[32], yespower_output[1024];

    //memcpy(yespower_input, input, 80);
    yespower_hash(input, yespower_output);


    //memcpy(hashA, yespower_output, 64);

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, yespower_input, 64);
    sph_groestl512_close(&ctx_groestl, hashA);

    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, hashA, 64);
    sph_keccak512_close(&ctx_keccak, hashB);

    memcpy(output, hashA, 32);
*/

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


