#include "../include/liste_lib.h"


GlobalList* GlobalListInit(){
	GlobalList* L = malloc(sizeof(GlobalList));
	L->begin = NULL;
	L->end = NULL;
	return L;
}

ListNode* listNodeInit(int symb,int occ){
	ListNode* L = malloc(sizeof(ListNode));
	L->tree = malloc(sizeof(Tree));
	L->tree = createNod(createCouple(symb,occ));
	L->next=NULL;
	return L;
}


Tree getFirstElem(GlobalList *L){
	if(L==NULL || L->begin==NULL){
		fprintf(stderr,"getFirstElem : trying to get from an empty list");
		exit(1);
	}

	Tree A = L->begin->tree;
	ListNode *tmp = L->begin;
	L->begin=L->begin->next;
	free(tmp);

	return A;
}

/*
int getFirstSymb(SymbolList S){
	if(S==NULL){
		fprintf(stderr,"getFirstSymb : trying to get from an empty list");
		exit(1);
	}

	return S->symbol;

}

void stepSymbList(SymbolList *S){
	if(S==NULL || *S == NULL){
		fprintf(stderr,"stepSymbList : trying to get step in an empty list");
		exit(1);
	}
	*S = (*S)->next;
}

void addSymbList(SymbolList *S, int x){
	if(*S==NULL){
		fprintf(stderr,"addSymbList : trying to add in a non-existing list");
		exit(1);
	}

}
*/

GlobalList* completeList(int* tab_occurences){
	int i = 0;
	GlobalList* L = GlobalListInit();

	while((i<MAX_SYM) && (tab_occurences[i]==0)){
		i++;
	}

	L->begin = listNodeInit(i,tab_occurences[i]);
	L->end = L->begin;
	i++;

	while (i<MAX_SYM){
		if(tab_occurences[i] != 0){
			insertionOnList(L,createNod(createCouple(i,tab_occurences[i])));
		}
		i++;
	}
	return L;
}


void insertionOnList(GlobalList *L,Tree tree){
	ListNode *tampon,*prev,*elem;
	int occu;

	elem = listNodeInit(0,0);
	elem->tree = tree;
	if(L == NULL){
		L = GlobalListInit();
		L->begin = elem;
		L->end = elem;

	}else{
		tampon=L->begin;
		prev=tampon;
		if(tree==NULL){
			fprintf(stderr,"insertionOnList : Empty Tree");
			exit(1);
		}
		occu = tree->c.nbOcc;
		if(tampon == NULL){L->begin = elem; L->end = elem;}else{

			if(occu < L->begin->tree->c.nbOcc){
				L->begin = elem;
				elem->next = tampon;
			}else{
				while((tampon->next != NULL) && (occu > (tampon->tree->c.nbOcc))){
					prev = tampon;
					tampon = tampon->next;
				}
				if(tampon->next == NULL){
					if(occu > (tampon->tree->c.nbOcc)){
						L->end = elem;
						tampon->next = elem;
					}else{
						prev->next = elem;
						elem->next = tampon;
					}
				}else{
					elem->next = prev->next;
					prev->next = elem;
				}
			}
		}
	}
}


void insertOnSymbol(GlobalList *L,Tree tree){
	ListNode *tampon,*prev,*elem;
	int symb;

	elem = listNodeInit(0,0);
	elem->tree = tree;
	if(L == NULL){
		L = GlobalListInit();
		L->begin = elem;
		L->end = elem;

	}else{
		tampon=L->begin;
		prev=tampon;
		if(tree==NULL){
			fprintf(stderr,"InsertOnSymbol : Empty Tree");
			exit(1);
		}
		symb = tree->c.symbol;
		if(tampon == NULL){L->begin = elem; L->end = elem;}else{

			if(symb < L->begin->tree->c.symbol){
				L->begin = elem;
				elem->next = tampon;
			}else{
				while((tampon->next != NULL) && (symb > (tampon->tree->c.symbol))){
					prev = tampon;
					tampon = tampon->next;
				}
				if(tampon->next == NULL){
					if(symb > (tampon->tree->c.symbol)){
						L->end = elem;
						tampon->next = elem;
					}else{
						prev->next = elem;
						elem->next = tampon;
					}
				}else{
					elem->next = prev->next;
					prev->next = elem;
				}
			}
		}
	}
}

void insertOnSymbolD(GlobalList *L,Tree tree){
	ListNode *tampon,*prev,*elem;
	int symb;

	elem = listNodeInit(0,0);
	elem->tree = tree;
	if(L == NULL){
		L = GlobalListInit();
		L->begin = elem;
		L->end = elem;

	}else{
		tampon=L->begin;
		prev=tampon;
		if(tree==NULL){
			fprintf(stderr,"InsertOnSymbol : Empty Tree");
			exit(1);
		}
		symb = tree->c.symbol;
		if(tampon == NULL){L->begin = elem; L->end = elem;}else{
			if(symb > L->begin->tree->c.symbol){
				L->begin = elem;
				elem->next = tampon;
			}else{
				while((tampon->next != NULL) && (symb < (tampon->tree->c.symbol))){
					prev = tampon;
					tampon = tampon->next;
				}
				if(tampon->next == NULL){
					if(symb > (tampon->tree->c.symbol)){
						L->end = elem;
						tampon->next = elem;
					}else{
						prev->next = elem;
						elem->next = tampon;
					}
				}else{
					elem->next = prev->next;
					prev->next = elem;
				}
			}
		}
	}
}


void insertOnHead(GlobalList *L,Tree tree){
	ListNode* elem;
	elem = listNodeInit(0,0);
	elem->tree = tree;
	if(L->begin == NULL){
		L->begin = elem;
		L->end = elem;
	}else{
		elem->next = L->begin;
		L->begin = elem;
	}

}

void insertOnQueu(GlobalList *L,Tree tree){
	ListNode *elem,*tampon;
	elem = listNodeInit(0,0);
	elem->tree = tree;
	if(L->begin == NULL){
		L->begin = elem;
		L->end = elem;
	}else{
		tampon = L->begin;
		while(tampon->next != NULL){
			tampon = tampon -> next;
		}
		elem->next = NULL;
		tampon->next = elem;
	}

}

void dispList(GlobalList *A){
	int i = 0;
	ListNode* L = NULL;
	if(A!=NULL){
		L = A->begin;
	}
	while(L!=NULL){
		printf("|(%02x)%3d",L->tree->c.symbol,L->tree->c.nbOcc);
		i++;
		if(i%10==0){ printf("\n"); }
		L = L->next;
	}
	if(i%10!=0){	printf("\n"); }
}

void freeList(GlobalList *L) {
	if((L) == NULL) exit(0);
	ListNode *currentNode,*ancnode;
	currentNode = L->begin;
	while(currentNode != NULL) {
		ancnode = currentNode->next;
		free(currentNode);
		currentNode = ancnode;
	}
	free(L);
}
