#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <conio.h>
#include <time.h>
#include "myclass2.cpp"

using namespace std;

int main(){
	srand(time(NULL));
	int N, i, d=800, ch=600, k, page=0;
	float l=0;
	setlocale(LC_ALL, "Russian");
	cout<<"������� ���-�� �����: ";
	cin>>N;
	cout<<"�������� ��� ��������: "<<endl;
	cout<<"1. �������������"<<endl;
	cout<<"2. ���������"<<endl;
	cout<<"����: ";
	cin>>k;
	tPoint *A;
	A=new tPoint [N];
	if(k==1){
		initwindow(d,ch);
		while(1){
			if(kbhit()){
				break;
			}
			setactivepage(page);
			setvisualpage(1-page);
			cleardevice();
			for(i=0;i<N;i++){
				A[i].otris();
				A[i].animeline();
			}
			page=1-page;
			delay(10);	
		}
		closegraph();
	}
	if(k==2){
		initwindow(d,ch);
		while(1){
			if(kbhit()){
				break;
			}
			setactivepage(page);
			setvisualpage(1-page);
			cleardevice();
			for(i=0;i<N;i++){
				A[i].otris();
				A[i].animechaos();	
			}
			page=1-page;
			delay(10);
		}
		closegraph();
	}
	system("PAUSE");
	return 0;
}
