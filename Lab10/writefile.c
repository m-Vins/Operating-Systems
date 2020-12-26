#include <stdio.h>
#include <ctype.h>


int main(int argc, char **argv){
	float x,c;
	int n;
	FILE *fp;

	if(argc!=2){
		fprintf(stderr,"parameters error");
		return -1;
	}

	if((fp=fopen(argv[1],"w"))==NULL){
		fprintf(stderr,"error occurred while opening file");
		return -1;
	}
	
	while(1){
		fprintf(stdout,"insert float");
		if(fscanf(stdin,"%f",&c)!=1)
			break;
		fprintf(stdout,"float readed is : %f\n",c);
		fwrite(&c,sizeof(float),1,fp);
		fprintf(stdout,"insert float");
		if(fscanf(stdin,"%f",&x)!=1)
			break;
		fprintf(stdout,"float readed is : %f\n",x);
		fwrite(&x,sizeof(float),1,fp);
		fprintf(stdout,"insert integer");
		if(fscanf(stdin,"%d",&n)!=1)
			break;
		fprintf(stdout,"float readed is : %d\n",n);
		fwrite(&n,sizeof(int),1,fp);
	}
	fclose(fp);
	return 0;
}


