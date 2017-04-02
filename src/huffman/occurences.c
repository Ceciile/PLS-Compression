#include "occurences.h"
#include <stdlib.h>
#include <stdio.h>


int* getOccurences(char* fileName){
    
    FILE *f;
    int* tab_occurences;
    int i, symbol;
    
    f = fopen(fileName,"r");
    
    // If the file isn't opened/doesn't exist, print an error and quit the program
    if(f == NULL){
        fprintf(stderr,"getOccurences : file not opened\n");
        exit(1);
    }
    
    /* The file is opened.
    We want to count the appearance of each symbol.
    As they are considered as integers, we'll just increment the corresponding cell.
    For that, we need to initialize the table with 0 in each cell.
    */
    
    // Initializing the table
    tab_occurences = malloc(MAX_SYM*sizeof(int));
    for(i = 0; i < MAX_SYM; i++){
        tab_occurences[i] = 0;
    }
    
    // While we aren't at the end of the file, we count the occurences
    while(!feof(f)){
        symbol = fgetc(f);
        if(symbol < MAX_SYM){
			tab_occurences[symbol]++;
		}
    }
     
    return tab_occurences;
    
}

void printOccurences(int* tab_occurences){
    int i;
    for(i = 0; i < MAX_SYM; i++){
        printf("|0x%02X ",i);
        if((31 < i) && (i < 127)){
			printf("[%c]",i);
		} else {
			printf("[~]");
		}
        printf("|%4d| ", tab_occurences[i]); 
        if(i%3==2){ printf("\n"); }
    }
    printf("\n");
}


