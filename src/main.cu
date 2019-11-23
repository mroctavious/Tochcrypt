#include "MatrixKey.h"
#include "HillCipher.h"
#include "Tochfile.h"

int main( int argc, char **argv ){
    MatrixKey key(8,256);

    /*
    std::string inp(argv[1]);
    Tochfile llave(inp);
    llave.print();
    printf("-----------------\n");
    MatrixKey customKey(llave.main_key, llave.keySize, llave.mod);
    customKey.printKey();
    customKey.inverse();
    customKey.printKey();
    */

    /*
    key.createKey();
    key.printKey();

    HillCipher pko(argv[1]);
    std::string outEnc("salidaEnc");

    size_t org_size=pko.file_size;
    size_t enc_size=pko.next_multiple(org_size);
    Tochfile llave( key.key, 8, outEnc, enc_size, org_size);
    
    if( pko.create_output(outDec) != 0 )
        return 1;
    pko.apply_key(key.key, llave);
    

    //pko.apply_key(NULL);
    //pko.print();*/
/*
    printf("#####################################\n");
    key.inverse();
    key.printKey();
    std::string outDec("salidaDec");
    pko.read_file(argv[2]);

    if( pko.create_output(outDec) != 0 )
        return 1;

    pko.apply_key(key.key);
    */
    return 0;
}