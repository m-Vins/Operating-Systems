//
// Created by vins on 14/11/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){
    int fp;
    int tmp;

    if(argc!=3){
        fprintf(stdout,"Parameter error\n");
        exit(-10);
    }

    fp = creat (argv[1], 0666);
    if (fp == -1) {
        fprintf(stderr, "Cannot create file %s\n", argv[1]);
        exit (-1);
    }

    fprintf(stdout,"Writing file..\n");
    for (int i=0; i<atoi(argv[2]); i++) {
        tmp=rand()%1000;
        write (fp, &tmp, sizeof (int));
        fprintf (stdout, "%d ", tmp);
    }
    fprintf (stdout, "\n");
    return(0);
}
