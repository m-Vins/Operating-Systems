#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFSIZE 256

int main(void){
    int pipe1[2],pipe2[2];
    char *msg="run",*stop="stp";//sono della stessa dimensione così non devo gestire un protocollo di lettura
    char buf[BUFFSIZE];
    int sizeofmsg=strlen(msg);
    int cont=0;

    pipe(pipe1);
    pipe(pipe2);

    if(fork()){

        while(cont!=20) {
            cont++;
            fprintf(stdout, "I am the father : %d\n", getpid());

            write(pipe1[1], msg, sizeofmsg);

            read(pipe2[0], buf, sizeofmsg);
        }

        write(pipe1[1], stop, sizeofmsg);
        exit(0);

    }else{
        while(1) {
            read(pipe1[0], buf, sizeofmsg);
            if (strcmp(buf, stop) == 0)
                exit(0);
            fprintf(stdout, "I am the child : %d\n", getpid());
            write(pipe2[1], msg, sizeofmsg);
        }

    }
}