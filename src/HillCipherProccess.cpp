#include "HillCipherProccess.h"
extern "C"{
    void encrypt( char *input_file, char *output_file ){
        printf("ARGS: <%s>   <%s> \n", input_file, output_file);
        HillCipherProccess HC;
        std::string out=output_file;
        HC.encrypt(input_file, out);
    }

    void decrypt(char *input_file, char *key_file, char *output_file){
        HillCipherProccess HC;
        std::string out(output_file);
        std::string key_str(key_file);
        HC.decrypt(input_file, key_str, out);
    }
}
HillCipherProccess::HillCipherProccess(){
    modulus=256;
}

HillCipherProccess::HillCipherProccess(int mod){
    modulus=mod;
}

///* PROCESO DE ENCRIPTACION */
//Input:
int HillCipherProccess::encrypt( char *input_filename, std::string output_filename ){
    //Create Random compatible key
    MatrixKey modularMatrix(KEY_SIZE, modulus);
    modularMatrix.createKey();

    //Open file
    HillCipher hc( input_filename );

    //Calculate the size to be occupied
    size_t org_size=hc.file_size;
    size_t enc_size=hc.next_multiple(org_size);

    //std::string key_filename(
    //Save the key file
    Tochkey key( modularMatrix.key, KEY_SIZE, input_filename, enc_size, org_size, output_filename );

    //Creates file to write output data(encrypted data)
    if( hc.create_output(output_filename) != 0 ){
        printf("No se pudo crear archivo de salida\n");
        return 1;
    }

    //Start Encryption process
    hc.encrypt(key);
    return 0;
}

int HillCipherProccess::decrypt( char *input_filename, std::string key_filename, std::string output_filename ){
    HillCipher hc(input_filename);

    Tochkey key(key_filename);
    
    MatrixKey unlock_matrix(key.main_key, key.keySize, key.mod);
    unlock_matrix.inverse();
    key.update_key(unlock_matrix.key, unlock_matrix.key_size, unlock_matrix.mod);

    if( hc.create_output(output_filename) != 0 )
        return 1;

    hc.decrypt(key);

    return 0;
}
