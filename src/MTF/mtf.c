#include "mtf.h"

//show the list of char
void printList(char* list)
{ 	int i ;
	for(i=0;i<NBCHAR;i++)
	{
		printf("| %c|\n",list[i]);
	}
}

//show the ASCII character
void printASCII()
{ 	int i ;
	for(i=0;i<NBCHAR;i++)
	{
		printf("| %c|\n",i);
	}
}

//initialize the list of char
void initList(char* list)
{
	int i;
	for (i=0;i<NBCHAR;i++)
	{
		list[i]=i;
	}
}

//put the element at the indice in the head
void moveElem(int indice,char* list){
	if(indice!=0){
		int tampon = list[indice];
		int i;
		for (i=indice-1;i>=0;i--)
		{
			list[i+1]=list[i];
		}
		list[0]=tampon;
	}
}

//use moveElem to ajust the list and repeat the operation to compress
char* moveToFront(const char* f)
{	
	char list[NBCHAR];
	initList(list);
	char* name = malloc(sizeof(char)*(strlen(f)+4));
	char gottenSymbol;
	strcpy(name,f);
	strcat (name,".mtf");
	FILE* fbis = fopen(name,"w+"); //create the compressed file
	FILE* fone = fopen(f,"r");	//open the file to compress
	if (fone!=NULL) //if the file is successfully openned
	{
		int i;
		while (!feof(fone))
		{
			gottenSymbol = fgetc(fone);
			//printf("%c",gottenSymbol);
			i = 0 ;
			while (list[i]!=gottenSymbol)
			{
				i++;
			}
			fputc(i,fbis);
			moveElem(i,list);
		}
		fclose(fone);
		fclose(fbis);
		return name;
	}
	else
	{
		fprintf(stderr,"This file doesn't exist");
		exit(1);
	}
}

//use moveElem to ajust the list and decompress
char* unMoveToFront(const char* f)
{		
	char list[NBCHAR];
	initList(list);
	char* name1 = malloc(sizeof(char)*(strlen(f)+6));
	unsigned int gottenSymbol;
	strcpy(name1,f);
	strcat (name1,".unmtf");
	FILE* fbis = fopen(name1,"w+"); //create the compressed file
	FILE* fone = fopen(f,"r");	//open the file to compress
	if (fone!=NULL) //if the file is successfully openned
	{
		int i;
		while (!feof(fone))
		{
			gottenSymbol = fgetc(fone);
			i = 0 ;
			while (i!=gottenSymbol)
			{
				i++;
			}
			fputc(list[i],fbis);
			moveElem(i,list);
		}
		fclose(fone);
		fclose(fbis);
		return name1;
	}
	else
	{
		fprintf(stderr,"This file doesn't exist");
		exit(1);
	}
}

int main(int argc, const char* argv[])  
{  
  const char* f = argv[1]; //arg1 = name of file to compress  
  const char* g = argv[2]; //arg2 = name of file to decompress=file to compress+.mtf  
  char list[NBCHAR];  
  //printASCII();  
  //printList(list);  
  moveToFront(f);  
  unMoveToFront(g);  
  return 0;  
}
