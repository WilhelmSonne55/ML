#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<stdlib.h>
#include<string>
using namespace std;

#define sign(w,x) (_sign(w,x)>0.0?1:-1)
#define _sign(w,x)((w[0])*(x[0])+(w[1])*(x[1])+(w[2])*(x[2])+(w[3])*(x[3])+(w[4])*(x[4]))

typedef struct data{
	float x[5];
	int y;
}Data;

void readData( vector<Data>& D, string s){
	ifstream file(s);
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

float getErate(vector<Data> &D, float w[5]){
	float eRate=0.0;
	
	for(int i=0;i<D.size();++i){
		if(sign(w,D[i].x) != D[i].y )
			++eRate ;
	}
	
	return eRate/D.size();
}

float plcketPLA(vector<Data>& D, int update){
	float w[5] ={0};	
	float pw[5] ={0};
	
	//shuffle
	srand((unsigned)time(NULL));
	random_shuffle(D.begin(),D.end());
	
	
	for(int i=0;i<update;++i){
				
			if(sign(w,D[i].x) != D[i].y){
				for(int j=0;j<5;++j)
					w[j] += (D[i].y * D[i].x[j]); 
				
				//pocket?
				// if(getErate(D,w) < getErate(D,pw)){
					for(int j=0;j<5;++j)
						pw[j] = w[j];
				// }
			}
	}
	
	return getErate(D,pw);
}

int main(){
	
	vector<Data> D;
	vector<Data> Dtest;
	readData(D,"hw1_18_train.dat");
	readData(Dtest,"hw1_18_test.dat");
	int random = 1, update=100;
	float avError=0.0, avTestError=0.0;
	int x[100]={0};
	
	for(int i=0;i<2000;++i){
		float trainingError = plcketPLA(D,update);
		float testError = plcketPLA(Dtest, update);
		cout<<i+1<<"times:  training error:"<<trainingError<<"  test error: "<<testError<<endl;

		avError += trainingError;
		avTestError += testError;
	}
	
	cout<<"training error: "<<avError/2000.0<<endl;
	cout<<"test error: "<<avTestError/2000.0<<endl;

	return 0;
}

