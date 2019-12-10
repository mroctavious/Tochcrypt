#Main Config
HEADERS = MatrixKey.h Tochkey.h #HillCipher.cu
CC=g++
NVCC=nvcc
CFLAGS=-I.
MKDIR=mkdir -p
OBJ_DIR=build/objects
SRC_DIR=src

#Objets to create
OBJS_CUDA=$(OBJ_DIR)/mainCUDA.o $(OBJ_DIR)/HillCipherProccessCUDA.o $(OBJ_DIR)/HillCipherCUDA.o $(OBJ_DIR)/Tochkey.o $(OBJ_DIR)/MatrixKey.o
OBJS_SEQ=$(OBJ_DIR)/main.o $(OBJ_DIR)/HillCipherProccess.o $(OBJ_DIR)/HillCipher.o $(OBJ_DIR)/Tochkey.o $(OBJ_DIR)/MatrixKey.o

##Main program
default: TochcryptSeq

cuda: Tochcrypt


clean:
	rm -rf build 2>&1 > /dev/null
	rm Tochcrypt 2>&1 > /dev/null

Directories:
	${MKDIR} $(OBJ_DIR)

$(OBJ_DIR)/HillCipherProccessCUDA.o: Directories
	$(NVCC) -c -std=c++11 -o $(OBJ_DIR)/HillCipherProccessCUDA.o $(SRC_DIR)/HillCipherProccess.cu

$(OBJ_DIR)/HillCipherCUDA.o: Directories
	$(NVCC) -c -std=c++11 -o $(OBJ_DIR)/HillCipherCUDA.o $(SRC_DIR)/HillCipher.cu

$(OBJ_DIR)/HillCipherProccess.o: Directories
	$(CC) -c -std=c++11 -o $(OBJ_DIR)/HillCipherProccess.o $(SRC_DIR)/HillCipherProccess.cpp

$(OBJ_DIR)/HillCipher.o: Directories
	$(CC) -c -std=c++11 -o $(OBJ_DIR)/HillCipher.o $(SRC_DIR)/HillCipher.cpp

$(OBJ_DIR)/MatrixKey.o: Directories
	$(CC) -c -std=c++11 -o $(OBJ_DIR)/MatrixKey.o $(SRC_DIR)/MatrixKey.cpp

$(OBJ_DIR)/Tochkey.o: Directories
	$(CC) -c -std=c++11 -o $(OBJ_DIR)/Tochkey.o $(SRC_DIR)/Tochkey.cpp

$(OBJ_DIR)/mainCUDA.o: Directories
	$(NVCC) -c -std=c++11 -o $(OBJ_DIR)/mainCUDA.o $(SRC_DIR)/main.cu

$(OBJ_DIR)/main.o: Directories
	$(CC) -c -std=c++11 -o $(OBJ_DIR)/main.o $(SRC_DIR)/main.cpp

Tochcrypt: $(OBJS_CUDA)
	$(NVCC) -o Tochcrypt -std=c++11 $(OBJS_CUDA)

TochcryptSeq: $(OBJS_SEQ)
	$(CC) -o Tochcrypt -std=c++11 $(OBJS_SEQ)