#include "HillCipher.h"

size_t HillCipher::next_chunk(){
    return fread( chunk, sizeof(unsigned char), buffer_size, file);
}

void HillCipher::clear_chunks(){
    memset( chunk, 0, buffer_size);
    memset( newChunk, 0, buffer_size);
}

void HillCipher::copy_key( int *key_vector ){
    
    memcpy( key, key_vector, sizeof(int) * key_size * key_size );
}

unsigned char HillCipher::create_output( std::string output_str ){
    //output=NULL;
    output=fopen(output_str.c_str(), "wb" );
    if( output == NULL ){
        printf("Couldn't create output file %s.\n", output_str.c_str());
        return 1;
    }
    return 0;
}

int HillCipher::next_multiple(int bytes){
    if ( bytes % key_size == 0 )
        return bytes;
    else
        return ( key_size - ( bytes % key_size ) ) + bytes;
}
void HillCipher::set_buffer_size(size_t size){
    buffer_size = size;
}

void HillCipher::apply_key( int *key_vector, Tochkey &tochkey  ){
    size_t bytes_readed;
    MatrixKey matrix(1,256);
    while( (bytes_readed=next_chunk()) > 0 ){
        if( bytes_readed != buffer_size ){
            memset( chunk+bytes_readed, 0, buffer_size-bytes_readed);
        }
        bytes_readed=next_multiple(bytes_readed);
        
        //Ejecutar el kernel paralelo
        matrix.matrixMult8( chunk, key, newChunk, key_size );

        if( bytes_readed != buffer_size ){
            memset( newChunk+bytes_readed, 0, buffer_size-bytes_readed);
        }

        //Write back to file
        if( bytes_readed != buffer_size ) printf("Last byte: %d %d     bytes read:%zu\n", chunk[bytes_readed-1], newChunk[bytes_readed-1], bytes_readed);
        tochkey.write(newChunk, bytes_readed);
    }
    tochkey.close();
    fclose(output);
    clear_chunks();
    output=NULL;

}


void HillCipher::encrypt( Tochkey &tochkey  ){ 
    size_t bytes_readed;
    MatrixKey matrix(1,256);
    while( (bytes_readed=next_chunk()) > 0 ){
        if( bytes_readed != buffer_size )
            memset( chunk+bytes_readed, 0, buffer_size-bytes_readed);

        bytes_readed=next_multiple(bytes_readed);

        //printf("Org: ");
        //for(int q=0; q<buffer_size; q++) printf("%d ", key[q]);
        //printf("\n");
        matrix.matrixMult8( chunk, tochkey.main_key, newChunk, key_size );
        //printf("New: ");
        //for(int q=0; q<buffer_size; q++) printf("%d ", newChunk[q]);
        //printf("\n");
        if( bytes_readed != buffer_size ){
            memset( newChunk+bytes_readed, 0, buffer_size-bytes_readed);
        }

        //Write back to file
        //printf("Writing to file... %zu\n", bytes_readed);
        //printf("Last byte: %d %d     bytes read:%zu\n", chunk[bytes_readed-1], newChunk[bytes_readed-1], bytes_readed);
        fwrite ( newChunk , sizeof(unsigned char), bytes_readed, output);
    }
    fclose(output);
    clear_chunks();
    output=NULL;
}


void HillCipher::decrypt( Tochkey &tochkey  ){
    size_t bytes_readed; 
    size_t total_bytes_readed=0;
    MatrixKey matrix(1,256);
    unsigned char offset=tochkey.enc_size-tochkey.org_size;
    while( (bytes_readed=next_chunk()) > 0 ){
        if( bytes_readed != buffer_size )
            memset( chunk+bytes_readed, 0, buffer_size-bytes_readed);


        //Ejecutar el kernel paralelo
        matrix.matrixMult8( chunk, tochkey.main_key, newChunk, key_size );

        if( bytes_readed != buffer_size ){
            memset( newChunk+bytes_readed, 0, buffer_size-bytes_readed);
        }
        total_bytes_readed+=bytes_readed;
        //Write back to file
        if( total_bytes_readed > tochkey.org_size )
            fwrite ( newChunk , sizeof(unsigned char), bytes_readed-offset, output);
        else
            fwrite ( newChunk , sizeof(unsigned char), bytes_readed, output);

    }
    fclose(output);
    clear_chunks();
    output=NULL;

}

void HillCipher::set_key_size(int size){
    key_size=size;
}


void HillCipher::read_file( char *path_to_file ){
    //Try to open the file
    FILE* file_ptr = fopen( path_to_file, "rb" );
    if (file_ptr == NULL)
    {
        fprintf( stderr, "Unable to open file: %s\n", path_to_file );
        return;
    }
    file = file_ptr;
    file_size = getFileSize(file);
    filename = std::string(basename(path_to_file));
}

HillCipher::HillCipher(  ){
    //Set defaults
    set_defaults();

    //Reserve memory for the chunk 
    chunk = (unsigned char*)malloc( sizeof(unsigned char) * buffer_size );
    newChunk = (unsigned char*)malloc( sizeof(unsigned char) * buffer_size );
    key = (int*)malloc( sizeof(int) * key_size * key_size );

}

HillCipher::HillCipher( char *path_to_file ){
    //Set defaults
    set_defaults();

    //Reserve memory for the chunk
    chunk = (unsigned char*)malloc( sizeof(unsigned char) * buffer_size );
    newChunk = (unsigned char*)malloc( sizeof(unsigned char) * buffer_size );
    key = (int*)malloc( sizeof(int) * key_size * key_size );

    memset(chunk, 0, sizeof(unsigned char) * buffer_size );
    memset(newChunk, 0, sizeof(unsigned char) * buffer_size );
    memset(key, 0, sizeof(int) * key_size * key_size );
    
    //Read file
    read_file(path_to_file);
}



HillCipher::~HillCipher(){
    
    if( file != NULL )
        fclose(file);
    file=NULL;

    if( chunk != NULL )
        free(chunk);
    chunk=NULL;
    if( key != NULL )
        free(key);
    key=NULL;
    if( newChunk != NULL )
        free(newChunk);
    newChunk=NULL;

}

void HillCipher::print(){
    if( file_size > 0 )
        printf("Filename: %s\nFile size: %zu\n", filename.c_str(), file_size );
}


// find the file size
size_t HillCipher::getFileSize(FILE* inFile)
{
    size_t fileSize = 0;
    fseek(inFile, 0, SEEK_END);

    fileSize = ftell(inFile);

    fseek(inFile, 0, SEEK_SET);
    return fileSize;
}

void HillCipher::set_defaults(){
    //Set attributes to default
    file_size=0;
    buffer_size = 8;
    //buffer_size = 32;
    file=NULL;
    chunk=NULL;
    mod=MOD;
    key_size=8;

}

/*Super formula nextInt = (cM - (tamAudio % cM)) + tamAudio;
<<El comun multiplo esta dado por cM = (tamAudio * tamLlave)>> */
size_t nextInt(int vect_size, int key_size)
{
    int cm=vect_size * key_size;
    return (cm - (vect_size % cm)) + vect_size;
}
   ;