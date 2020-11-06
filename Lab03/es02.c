#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(int argc,char **argv){
    int n,t;
    int i;
    int counter=0;
    pid_t pid1,pid2;

    if(argc!=3){
        fprintf(stderr,"parameters error!");
        return 1;
    }

    n=atoi(argv[1]);
    t=atoi(argv[2]);

    fprintf(stdout, "PID = %d, PPID = %d , COUNTER = %d\n", getpid(), getppid(),counter);

    for(i=0;i<n;i++){
        pid1=fork();
        if(pid1!=0){
            pid2=fork();
            if(pid2!=0)
                exit(0);
            else {
                counter++;
                fprintf(stdout, "PID = %d, PPID = %d , COUNTER = %d\n", getpid(), getppid(),counter);
            }
        }else{
            counter++;
            fprintf(stdout, "PID = %d, PPID = %d , COUNTER = %d\n", getpid(), getppid(),counter);
        }

    }
    for(int j=0;j<10;j++) fprintf(stdout,"-");
	fprintf(stdout,"\n");
    fprintf(stdout,"leaf PID = %d\n",getpid());
    for(int j=0;j<10;j++) fprintf(stdout,"-");
	fprintf(stdout,"\n");

    sleep(t);
    return 0;
}
