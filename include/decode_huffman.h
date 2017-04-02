#ifndef H_TREE_FROM_LENGTH
#define H_TREE_FROM_LENGTH

#include <stdio.h>
#include <stdlib.h>
#include "tree_lib.h"
#include "liste_lib.h"
#include "occurences.h"

/**
 * Reads the header to know the size of each symbol
 * @returns a table, t[i] = size of the symbol i
 */
int* readSize(FILE *f);

/**
 * Reads the number of symbols coded in the file
 */
unsigned long long int readNbSymb(FILE *f);

/**
 * Gives the canonical tree corresponding to the table of the sizes of the code
 */
Tree sizeToTree(int* tab_size);

#endif
