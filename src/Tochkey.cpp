#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Tochkey.h"
#include <libgen.h>

#ifndef MOD
#define MOD 256
#endif

using namespace std;

Tochkey::Tochkey(int *key, int key_size, string filename, size_t encryptedSize, int originalSize, string out_name ){
    //Preparando el encabezado del archivo
    memset(&header, 0, sizeof(TFile) );
    char tmp[ filename.length() + 1 ];
    tmp[ filename.length() ] = '\0';
    strcpy(tmp, filename.c_str());
    char *base=basename(tmp);
    strcpy(header.filename, base);
    header.key_size = key_size;
    header.original_size = originalSize;
    header.encrypted_size = encryptedSize;
    header.mod = MOD;

    //Copiando datos del encabezado a la clase
    strcpy(name, header.filename);

    keySize = header.key_size;
    org_size = header.original_size;
    enc_size = header.encrypted_size;
    mod = header.mod;
    main_key = (int*)malloc(sizeof(int)*keySize*keySize);
    memcpy(main_key, key, sizeof(int)*keySize*keySize);

    //Abrir archivo
    string out = out_name + ".tochkey";
    file_ptr=fopen(out.c_str(), "wb" );
    if( file_ptr != NULL ){
        
        //Escribir el encabezado
        fwrite(&header, sizeof(header), 1, file_ptr);

        //Escribir la llave
        fwrite(main_key, sizeof(int), key_size*key_size, file_ptr);

        fclose(file_ptr);
        file_ptr=NULL;
    }
    else{
        printf("Couldn't create output file %s.\n", filename.c_str());
        file_ptr=NULL;
    }
    
}
Tochkey::~Tochkey(){
    if( file_ptr != NULL ){
        fclose(file_ptr);
        file_ptr = NULL;
    }

    if( main_key != NULL ){
        free(main_key);
        main_key=NULL;
    }
}

Tochkey::Tochkey(string filepath){
    readfile(filepath);
}

void Tochkey::close(){
    if( file_ptr != NULL ){
        fclose(file_ptr);
        file_ptr = NULL;
    }    
}

void Tochkey::update_key( int *key, int key_size, int modulus ){
    if( main_key != NULL ){
        free(main_key);
        main_key=NULL;
    }
    main_key = (int*)malloc(sizeof(int)*key_size*key_size);

    //Copiar llave a key
    memcpy(main_key, key, sizeof(int)*key_size*key_size);
    mod = modulus;
    keySize = key_size;
}

void Tochkey::print()
{
    printf("Filename:%s\n", name);
    printf("Original Size:%zu\n", org_size);
    printf("Encryted Size:%zu\n", enc_size);
    printf("Key Size:%d\n", keySize);
    printf("Mod:%d\n", mod);
    printV(main_key, keySize);
}

void Tochkey::printHeader()
{
    printf("Filename:%s\n", header.filename);
    printf("Original Size:%zu\n", header.original_size);
    printf("Encryted Size:%zu\n", header.encrypted_size);
    printf("Key Size:%d\n", header.key_size);
    printf("Mod:%d\n", header.mod);
    //printV(main_key, keySize);
}

void Tochkey::write(unsigned char *values, int size)
{
    fwrite(values, sizeof(unsigned char), size, file_ptr); 
}

void Tochkey::readfile(string filepath)
{
    file_ptr=fopen(filepath.c_str(), "rb" );
    if( file_ptr != NULL ){
        //Leer el encabezado
        fread(&header, sizeof(header), 1, file_ptr);
        strncpy(name, header.filename, 256);
        org_size=header.original_size;
        enc_size=header.encrypted_size;
        keySize = header.key_size;
        mod = header.mod;

        main_key = (int*)malloc(sizeof(int)*keySize*keySize);
        fread(main_key, sizeof(int), keySize*keySize, file_ptr);
    }
    else{
        printf("File no exist %s.\n", filepath.c_str());
        file_ptr=NULL;
    }
}

void Tochkey::printV( int *vect, int size )
{
    int i=0, j=0;
    for( i=0; i<size; ++i )
    {
        for( j=0; j<size; ++j )
            printf("%d ", vect[i*size+j]);
        printf("\n");
    }

}


