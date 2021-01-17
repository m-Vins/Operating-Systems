//
// Created by vins on 15/01/21.
//
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define R 3
#define C 4

pthread_t t_id[R];
sem_t sem[R];

int mat[R][C];

void *readd(void *arg);
void *writee(void *arg);

int main(void) {
    setbuf(stdout, 0);
    for (int i = 0; i < R; i++) {
        sem_init(&sem[i], 0, 0);
    }
    sem_post(&sem[0]);
    for (int i = 0; i < R; i++) {
        fprintf(stdout, "creating thread n : %d\n", i);
        pthread_create(&t_id[i], NULL, readd, (void *) (intptr_t) i);
    }
    for(int i=0;i<R;i++)
        pthread_join(t_id[i],NULL);

    fprintf(stdout,"each thread was terminated\n");

    sem_post(&sem[0]);

    for(int i=0;i<R;i++) {
        fprintf(stdout, "creating thread n : %d\n", i);
        pthread_create(&t_id[i], NULL, writee, (void *) (intptr_t) i);
    }
    for(int i=0;i<R;i++)
        pthread_join(t_id[i],NULL);
    fprintf(stdout,"each thread was terminated\n");
    return 0;
}

void *readd(void *arg){
    int n=(intptr_t)arg;

    sem_wait(&sem[n]);

    for(int i=0; i<C; i++) {
        printf("thread n : %d . inserisci numero %d\n",n,i);
        fscanf(stdin, "%d", &mat[n][i]);

    }
    if (n!=R-1) {
        fprintf(stdout,"thread %d sending signal to thread %d\n",n,n+1);
        sem_post(&sem[n + 1]);
    }
    pthread_exit(NULL);
}

void *writee(void *arg){
    int n=(intptr_t)arg;

    sem_wait(&sem[n]);

    for (int i=0;i<C; i++)
        fprintf(stdout,"%d",mat[n][i]);
    fprintf(stdout,"\n");

    if (n!=R-1)
        sem_post(&sem[n+1]);
    pthread_exit(NULL);
}