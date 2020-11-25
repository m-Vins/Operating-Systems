#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>



struct arguments {
    char *ReadingFiles;
    char *WritingFiles;
};

void *threadFunction(void *arg);

int main(int argc, char **argv){
    struct arguments *Names;
    int n=atoi(argv[1]);
    pthread_t *threads;
    setbuf(stdout,0);


    Names=(struct arguments *)malloc(sizeof(struct arguments)*n);
    threads=(pthread_t *)malloc(sizeof(pthread_t) * n);


    if(argc!=2*n+2){
        fprintf(stdout,"PARAMETERS ERROR\n");
        exit(-1);
    }

    for(int i=0;i<2*n;i++){
        if(i<n) {
            Names[i].ReadingFiles=(char *)malloc(sizeof(char)*strlen(argv[i+2])+1);
            strcpy(Names[i].ReadingFiles,argv[i+2]);
            fprintf(stdout,"ReadingFile[%d] = %s \n",i,Names[i].ReadingFiles);
        }
        else {
            Names[i-n].WritingFiles=(char *)malloc(sizeof(char)*strlen(argv[i+2])+1);
            strcpy(Names[i-n].WritingFiles,argv[i+2]);
            fprintf(stdout,"WritingFile[%d] = %s \n",i-n,Names[i-n].WritingFiles);
        }
    }

    for(int i=0;i<n;i++){
        pthread_create(&threads[i], NULL, threadFunction, (void *)&Names[i]);
    }




    pthread_exit(NULL);

}


int ReadFromFile(char *fileName, int **vect){
    FILE *fp=fopen(fileName,"r");
    int n;
    int *tmp;

    if(fp==NULL){
        fprintf(stderr,"File Opening Error!\n");
        exit(0);
    }
    fprintf(stdout,"%s opened succesfully\n",fileName);

    fscanf(fp,"%d",&n);

    tmp=(int *)malloc(sizeof(int)*n);

    for(int i=0;i<n;i++)
        fscanf(fp,"%d",&tmp[i]);

    *vect=tmp;
    fclose(fp);
    return n;
}

int writeOnFIle(char *fileName, int *vect, int n){
    FILE *fp=fopen(fileName,"w");
    int count=0;

    if(fp==NULL){
        fprintf(stderr,"File Opening Error!\n");
        exit(-1);
    }

    fprintf(stdout,"%d\n",n);
    for(int i=0;i<n;i++) {
        fprintf(fp, "%d\n", vect[i]);
        count++;
    }

    fclose(fp);
    return count;
}


void swap(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int *arr, int n){
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
    }
}


void *threadFunction(void *arg){
    struct arguments *tmp;
    tmp= (struct arguments *) arg;
    fprintf(stdout,"thread start with argument: %s %s\n",tmp->ReadingFiles,tmp->WritingFiles);
    int *vect=NULL;
    int n=ReadFromFile(tmp->ReadingFiles,&vect);
    bubbleSort(vect,n);
    writeOnFIle(tmp->WritingFiles,vect,n);
    pthread_exit(NULL);
}