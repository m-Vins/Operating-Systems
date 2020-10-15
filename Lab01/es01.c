#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv){
	FILE *fin,*fout;
	char buffer[256];


	if(argc!=3){
		printf("errore parametri");
		return 1;
	}

	if((fin=fopen(argv[1],"r"))==NULL){
		printf("errore apertura file input");
		return 1;
	}

	if((fout=fopen(argv[2],"w"))==NULL){
		printf("errore apertura file output");
		return 1;
	}
	
	while(1) {
    	fgets(buffer, 256, fin);
    	if( feof(fin) )
     		 break;
    	fputs(buffer, fout);
	}
	
	fclose(fin);
	fclose(fout);
	
	return 0;
}
