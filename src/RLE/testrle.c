#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rle.h"
#define MAX_SIZE 4096 

int main(int argc, char const *argv[]) {
        char* pchBufSTR = (char*)malloc(MAX_SIZE);  
 
        char* resultSTR = (char*)malloc(MAX_SIZE);  
        char* outputSTR = (char*)malloc(2*MAX_SIZE); //2*Max
        memset(pchBufSTR,0,MAX_SIZE);  
        memset(outputSTR,0,2*MAX_SIZE);  
        memset(resultSTR,0,MAX_SIZE);  
        printf("please input a string:\n");  
        scanf("%s",pchBufSTR);  
        printf("input = %s\n",pchBufSTR);  
        CompressRLE(pchBufSTR,outputSTR);  
        printf("output = %s\n",outputSTR);  
        UnCompressRLE(outputSTR,resultSTR);  
        printf("result = %s",resultSTR); 


  printf("\n");
  char* input = (char*)malloc(2*MAX_SIZE); 
  printf("please input a message_fich:\n");  
  scanf("%s",input);
  char* comfich=fich_to_char(input);
  char* comresult = (char*)malloc(2*MAX_SIZE); //2*Max
  printf("%s\n",comfich);

  CompressRLE(comfich,comresult);
  char_to_txt("comresult.txt",comresult);
  

  char* output = (char*)malloc(2*MAX_SIZE);
  printf("please input a code_fich:\n");  
  scanf("%s",output);
  char* uncomfich=fich_to_char(output);
  char* obtenu_ormess = (char*)malloc(2*MAX_SIZE); //2*Max
  printf("%s\n",uncomfich);
  UnCompressRLE(uncomfich,obtenu_ormess);
  char_to_txt("uncom.txt",obtenu_ormess);

  return 0;
}
