#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>
#include <inttypes.h>
#include <string.h>
#include <math.h>

#ifndef MATRIX_KEY
#define MATRIX_KEY

class MatrixKey{
public:

    int *key;
    int key_size;
    int mod;
    //Nueva llave
    MatrixKey(int, int);

    //Destructor
    ~MatrixKey();

    //Crear llave a partir de nueva llave
    MatrixKey( int *custom_key, int custom_key_size, int mod );

    //Funcion que aplica la matriz A a la llave B
    void matrixMult8(  uint8_t *A, int *B, uint8_t *C, int N );

    void createKey();

    void inverse();

    void printKey();

private:
 
    //Quasirandom
    int qRandom();

    int gcd ( long long int a, int b );

    //Recursive definition of determinate using expansion by minors.
    int Determinant(int **a,int n);

    //Find the cofactor matrix of a square matrix
    void CoFactor(int **a,int n,int **b);


    //Transpose of a square matrix, do it in place
    void Transpose(int **a,int n);

    //Euclidan module
    int mymod (long long int n, int m);


    //This function will calculate if its an integer number
    bool isInt(double number);

    //Modular Multiplicative Inverse
    ///////////////////////////////////////
    //FORMULA//////////////////////////////
    //      X=( ( MODULE * i) + 1 ) / R  //
    ///////////////////////////////////////
    int modular_inverse_multiplicative(int determinant, int mod);

    /*Apply modular*/
    int *applyModular(int **a, int n, int det, int mod);

    int *getInverseKey( int **key, int size, int mod );

    int **getRandomKey( int **key, int size, int mod );

    int **createRandomKey( int size, int mod );

    void printV( int *vect, int size );

    void printM( int **mat, int size );

    void freeMat( int **key, int size );

    

    //Funcion que aplica la matriz A a la llave B
    void matrixMult16(long long unsigned int *C, uint16_t *B, int *A, int N, int mod );

    int *key2Dto1D( int **matrix, int size);

    int **key1Dto2D( int *vector, int size);

};

#endif

