#include <stdlib.h>
#include <stdio.h>

void stat(char* f1,char* f2);

int main(int argc, char* argv[]){
	if(argc!=3){
		fprintf(stderr,"Please imput the compressed and original file\n");
		exit(1);
	}
	stat(argv[1],argv[2]);
}

void stat(char* f1,char* f2)  
//f1 is the compressed file and f2 normal file

{	//Initialize the variables
	FILE* f= NULL;
	float comp_rate;
	float comp_ratio;
	float compteur1=0;
	float compteur2=0;

	//Openning of the first file
	f = fopen(f1,"r");
	if (f != NULL)
	{	//The file is successfully openned
		
		while (!feof(f))
		{ //Repeat while the end of the file isn't reached
			fgetc(f);
			compteur1++;}
		
		//Close the file
		fclose(f);}	
		
	else {printf("Impossible to open the file %s",f1);}
	
	printf("Size of file 1 : %f\n",compteur1);
	
	//Openning the second file
	f = fopen(f2,"r");
	if (f != NULL)
	{	//The file is successfully openned
		
		while (!feof(f))
		{ //Repeat while the end of the file isn't reached
			fgetc(f);
			compteur2++;
		}
		
		//Close the file
		fclose(f);
	}	
		
	else {printf("Impossible to open the file %s",f2);}
	
	
	printf("Size of file 2 : %f\n",compteur2);
	
	//Calculating of the ratio/rate
	comp_ratio = (compteur1/compteur2) * 100;
	comp_rate = (1 - compteur1/compteur2) * 100;
	
	printf("The compression ratio is %f percent \n",comp_ratio);
	printf("and the compression rate is %f percent\n",comp_rate);		
}
