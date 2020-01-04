# Tochcrypt

[![N|Solid](https://tochcrypt.tk/static/img/TochcryptNegroPeque.png)](https://tochcrypt.tk/)

# Author:
Eric Octavio Rodriguez Garcia (Mroctavious)
- [LinkedIn](https://www.linkedin.com/in/eric-octavio-rodríguez-garcia-a3058919a)
- [Github](https://github.com/mroctavious)

# Abstract
Encryption is a process to protect the data by means of an encryption associated with a key so that the information is not visible, this with the aim of protecting the information of third parties that are not authorized to view it, for this we use a symmetric encryption algorithm called Hill Cipher (HC). The HC algorithm fits perfectly to the resolution of the problem since it is used with an N * N matrix to encrypt the data of a file.

- This kind of encryption can help people to share evidence of corruption without the risk of the message being intercepted.
- Can help you to keep your nudes safe.
- Only the person with the key can view the content of the file.

This a project I have been working during my studies at the university, here is the article:
Revista NTHE, 23: 1-5, 2018
ISSN: 2007-9079
http://nthe.mx/archivos/revista23.php

# New Features!

  - Now you can encrypt any kind of file, no matter the format.
  - Created a parallel version for the use of tegra devices with CUDA.
# Details:
- Works incredibly fast using "Unified Memory" in Nvidia Jetson devices.
- It is an artisan work since I programmed it with standard libraries. You should not have problems with compilation and dependencies.
- Using the power of C++ and C to provide a very fast program with very low memory consumption.
- It creates a shared library so you can include Tochcrypt to your other programs.

#### Building for source
First clone the repository:
```sh
$ git clone https://github.com/mroctavious/Tochcrypt.git
```

For production release under any Linux distro. This command will create executable(***Tochcrypt***) and also a shared library called libtochcrypt.so in the PREFIX folder(Default:/usr/local):
```sh
$ sudo make install
```

To create the program using the power of Nvidia GPUs with CUDA. This command will create executable(***Tochcrypt***) in the current folder
```sh
$ make cuda
```

To create the program under OSX. This command will create executable(***Tochcrypt***) in the current folder
```sh
$ make osx
```

### Using the software
When you compile the source code it will generate an executable program called ***Tochcrypt***.
```sh
$ Tochcrypt --help
```

### Encrypting

To encrypt a file just execute the following command, replacing "PATH/TO/FILE" with the path to your file to be encrypted and "PATH/TO/OUTPUT_NAME" with the name of the output generated.
The program will generate 2 output files:
- OUTPUT_NAME
  - Encrypted File
- OUTPUT_NAME.tochkey
  - Key file. This file is the "key" to open the encrypted file and read the original content
```sh
$ Tochcrypt -e PATH/TO/FILE -o PATH/TO/OUTPUT_NAME
```

### Decrypting
To restore the original file, it must go through a decryption process. To do this use the --decrypt(-d) and --key(-k) options, just execute the following command, replacing "PATH/TO/ENCRYPTED_FILE" with the path to your encrypted file, "PATH/TO/KEY_FILE" with the path to the key file(***.tochkey***) and "PATH/TO/OUTPUT_NAME" with the name of the output generated.
The program will generate 1 output file:
- OUTPUT_NAME
  - Decrypted file. It is the original file.
```sh
$ Tochcrypt -d PATH/TO/ENCRYPTED_FILE -k PATH/TO/KEY_FILE \ 
-o PATH/TO/OUTPUT_NAME
```
### Using the shared library


### Todos

 - Write version for GPUs not capable of using Unified Memory
 - Implement the proposed Gauss-Jacques method to obtain modular inverse matrices variable sized without a theoretical limit. This will allow us to create very big matrix keys, doing the processs unhackable using brute force. (https://www.researchgate.net/publication/327895519_The_proposed_Gauss-Jacques_method_to_obtain_modular_inverse_matrices_variable_sized_without_a_theoretical_limit)
 

License
----
MIT License

Copyright (c) 2020 Eric Octavio Rodriguez Garcia

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


**FEED YOUR HEAD**
[![N|Solid](https://tochcrypt.tk/static/img/coatlicue.png)](https://tochcrypt.tk/)
***Coatlicue***

