#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct sortedVector{
    int n;
    int *vect;
};


void *threadFunction(void *arg);
void merge(int *a, int p, int q, int r);
void write_on_file(char *file_name, int *vect, int n);

int main(int argc, char **argv){
    int n=atoi(argv[1]);
    char **input_files,*output_file;
    pthread_t *threads;
    int *vect;
    int size=0;
    struct sortedVector *tmp;
    setbuf(stdout,0);


    input_files=(char **)malloc(sizeof(char *) * n);
    threads=(pthread_t *)malloc(sizeof(pthread_t) * n);


    if(argc!=n+3){
        /**
         * first argument is the number of input files
         * the next n argument is the name of input files
         * the last argument is the name of the output file
         *
         */
        fprintf(stdout,"PARAMETERS ERROR\n");
        exit(-1);
    }

    for(int i=0;i<n;i++){
        input_files[i]=argv[i + 2];
        fprintf(stdout, "ReadingFile[%d] = %s \n", i, input_files[i]);
    }

    output_file=argv[n+2];

    for(int i=0;i<n;i++){
        pthread_create(&threads[i], NULL, threadFunction, (void *)input_files[i]);
    }



    //wait for the threads

    for(int i=0;i<n;i++) {
        pthread_join(threads[i],(void *) &tmp);

        if(size==0){
            vect=malloc(sizeof(int)*tmp->n);
        }else{
            vect=realloc(vect,(size+tmp->n)*sizeof(int));
        }

        for(int j=0;j<tmp->n;j++){
            vect[j+size]=tmp->vect[j];
        }

        fprintf(stdout,"array before merging: ");
        for(int j=0;j<size+tmp->n;j++){
            fprintf(stdout,"%d ",vect[j]);
        }
        fprintf(stdout,"\n");
        if(size!=0)
            merge(vect,0,size,size+tmp->n);

        fprintf(stdout,"array after merging: ");
        for(int j=0;j<size+tmp->n;j++){
            fprintf(stdout,"%d ",vect[j]);
        }
        fprintf(stdout,"\n");
        size+=tmp->n;

        free(tmp);
    }

    write_on_file(output_file,vect,size);
    free(vect);
    free(input_files);
    return 0;

}


void write_on_file(char *file_name, int *vect, int n){
    FILE *fp=fopen(file_name,"w");
    if(fp==NULL){
        fprintf(stderr,"File Opening Error!\n");
        exit(0);
    }
    fprintf(stdout,"%s opened succesfully\n",file_name);
    fprintf(fp,"%d\n",n);
    for(int i=0;i<n;i++)
        fprintf(fp,"%d\n",vect[i]);
    fclose(fp);
}


void merge(int *a, int p, int q, int r) {
    int i, j, k=0, b[r];
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
    char *file_name=(char *)arg;
    struct sortedVector *ret=malloc(sizeof(struct sortedVector));
    int *vect;

    int n=ReadFromFile(file_name,&vect);

    fprintf(stdout,"thread start with argument: %s \n",file_name);


    bubbleSort(vect,n);

    ret->vect=vect;


    ret->n=n;


    pthread_exit(ret);
}