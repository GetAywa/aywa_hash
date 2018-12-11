#include "aywahash.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "yespower/yespower.h"
#include "sha3/sph_groestl.h"
#include "sha3/sph_keccak.h"

void GroestlKeccakHash(const char* input, char* output)
{
    sph_groestl512_context   ctx_groestl;
    sph_keccak512_context    ctx_keccak;
    uint32_t hashA[16], hashB[16];
    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, input, 64);
    sph_groestl512_close(&ctx_groestl, &hashA);
    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, &hashA, 64);
    sph_keccak512_close(&ctx_keccak, &hashB);
    memcpy(output, &hashB, 32);
}


void aywa_hash(const char* input, char* output)
{
    uint32_t yespower_output[8] ={0}, gk_input[16]={0};
    yespower_hash(input, &yespower_output);
    memcpy(gk_input, &yespower_output, 32);
    GroestlKeccakHash(&gk_input, output);
}
