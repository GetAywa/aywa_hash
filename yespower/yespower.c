#include "yespower.h"
//#include "yespower-opt.c"

int yespower_hash(const char *input, char *output)
{
	yespower_params_t params = {YESPOWER_1_0, 2048, 32, NULL, 0};
     yespower_tls(input, 80, &params, (yespower_binary_t *) output);

//    for(int j = 0; j < 16; j++){  // reverse output
//           int t = output[j];
//           output[j] = output[32- j - 1];
//           output[32 - j - 1] = t;
//       }
    return output;
}
