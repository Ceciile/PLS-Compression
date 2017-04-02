#include "../include/tree_lib.h"


/* Creating and removing trees */
Tree initTree(Couple c){
	Tree A;
	A = malloc(sizeof(Nod));
	A -> ls = NULL;
	A -> rs = NULL;
	A -> c = c;
	return A;
}

void removeTree(Tree A){
	if (A!= NULL){
		if(isLeaf(A)){
			free(A);
		} else {
			removeTree(A->ls);
			removeTree(A->rs);
			free(A);
		}
	}
}

/* Displaying a Tree */
/**
 * Displays a Nod
 */
void dispNod(Tree A){
	if((A->c.symbol > 31) && (A->c.symbol < 126)){
		printf("   %c | %d \n",A->c.symbol, A->c.nbOcc);
	} else {
		printf("0x%03x| %d \n",A->c.symbol, A->c.nbOcc);
	}
}

/**
 * Displays a Tree
 */
void dispTree(Tree A) {
	char esp[20];
	esp[0]=0;


	void aux(Tree A,char *esp){
		char newesp[20];
		strcpy(newesp,esp);
		if (A != NULL){
			strcat(newesp,"\t");

			if(A->rs!=NULL){
				aux(A->rs,newesp);
			}

			printf("%s", esp); dispNod(A);

			if(A->ls!=NULL){
				aux(A->ls,newesp);
			}
		}
	}

	aux(A,esp);
}

/* Adding nods to the tree */
/**
 * This function creates a Nod from a couple and gives back the adress of that Nod.
 * Same as initTree
 */
Tree createNod(Couple c){
	return initTree(c);
}

/**
 * Creates a couple from a symbol and a number of occurences
 */
 Couple createCouple(int symbol, int nbOcc){
	Couple c;
	c.symbol = symbol;
	c.nbOcc = nbOcc;
	return c;
 }

 /**
  * Creates a sub tree from two Trees, putting them in alphabetical order
  * @require t1 != NULL && t2!= NULL
  */
Tree createSubTree(Tree t1, Tree t2){
	Tree A;

	if( (t1 == NULL) || (t2 == NULL)){
		fprintf(stderr,"createSubTree : empty leaves\n");
		exit(1);
	}

	A = createNod(createCouple(256,(t1->c.nbOcc+t2->c.nbOcc)));

	if(depth(t1) > depth(t2)){
		A->ls = t1;
		A->rs = t2;
	} else {
		A->ls = t2;
		A->rs = t1;

	}

	return A;

}

// Test //
/**
* Returns true if the tree only has a leaf
*/
int isLeaf(Tree A){
	return (A!=NULL) && (A->ls==NULL) && (A->rs==NULL);
}

int isNode(Tree A){
	return (A!=NULL) && (A->ls!=NULL) && (A->rs!=NULL);
}
/**
 * Returns the depth of a Tree
 */
int depth(Tree A){
	if (A==NULL){
		return 0;
	} else {
		int ll,rl;
		ll = depth(A->ls);
		rl = depth(A->rs);
		if(ll>rl){
			return 1 + ll;
		} else{
			return 1 + rl;
		}
	}
}
