#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem1,sem2,sem3,sem_merge;
float first,second,third;
int flag;



void *thread_first(void *arg);
void *thread_second(void *arg);
void *thread_third(void *arg);
void *thread_merge(void *arg);



int main(int argc, char **argv){
    pthread_t tid[4];
    FILE *fp;
    flag=0;

    if(argc!=2){
        fprintf(stderr,"parameters number error!\n");
        return 0;
    }


    if((fp=fopen(argv[1],"r"))==NULL){
        fprintf(stderr,"error occurred while opening file!\n");
        return 0;
    }

    sem_init(&sem1,0,1);
    sem_init(&sem2,0,0);
    sem_init(&sem3,0,0);
    sem_init(&sem_merge,0,0);

    pthread_create(&tid[0],NULL,thread_first,fp);
    pthread_create(&tid[1],NULL,thread_second,fp);
    pthread_create(&tid[2],NULL,thread_third,fp);
    pthread_create(&tid[3],NULL,thread_merge,NULL);

    for(int i=0;i<4;i++){
        pthread_join(tid[i],NULL);
    }

    fclose(fp);

    return 0;
}



void *thread_first(void *arg){
    FILE *fp=(FILE *)arg;
    float x,c;
    int n;
    first=1;

    while(1){
        sem_wait(&sem1);
        if(flag==1)
        {
            first=0;
            sem_post(&sem2);
            pthread_exit(0);
        }
        if(fread(&x,sizeof(float),1,fp)==0||
        fread(&c,sizeof(float),1,fp)==0||
        fread(&n,sizeof(int),1,fp)==0){
            flag=1;
            first=0;
            sem_post(&sem2);
            pthread_exit(0);
        }
        fprintf(stdout,"read c: %f, x: %f, n: %d\n",c,x,n);
        for(int i=0;i<n;i++){
            first*=x;
        }
        first*=c;
        sem_post(&sem2);
    }
}


void *thread_second(void *arg){
    FILE *fp=(FILE *)arg;
    float x,c;
    int n;
    second=1;

    while(1){
        sem_wait(&sem2);
        if(flag==1)
        {
            second=0;
            sem_post(&sem3);
            pthread_exit(0);
        }
        if(fread(&x,sizeof(float),1,fp)==0||
           fread(&c,sizeof(float),1,fp)==0||
           fread(&n,sizeof(int),1,fp)==0){
            flag=1;
            second=0;
            sem_post(&sem3);
            pthread_exit(0);
        }
        fprintf(stdout,"read c: %f, x: %f, n: %d\n",c,x,n);
        for(int i=0;i<n;i++){
            second*=x;
        }
        second*=c;
        sem_post(&sem3);
    }
}



void *thread_third(void *arg){
    FILE *fp=(FILE *)arg;
    float x,c;
    int n;
    third=1;

    while(1){
        sem_wait(&sem3);
        if(flag==1)
        {
            third=0;
            sem_post(&sem_merge);
            pthread_exit(0);
        }
        if(fread(&x,sizeof(float),1,fp)==0||
           fread(&c,sizeof(float),1,fp)==0||
           fread(&n,sizeof(int),1,fp)==0){
            flag=1;
            third=0;
            sem_post(&sem_merge);
            pthread_exit(0);
        }
        fprintf(stdout,"read c: %f, x: %f, n: %d\n",c,x,n);
        for(int i=0;i<n;i++){
            third*=x;
        }
        third*=c;
        sem_post(&sem_merge);
    }
}

void *thread_merge(void *arg){
    int count=0;
    while(1){
        sem_wait(&sem_merge);
        count++;
        fprintf(stdout,"monomial number %d is equal to %f\n",count,first+second+third);
        if(flag==1){
            sem_post(&sem1);
            pthread_exit(0);
        }
        sem_post(&sem1);
    }
}

