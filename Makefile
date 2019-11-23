#Main Config
HEADERS = MatrixKey.h Tochkey.h#HillCipher.cu
CC=g++
NVCC=nvcc
CFLAGS=-I.
MKDIR=mkdir -p
OBJ_DIR=build/objects
SRC_DIR=src

#Objets to create
OBJS=$(OBJ_DIR)/main.o $(OBJ_DIR)/MatrixKey.o $(OBJ_DIR)/HillCipher.o $(OBJ_DIR)/Tochkey.o $(OBJ_DIR)/HillCipherProccess.o

##Main program
all: Tochcrypt

clean:
	rm -rf build 2>&1 > /dev/null
	rm Tochcrypt 2>&1 > /dev/null

Directories:
	${MKDIR} $(OBJ_DIR)

$(OBJ_DIR)/HillCipherProccess.o: Directories
	$(NVCC) -c -std=c++11 -o $(OBJ_DIR)/HillCipherProccess.o $(SRC_DIR)/HillCipherProccess.cu

$(OBJ_DIR)/HillCipher.o: Directories
	$(NVCC) -c -std=c++11 -o $(OBJ_DIR)/HillCipher.o $(SRC_DIR)/HillCipher.cu

$(OBJ_DIR)/MatrixKey.o: Directories
	$(CC) -c -std=c++11 -o $(OBJ_DIR)/MatrixKey.o $(SRC_DIR)/MatrixKey.cpp

$(OBJ_DIR)/Tochkey.o: Directories
	$(CC) -c -std=c++11 -o $(OBJ_DIR)/Tochkey.o $(SRC_DIR)/Tochkey.cpp

$(OBJ_DIR)/main.o: Directories
	$(NVCC) -c -std=c++11 -o $(OBJ_DIR)/main.o $(SRC_DIR)/main.cu

Tochcrypt: $(OBJS)
	$(NVCC) -o Tochcrypt -std=c++11 $(OBJS)

