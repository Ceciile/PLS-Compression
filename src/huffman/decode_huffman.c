#include "../../include/decode_huffman.h"

/**
 * Reads the header to know the size of each symbol
 * @returns a table, t[i] = size of the symbol i
 */
int* readSize(FILE *f){
	int i; // Counts the symbols
	int* tab_size;
	int c;

	// If the file isn't opened/doesn't exist, print an error and quit the program
    if(f == NULL){
        fprintf(stderr,"read_size : file not opened\n");
        exit(1);
    }

    tab_size = malloc(sizeof(int)*MAX_SYM);
    // fill the size with 0
    for(i=0; i < MAX_SYM;i++){
		tab_size[i]=0;
	}
    i = 0;
    while( !(feof(f)) && i < MAX_SYM){
		c = fgetc(f);
		tab_size[i] = c;
		i++;
	}

	// Error
	if( i != MAX_SYM ) {
		fprintf(stderr,"read_size : incomplete header\n");
	}

    return tab_size;
}

/**
 * Reads the number of symbols present in the file
 */
unsigned long long int readNbSymb(FILE *f){
	unsigned long long int nb;
	// If the file isn't opened/doesn't exist, print an error and quit the program
    if(f == NULL){
        fprintf(stderr,"readNbSymb : file not opened\n");
        exit(1);
    }
    fscanf(f,"%lld",&nb);
    return nb;

}


/**
 * Fills tables for the reconstruction of the tree
 */
void fillInfos(int* tab_size, int lmax, int *nbSymb, GlobalList **symb){
	int i;
	for( i = 0; i <= lmax; i++){
		symb[i] = GlobalListInit();
		nbSymb[i] = 0;
	}

	for( i = 1; i < MAX_SYM; i++){
		if(tab_size[i] > 0){
			nbSymb[tab_size[i]]++;
			insertOnSymbol(symb[tab_size[i]],createNod(createCouple(i,0))); // must be ordered
		}
	}
}

int maxlength(int* tab_size){
	int i;
	int lmax = tab_size[0];
	// Maximal size of symbol
	for( i = 1; i < MAX_SYM; i++){
		if(tab_size[i] > lmax){
			lmax = tab_size[i];
		}
	}
	return lmax;
}


Tree sizeToTree(int* tab_size){
	Tree A;
	int lmax;
	int *nbSymb;
	GlobalList **symb;

	int p; // current depth
	GlobalList *sonlist, *parentlist, *newParentList; // List of groups and one to be created
	newParentList = GlobalListInit();
	ListNode *currentSon, *currentParent, *previousNode;

	/* Creating tables and lists. */
	lmax = maxlength(tab_size);
	
	// List of symbols of size i in symb[i], in the right order of symbols
	symb = malloc(sizeof(GlobalList*)*(lmax+1));
	// number of symbols of size i in nbSymb[i]
	nbSymb = malloc(sizeof(int)*(lmax+1));

	fillInfos(tab_size,lmax,nbSymb,symb);
	/* Initialisation */
	p = 0;
	symb[0]->begin = listNodeInit(0,0);
	parentlist = symb[0];
	A = symb[0]->begin->tree;
	
	for ( p = 1; p <= lmax; p++){
		sonlist = symb[p];
		// TODO free GL @ a moment
		currentParent = parentlist->begin;
		currentSon = sonlist->begin;
		while(currentParent != NULL) { // browse each parent
			if(currentSon != NULL) { //if son isn't empty, add each occurency of it in the tree
				if(currentParent->tree->rs == NULL) { //creates a right-son if possible
					previousNode = currentSon;
					currentParent->tree->rs = currentSon->tree;
					currentSon = currentSon->next;
					free(previousNode);
				} else if(currentParent->tree->ls == NULL) { //creates a left-son if possible
					previousNode = currentSon;
					currentParent->tree->ls = currentSon->tree;
					currentSon = currentSon->next;
					free(previousNode);
				}
			} else { //son is empty >> add new nodes to parent and add them to a new GlobalList (which will become new parent)
				Tree newTreeNode = createNod(createCouple(0, 0));
				if(currentParent->tree->rs == NULL) currentParent->tree->rs = newTreeNode;
				else if(currentParent->tree->ls == NULL) currentParent->tree->ls = newTreeNode;
				insertOnQueu(newParentList, newTreeNode);
			}
			if(currentParent->tree->ls!=NULL && currentParent->tree->rs!=NULL) { //change the current Parent if full
				previousNode = currentParent;
				currentParent = currentParent->next;
				free(previousNode);
			}
		}

		parentlist = newParentList; //TODO not sure if the list is made empty in the loop
		newParentList = GlobalListInit();
	}
	return A;

}
