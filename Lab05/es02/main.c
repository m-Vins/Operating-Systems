#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define N 12

void childIteractions(int fp,int i,int n);
void print_line(int fp,int n);


int main(int argc,char **argv){
    char *FileName;
    int n;
    int fp;
    int exitStatusChild;



    if(argc!=3){
        fprintf(stderr,"parameters error!\n");
        return 1;
    }
    FileName=argv[1];
    n=atoi(argv[2]);


    fprintf(stdout,"Calling write_file..\n");

    if(fork()){
        sleep(2);
        exitStatusChild=wait(NULL);
        if(exitStatusChild<=0)
            exit(-1);
    }else{
        if(execlp("write_file",argv[1],argv[2],(char *)0)==-1){
            fprintf(stderr,"ERROR\n");
            exit(-1);
        }
    }



    fprintf(stdout,"Opening File...\n");
    fp=open(FileName, O_RDWR);
    if(fp == -1){
        fprintf(stderr,"Cannot open file!\n");
        exit(-1);
    }
    fprintf(stdout,"File opened succesfully!\n");

    fprintf(stdout,"Starting bubblesort...\n");



    /*
     * bubblesort
     */
    for(int i=0;i<n-1;i++){
        if(fork()){
            //parent
            wait(NULL);
            print_line(fp,n);
        }
        else{
            //child
            childIteractions(fp,i,n);
            exit(0);
        }
    }

    fprintf(stdout,"\nReading ordered File:\n");
    print_line(fp,n);

    close(fp);
}

void childIteractions(int fp,int i,int n){
    int n1,n2,c1,c2;

    lseek(fp,0,SEEK_SET);

    for(int j=0;j<n-1-i;j++){


        //read v[j] and v[j+1]
        c1=read(fp,&n1,sizeof(int));
        c2=read(fp,&n2,sizeof(int));

        //set the pointer to v[j]
        lseek(fp,-sizeof(int),SEEK_CUR);

        //check the reading
        if(c2<=0||c1<=0){
            fprintf (stderr, "Error reading file\n");
            exit (-1);
        }

        //swap
        if(n1>n2){
            lseek(fp,-sizeof(int),SEEK_CUR);
            write(fp,&n2,sizeof(int));
            write(fp,&n1,sizeof(int));
            lseek(fp,-sizeof(int),SEEK_CUR);
        }


    }


}

void print_line(int fp,int n){
    int tmp;
    lseek(fp,0,SEEK_SET);
    for(int i=0;i<n;i++){
        read(fp,&tmp,sizeof(int));
        fprintf(stdout,"%d ",tmp);
    }
    fprintf(stdout,"\n");
}
