#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc,char **argv){
    int n;
    int *vett;
    int retvalue;
    int i;
    
    pid_t pid;
    
    n=atoi(argv[1]);
    
    vett=(int *)malloc(sizeof(int)*n);
    
    if(vett==NULL){
        fprintf(stderr,"Allocation Error.\n");
        exit(1);
    }
    //acquisizione vettore
    fprintf(stdout,"Input:\n");
    for(i=0;i<n;i++){
        fprintf(stdout,"vet[%d]:",i);
        scanf("%d",&vett[i]);
    }
    
    fprintf(stdout,"Output:\n");
    //costruisco la pila di processi
    for(i=0;i<n-1;i++){
        pid=fork();
        if(pid>0){
            pid=wait(&retvalue);
            break;
        }
        fprintf(stdout,"Run PID=%d\n",getpid());
    }
    fprintf(stdout,"vett[%d]:%d -",i,vett[i]);
    fprintf(stdout,"End PID=%d\n",getpid());
    
    exit(0);
        
}
