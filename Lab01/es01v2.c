#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv){
	FILE *fin,*fout;
	char buffer[256];
	int n_elementi;


	if(argc!=3){
		printf("errore parametri");
		return 1;
	}

	if((fin=fopen(argv[1],"rb"))==NULL){
		printf("errore apertura file input");
		return 1;
	}

	if((fout=fopen(argv[2],"wb"))==NULL){
		printf("errore apertura file output");
		return 1;
	}
	
	while((n_elementi=fread(buffer,sizeof(char),sizeof(buffer),fin))!=0){
			fwrite(buffer,sizeof(char),n_elementi,fout);
			}
	fclose(fin);
	fclose(fout);
	
	return 0;
}
