#Main Config
HEADERS = MatrixKey.h Tochfile.h#HillCipher.cu
CC=g++
NVCC=nvcc
CFLAGS=-I.
MKDIR=mkdir -p
OBJ_DIR=build/objects
SRC_DIR=src

#Objets to create
OBJS=$(OBJ_DIR)/main.o $(OBJ_DIR)/MatrixKey.o $(OBJ_DIR)/HillCipher.o $(OBJ_DIR)/Tochfile.o

##Main program
all: Tochcrypt

clean:
	rm -rf build

Directories:
	${MKDIR} $(OBJ_DIR)

$(OBJ_DIR)/HillCipher.o: Directories
	$(NVCC) -c -std=c++11 -o $(OBJ_DIR)/HillCipher.o $(SRC_DIR)/HillCipher.cu

$(OBJ_DIR)/MatrixKey.o: Directories
	$(CC) -c -std=c++11 -o $(OBJ_DIR)/MatrixKey.o $(SRC_DIR)/MatrixKey.cpp

$(OBJ_DIR)/Tochfile.o: Directories
	$(CC) -c -std=c++11 -o $(OBJ_DIR)/Tochfile.o $(SRC_DIR)/Tochfile.cpp

$(OBJ_DIR)/main.o: Directories
	$(NVCC) -c -std=c++11 -o $(OBJ_DIR)/main.o $(SRC_DIR)/main.cu

Tochcrypt: $(OBJS)
	$(NVCC) -o Tochcrypt -std=c++11 $(OBJS)

