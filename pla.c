#include<stdio.h>
#define sign(w,x) (_sign(w,x)>0.0?1:-1)
#define _sign(w,x)((w[0])*(x[0])+(w[1])*(x[1])+(w[2])*(x[2])+(w[3])*(x[3])+(w[4])*(x[4]))

void readFile(FILE **fptr){
	*fptr= fopen("hw1.dat","r");		
	if(*fptr == NULL)
		puts("open failure");
}


int main(){	

	double x[5]={1};
	double w[5] ={0};
	
	int y=0;
	int update=0, index=0, error = 0, number=400;
	FILE *file;
	readFile(&file);
	
	while(1){
		error =0;

		while(fscanf(file,"%lf%lf%lf%lf%d",&x[1],&x[2],&x[3],&x[4],&y)!=EOF){
			
			if(sign(w,x) != y){
				
				w[0] += y*x[0]; 
				w[1] += y*x[1]; 
				w[2] += y*x[2]; 
				w[3] += y*x[3];
				w[4] += y*x[4];
				
				++update;
				++error;
			}	
			
			++index;	
		}
		if(error ==0)
			break;
		
		fseek(file,0,SEEK_SET);
	}
	
	printf("%d\n",update);
	
	return 0;
}
