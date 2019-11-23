#include "HillCipher.h"

__global__ void matrixMultiplication( unsigned char *newVect, int *key, unsigned char *resultado, int keySize ){

    extern __shared__ int cache[];//Determina que es memoria que solo conocen los hilos del mismo bloque y se genera la variable cache por cada conjunto(Lo realiza el primer hilo en llegar)

    //Index para el elemento del vector
    int vectId = 0;

    //Index para la posicion del elemento de la llave
    int keyId = 0;

    int mod = 0;

    //Indexacion para la llave bidimensional
    keyId = ((threadIdx.x * keySize)+ threadIdx.y);

    //Indexacion para el vectorAudio
    vectId = ((blockIdx.x * keySize) + threadIdx.y);

    //Se realiza la multiplicacion de matrices renglon * columna
    mod = (key[(keyId)] * newVect[(vectId)]);

    //Se realiza una variable cache por cada bloque de hilos
    cache[(threadIdx.x * keySize) + threadIdx.y] = mod;

    __syncthreads();//Se sicronizan los hilos
    //Una vez que todos los hilos terminan se puede realizar la suma



    //Se va recorriendo el cache
    if (threadIdx.y  == 0)  // soy el hilo 0
    {
        int suma = 0;
        int j = 0;

        for ( j = 0; j < keySize; j++){
            //Realizamos la sumatoria de la cantidad de numeros correspondidos por el tamLlave(numColumnas) para
            //despues asignar el valor a la posicion que le corresponde al arregle resultado
            suma += cache[(threadIdx.x * keySize) + j];
        }

    //El resultado se almacenara en la posicion que indique su propia indexaxion, antes de almacenarlo se aplicara un mod 256
    resultado[blockIdx.x*blockDim.x+threadIdx.x] = (suma % 256);

    }
}

size_t HillCipher::next_chunk(){
    return fread( chunk, sizeof(unsigned char), buffer_size, file);
}

void HillCipher::clear_chunks(){
    cudaMemset( chunk, 0, buffer_size);
    cudaMemset( newChunk, 0, buffer_size);
}

void HillCipher::copy_key( int *key_vector ){
    /*for( int i=0; i<key_size*key_size; ++i ){
        key[i]=key_vector[i];
    }*/
    cudaMemcpy(key, key_vector, sizeof(int) * key_size * key_size, cudaMemcpyHostToDevice );
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

void HillCipher::apply_key( int *key_vector, Tochfile &tochkey  ){
    //CUDA CONFIG
    dim3 dimBlock( key_size, key_size );
    copy_key(key_vector);
    cudaDeviceSynchronize();
    size_t bytes_readed; 
    while( (bytes_readed=next_chunk()) > 0 ){
        if( bytes_readed != buffer_size ){
            cudaMemset( chunk+bytes_readed, 0, buffer_size-bytes_readed);
        }
        bytes_readed=next_multiple(bytes_readed);
        dim3 dimGrid(bytes_readed);

        //Ejecutar el kernel paralelo
        matrixMultiplication << <dimGrid, dimBlock, sizeof(int)*(key_size*key_size)>> >( chunk, key, newChunk, key_size );
        cudaDeviceSynchronize();
        if( bytes_readed != buffer_size ){
            cudaMemset( newChunk+bytes_readed, 0, buffer_size-bytes_readed);
        }

        //Write back to file
        printf("Writing to file...\n");
        if( bytes_readed != buffer_size ) printf("Last byte: %d %d     bytes read:%zu\n", chunk[bytes_readed-1], newChunk[bytes_readed-1], bytes_readed);
        tochkey.write(newChunk, bytes_readed);
    }
    tochkey.close();
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
    printf("Reading %s\n",path_to_file);
    file = file_ptr;
    file_size = getFileSize(file);
    filename = std::string(basename(path_to_file));
}

HillCipher::HillCipher(  ){
    //Set defaults
    set_defaults();

    //Reserve memory for the chunk 
    cudaMallocManaged( &chunk, sizeof(unsigned char) * buffer_size );
    cudaMallocManaged( &newChunk, sizeof(unsigned char) * buffer_size );
    cudaMallocManaged( &key, sizeof(int) * key_size * key_size );
}

HillCipher::HillCipher( char *path_to_file ){
    //Set defaults
    set_defaults();

    //Reserve memory for the chunk
    cudaMallocManaged( &chunk, sizeof(unsigned char) * buffer_size );
    cudaMallocManaged( &newChunk, sizeof(unsigned char) * buffer_size );
    cudaMallocManaged( &key, sizeof(int) * key_size * key_size );
    //Read file
    read_file(path_to_file);
}



HillCipher::~HillCipher(){
    if( file != NULL )
        fclose(file);
    file=NULL;

    if( chunk != NULL )
        cudaFree(chunk);
    if( key != NULL )
        cudaFree(key);
    if( newChunk != NULL )
        cudaFree(newChunk);
        
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
    buffer_size = 1024 * 1024 * 32;
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