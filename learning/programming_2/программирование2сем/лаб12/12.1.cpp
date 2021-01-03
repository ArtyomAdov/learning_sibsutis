#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include "timerint.cpp"
#include "timerfloat.cpp"
using namespace std;
int random (int n) {return rand()%10;}

int FillRandInt(int A[], int N){int i, a=0, b=N-1;
	srand(time(NULL));
	for (i=0;i<N;i++){
	A[i]=rand()%(b-a+1)+a;
	}
	return 0;
}

 int FillRandFloat(float B[], int N){int i, a=0, b=N-1;
	srand(time(NULL));
	for (i=0;i<N;i++){
	B[i]=(float)rand()*(b-a)/RAND_MAX+a;
	}
	return 0;
}

int main(){
	int i, j, N, *A;
	float *B;
	double vrem;
	while(1){
		cout<<"vvedite kol-vo elementov";
		cin>>N;
		cout<<endl;
		while(1){
			cout<<"Viberite tip dannih"<<endl;
			cout<<"1) Celie"<<endl;
			cout<<"2) Vehestvennie"<<endl;
			vvod:cin>>i;
			if(i==1) {
				A=new int [N];
				break;
			}
			if(i==2){
				B=new float [N];
				break;
			}
			if(i!=2 && i!=1) cout<<"neverno vvel"<<endl;
		}
		while(1) {
			if(i==1) FillRandInt(A,N); 
			if(i==2) FillRandFloat(B,N);
			if(i!=1&&i!=2) {printf("neverno"); goto vvod;}
			cout<<"Viberite tip sortirovki"<<endl;
			cout<<"1) SelectSort"<<endl;
			cout<<"2) BubbleSort"<<endl;
			cout<<"3) ShakerSort"<<endl;
			cout<<"4) InsertSort"<<endl;
			cout<<"0) Vihod"<<endl;
			cin>>j;
			if(i==1){	
				switch(j){
					case 1:timerint(SelectSortInt, A, N);break;
					case 2:timerint(BubbleSortInt, A, N);break;
					case 3:timerint(ShakerSortInt, A, N);break;
					case 4:timerint(InsertSortInt, A, N);break;
					case 0:return 0;break;
				}
			}
			if(i==2){	
				switch(j) {
					case 1:timerfloat(SelectSortFloat, B, N);break;
					case 2:timerfloat(BubbleSortFloat, B, N);break;
					case 3:timerfloat(ShakerSortFloat, B, N);break;
					case 4:timerfloat(InsertSortFloat, B, N);break;
					case 0:return 0;break;
				}
			}
		}
	}
}
