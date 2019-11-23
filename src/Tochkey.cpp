#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Tochfile.h"

#ifndef MOD
#define MOD 256
#endif

using namespace std;

Tochfile::Tochfile(int *key, int key_size, string filename, size_t encryptedSize, int originalSize ){
    //Preparando el encabezado del archivo
    strcpy(header.filename, filename.c_str());
    header.key_size = key_size;
    header.original_size = originalSize;
    header.encrypted_size = encryptedSize;
    header.mod = MOD;

    //Abrir archivo
    filename = filename + ".key";
    file_ptr=fopen(filename.c_str(), "wb" );
    if( file_ptr != NULL ){
        //Escribir el encabezado
        fwrite(&header, sizeof(header), 1, file_ptr);

        //Escribir la llave
        fwrite(key, sizeof(int), key_size*key_size, file_ptr);
    }
    else{
        printf("Couldn't create output file %s.\n", filename.c_str());
        file_ptr=NULL;
    }
    
}

Tochfile::Tochfile(string filepath){
    readfile(filepath);
}

void Tochfile::close(){
    if( file_ptr != NULL ){
        fclose(file_ptr);
        file_ptr = NULL;
    }    
}

void Tochfile::print()
{
    printf("Filename:%s\n", name);
    printf("Original Size:%zu\n", org_size);
    printf("Encryted Size:%zu\n", enc_size);
    printf("Key Size:%d\n", keySize);
    printf("Mod:%d\n", mod);
    printV(main_key, keySize);
}

void Tochfile::write(unsigned char *values, int size)
{
    fwrite(values, sizeof(unsigned char), size, file_ptr); 
}

void Tochfile::readfile(string filepath)
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

void Tochfile::printV( int *vect, int size )
{
    int i=0, j=0;
    for( i=0; i<size; ++i )
    {
        for( j=0; j<size; ++j )
            printf("%d ", vect[i*size+j]);
        printf("\n");
    }

}


