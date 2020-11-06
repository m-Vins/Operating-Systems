#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void right(FILE *fp);
void left(FILE *fp);

int main(void){
    fprintf(stdout,"PID=%d-->P1\n",getpid());
    if(fork()!=0){
        sleep(1);
        left(stdout);
        wait(NULL);
        fprintf(stdout,"PID=%d-->P9\n",getpid());
        return 0;
    }else{
        sleep(1);
        right(stdout);
        exit(0);
    }

}


void left(FILE *fp){
    pid_t pid;

    fprintf(fp,"PID=%d-->P2\n",getpid());

    if((pid=fork())!=0){
        sleep(1);
        fprintf(fp,"PID=%d-->P4\n",getpid());
        while(wait(NULL)!=pid);
        sleep(1);
        fprintf(fp,"PID=%d-->P7\n",getpid());
        return;

    }else{
        sleep(1);
        fprintf(fp,"PID=%d-->P5\n",getpid());
        exit(0);
    }
}


void right(FILE *fp){

    fprintf(fp,"PID=%d-->P3\n",getpid());

    if(fork()!=0){
        sleep(1);

        wait(NULL);

        fprintf(fp,"PID=%d-->P8\n",getpid());
        return;
    }else{
        sleep(1);
        fprintf(fp,"PID=%d-->P6\n",getpid());
        exit(0);
    }
}