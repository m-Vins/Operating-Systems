#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 32
#define MAX_ARGUMENT 5

#define GDB 0

int main(int argc,char **argv){
    char end[]="end\0";
    FILE *fp;
    char buf[BUFFER_SIZE];
    int i=0,flag_path=0;
    char *cmd[MAX_ARGUMENT];
    char path[BUFFER_SIZE];
    char tmp[BUFFER_SIZE*6]="\0";



    if(argc!=2){
        printf("paramaters number error!\n");
        exit(0);
    }

    if((fp=fopen(argv[1],"r"))==NULL){
        printf("invalid name of file!\n");
        exit(0);
    }

#if GDB
    while(fscanf(fp,"%s",buf)!=EOF){
        if(strcmp(buf,end)!=0){
            if(!flag_path){
                strcpy(path,buf);
                flag_path=1;
            }else {
                cmd[i] = (char *) malloc(sizeof(char) * BUFFER_SIZE);
                strcpy(cmd[i], buf);
                i++;
            }
        }else{
            cmd[i]=NULL;
            //exec
            if(!fork()){
		        sleep(3);
                fprintf(stdout,"Running Exec.\n");
                execvp(path,cmd);
            }else{
		        strcat(tmp,path);
		        strcat(tmp," ");
		        for(int j=0;j<i;j++){
			        strcat(tmp,cmd[j]);
			        if(j!=i-1)
                         strcat(tmp," ");
		}
		        system(tmp);
		        strcpy(tmp,"\0");
            }


            for(int j=0;j<i;j++){
                free(cmd[j]);
            }
            i=0;
            flag_path=0;
        }
    }

#else
    char *tmpaddress;

    for(int i=0;i<MAX_ARGUMENT;i++)
        cmd[i]=(char *)malloc(BUFFER_SIZE*sizeof(char));

    while(fscanf(fp,"%s",buf)!=EOF){
        if(strcmp(buf,end)!=0){
            if(!flag_path){
                strcpy(path,buf);
                flag_path=1;
            }else {
                strcpy(cmd[i], buf);
                i++;
            }
        }else{
            tmpaddress=cmd[i];
            cmd[i]=NULL;
            //exec
            if(!fork()){
                sleep(3);
                fprintf(stdout,"Running Exec.\n");
                execvp(path,cmd);
            }else{
                strcat(tmp,path);
                strcat(tmp," ");
                for(int j=0;j<i;j++){
                    strcat(tmp,cmd[j]);
                    if(j!=i-1)
                        strcat(tmp," ");
                }
                system(tmp);
                strcpy(tmp,"\0");
            }
            cmd[i]=tmpaddress;
            i=0;
            flag_path=0;
        }
    }

    for(int i=0;i<MAX_ARGUMENT;i++)
        free(cmd[i]);


#endif
    return 0;
}
