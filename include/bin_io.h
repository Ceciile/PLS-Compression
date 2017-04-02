#ifndef H_BIN_IO
#define H_BIN_IO


#include <stdio.h>
#include <stdlib.h>

void setBit(int numbit, char* x, char value);
char readBit(int numbit, char x);
void displayBinary(char x);
void writeByte(FILE* f, char* x);
char* readByte(FILE* f);

#endif

