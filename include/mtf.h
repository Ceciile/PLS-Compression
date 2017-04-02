#ifndef H_MTF
#define H_MTF

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define NBCHAR 256

void printList(char* list); //show the list of char
void printASCII(); //show the ASCII character
void initList(char* list); //initialize the list of char
void moveElem(int indice,char* list); //put the element at the indice in the head
char* moveToFront(const char* f); //use moveElem to ajust the list and repeat the operation to compress
char* unMoveToFront(const char* f); //use moveElem to ajust the list and decompress

#endif
