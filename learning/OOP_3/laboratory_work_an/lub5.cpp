#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <conio.h>
#include <time.h>
#include "myclass.cpp"

using namespace std;

int main(){
	srand(time(NULL));
	int N, i, d=800, ch=600, k, page=0;
	float l=0;
	int p=10;
	setlocale(LC_ALL, "Russian");
	cout<<"Введите кол-во точек: ";
	cin>>N;
	cout<<"Выберите тип движения: "<<endl;
	cout<<"1. Прямолинейное"<<endl;
	cout<<"2. Вокруг своей оси"<<endl;
	cout<<"Ввод: ";
	cin>>k;
	tPoint *A;
	otrez a[p];
	okr b[p];
	pryam c[p];
	trey g[p];
	ellips f[p];
	romb z[p];
	for(i=0;i<p;i++){
		a[i]=otrez(k);
		c[i]=pryam(k);
		g[i]=trey(k);
		z[i]=romb(k);
	}
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
				a[i].otris();
				a[i].animeline();
				b[i].otris();
				b[i].animeline();
				c[i].otris();
				c[i].animeline();
				g[i].otris();
				g[i].animeline();
				f[i].otris();
				f[i].animeline();
				z[i].otris();
				z[i].animeline();
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
			l+=0.1;
			for(i=0;i<N;i++){
				A[i].otris();
				a[i].otris();
				a[i].animer(l);
				b[i].otris();
				c[i].otris();
				c[i].animer(l);
				g[i].otris();
				g[i].animer(l);
				f[i].otris();
				f[i].animer(l);
				z[i].otris();
				z[i].animer(l);	
			}
			page=1-page;
			delay(10);
		}
		closegraph();
	}
	system("PAUSE");
	return 0;
}

