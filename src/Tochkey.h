//CREATE BY ROBERTO CARLOS MATA
#include <iostream>
#include <stdio.h>
#include <string.h>

#ifndef TOCH_KEY
#define TOCH_KEY

#define MAX_FILENAME_CHARS 256
class Tochkey
{
public:
    char name[256];
    size_t org_size;
    size_t enc_size;
    int keySize;
    int mod;
    FILE *file_ptr;
    int *main_key;

    Tochkey(int *key, int key_size, std::string filename, size_t encryptedSize, int originalSize );
    ~Tochkey();
    Tochkey(std::string filepath);

    void close();
    void update_key(int* key, int size, int modulus);
    void print();
    void printHeader();

    void write(unsigned char *values, int size);

    void readfile(std::string filepath);
    
    void printV( int *vect, int size );

    struct TFile
    {
        char filename[MAX_FILENAME_CHARS];
        size_t original_size;
        size_t encrypted_size;
        int key_size;
        int mod;
    };

private:
    TFile header;
};

#endif
