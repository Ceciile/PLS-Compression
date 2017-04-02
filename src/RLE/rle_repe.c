//@author:Cecile

#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>


#include "rle.h"
#define MAX_SIZE 4096

void CompressRLE(char* input ,char* output)
{
    int length = strlen(input);
    //char dic[MAX_SIZE];//这个是字典，用于存储出现过的字符
    //dic[0] = input[0];
    int iter = 0;//字符重复的次数，归零
    int pAddr = 0;//这是往输出数组存入时的位置量
    int p=0;
    for(p = 0;p < length;p++)
    {
        if(input[p] == input[p+1])
        {
            iter++;
        }
        else//这个else就是下一个跟这一个不重复。则分类讨论,一种就是重复字符数量大于2
            //
        {
            if(iter > 0)//说明前面存在重复的字符并且数量大于2
            {
                output[pAddr++] = input[p];
                output[pAddr++] = input[p];
                output[pAddr++] = '0' + (iter-1);
            }
            else
            {
                output[pAddr++] = input[p];
            }
            iter = 0;//循环次数重新置零
        }

/*      l=j+1;               //vraiment pas efficace!!!
        while((input[i+1] != input[i])&&(input[i]==input[l]))
        {
             output[k++]='-';
             output[k++]=l-i-'1';
             l++;
        }
*/

    }
    output[pAddr] = '\0';
    //if(j>=m){i = m-1;}
    //else{i=l-1;};

}


void UnCompressRLE(char* input ,char* output)
    {
        unsigned int j=0;
        unsigned int i,k=0;
        for(i = 0; i < strlen(input);i++)
        {
            if((input[i-1]-'-'!=0)&&(input[i]-'0'>=0)&&(input[i]-'0'<9))
            {
                int count=0;
                for( j = k; count < (input[i]-'0');j++)
                {
                    output[j] = input[i-1];
                    count ++;
                    k++;
                }
            }
            else if(input[i]-'-'==0)
            {
                output[k]=output[i-(input[i+1]-'0')-1];
                k++;
                output[k]=input[i+2];
                /*for(s=strlen(output);count< (input[i+1]-'0');s++)
                {
                    output[s]=output[s-(input[i+1]-'0')-1];
                    count++;
                }*/
            }
            else if(!((input[i]-'0'>0)&&(input[i]-'0'<9))){
            output[k]=input[i];
            k++;}
        }
        output[k] = '\0';
    }

char *fich_to_char(char* pchPath)
{

    char* pchBuf = NULL;  //read message to char[]
    int  nLen = 0;
    // open~
    FILE *pF  = fopen(pchPath, "r");

    // to the end of the txt~
    fseek(pF, 0, SEEK_END);

    // aiguille actuelle= longeur de fichier
    nLen = ftell(pF);

    // return to the begin//文件指针恢复到文件头位置~
    rewind(pF);

    // spatiales dynamiques,\0=end//动态申请空间, 为保存字符串结尾标志 \0, 多申请一个字符的空间~
    pchBuf = (char*) malloc(2*MAX_SIZE);//sizeof(char)*nLen+1
    if(!pchBuf) {
        perror("not enough space!\n");
        exit(0);
    }
    // read读取文件内容~
////////////////////////////////////////////////////////////////////
    // longeur de fichier?=read读取的长度和源文件长度有可能有出入，这里自动调整 nLen~  !!!!!??
    nLen = fread(pchBuf, sizeof(char), 2*MAX_SIZE, pF);  //sizeof(pchBuf)=8

    // put end添加字符串结尾标志~
    pchBuf[nLen] = '\0';

    // 把读取的内容输出到屏幕看看~
    //printf("%s\n", pchBuf);


    return pchBuf;
    // 释放空间~
    //free(pchBuf);

    fclose(pF);
}

void char_to_txt(char* exitetxt,char* szwrite)
{
    FILE *ofp;

    ofp=fopen(exitetxt,"wb");
    while(ofp==NULL)
    {
        printf("can't open file,write the correct namepath:");
        ofp=fopen(exitetxt,"wb");
    }
  fseek(ofp, 0,SEEK_END);
  fwrite(szwrite, strlen(szwrite) * sizeof(char), 1, ofp);
  fclose(ofp);
}

char *execRLE(char *filein){
  char* comfich=fich_to_char(filein);
  char* comresult = (char*)malloc(2*MAX_SIZE); //allocation of memory for the output file
  CompressRLE(comfich,comresult); // char* unprecoded to char* precoded with RLE

  //creating the name of the output file
  char *fileout = (char *) malloc(sizeof(char)*(strlen(filein) + 4 ));
  strcpy(fileout, filein);
  strcat(fileout, ".rle");

  char_to_txt(fileout,comresult); // writting the RLE precode into an output file
  return fileout;
}

char *unexecRLE(char *filein) {
  char* precodedRLEFile=fich_to_char(filein);
  char* precodedRLETab = (char*)malloc(2*MAX_SIZE);
  UnCompressRLE(precodedRLEFile,precodedRLETab);

  // adding .unrle to the file
  char *fileout = (char *) malloc(sizeof(char)*(strlen(filein) + 6 ));
  strcpy(fileout, filein);
  strcat(fileout, ".unrle");

  char_to_txt(fileout,precodedRLETab);
  return fileout;
}
