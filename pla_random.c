#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<stdlib.h>
using namespace std;

#define sign(w,x) (_sign(w,x)>0.0?1:-1)
#define _sign(w,x)((w[0])*(x[0])+(w[1])*(x[1])+(w[2])*(x[2])+(w[3])*(x[3])+(w[4])*(x[4]))

typedef struct data{
	float x[5];
	int y;
}Data;

void readData( vector<Data>& D){
	ifstream file("hw1.dat");
	if(!file)
		cout<<"file open failture"<<endl;	
	else
	while(!file.eof()){
		Data data;
		data.x[0]=1;
		
		for(int i=1;i<5;++i)
			file >> data.x[i];	
		file>>data.y;
		// printf("%f %f %f %f %f %d\n",data.x[0],data.x[1],data.x[2],data.x[3],data.x[4],data.y);
		D.push_back(data);
	}
}


int pla(vector<Data> &D, int random){
	float w[5] ={0};
	int update =0;
	
	//shuffle
	if (random){
		srand((unsigned)time(NULL));
		random_shuffle(D.begin(),D.end());
	}
	
	while(1){
	int error = 0, i;
	
		for(i=0;i<D.size();++i){
			
			if(sign(w,D[i].x) != D[i].y){
				for(int j=0;j<5;++j)
					w[j] += D[i].y*D[i].x[j]; 
				++update;
				error =1;
				// cout<<"update:"<<update<<" "<<"index:"<<i<<endl;
			}
			
		}
		if(i==D.size() && error==0)
			break;
	}
	
	return update;
}

int main(){
	
	vector<Data> D;
	readData(D);
	int random = 1, update=0, average=0;
	int x[100]={0};
	
	for(int i=0;i<2000;++i){
		update = pla(D,random);
		average +=update;
		++x[update];
	}
	
	// for(int i=0;i<100;i++){
		// cout<<i+1<<": ";
		
		// for(int j=0;j<x[i];++j)
			// cout<<"*";
		// cout<<endl;
	// }
	
	cout<<"update:"<<average/2000<<endl;

	return 0;
}

