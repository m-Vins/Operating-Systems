
#include <stdio.h>


int main(void){
    int tmp;

    while(1){
        fscanf(stdin,"%d",&tmp);
	if(!tmp)
		break;
        if(tmp%2)
            	fprintf(stderr,"%d\n",tmp);
	else
		fprintf(stdout,"%d\n",tmp);
    }
}


