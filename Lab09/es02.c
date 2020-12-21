#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef int *Semaphore;

/**
 * semafori globali
 */
Semaphore semA,semBCD,semEF,semG,semH,semI;

/*
 * gestione semafori
 */


Semaphore semaphore_init(){
    int *sem;
    sem = calloc(2,sizeof(int));
    pipe(sem);
    return sem;
}

void semaphore_wait(Semaphore s){
    int junk;
    read(s[0],&junk,1);
}


void semaphore_signal(Semaphore s){
    write(s[1],"c",1);
}


void semaphore_free(Semaphore s){
    free(s);
}


/*
 * thread
 */


void *thread_A(void *arg){
    semaphore_wait(semA);

    fprintf(stdout,"thread A\n");


    semaphore_signal(semBCD);

    semaphore_signal(semBCD);

    semaphore_signal(semBCD);

    pthread_exit(0);
}

void *thread_B(void *arg){
    semaphore_wait(semBCD);

    fprintf(stdout,"thread B\n");

    semaphore_signal(semI);

    pthread_exit(0);
}



void *thread_C(void *arg){
    semaphore_wait(semBCD);

    fprintf(stdout,"thread C\n");

    semaphore_signal(semEF);

    semaphore_signal(semEF);

    pthread_exit(0);
}



void *thread_D(void *arg){
    semaphore_wait(semBCD);

    fprintf(stdout,"thread D\n");

    semaphore_signal(semH);

    pthread_exit(0);
}



void *thread_E(void *arg){
    semaphore_wait(semEF);

    fprintf(stdout,"thread E\n");

    semaphore_signal(semG);

    pthread_exit(0);
}

void *thread_F(void *arg){
    semaphore_wait(semEF);

    fprintf(stdout,"thread F\n");

    semaphore_signal(semG);
    pthread_exit(0);
}

void *thread_G(void *arg) {
    semaphore_wait(semG);
    semaphore_wait(semG);

    fprintf(stdout,"thread G\n");

    semaphore_signal(semI);
    pthread_exit(0);
}

void *thread_H(void *arg){
    semaphore_wait(semH);
    fprintf(stdout,"thread H\n");
    semaphore_signal(semI);
    pthread_exit(0);
}

void thread_I(void *arg){
    semaphore_wait(semI);
    semaphore_wait(semI);
    semaphore_wait(semI);

    fprintf(stdout,"thread I\n");

    return;
}


int main() {
    pthread_t tidA,tidB,tidC,tidD,tidE,tidF,tidG,tidH;
    setbuf(stdout,0);


    semA=semaphore_init();
    semBCD=semaphore_init();
    semEF=semaphore_init();
    semH=semaphore_init();
    semI=semaphore_init();
    semG=semaphore_init();


    pthread_create(&tidA,NULL,thread_A,NULL);
    pthread_create(&tidB,NULL,thread_B,NULL);
    pthread_create(&tidC,NULL,thread_C,NULL);
    pthread_create(&tidD,NULL,thread_D,NULL);
    pthread_create(&tidE,NULL,thread_E,NULL);
    pthread_create(&tidF,NULL,thread_F,NULL);
    pthread_create(&tidG,NULL,thread_H,NULL);
    pthread_create(&tidH,NULL,thread_G,NULL);


    semaphore_signal(semA);

    thread_I(NULL);

    fprintf(stdout,"destoying allocated memory\n");
    semaphore_free(semA);
    semaphore_free(semBCD);
    semaphore_free(semEF);
    semaphore_free(semH);
    semaphore_free(semI);
    semaphore_free(semG);

    return 0;
}
