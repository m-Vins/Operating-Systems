#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void){
    int checkPid3=0;
    int pid3,pid4,pid6;


    printf("S1->PID=%d\n",getpid());
    pid3=fork();
    if(pid3!=0){
        sleep(1);
        pid4=fork();
        if(pid4!=0){
            sleep(1);
            printf("S2->PID=%d\n",getpid());

            pid6=fork();

            if(pid6!=0){
                sleep(1);
                if(!checkPid3){
                    sleep(1);
                    waitpid(pid3,NULL,0);
                    checkPid3=1;
                }
                sleep(1);
                printf("S5->PID=%d\n",getpid());
                waitpid(pid6,NULL,0);
                sleep(1);
                printf("S7->PID=%d\n",getpid());
                exit(0);
            }else{
                if(!checkPid3){
                    waitpid(pid3,NULL,0);
                    checkPid3=1;
                }
                waitpid(pid4,NULL,0);
                sleep(1);
                printf("S6->PID=%d\n",getpid());
                exit(0);
            }

        }else{
            sleep(1);
            printf("S4->PID=%d\n",getpid());
            exit(0);
        }

    }else{
        sleep(1);
        printf("S3->PID=%d\n",getpid());
        exit(0);
    }

}

