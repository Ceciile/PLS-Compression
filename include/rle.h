#ifndef H_RLE
#define H_RLE

#define MAX_SIZE 4096

void CompressRLE(char* input ,char* output);
void UnCompressRLE(char* input ,char* output);
char *fich_to_char(char* pchPath);
void char_to_txt(char* exitetxt,char* szwrite);
char *execRLE(char *filein);
char *unexecRLE(char *filein);

#endif H_RLE
