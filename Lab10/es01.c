#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>


#define DBG 0
#define BUFFERSIZE 512

void *read_thread(void *args);
void *write_thread(void *arg);
void *modify_thread(void *arg);


sem_t sem_read,sem_modify,sem_write;

char buffer[BUFFERSIZE];


int main(int argc, char **argv){
    FILE *fin,*fout;
    pthread_t tw,tm,tr;

    if(argc!=3){
        fprintf(stderr,"parameters number error!\n");
        return -1;
    }

    if((fin=fopen(argv[1],"r"))==NULL){
        fprintf(stderr,"file input error while opening!\n");
        return 0;
    }

    if((fout=fopen(argv[2],"w"))==NULL){
        fprintf(stderr,"file output error while opening!\n");
        return 0;
    }


    sem_init(&sem_read,0,1);
    sem_init(&sem_modify,0,0);
    sem_init(&sem_write,0,0);
#if DBG
    fprintf(stdout,"address of fin : %p\n",fin);
    fprintf(stdout,"address of fout : %p\n",fout);
#endif
    pthread_create(&tr,NULL,read_thread,fin);
    pthread_create(&tm,NULL,modify_thread,NULL);
    pthread_create(&tw,NULL,write_thread,fout);

    pthread_join(tw,NULL);
    pthread_join(tm,NULL);
    pthread_join(tr,NULL);

    return 0;

}



void *read_thread(void *arg){
    FILE *fp=(FILE *)arg;
#if DBG
    fprintf(stdout,"address of fin : %p\n",fp);
#endif

    while(1){
        sem_wait(&sem_read);
        if(fgets(buffer,BUFFERSIZE,fp)==NULL){
            /*
             * if fgets() return NULL, buffer[0] is set to EOF
             * as flag to communicate the end of file to the
             * other thread, then this thread will exit.
             */
            buffer[0]=EOF;
            sem_post(&sem_modify);
            pthread_exit(0);
        }
    fprintf(stdout,"line readed is : %s \n",buffer);
        sem_post(&sem_modify);
    }
}

void *modify_thread(void *arg){
    while(1){
        sem_wait(&sem_modify);
        if(buffer[0]==EOF){
            sem_post(&sem_write);
            pthread_exit(0);
        }
        for(int i=0;i<strlen(buffer);i++){
            buffer[i]=(char)tolower(buffer[i]);
        }
        fprintf(stdout,"line modified is : %s \n",buffer);
        sem_post(&sem_write);
    }
}

void *write_thread(void *arg){
    FILE *fp=(FILE *)arg;
#if DBG
    fprintf(stdout,"address of fin : %p\n",fp);
#endif
    while(1){
        sem_wait(&sem_write);
        if(buffer[0]==EOF){
            fclose(fp);
            pthread_exit(0);
        }

        fprintf(fp,"%s",buffer);
        fprintf(stdout,"line writed is : %s \n",buffer);
        sem_post(&sem_read);

    }
}
