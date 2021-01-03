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
	setlocale(LC_ALL, "Russian");
	cout<<"Введите кол-во точек: ";
	cin>>N;
	cout<<"Выберите тип движения: "<<endl;
	cout<<"1. Прямолинейное"<<endl;
	cout<<"2. Вокруг своей оси"<<endl;
	cout<<"Ввод: ";
	cin>>k;
	tPoint *A;
	otrez a(k);
	okr b;
	pryam c(k);
	trey g(k);
	ellips f;
	romb z(k);
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
			a.otris();
			a.animeline();
			b.otris();
			b.animeline();
			c.otris();
			c.animeline();
			g.otris();
			g.animeline();
			f.otris();
			f.animeline();
			z.otris();
			z.animeline();
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
			a.otris();
			a.animer();
			b.otris();
			c.otris();
			c.animer();
			g.otris();
			g.animer(l);
			l+=0.1;
			f.otris();
			f.animer();
			z.otris();
			z.animer();
			for(i=0;i<N;i++){
				A[i].otris();	
			}
			page=1-page;
			delay(10);
		}
		closegraph();
	}
	system("PAUSE");
	return 0;
}

