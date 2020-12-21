#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


/**
 * semafori globali
 */
sem_t semA,semB,semC,semD,semE,semF,semG,semH,semI;


/*
 * thread
 */


_Noreturn void *thread_A(void *arg){
    while(1) {
        sem_wait(&semA);
        fprintf(stdout, "thread A\n");
        sleep(2);
        sem_post(&semB);
        sem_post(&semC);
        sem_post(&semD);
    }
}

_Noreturn void *thread_B(void *arg){
    while(1) {
        sem_wait(&semB);
        fprintf(stdout, "thread B\n");
        sleep(2);
        sem_post(&semI);
    }
}


_Noreturn void *thread_C(void *arg){
    while(1) {
        sem_wait(&semC);
        fprintf(stdout, "thread C\n");
        sleep(2);
        sem_post(&semE);
        sem_post(&semF);
    }

}


_Noreturn void *thread_D(void *arg){
    while(1) {
        sem_wait(&semD);
        fprintf(stdout, "thread D\n");
        sleep(2);
        sem_post(&semH);
    }

}


_Noreturn void *thread_E(void *arg){
    while(1) {
        sem_wait(&semE);
        fprintf(stdout, "thread E\n");
        sleep(2);
        sem_post(&semG);
    }

}

_Noreturn void *thread_F(void *arg){
    while(1) {
        sem_wait(&semF);
        fprintf(stdout, "thread F\n");
        sleep(2);
        sem_post(&semG);
    }
}

_Noreturn void *thread_G(void *arg) {
    while(1) {
        sem_wait(&semG);
        sem_wait(&semG);
        fprintf(stdout, "thread G\n");
        sleep(2);
        sem_post(&semI);
    }
}

_Noreturn void *thread_H(void *arg){
    while(1) {
        sem_wait(&semH);
        fprintf(stdout, "thread H\n");
        sleep(2);
        sem_post(&semI);
    }
}

_Noreturn void thread_I(void *arg){
    while(1) {
        sem_wait(&semI);
        sem_wait(&semI);
        sem_wait(&semI);
        fprintf(stdout, "thread I\n");
        sleep(2);
        sem_post(&semA);
    }
}


int main() {
    pthread_t tidA,tidB,tidC,tidD,tidE,tidF,tidG,tidH;
    setbuf(stdout,0);


    sem_init(&semA,0,1);
    sem_init(&semB,0,0);
    sem_init(&semC,0,0);
    sem_init(&semD,0,0);
    sem_init(&semE,0,0);
    sem_init(&semF,0,0);
    sem_init(&semG,0,0);
    sem_init(&semH,0,0);
    sem_init(&semI,0,0);



    pthread_create(&tidA,NULL,thread_A,NULL);
    pthread_create(&tidB,NULL,thread_B,NULL);
    pthread_create(&tidC,NULL,thread_C,NULL);
    pthread_create(&tidD,NULL,thread_D,NULL);
    pthread_create(&tidE,NULL,thread_E,NULL);
    pthread_create(&tidF,NULL,thread_F,NULL);
    pthread_create(&tidG,NULL,thread_H,NULL);
    pthread_create(&tidH,NULL,thread_G,NULL);


    thread_I(NULL);

    sem_destroy(&semA);
    sem_destroy(&semB);
    sem_destroy(&semC);
    sem_destroy(&semD);
    sem_destroy(&semE);
    sem_destroy(&semF);
    sem_destroy(&semH);
    sem_destroy(&semI);
    sem_destroy(&semG);


    return 0;
}
