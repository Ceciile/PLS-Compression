CC=gcc -O2
CFLAGS=-W -Wall -I ./include -ansi -pedantic -std=c99

HUFF = ./src/huffman/huffman.o  ./src/huffman/decode_huffman.o ./src/huffman/occurences.o
LIB =  ./lib/bin_io.o ./lib/tree_lib.o ./lib/liste_lib.o
MTF = ./src/MTF/mtf.o
RLE = ./src/RLE/rle_repe.o

#OBJS= ./src/main.o ./src/huffman/test_hf.o ./src/huffman/huffman.o  ./src/huffman/decode_huffman.o ./src/huffman/occurences.o ./lib/bin_io.o ./lib/tree_lib.o ./lib/liste_lib.o ./src/MTF/mtf.o ./src/RLE/rle_repe.o
OBJS = ./src/main.o ./src/huffman/test_hf.o $(HUFF) $(LIB) $(RLE) $(MTF)
SRCS= $(OBJS:.o=.c)

EXEC=  ./bin/test_hf.exe compress

all: $(EXEC)

compress:  ./src/main.o $(RLE) $(MTF) $(HUFF) $(LIB)
	@echo "------------------------------------------------------------"
	@echo "Création de l'éxécutable bin/main.exe"
	@echo "------------------------------------------------------------"
	$(CC) -o ./bin/main.exe $(CFLAGS) $< $(RLE) $(MTF) $(HUFF) $(LIB)
	
./bin/test_hf.exe : ./src/huffman/test_hf.o  ./src/huffman/huffman.o  ./src/huffman/decode_huffman.o ./src/huffman/occurences.o ./lib/bin_io.o ./lib/tree_lib.o ./lib/liste_lib.o
	@echo "------------------------------------------------------------"
	@echo "Création de l'éxécutable $@"
	@echo "------------------------------------------------------------"
	$(CC) $(CFLAGS) ./src/huffman/test_hf.o  ./src/huffman/huffman.o  ./src/huffman/decode_huffman.o ./src/huffman/occurences.o ./lib/bin_io.o ./lib/tree_lib.o ./lib/liste_lib.o -o $@


clean :
	@echo "Suppression des objets, des fichiers compressés et décompressés"
	-rm $(OBJS) tests/*.hf tests/*.unhf tests/*.rle tests/*.unmtf tests/*.mtf
	
rmexec :
	@echo "Suppression des executables"
	-rm *.exe
