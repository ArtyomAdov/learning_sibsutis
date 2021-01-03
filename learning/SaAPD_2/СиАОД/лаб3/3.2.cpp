#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <clocale>
#include <math.h>
#include <graphics.h>
int BubbleSort(int);
void DrawValue(int,int);
void DrawGraphics(int);
int main()
{   int n=100;
	initwindow(700,700);
	DrawGraphics(n);
system("PAUSE");
}
int BubbleSort(int n1)
{
	if(n1>500)
	{
		return 0;//xmmm
	};
	int A[n1];
	int temp, M1=0, C1=0,T1=0;
	srand(time(NULL));
	for(int i=0;i<n1;i++)
	{
		A[i]=rand()%n1;
	};
	printf("otsortirovanii massiv=  ");
	for(int i=0;i<n1;i++) 
	{
		for(int j=i+1;j<n1;j++)
		{
			C1++;
			if(A[i]>A[j])
			{
				M1++;
				temp=A[i];
				M1++;
				A[i]=A[j];
				M1++;
				A[j]=temp;
			};
		};
	};
	T1=M1+C1;
	DrawValue(T1,n1);
	BubbleSort(n1+100);
}
void DrawGraphics(int x)
{
	setcolor(7);
	moveto(25,15);
	lineto(25,675);
	moveto(25,675);
	lineto(675,675);
	outtextxy:
		outtextxy(15,600,"50k");//50/100=0.5
		outtextxy(15,500,"100k");//100/200=0.5
		outtextxy(15,400,"150k");
		outtextxy(15,300,"200k");
		outtextxy(15,200,"250k");
		outtextxy(15,100,"300k");
        outtextxy(120,680,"100");
        outtextxy(240,680,"200");
        outtextxy(360,680,"300");
        outtextxy(480,680,"400");
        outtextxy(600,680,"500");
        outtextxy(5,15,"M+C");
        outtextxy(680,680,"N");
}
void DrawValue(int T,int n)//типо как то за y брать трудоемкость(в обратном порядке только) за x брать n после чего и как то это делить на че то чтобы в пиксли как то перевести
{
	int x=1, y=1;
	for(int i=0;i<T;i++)
	{
		moveto(x,y);
		x=x+0.5;
		y=y+0.5;
		lineto(x,y);
	};
}
