#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 32
#define MAX_ARGUMENT 5
#define END "end\0"

int main(int argc,char **argv){
    
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


    while(fscanf(fp,"%s",buf)!=EOF){
        if(strcmp(buf,END)!=0){
            if(!flag_path){
                strcpy(path,buf);
                flag_path=1;
            }else {
                cmd[i] = (char *) malloc(sizeof(char) * (strlen(buf)+1));
                strcpy(cmd[i], buf);
                i++;
            }
        }else{
            cmd[i]=NULL;
            
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
    fclose(fp);
    return 0;
}
