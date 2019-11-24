#include <iostream>
#include <string>
#include <vector>
#include "HillCipherProccess.h"

static void show_usage(std::string name)
{
    std::cerr << "Tochcrypt\n"
              << "Usage: " << name << " <option(s)> FILE\n"
              << "Options:\n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t-e,--encrypt INPUT_FILE\tSpecify the file path\n"
              << "\t-d,--decrypt ENCRYPTED_FILE\tSpecify the file path\n"
              << "\t-k,--key KEY_FILE\tSpecify the file path\n"
              << std::endl;
}

int main( int argc, char **argv ){
    if (argc < 3) {
        show_usage(argv[0]);
        return 1;
    }

    char *input_file=NULL;
    char *output_file=NULL;
    char *key_file=NULL;

    bool encrypt_option=false;
    bool decrypt_option=false;
    bool key_option=false;
    bool output_option=false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ( (arg == "-h") || (arg == "--help") ) {
            show_usage(argv[0]);
            return 0;
        } else if ( (arg == "-e") || (arg == "--encrypt") ) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                i++;
                input_file = argv[i]; // Increment 'i' so we don't get the argument as the next argv[i].
                encrypt_option=true;
            } else { // Uh-oh, there was no argument to the destination option.
                  std::cerr << "--encrypt option requires one argument." << std::endl;
                return 1;
            }
        } else if ( (arg == "-k") || (arg == "--key") ) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                i++;
                key_file = argv[i]; // Increment 'i' so we don't get the argument as the next argv[i].
                key_option=true;
            } else { // Uh-oh, there was no argument to the destination option.
                  std::cerr << "--key option requires one argument." << std::endl;
                return 1;
            }
        } else if ( (arg == "-d") || (arg == "--decrypt") ) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                i++;
                input_file = argv[i]; // Increment 'i' so we don't get the argument as the next argv[i].
                decrypt_option=true;
            } else { // Uh-oh, there was no argument to the destination option.
                  std::cerr << "--decrypt option requires one argument." << std::endl;
                return 1;
            }
        }

        else if ( (arg == "-o") || (arg == "--output") ) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                i++;
                output_file = argv[i]; // Increment 'i' so we don't get the argument as the next argv[i].
                output_option = true;
            } else { // Uh-oh, there was no argument to the destination option.
                  std::cerr << "--decrypt option requires one argument." << std::endl;
                return 1;
            }
        }
    }
    
    //Do instructions depending with args
    if( encrypt_option && output_option ){
        
        HillCipherProccess HC;
        std::string out=output_file;
        HC.encrypt(input_file, out);
    }
    else if( decrypt_option && key_option && output_option ){
        HillCipherProccess HC;
        std::string out(output_file);
        std::string key_str(key_file);
        HC.decrypt(input_file, key_str, out);
    }
    else{
        printf("Wrong usage...");
        show_usage(argv[0]);
        return 1;
    }
    return 0;
}
