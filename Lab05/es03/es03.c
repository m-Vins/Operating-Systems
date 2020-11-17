#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static void signalHandler(){fprintf(stdout,"Received signal..\n"); return;}

int main(void){
  pid_t pid;

  if(signal(SIGUSR1, signalHandler)==SIG_ERR){
    fprintf(stderr,"signalHandler function ERROR!\n");
    return 1;
  }

  if(pid=fork()){
    //parent
    while(1){
      pause();
      fprintf(stdout,"Father Woke-up\n");
      sleep(2);
      kill(pid,SIGUSR1);
    }
  }else{
    //child
    while(1){
      sleep(2);
      fprintf(stdout,"Child Woke-up\n");
      kill(getppid(),SIGUSR1);
      pause();
    }
  }
}
