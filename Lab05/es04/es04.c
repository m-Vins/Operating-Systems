#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


#define FILENAME "file.txt"
#define BUFFSIZE 256


void mytoUpper(char *str);
void signalHandler(){return;}
void consumer(pid_t producerPid);
void producer();

int main(void){
  pid_t pproducer,pconsumer;

  if(signal(SIGUSR1,signalHandler)==SIG_ERR){
    fprintf(stderr,"signal Handler function error!\n");
    return 1;
  }

  pproducer=fork();
  if(pproducer==0){
    producer();
  }else{
    pconsumer=fork();
    if(pconsumer==0){
      consumer(pproducer);
    }
  }

  wait(NULL);
  fprintf(stderr,"parent process has finished\n");

  return 0;

}


void mytoUpper(char *str){
  int l=strlen(str);

  for(int i=0;i<l;i++){
    if(islower(str[i]))
      str[i]=toupper(str[i]);
  }

}


void consumer(pid_t producerPid){
  FILE *fp;
  char line[BUFFSIZE];
  int flag=1;
  fprintf(stdout,"Consumer process : %d\n",getpid());
  fprintf(stdout,"opening file..\n");

  if((fp=fopen(FILENAME,"w"))==NULL){
    fprintf(stderr,"opening file error!\n");
    exit(-1);
  }
  fprintf(stdout,"File opened succesfully!\n");
  fprintf(fp,"%d\n",getpid());

  while(1){
    if(!flag){
      fprintf(stdout,"opening file..\n");
      if((fp=fopen(FILENAME,"w"))==NULL){
        fprintf(stderr,"opening file error!\n");
        exit(-1);
      }
      fprintf(stdout,"File opened succesfully!\n");
    }
    fprintf(stdout,"plese enter the line: ");
    scanf("%s",line);
    fprintf(stdout,"your line is: %s\n",line);
    fprintf(fp,"%s",line);
    fprintf(stdout,"%s writed in the file\n",line);
    fclose(fp);
    fprintf(stdout,"file closed succesfully.\n");
    fprintf(stdout,"sending signal to producer..\n");
    kill(producerPid,SIGUSR1);
    if(strcmp(line,"end")==0)
      break;
    fprintf(stdout,"consumer waiting for signal..\n");
    pause();
    fprintf(stdout,"signal received by consumer\n");
    flag=0;
  }
  fprintf(stderr,"consumer has finished\n");
  exit(0);
}


void producer(){
  FILE *fp;
  char line[BUFFSIZE];
  pid_t consumer;
  int flag=1;
  fprintf(stdout,"producer process: %d \n",getpid());

  while(1){

    fprintf(stdout,"producer waiting for signal..\n");
    pause();
    fprintf(stdout,"signal received by producer\n");
    fprintf(stdout,"Opening file..\n");
    if((fp=fopen(FILENAME,"r"))==NULL){
      fprintf(stderr,"opening file error!\n");
      exit(-1);
    }
    if(flag){
      fprintf(stdout,"Reading consumer pid\n");
      fscanf(fp,"%d",&consumer);
      fprintf(stdout,"consumer pid: %d\n",consumer);
      flag=0;
    }
    fprintf(stdout,"Reading the line\n");
    fscanf(fp,"%s",line);
    fprintf(stdout,"line is : %s\n",line);
    fprintf(stdout,"Closing file\n");
    fclose(fp);
    if(strcmp(line,"end")==0)
      break;
    mytoUpper(line);
    fprintf(stdout,"Line converted is: \n");
    fprintf(stdout,"%s\n",line);
    fprintf(stdout,"sending signal to consumer \n");
    kill(consumer,SIGUSR1);
  }

  fprintf(stderr,"producer has finished\n");
  exit(0);
}
