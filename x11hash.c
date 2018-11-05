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


///** Compute the 256-bit hash of an object. */
//inline void Hash(const T1 pbegin, const T1 pend, uint32_t result[8])
//{
//    static const unsigned char pblank[1] = {};
//    //uint256 result;
//    CHash256().Write(pbegin == pend ? pblank : (const unsigned char*)&pbegin[0], (pend - pbegin) * sizeof(pbegin[0]))
//              .Finalize((unsigned char*)&result);
//    return result;
//}


//int yespower_hash(const char *input, char *output)
//{
//	yespower_params_t params = {YESPOWER_1_0, 2048, 32, NULL, 0};
//	return yespower_tls(input, 80, &params, (yespower_binary_t *) output);
//}

/*void GroestlKeccakHash(const char * input_gk, char * output_gk)
{
    uint32_t hashA[16], hashB[16];

    sph_groestl512_context   ctx_groestl;
    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, input_gk, 64);
    sph_groestl512_close(&ctx_groestl, hashA);

    sph_keccak512_context    ctx_keccak;
    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, hashA, 64);
    sph_keccak512_close(&ctx_keccak, hashB);

    memcpy(output_gk, hashB, 32);


    //output = input;
}*/

void GroestlKeccakHash(const char* input, char* output)
{
    sph_groestl512_context   ctx_groestl;
    sph_keccak512_context    ctx_keccak;
    uint32_t hashA[16], hashB[16];
    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, input, 64);
    sph_groestl512_close(&ctx_groestl, hashA);
    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, hashA, 64);
    sph_keccak512_close(&ctx_keccak, hashB);
    memcpy(output, hashB, 32);
}


void x11_hash(const char* input, char* output)
{
    uint32_t yespower_output[8], gk_input[32];
    yespower_hash(input, yespower_output);
    memcpy(gk_input, yespower_output, 80);
    GroestlKeccakHash(gk_input, output);

/* version 101
     //char * yespower_output[160], * groestlkeccak_input;
    uint8_t yespower_output_u256[32], groestlkeccak_input[32];
    yespower_hash(input, yespower_output_u256);
    memcpy(groestlkeccak_input, yespower_output_u256, 32);

//    for(int j = 0; j < 16; j++){  // reverse output
//         int t = groestlkeccak_input[j];
//         groestlkeccak_input[j] = groestlkeccak_input[32- j - 1];
//         groestlkeccak_input[32 - j - 1] = t;
//     }

    //memcpy(output, groestlkeccak_input, 32);

    GroestlKeccakHash((char *)groestlkeccak_input, output);
*/

 /* version 100
    sph_groestl512_context   ctx_groestl;
    sph_keccak512_context    ctx_keccak;

    //these uint512 in the c++ source of the client are backed by an array of uint32
    uint32_t hashA[16], hashB[16];//, yespower_input[32], yespower_output[32];
    char * yespower_output;//* yespower_input;

//    void * rawData;
//    memcpy(rawData, input, 160);
//    char *src = rawData;

    yespower_hash(input, &yespower_output);
    //memcpy(yespower_output, hashA, 64);


//    sph_blake512 (&ctx_blake, input, 80);

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, &yespower_output, 64);
    sph_groestl512_close(&ctx_groestl, &hashA);

    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, &hashA, 64);
    sph_keccak512_close(&ctx_keccak, &hashB);

    memcpy((void*)output, (void*)hashB, 32);
    //memcpy(output, yespower_input, 32);
    */
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


//*------Aywa Hash Power--------
//template<typename T>
//uint256 SerializeHashYespower(const T& obj, int nType=SER_GETHASH, int nVersion=PROTOCOL_VERSION)
//{
//    CHashWriterYespower ss(nType, nVersion);
//    ss << obj;
//    return ss.GetHash();
//}





