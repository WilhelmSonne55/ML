#include<stdio.h>
#define sign(w,x) (_sign(w,x)>0?1:-1)
#define _sign(w,x)((w[0])*(x[0])+(w[1])*(x[1])+(w[2])*(x[2])+(w[3])*(x[3]))


void readFile(FILE **fptr){
	*fptr= fopen("hw1.dat","r");		
	if(*fptr == NULL)
		puts("open failure");
}


int main(){	
	float x[4]={1,1,1,1};
	int data=-1, y=-data;
	int update=0, index=0, i;
	int end = -5;
	float w[4] = {0};
	FILE *file;
	readFile(&file);
	
	while(1){

		// correct
		if(data != y){
	        w[0] += y*x[0]; 
	        w[1] += y*x[1]; 
	        w[2] += y*x[2]; 
	        w[3] += y*x[3];
			
			// printf("%f %f %f %f %d\n",w[0],w[1],w[2],w[3], y);

			i=index=1;
			++update;
			fseek(file,0,SEEK_SET);
		}	

		if(fscanf(file, "%f%f%f%f%d",&x[0],&x[1],&x[2],&x[3],&y)==EOF)
			break;
		
	    data = sign(w,x);	
		++index;
	}

	printf("%d %d\n",update,i);
	printf("%d %d",data, y);
	
	return 0;
}
