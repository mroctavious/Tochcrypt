#ifndef HILL_CIPHER_PROCESS
#define HILL_CIPHER_PROCESS

#include <iostream>
#include "MatrixKey.h"
#include "HillCipher.h"
#define KEY_SIZE 8
class HillCipherProccess{
public:
    HillCipherProccess();
    HillCipherProccess(int mod);
    int modulus;

    ///* PROCESO DE ENCRIPTACION */
    int encrypt( char *input_filename, std::string output_filename );

    ///* PROCESO DE DECRIPTACION */
    int decrypt( char *input_filename, std::string key_filename, std::string output_filename );
};
#endif