#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define MAXSIZE 256


typedef struct {
    int l;
    int r;
    int *vector;
}arg_t;

void *mergesort(void *args);

int main(void){
    arg_t *arg=(arg_t *)malloc(sizeof(arg_t));
    pthread_t t;
    int vect[]={1,3,4,2,9,2,3,8,4};

    arg->vector=vect;
    arg->l=0;
    arg->r=8;

    pthread_create(&t,NULL,mergesort,arg);

    pthread_join(t,NULL);

    for(int i=0;i<9;i++)
        fprintf(stdout,"%d",vect[i]);

}

void merge(int *a, int p, int q, int r);

void *mergesort(void *args){
    arg_t *arguments=(arg_t *)args;
    arg_t *argl,*argr;

    sleep(1);
    fprintf(stdout,"pthread id : %lu ; args--> l=%d ,r=%d, vector=%p\n",pthread_self(),arguments->l,
                arguments->r,arguments->vector);

    if(arguments->l>=arguments->r) {
        fprintf(stdout,"recursive function reach the leaf\n");
        pthread_exit(0);
    }

    pthread_t tidl,tidr;


    int c=(arguments->l+arguments->r)/2;

    argl=malloc(sizeof(arg_t));
    argr=malloc(sizeof(arg_t));

    /**
     * setting the parameters for the next threads
     */

    argl->l=arguments->l;
    argl->r=c;
    argr->l=c+1;
    argr->r=arguments->r;
    argl->vector=argr->vector=arguments->vector;

    pthread_create(&tidl,NULL,mergesort,argl);
    pthread_create(&tidr,NULL,mergesort,argr);

    pthread_join(tidl,NULL);
    pthread_join(tidr,NULL);

    merge(arguments->vector,arguments->l,c,arguments->r);

    pthread_exit(0);
}


void merge(int *a, int p, int q, int r) {
    int i, j, k=0, b[MAXSIZE];
    i = p;
    j = q+1;

    while (i<=q && j<=r) {
        if (a[i]<a[j]) {
            b[k] = a[i];
            i++;
        } else {
            b[k] = a[j];
            j++;
        }
        k++;
    }
    while (i <= q) {
        b[k] = a[i];
        i++;
        k++;
    }
    while (j <= r) {
        b[k] = a[j];
        j++;
        k++;
    }
    for (k=p; k<=r; k++)
        a[k] = b[k-p];

}