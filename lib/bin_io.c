
// Fonction pour passer en binaire un char http://stackoverflow.com/questions/4892579/how-to-convert-a-char-to-binary
#include "../include/bin_io.h"


//Read a bit from an x character, numbit is the offset of the bit from the left
char readBit(int numbit, char x){
    if(numbit>7){printf("Error : Trying to read a bit not in 0..7 range"); exit(1);}
    return ((x >> numbit) & 1);
}


//Set a bit of an x char, numbit is the offset of the bit from the left, value is the 1 or 0 bit to set
void setBit(int numbit, char* x, char value){
    if(numbit>7){printf("Error : Trying to set a bit not in 0..7 range\n"); exit(1);}
	char cop = 1 << numbit;
    char op = ~cop;
    *x = *x & op;
	if(value==1){*x = *x | cop;}
}

//display the binary of the x character, on 8 bits
void displayBinary(char x){
	for(int i=7;i>=0;i--){
		printf("%d",readBit(i,x));
	}
}



/*////////// FILE METHOD \\\\\\\\\\\\ */
//All char array have a size of 8(un byte)

void writeByte(FILE* f, char* x){
	char z = 0;
	for(int i=0;i<8;i++){
		z = z << 1;
		setBit(0,&z,x[i]);
	}
	fputc(z,f);
}

char* readByte(FILE* f){
	char c = fgetc(f);
	char *x = malloc(sizeof(char)*7);
	for(int i=7;i>=0;i--){
		x[7-i]=readBit(i,c);
	}
	return x;
}
