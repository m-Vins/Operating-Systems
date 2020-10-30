#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>



#define N 500
#define BSIZE 1024


void copy(char *src,char *dst);
void visitR(char *src, char *dest);

int main(int argc,char **argv){


    if(argc!=3){
        fprintf(stderr,"parameters error, please use <src> <dest>\n");
        return 1;
    }

    visitR(argv[1],argv[2]);

    return 0;
}

void newPath(char *new, char *old, char *str){
    strcpy(new,old);
    strcat(new,"/");
    strcat(new,str);
}


void visitR(char *src, char *dest) {
    DIR *dir;
    struct stat statbuffer;
    struct dirent *dp;
    char new_src[N];
    char new_dest[N];

    if(lstat(src,&statbuffer)<0){
        exit(1);  
    }


    mkdir(dest,statbuffer.st_mode);

    if((dir=opendir(src))==NULL){
        fprintf(stderr,"opendir() error at %s!\n",src);
        return;
    }

    while((dp=readdir(dir))!=NULL){
        if(strcmp(".",dp->d_name)!=0){
            if(strcmp("..",dp->d_name)!=0){

                newPath(new_dest,dest,dp->d_name);
                newPath(new_src,src,dp->d_name);

                if(dp->d_type==DT_DIR){
                    visitR(new_src, new_dest);
                }else{
                    copy(new_src,new_dest);
                }
            }
        }
    }
}


void copy(char *src,char *dst){
    int f_dst,f_src;
    char buffer[BSIZE];

    f_src=open(src,O_RDONLY);
    f_dst=open(dst,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);

    if(f_src<0||f_dst<0){
        fprintf(stderr,"Error");
        exit(1);
    }

    while(read(f_src,buffer,BSIZE)>0){
        write(f_dst,buffer,BSIZE);
    }

    close(f_src);
    close(f_dst);
}

