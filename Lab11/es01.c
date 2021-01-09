/**
 * thread C and thread D are readers
 * thread A and thread B are writers
 *
 *
 */

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t meAB,semC,semD;
pthread_t tidA,tidB,tidC,tidD;

_Noreturn void *thread_A(void *arg);

_Noreturn void *thread_B(void *arg);
_Noreturn void *thread_C(void *arg);
_Noreturn void *thread_D(void *arg);


int main(void) {

    fprintf(stdout,"creating semaphores\n");
    sem_init(&meAB,0,1);
    //sem_init(&semC,0,0);
    //sem_init(&semD,0,0);
    fprintf(stdout,"creating thread\n");


    pthread_create(&tidA, NULL, thread_A, NULL);
    pthread_create(&tidB, NULL, thread_B, NULL);
    pthread_create(&tidC,NULL,thread_C,NULL);
    pthread_create(&tidD,NULL,thread_D,NULL);

    pthread_join(tidA,NULL);
    pthread_join(tidB,NULL);
    pthread_join(tidC,NULL);
    pthread_join(tidD,NULL);


    return 0;
}

_Noreturn void *thread_A(void *arg){
while(1) {
    fprintf(stdout, "thread A waiting for semAB\n");
    sem_wait(&meAB);

    sleep(1);
    fprintf(stdout, "thread A\n");
    fprintf(stdout, "thread A sending signal to semC\n");
    sem_post(&semC);
}

}

_Noreturn void *thread_B(void *arg){
while(1) {
    fprintf(stdout, "thread B waiting for semAB\n");
    sem_wait(&meAB);

    sleep(1);
    fprintf(stdout, "thread B\n");
    fprintf(stdout, "thread B sending signal to semC\n");
    sem_post(&semC);
}
}


_Noreturn void *thread_C(void *arg){
    while(1){
        fprintf(stdout, "thread C waiting for semC\n");
        sem_wait(&semC);

        sleep(1);
        fprintf(stdout,"thread C\n");
        fprintf(stdout, "thread C sending signal to semD\n");
        sem_post(&semD);
    }
}

_Noreturn void *thread_D(void *arg){
    while(1){
        fprintf(stdout, "thread D waiting for semD\n");
        sem_wait(&semD);

        sleep(1);
        fprintf(stdout,"thread D\n");
        fprintf(stdout, "thread D sending signal to semAB\n");
        sem_post(&meAB);
    }
}
