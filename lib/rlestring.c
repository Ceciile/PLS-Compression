//@author:Cecile

#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>


#define MAX_SIZE 4096

void CompressRLE(char* input ,char* output)
{
    int length = strlen(input);
    //char dic[MAX_SIZE];//这个是字典，用于存储出现过的字符
    //dic[0] = input[0];
    int iter = 0;//字符重复的次数，归零
    int pAddr = 0;//这是往输出数组存入时的位置量
    int p,l=0;
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
        int j=0;
        int i,k=0;
        for(i = 0; i < strlen(input);i++)
        {
            if((input[i-1]-'-'!=0)&&(input[i]-'0'>0)&&(input[i]-'0'<9))
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
    }


/* test function
int main(int argc, char* argv[])
{
    char pchBuf[] = {'z','z','z','y','x','x','x','s','f','s'};
    char codemess[] = {'y','z','x','s','-','2','f','f','3'};

    char* output = (char*)malloc(MAX_SIZE); //2*Max
    memset(output,0,MAX_SIZE);
    CompressRLE(pchBuf,output);
    printf("%s\n", output);
    
// un!~compress!~need (char* -->txt)

    char* result = (char*)malloc(MAX_SIZE);
    memset(result,0,MAX_SIZE);
    UnCompressRLE(codemess,result);
    printf("%s\n", result);

    return 0;
} */
