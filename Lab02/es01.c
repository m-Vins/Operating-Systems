#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>


void lsRecursive(FILE *fp,char *path,int space);

int main(int argc,char **argv){

	if(argc!=2){
		printf("errore parametri!\n");
		return 1;
	}

	printf("content of the root:\n");

	lsRecursive(stdout,argv[1],0);

	return 0;
}


void lsRecursive(FILE *fp,char *path,int space){
	DIR *dir;
	struct dirent *dp;
	char new_path[500];

	dir=opendir(path);

	if(dir==NULL){
		fprintf(stderr,"opendir() error at %s!\n",path);
		return;
	}

	fprintf(fp,"%s\n",path);
	while((dp=readdir(dir))!=NULL){
		if(strcmp(dp->d_name,".")!=0){
			if(strcmp(dp->d_name,"..")!=0){
				for(int i=0;i<space;i++)
					fprintf(fp,"  ");
				fprintf(fp,"-%s\n",dp->d_name);
				if(dp->d_type==DT_DIR){
					strcpy(new_path,path);
					strcat(new_path,"/");
					strcat(new_path,dp->d_name);
					lsRecursive(fp,new_path,space+1);
				}
			}
		}
	}

	closedir(dir);
}

