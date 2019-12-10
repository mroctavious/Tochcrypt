#include "MatrixKey.h"

MatrixKey::MatrixKey( int sqr_size, int modulus ){
    key = NULL;
    key_size = sqr_size;
    mod=modulus;
}

MatrixKey::~MatrixKey( ){
    if ( key != NULL ) free(key);
}

void MatrixKey::createKey(){
    if( key != NULL )
        free(key);
    //Create a quasirandom key
    int **keyMatrix=createRandomKey(key_size, mod);

    //Transform the 2D key to a single big vector
    key=key2Dto1D(keyMatrix, key_size);

}
MatrixKey::MatrixKey( int *custom_key, int custom_key_size, int custom_mod ){
    key = (int*)malloc(sizeof(int)*custom_key_size*custom_key_size);

    //Copiar llave a key
    memcpy(key, custom_key, sizeof(int)*custom_key_size*custom_key_size);
    mod = custom_mod;
    key_size = custom_key_size;
}

void MatrixKey::inverse(){
    int **matrixKey=key1Dto2D(key, key_size);
    key=getInverseKey( matrixKey, key_size, mod);
}

void MatrixKey::printKey(){
    printV(key, key_size);
}

//Quasirandom
int MatrixKey::qRandom()
{
    srand(  rand() );
    srand(  rand() );
    srand(  rand() );
    srand(  rand() );
    return rand();
}

int MatrixKey::gcd ( long long int a, int b )
{
    int c;
    while ( a != 0 )
    {
        c = a; a = b%a;  b = c;
    }
    return b;
}
//Recursive definition of determinate using expansion by minors.
int MatrixKey::Determinant(int **a,int n)
{
    int i,j,j1,j2;
    long long int det = 0;
    int **m = NULL;

    if (n < 1)
    {
        //Error
        //Caso Base
    }
    else if (n == 1) //Caso base, solo 1 elemento
    {
        //Shouldnt get used
        det = a[0][0];
    }
    else if (n == 2)
    {
        det = a[0][0] * a[1][1] - a[1][0] * a[0][1];
    }
    else
    {
        det = 0;
        for (j1=0;j1<n;j1++)
        {
            m = (int**)malloc((n-1)*sizeof(int *));
            for (i=0;i<n-1;i++)
                m[i] = (int*)malloc((n-1)*sizeof(int));
            for (i=1;i<n;i++)
            {
                j2 = 0;
                for (j=0;j<n;j++)
                {
                    if (j == j1)
                        continue;
                    m[i-1][j2] = a[i][j];
                    j2++;
                }
            }

            //Recursion
            det += pow(-1.0,j1+2.0) * a[0][j1] * Determinant(m,n-1);
            for (i=0;i<n-1;i++)
                free(m[i]);
            free(m);
        }
    }

    return(det);
}

//Find the cofactor matrix of a square matrix
void MatrixKey::CoFactor(int **a,int n,int **b)
{
    int i,j,ii,jj,i1,j1;
    int det;
    int **c;

    c = (int**)malloc((n-1)*sizeof(int *));
    for (i=0;i<n-1;i++)
        c[i] = (int*)malloc((n-1)*sizeof(int));

    for (j=0;j<n;j++)
    {
        for (i=0;i<n;i++)
        {
            //Form the adjoint a_ij
            i1 = 0;
            for (ii=0;ii<n;ii++)
            {
                if (ii == i)
                    continue;
                j1 = 0;
                for (jj=0;jj<n;jj++)
                {
                    if (jj == j)
                        continue;
                    c[i1][j1] = a[ii][jj];
                    j1++;
                }
                i1++;
            }

            /* Calculate the determinate */
            det = Determinant(c,n-1);

            /* Fill in the elements of the cofactor */
            b[i][j] = pow(-1.0,i+j+2.0) * det;
        }
    }
    for (i=0;i<n-1;i++)
        free(c[i]);
    free(c);
}


//Transpose of a square matrix, do it in place
void MatrixKey::Transpose(int **a,int n)
{
int i,j;
int tmp;

    for (i=1;i<n;i++)
    {
        for (j=0;j<i;j++)
        {
            tmp = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = tmp;
        }
    }
}


//Euclidan module
int MatrixKey::mymod (long long int n, int m)
{
    if( n < 0 )
    {
        if ( ((n % m) + m) == m )
        {
            return 0;
        }
        else
        {
            return ((n % m) + m);
        }
    }
    else
    {
        return n % m;
    }
}


//This function will calculate if its an integer number
bool MatrixKey::isInt(double number)
{
    int integer=(int) number;
    return (number == integer);
}

//Modular Multiplicative Inverse
int MatrixKey::modular_inverse_multiplicative(int determinant, int mod)
{
    ///////////////////////////////////////
    //FORMULA//////////////////////////////
    //      X=( ( MODULE * i) + 1 ) / R  //
    ///////////////////////////////////////
    //printf("modular_inverse_multiplicative now1\nDeterminant:%d\n",determinant);

    //Iterator variable
    int i;
    //printf("modular_inverse_multiplicative now2\n");
    //Get the euclidan module of the determinant and save it in r, this will be used to get the inverse(part of the formula).
    int r=mymod(determinant, mod);
    //printf("modular_inverse_multiplicative now3\n");

    //Applying brute force to get the number which will feet to the first INTEGER number
    for(i=1; i<9457; i++)
    {
        //Apply the formula
        double x=( ( (double) mod * (double) i ) + 1 ) / (double) r;

        //printf("x=( ( %d * %d ) + 1 ) / %d\n",MODULE,i,r);
        //printf("x=%f\n",x);

        //Check if its an integer number
        if(isInt(x) == true)
        {
            return (int) x;
        }
    }
    return 0;
}

/*Apply modular*/
int *MatrixKey::applyModular(int **a, int n, int det, int mod)
{
    int *inverse_array=(int*)malloc( sizeof(int) * n*n );
    int i,j;
    for( i=0; i<n; i++ )
        for( j=0; j<n; j++)
            a[i][j]=mymod(a[i][j], mod);

    int mim=modular_inverse_multiplicative(det, mod);

    for(i=0;i<n;i++)
    {
        for( j=0; j<n; j++)
        {
            inverse_array[i*n+j]=mymod((mim * a[i][j]), mod );
        }
    }
    return inverse_array;

}

int *MatrixKey::getInverseKey( int **key, int size, int mod )
{
    //Reservar memoria para matriz de cofactores
        int **coFact =(int **)malloc( sizeof(int*) * size );
    int i=0;
    for( i=0; i<size; i++ )
    {
        coFact[i]=(int*)malloc(sizeof(int) * size );
    }

    //Calcular determinante
    int determinant=Determinant( key, size);

    //Calcular matriz de cofactores
    CoFactor( key, size, coFact );

    //Transpuesta de la matriz
    Transpose( coFact, size );

    //Aplicamos el modulo(Aqui el truco de la matriz inversa MODULAR)
    int *inverseMatrix=applyModular( coFact, size, determinant, mod);

    //Liberar memoria para matriz de cofact
    for( i=0; i<size; i++ )
        free(coFact[i]);
    free(coFact);
    freeMat(key, size);
    return inverseMatrix;
}

int **MatrixKey::getRandomKey( int **key, int size, int mod )
{
    int i=0, j=0;
    int tries=0;
    while( 1 )
    {
        for( i=0; i<size; ++i )
            for( j=0; j<size; ++j )
            {
                key[i][j]=qRandom() % mod;
            }

        //Get determinant of the key
        int det=Determinant(key, size);

        //If its a HC compatible key
        if( gcd(det,mod) == 1 )
        {
            if( modular_inverse_multiplicative(det, mod) != 0 )
                return key;
        }

        //printf( "\rKeys Tried: %d      GCD:%d  \n ", ++tries, gcd( Determinant(key, size), mod ) );
    }


}

int **MatrixKey::createRandomKey( int size, int mod )
{
    //Reservar memoria para la llave
    int **key =(int **)malloc( sizeof(int*) * size );
    int i=0;
    for( i=0; i<size; ++i )
    {
        //Reservar memoria para la 2da dim de la llave
        key[i]=(int*)malloc(sizeof(int) * size );

        //Limpiar de basura
        memset( key[i], 0, sizeof(int) * size );

    }

    //Cambiar la semilla
    srand( (int)time(NULL) );
    //Crear llave y regresarla
    return getRandomKey( key, size, mod );
}

void MatrixKey::printV( int *vect, int size )
{
    int i=0, j=0;
    for( i=0; i<size; ++i )
    {
        for( j=0; j<size; ++j )
            printf("%d ", vect[i*size+j]);
        printf("\n");
    }

}

void MatrixKey::printM( int **mat, int size )
{
    int i=0, j=0;
    for( i=0; i<size; ++i )
    {
        for( j=0; j<size; ++j )
            printf("%d ", mat[i][j]);
        printf("\n");
    }

}

void MatrixKey::freeMat( int **key, int size )
{
    int i=0;
    for( i=0; i<size; ++i )
    {
        free(key[i]);
    }
    free(key);

}

//Funcion que aplica la matriz A a la llave B
void MatrixKey::matrixMult8(  uint8_t *A, int *B, uint8_t *C, int N )
{
    int i,j;
    int tmp[N]={0};
    //memset(tmp, 0, sizeof(int) * N);

    //Multiply the key
    for(i = 0; i < N; ++i)
    {
        for(j = 0; j < N; ++j)
        {
                tmp[i] += (int)A[j] * B[i*N+j];
        }
        C[i]=tmp[i]%mod;
    }


}

//Funcion que aplica la matriz A a la llave B
void MatrixKey::matrixMult16(long long unsigned int *C, uint16_t *B, int *A, int N, int mod )
{
    int i,j;
    //Multiply the key
    for(i = 0; i < N; ++i)
    {
        for(j = 0; j < N; ++j)
        {
                C[i] += A[i*N+j] * B[j];
        }
    }
/*  for( i=0; i<N; ++i)
    {
        C[i]=mymod(C[i], mod) - 32768;
    }
*/
}

int *MatrixKey::key2Dto1D( int **matrix, int size)
{
    //Reserve memory for the lineal
    int *vector=(int *)malloc(sizeof(int) * size*size );
    int i,j;
    for( i=0; i<size; ++i )
    {
        for( j=0; j<size; ++j )
        {
            vector[i*size+j]=matrix[i][j];
        }
    }
    freeMat(matrix, size);
    return vector;
}
int **MatrixKey::key1Dto2D( int *vector, int size)
{
    //Reserve memory for the lineal
    int **matrix=(int **)malloc(sizeof(int*) * size );
    int i,j;
    for( i=0; i<size; ++i )
    {
        matrix[i]=(int*)malloc(sizeof(int) * size );
        for( j=0; j<size; ++j )
        {
            matrix[i][j]=vector[ i*size+j ];
        }
    }
    free(vector);
    return matrix;
}

