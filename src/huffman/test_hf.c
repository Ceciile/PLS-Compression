#include "../../include/huffman.h"
#include "../../include/decode_huffman.h"

int main(int argc, char* argv[]){
	if(argc==2){
				
		char* new = compress(argv[1]);
		
		decompress(new);
		
		free(new);
		
	} else {
		printf("Entrez le nom du fichier à traiter\n");
	}
	
	return 0;
}
