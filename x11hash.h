#ifndef X11HASH_H
#define X11HASH_H

#ifdef __cplusplus
extern "C" {
#endif

void x11_hash(const char* input, char* output);
void yespower_hash(const char *input, char *output);
//void yespowerhash(const char *input, char *output);
//void groestlkeccak_hash(const char* input, char* output);
//void GroestlKeccakHash(const char * input, char * output);
#ifdef __cplusplus
}
#endif

#endif
