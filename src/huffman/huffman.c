#include "../../include/huffman.h"

Tree occToTree(int* tab_occ){
	Tree A;
	GlobalList *L;
	ListNode *parc, *tmp;

	// Ordered Listwith adress to trees
	L = completeList(tab_occ);
	if(L==NULL){
		fprintf(stderr,"occToTree : Empty GlobalList");
		exit(1);
	}
	parc = L->begin;
	if(parc== NULL){
		fprintf(stderr,"occToTree : Empty List");
		exit(2);
	}
	// While the list has more than 1 element
	while(parc!=NULL && parc->next!=NULL){
		Tree B;
		// Link the two first nods.
		B = createSubTree(parc->tree,parc->next->tree);
		// Delete them
		tmp = parc;
		parc = parc->next;
		free(tmp);
		tmp = parc;
		parc = parc->next;
		free(tmp);
		// Replace the begining of the list
		L->begin = parc;
		// Insert the new tree in the list
		insertionOnList(L,B);
		parc = L->begin;
	}
	// Return the final tree.
	A = parc->tree;
	free(L);
	return A;
}

void dispCodes(char** codes){
	int i,j;
	j=0;
	for( i = 0; i < MAX_SYM; i++){
		if(codes[i]!=NULL){
			printf("|0x%02x",i);
			if( i > 31 && i < 126){
				printf("(%c)",i);
			} else {
				printf("(~)");
			}
			printf("%s",codes[i]);
			j++;
			if(j%1==0){ printf("\n"); }
		}
	}

}

/**
 * Fills the table codes recursively
 */
void fillCodes(Tree A, char** codes, char* read, int sizeString){
	// String containing the next code
	char* next = malloc(sizeof(char*)*(sizeString+1));

	// If it's a leaf, add the "read" code to the table of codes
	if(isLeaf(A)){
		// The string is in codes[symbol]
		codes[A->c.symbol] = malloc(sizeof(char*)*(sizeString));
		strcpy(codes[A->c.symbol],read);
	} else {
		// Call the fill with the left branch and right branch if possible
		if(A->ls!=NULL){
			strcpy(next,read);
			strcat(next,"0"); // Adding the 0 at the end of the code
			fillCodes(A->ls,codes,next,sizeString+1);
		}
		if(A->rs!=NULL){
			strcpy(next,read);
			strcat(next,"1"); // Adding the 1 at the end of the code
			fillCodes(A->rs,codes,next,sizeString+1);
		}
	}
	free(next);
}


char** treeToCode( Tree A){
	char** codes; // Char[i] contains the code (in a string) for the symbol i
	char* c = ""; // Current code;

	// The table contains MAX_SYM strings.
	codes = malloc(sizeof(char*)*MAX_SYM);
	fillCodes(A,codes,c,1);
	return codes;
}

void fillSize(Tree A, int* tabSize,int size){
	if(isLeaf(A)){
		tabSize[A->c.symbol]=size;
	} else {
		if(A->ls!=NULL){
			fillSize(A->ls,tabSize,size+1);
		}
		if(A->rs!=NULL){
			fillSize(A->rs,tabSize,size+1);
		}
	}
}

int* treeToSize(Tree A){
	int* tabSize;

	tabSize = malloc(sizeof(int)*MAX_SYM);

	int i;
	for( i = 0; i < MAX_SYM; i++){
		tabSize[i]=0;
	}

	fillSize(A,tabSize,0);
	return tabSize;
}

void dispSize(int* tab_size){
	int i,j;
	j=0;
	for( i = 0; i < MAX_SYM; i++){
		if(tab_size[i]!=0){
			printf("|0x%02x",i);
			if( i > 31 && i < 126){
				printf("(%c)",i);
			} else {
				printf("(~)");
			}
			printf("%3d ",tab_size[i]);
			j++;
			if(j%4==0){ printf("\n"); }
		}
	}
	printf("\n");
}


char* write(char** codes, char* filename){
	 FILE *fwrite,*fsource;
     char* file = malloc(sizeof(char)*(strlen(filename)+3));

     strcpy(file,filename);
	 strcat(file,".hf");
	 fsource = fopen(filename,"r");
	 fwrite = fopen(file,"w");

	 if(fsource == NULL){
     fprintf(stderr,"write : file not opened\n");
     exit(1);
     }

     // If the file isn't opened/doesn't exist, print an error and quit the program
     if(fwrite == NULL){
     fprintf(stderr,"write : file not opened\n");
     exit(1);
     }

	 char* string;
	 char buffer; //8b buffer
	 int c;
	 int x=7;
	 unsigned long long int count = 0;


	 //Header implementation
	 for(int z=0;z < MAX_SYM;z++){
		 if(codes[z]==NULL){
			fputc(0,fwrite);
		 } else {
			fputc(strlen(codes[z]),fwrite);
		}
	 }

	 while(!feof(fsource)) {
		c = fgetc(fsource);
		count++;
	 }
	 count--; // We don't want to count the EOF
	 
	 
	 //Write number of encoded character
	 fprintf(fwrite,"%lld",count);

	 //Encode it
	 fsource = fopen(filename,"r");
	 if(fsource == NULL){
     fprintf(stderr,"write : file %s not opened\n", filename);
     exit(1);
     }
	
	
	 c = fgetc(fsource);
	 while(!feof(fsource)) {
		string = codes[c];
		unsigned int i=0;
		while(i < strlen(string)){
			if(string[i]=='0'){
				setBit(x,&buffer,0);
			} else {
				setBit(x,&buffer,1);
			}
			i++;
			x--;
			if(x < 0){
				fputc(buffer,fwrite);
				x=7;
			}
		}
		c = fgetc(fsource);
	 }
	 if(x!=7){
		 int i;
		 for(i=x;i>=0;i--){
			setBit(i,&buffer,'0');
		 }
		 fputc(buffer,fwrite);
	 }

	 fclose(fwrite);
	return file;
 }

 //return 8b char
 char* read(FILE *f){
	if(f == NULL || feof(f)){
	fprintf(stderr,"read : file not opened\n");
	exit(1);
	}

	char* string = malloc(sizeof(char)*8);
	string[8]='\0';
	char c;
	int i=0;
	c = fgetc(f);
	for(i=7;i>=0;i--){
		if(readBit(i,c) == 0){
			string[7-i] = '0';
		}else {
			string[7-i] = '1';
		}
	}

	return string;
 }

/**
 * renames a .hf file
 */
char *renameHF(char *str)
{	
	int n = strlen(str);
	char* new = malloc(sizeof(char)*(n+2));
	if(str==NULL){
		fprintf(stderr,"chopN : error, empty name\n");
	}
	if (n < 3) {
	  fprintf(stderr, "rename : filename not big enough");
      exit(1);  // Or: n = len;
  }
  strncpy(new,str,n-3);
  strcat(new,".unhf");
  return new;
}

/**
 * Decodes an finput file and produces a decoded fouput file.
 */
char* decodeHF(FILE *finput, char *filename, Tree T,unsigned long long int nbSymb) {
	char *exitName = renameHF(filename); //cropping filename to obtain the exitName of the decoded file
	if(!(strcmp(exitName,filename))) { 
		fprintf(stderr, "Error : overwriting the filename given.\n"); 
		exit(1);	
	}

	FILE *foutput = fopen(exitName, "w"); //the file that will be written (decrypted)
	char *buffer; //character buffer to read the file bit by bit
	unsigned int i;
	Nod *pTree = T;
	unsigned long long int count = 0; // Counts the symbol viewed
	int debug = !(strcmp(getenv("DEBUG"),"1"));
	
	if(debug) printf("Number of symbols : %lld\n",nbSymb);
	// browse the encoded file
	while(count<nbSymb) {
		// update the buffer
		buffer = read(finput);
		for(i=0; i<strlen(buffer); i++) { // browse the buffer
			// following the tree path
			if(buffer[i]=='1') pTree = pTree->rs;
			else pTree = pTree->ls;

			if(isLeaf(pTree)) { // Current tree node is a leaf >> insert the corresponding char in the output file
				fprintf(foutput, "%c", pTree->c.symbol);
				count++;
				pTree = T; //replaces the tree pointer on the tree root
			}
			if(count==nbSymb){break;}
		}
		free(buffer);
	}
	
	if(debug) printf("Number of symbols written : %lld\n",count);

	fclose(foutput);
	return exitName;

}

char* compress(char* filename){
	Tree A,B;
	int *tab_occ;
	char** codes;
	int* tab_size;
	int debug = !(strcmp(getenv("DEBUG"),"1"));
	int afftree = !(strcmp(getenv("DEBUG"),"2"));
	char* newname;
	
	tab_occ = getOccurences(filename);
		if(debug){
			printf("Affichage du tableau d'occurences\n");
			printOccurences(tab_occ);
		}
		
	A = occToTree(tab_occ);
		if(afftree){
			printf("Affichage de l'arbre de Huffman non canonique\n");
			dispTree(A);
		}
	
	tab_size = treeToSize(A);
		if(debug){
			printf("Affichage du tableau des tailles de symbole\n");
			dispSize(tab_size);
			
			long long int final = 0;
			int i;
			for(i=0;i<MAX_SYM;i++){
				final += tab_occ[i]*tab_size[i];
			}
			printf("Final size after compression : %lld byte\n",final/8);
			
		}
	
	B = sizeToTree(tab_size);
		if(afftree){
			printf("Affichage de l'arbre de Huffman canonique\n");
			dispTree(B);
		}
		
	codes = treeToCode(B);
		if(debug){
			printf("Affichage des codes pour chaque symbole\n");
			dispCodes(codes);
		}
	
	// Free the tree
	removeTree(A);
	
	// Write the file.hf
	newname = write(codes,filename);
	
	
	// Free the codes
	for( int i = 0; i < MAX_SYM; i++){
		free(codes[i]);
	}
	free(codes);
	free(tab_size);
	
	return newname;
	
}

char* decompress(char* filename){
	int *tab_size;
	unsigned long long int l;
	Tree A;
	char* newname;
	int debug = !(strcmp(getenv("DEBUG"),"1"));
	
	
	FILE * f;
	f = fopen(filename,"r");
	tab_size = readSize(f);
		if(debug){
			printf("Affichage du tableau des tailles de symbole\n");
			dispSize(tab_size);
		}
	
	l = readNbSymb(f);
	
	A = sizeToTree(tab_size);
		//~ if(debug){
			//~ printf("Affichage de l'arbre de Huffman canonique\n");
			//~ dispTree(A);
		//~ }
		
	newname = decodeHF(f,filename,A,l);
	
	// Frees the Tree when it's not used anymore
	removeTree(A);
	
	return newname;
	
}

