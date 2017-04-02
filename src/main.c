#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../include/rle.h"
#include "../include/mtf.h"
#include "../include/huffman.h"

#define DEBUG 0

//realization of the main
int main (int argc, char *argv[]){

	//declaration of the variable
	int premethod;
	char *mtfOutput, *preOutput, *rleOutput, *huffmanOutput, *finalOutput;
	int docompress;
	int usehuff;

	//timeexec calculation
	clock_t t1, t2, tf;

	//verification of the given arguments
	if(argc!=2){
		fprintf(stderr,"Please give the name of the file you want to use in parameter.\n");
		exit(1);
	}

	do {
		printf("Choose what to do : \n 1 : Compress\n 2 : Decompress\n");
		scanf("%d", &docompress);
	} while (docompress != 1 && docompress != 2);
	
	do {
		printf("Choose what to do : \n 1 : Use huffman\n 2 : Don't use huffman\n");
		scanf("%d", &usehuff);
	} while (usehuff != 1 && usehuff != 2);

	char *fileName = argv[1];

	//opening of the file to compress
	FILE* f;
	f = fopen(fileName, "r");
	if (f==NULL){
		fprintf(stderr,"Couldn't open the file\n");
		exit(2);
	}

	//choice of the precompression option
	printf("Choose the options of precoding : 1 for RLE , 2 for MFT , 3 for both, 0 for none\n");
	scanf(" %d",&premethod);

	t1 = clock();

	if(docompress == 1) { //Compression
		switch (premethod){
			case 2 :
				printf("Filename : %s\n", fileName);
				mtfOutput = moveToFront(fileName);										// Call MTF
				printf("mtfOutput : %s\n", mtfOutput);
				preOutput = mtfOutput;
				break;
			case 3 :
				mtfOutput = moveToFront(fileName);										// Call MTF & RLE
				preOutput = mtfOutput;
			case 1 :
				if(premethod == 3) {rleOutput = execRLE(mtfOutput);}		// Call RLE
				else {rleOutput = execRLE(fileName);}
				preOutput = rleOutput;
				break;
			default :
				preOutput = fileName;
				printf("preOut : %s\n", preOutput);
				break;
		}
		if(usehuff==1){
			//Compressing with huffman
			printf("Compressing with huffman.\n");
			huffmanOutput = compress(preOutput);
			printf("Compressed file : %s\n",huffmanOutput);
		} else {
			huffmanOutput = preOutput;
		}
	} else {// uncompression
		if(usehuff==1){
			//Uncompressing with huffman
			printf("Decompressing with huffman.\n");
			huffmanOutput = decompress(fileName);
			preOutput = huffmanOutput;
		} else {
			preOutput = fileName;
		}
		switch (premethod){
			case 1 :
				printf("preOut : %s\n", preOutput);
				if(premethod == 1) {rleOutput = unexecRLE(preOutput); break;}		// Call RLE
				else {rleOutput = unexecRLE(preOutput); preOutput = rleOutput; }
			case 2 :
			case 3 :
				printf("preOut : %s\n", preOutput);
				mtfOutput = unMoveToFront(preOutput);										// Call MTF & RLE
				printf("mtfOut : %s\n", mtfOutput);
				preOutput = mtfOutput;
			default :
				printf("finalOut : %s\n", finalOutput);
				finalOutput = preOutput;
				break;
		}
		printf("Uncompressed file : %s\n",finalOutput);
	}
	t2 = clock();
	tf = t2-t1;
	printf("Temps d'exécution : %d secondes\n", (tf / 1000000));
	//▓░

	return 0;
}
