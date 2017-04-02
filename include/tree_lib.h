#ifndef H_TREE_LIB
#define H_TREE_LIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Types definition
typedef struct Couple Couple;
struct Couple{
	int symbol;
	int nbOcc;
};

typedef struct Nod Nod;
struct Nod{
	Couple c;
	Nod *ls; // left son
	Nod *rs; // right son
};

typedef struct Nod* Tree;

/* Creating and removing trees */
Tree initTree(Couple c);

void removeTree(Tree A);


/* Displaying a Tree */
/**
 * Displays a Nod
 */
void dispNod(Tree A);

/**
 * Displays a Tree
 */
void dispTree(Tree A);

/* Adding nods to the tree */
/**
 * This function creates a Nod from a couple and gives back the adress of that Nod.
 * Same as initTree
 */
Tree createNod(Couple c);

/**
 * Creates a couple from a symbol and a number of occurences
 */
Couple createCouple(int symbol, int nbOcc);

 /**
  * Creates a sub tree from two Trees, putting them in alphabetical order
  * @require t1 != NULL && t2!= NULL
  */
Tree createSubTree(Tree t1, Tree t2);

// Test //
/**
 * Returns true if the tree only has a leaf
 */
int isLeaf(Tree A);
int isNode(Tree A);

/**
 * returns the depth of a tree | 0 if no node, 1 for 1 node
 */
int depth(Tree A);

#endif
