#include "MatrixKey.h"
#include "HillCipher.h"

int main( int argc, char **argv ){
    MatrixKey key(8,256);

    key.createKey();
    key.printKey();


    HillCipher pko(argv[1]);
    std::string outEnc("salidaEnc");

    if( pko.create_output(outEnc) != 0 )
        return 1;
    
    pko.apply_key(key.key);
    

    //pko.apply_key(NULL);
    //pko.print();

    printf("#####################################\n");
    key.inverse();
    key.printKey();
    std::string outDec("salidaDec");
    pko.read_file(argv[2]);

    if( pko.create_output(outDec) != 0 )
        return 1;

    pko.apply_key(key.key);
    
    return 0;
}