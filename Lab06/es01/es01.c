#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>



#define BUFFSIZE 256


void mytoUpper(char *str);
void signalHandler(){}
void consumer(pid_t producerPid, int *file);
void producer(int *file);

int main(void){
  pid_t pproducer,pconsumer;
  int file[2];


  if(signal(SIGUSR1,signalHandler)==SIG_ERR){
    fprintf(stderr,"signal Handler function error!\n");
    return 1;
  }

  if(pipe(file)==0){
      fprintf(stdout,"Pipe created succesfully!\n");
  }else{
      fprintf(stderr,"Pipe function error!\n");
      return 1;
  }

  pproducer=fork();
  if(pproducer==0){
    producer(file);
  }else{
    pconsumer=fork();
    if(pconsumer==0){
      consumer(pproducer,file);
    }
  }

  wait(NULL);
  fprintf(stderr,"parent process has finished\n");

  return 0;

}


void mytoUpper(char *str){
  int l=(int)strlen(str);

  for(int i=0;i<l;i++){
    if(islower(str[i]))
      str[i]=(char)toupper(str[i]);
  }

}


void consumer(pid_t producerPid, int *file){
  char line[BUFFSIZE];
  pid_t myPid=getpid();
  int sizeofline;

  fprintf(stdout,"Consumer process : %d\n",getpid());

  fprintf(stdout,"Writing consumer pid in the pipe..\n");
  write(file[1],&myPid,sizeof(pid_t));
  fprintf(stdout,"consumer pid writed succesfully\n");
  fprintf(stdout,"Sending signal to producer..\n");
  kill(producerPid,SIGUSR1);

  fprintf(stdout,"consumer waiting for signal..\n\n");

  pause();

  while(1){

    fprintf(stdout,"please enter the line: ");
    fgets(line,BUFFSIZE,stdin);
    line[strlen(line)-1]='\0';
    fprintf(stdout,"your line is: %s\n",line);
    sizeofline=sizeof(line);
    fprintf(stdout,"the dimension of line is: %d\n",sizeofline);
    write(file[1], &sizeofline, sizeof(int));
    write(file[1],line,sizeof(line));
    fprintf(stdout,"%s writed in the pipe\n",line);

    fprintf(stdout,"sending signal to producer..\n");
    kill(producerPid,SIGUSR1);
    if(strcmp(line,"end")==0)
      break;
    fprintf(stdout,"consumer waiting for signal..\n");
    pause();
    fprintf(stdout,"signal received by consumer\n");

  }
  fprintf(stderr,"consumer has finished\n");
  exit(0);
}


void producer(int *file){
  char line[BUFFSIZE];
  int sizeofline;
  pid_t consumerPid;
  fprintf(stdout,"producer process: %d \n",getpid());

  fprintf(stdout,"producer waiting for signal..\n");
  pause();
  fprintf(stdout,"signal received by producer\n");
  fprintf(stdout,"reading consumerPid pid..\n \n");
  read(file[0], &consumerPid, sizeof(pid_t));
  fprintf(stdout, "consumerPid pid is: %d\n", consumerPid);
  fprintf(stdout,"sending signal to consumerPid \n");
  kill(consumerPid, SIGUSR1);


    while(1){

    fprintf(stdout,"producer waiting for signal..\n");
    pause();
    fprintf(stdout,"signal received by producer\n");


    fprintf(stdout,"reading the dimension of the line..\n");
    read(file[0],&sizeofline,sizeof(int));
    fprintf(stdout,"the dimension of line is: %d\n",sizeofline);

    fprintf(stdout,"Reading the line\n");
    read(file[0],line,sizeofline);
    fprintf(stdout,"line is : %s\n",line);

    if(strcmp(line,"end")==0)
      break;
    mytoUpper(line);

    fprintf(stdout,"Line converted is: \n");
    fprintf(stdout,"%s\n",line);

    fprintf(stdout,"sending signal to consumerPid \n");
    kill(consumerPid, SIGUSR1);

  }

  fprintf(stderr,"producer has finished\n");
  exit(0);
}
