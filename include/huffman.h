#ifndef H_HUFFMAN
#define H_HUFFMAN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "occurences.h"
#include "decode_huffman.h"
#include "tree_lib.h"
#include "liste_lib.h"
#include "bin_io.h"

/**
 * Transforms a table of number of occurences, into a Huffman tree
 */
Tree occToTree(int* tab_occ);

/**
 * Prints the table containing the codes
 */
void dispCodes(char** codes);

/**
 * returns the maximum value according to a char array
 */
int maxDepth(char *tab);

/**
 * Inserts into list the occurences of tab that have the right depth
 */
void getLeafsOfDepth(char *tab, int depth, GlobalList *list);

/**
 * Gives back a table of the binary representation of each symbol, from a huffman tree.
 * the representation are strings of '0' and '1'
 */
char** treeToCode( Tree A);

/**
 * Creates a huffman's tree based on a table of the various sizes of ascii symbols
 */
Tree codeToTree(char *tab);

void makeCanonical(Tree *T);

/**
 * Makes a table of size of symbols from a Tree
 */
int* treeToSize(Tree A);

/**
 * Displays the size of each symbol when not 0
 */
void dispSize(int* tab_size);


/**
 * writes a file filename.hf that hasbeen compressed using the code given
 * in codes.
 * Adding a header of 256 bytes for decoding purpose
 */
char* write(char** codes, char* filename);


/**
 * Return a string of 8 char '0' or '1' corresponding to the binary representation
 * of the next char in f
 * @require !feof(f) and f opened
 */
char* read(FILE *f);

/**
 * Decodes an finput file and produces a decoded fouput file.
 */
char* decodeHF(FILE *finput, char *filename, Tree T,unsigned long long int nbSymb);

/**
 * Compresses a file and writes a "filename.hf" file name (given back)
 */
char* compress(char* filename);

/**
 * Decompresses a file and writes a "filename.unhf" file name (given back)
 */
char* decompress(char* filename);

#endif
