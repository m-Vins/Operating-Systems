#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef int *Semaphore;

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


void semaphores_signal(Semaphore s){
    write(s[1],"c",1);
}



int main() {

    return 0;
}
