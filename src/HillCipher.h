#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <iostream>
#include "Tochfile.h"


#ifndef MOD
#define MOD 256
#endif

#ifndef HILL_CIPHER
#define HILL_CIPHER

__global__ void matrixMultiplication( unsigned char *newVect, int *key, unsigned char *resultado, int keySize );


class HillCipher{

public:
    int mod;
    size_t buffer_size; 
    unsigned char *chunk;
    unsigned char *newChunk;
    int *key;
    int key_size;
    size_t file_size;

    // find the file size
    size_t getFileSize(FILE* inFile);
    int next_multiple(int bytes);

    size_t next_chunk();

    void clear_chunks();

    void copy_key( int *key_vector );

    unsigned char create_output( std::string output_str );

    void apply_key( int *key_vector, Tochfile&  );
    void set_key_size(int size);

    void read_file( char *path_to_file );

    HillCipher(  );

    HillCipher( char *path_to_file );

    

    ~HillCipher();

    void print();
    
    

private:
    
    std::string filename;
    FILE *file;
    FILE *output;


    void set_defaults();
};

#endif
