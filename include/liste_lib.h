#ifndef H_LISTE_LIB
#define H_LISTE_LIB


#include <stdio.h>
#include <stdlib.h>
#include "tree_lib.h"


#define MAX_SYM 256

typedef struct ListNode ListNode;

typedef struct ListNode{
	Tree tree;
	ListNode* next;
} *List;

typedef struct GlobalList {
	ListNode* begin;
	ListNode* end;
} GlobalList;

/** Initialise a Global List */
GlobalList* GlobalListInit();

/** Initialise a List Node by creating a leaf int he first cell */
ListNode* listNodeInit(int symb,int occ);

/** Gets the first element of a global List*/
Tree getFirstElem(GlobalList *L);

/**
 * Transforms an occurence table into a list.
 * This list has adresses leading to leaves
 * The leaves contain a couple of (symbol,numberOfOccurences)
 * only is nbOcc > 0
 * This list is ORDERED in terms of occurences
 */
GlobalList* completeList(int* tab_occurences);

/**
 * Insert a Tree into the list depending of the number of occurences
 * of the root of this tree
 * @require tree != NULL
 */
void insertionOnList(GlobalList *L,Tree tree);

/**
 * Insert a Tree into the list depending of the symbol
 * of the root of this tree
 * @require tree != NULL
 */
void insertOnSymbol(GlobalList *L,Tree tree);

/**
 * Reverse insertion
 */
void insertOnSymbolD(GlobalList *L,Tree tree);

//head/queu insertion
void insertOnHead(GlobalList *L,Tree tree);
void insertOnQueu(GlobalList *L,Tree tree);

/**
 * Displays a List
 */
void dispList(GlobalList *L);

/**
 * Just a free function
 */
void freeList(GlobalList *L);


#endif
