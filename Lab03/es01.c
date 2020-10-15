#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>


int main(int argc,char **argv){
    char path[500];
    DIR *dir;
    struct dirent *dp;

    if(argc!=2){
        printf("errore parametri\n");
        return 1;
    }

    strcpy(path,argv[1]);

    dir=opendir(path);
    if(dir==NULL){
        printf("opendir() error\n");
        return 1;
    }

    printf("content of the root:\n");
    while((dp=readdir(dir))!=NULL){
      if(strcmp(dp->d_name,".")!=0){
	      if(strcmp(dp->d_name,"..")!=0){
	        printf("%s\n",dp->d_name);
        }
	    }
    }
    closedir(dir);
}
