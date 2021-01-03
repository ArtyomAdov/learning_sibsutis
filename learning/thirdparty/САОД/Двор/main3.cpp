#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void drawbrick(int x,int y,int a,int b,int color){
	setcolor(color);
	moveto (x,y);
	lineto(x+a,y);
	lineto(x+a,y+b);
	lineto(x,y+b);
	lineto(x,y);
	setfillstyle(SOLID_FILL, GREEN);
	floodfill(x+2,y+2,color);
}

void clearbrick(int x,int y,int a,int b,int color,int A[][40]){
	setcolor(RED);
	moveto (x+1,y+1);
	lineto(x+a-1,y+1);
	lineto(x+a-1,y+b-1);
	lineto(x+1,y+b-1);
	lineto(x+1,y+1);
	setfillstyle(SOLID_FILL, BLACK);
	floodfill(x+3,y+3,RED);
	setcolor(BLACK);
	moveto (x+1,y+1);
	lineto(x+a-1,y+1);
	lineto(x+a-1,y+b-1);
	lineto(x+1,y+b-1);
	lineto(x+1,y+1);
	moveto(x,y);
	lineto(x+a,y);
	lineto(x+a,y+b);
	lineto(x,y+b);
	lineto(x,y);
	setcolor(13);
	int e=y/b;
	int k=x/a;

	if((A[k-1][e])&&(k>0)){
		moveto((k)*a,e*b);
		lineto((k)*a,e*b+b);
	}
	if(A[k+1][e]){
		moveto((k)*a+a,e*b);
		lineto(x+a,e*b+b);
	}
	if((A[k][e-1])&&(e>0)){
		moveto((k)*a,e*b);
		lineto((k)*a+a,e*b);
	}
	if((A[k][e+1])){
		moveto((k)*a,e*b+b);
		lineto((k)*a+a,e*b+b);
	}
}

void drawball(int x,int y,int rball){
	setcolor(15);
	circle(x,y,rball);
}

void clearball(int x,int y,int rball){
	setcolor(0);
	circle(x,y,rball);
}

void drawplato(int x,int y,int a,int b,int color){
	setcolor(color);
	moveto (x,y);
	lineto(x+a,y);
	lineto(x+a,y+b);
	lineto(x,y+b);
	lineto(x,y);
	setfillstyle(SOLID_FILL, color);
	floodfill(x+2,y+2,color);
}
void clearplato(int x,int y,int a,int b,int color){
	setcolor(color);
	moveto (x,y);
	lineto(x+a,y);
	lineto(x+a,y+b);
	lineto(x,y+b);
	lineto(x,y);
	setfillstyle(SOLID_FILL, color);
	floodfill(x+2,y+2,BLACK);
}
void moveball(int A[][40],int* x,int* y,float *fi,float* a,float* b,int* RX1,int* RX2,int *Yflag,int *N,int* abrick,int* bbrick,int *rball,int *bplato,int *aplato)
{
	if(kbhit()) return;
	srand((unsigned int) time(NULL));
	int f,j,i;
	float v,temp,fitt,sdvig;
	v=20;
	if(*fi==0) *fi=((rand()%628)*0.01);*a=v*cos(*fi); *b=v*sin(*fi);

	while(true){
		if(*fi > 3 && *fi < 3.3) *fi=*fi+0.1;*a=v*cos(*fi); *b=v*sin(*fi);
		
		*Yflag=*y;

		drawball(*x,*y,*rball);
		delay(40);
		clearball(*x,*y,*rball);
		
		if (*x + *a + *rball > *N) *a=-*a;
		if (*x + *a - *rball < 0) *a=-*a;
		if (*y + *b + *rball < 0) *b=-*b;
		if (*y + *b + *rball + *bplato + 5 > *N/2){
			if(*x - *rball > *RX1 && *x - *rball < *RX2){
				temp=*RX2-*x;fitt=3.14*(temp/ *aplato);
				if(fitt < 0.2) fitt = 0.2;
				if(fitt > 3) fitt = 3;
				if(fitt > 1.55 && fitt < 1.65){
					sdvig = ((rand()%100+50)*0.01);
					fitt = fitt + sdvig;
				}
				*a = v*cos(-fitt);
				*b = v*sin(-fitt);
			}
		}

		if (*y + *b + *rball > *N/2) return;
		int i1 = (int(*x - *rball + *a) / (*abrick));
		int j1 = (int(*y - *rball + *b) / (*bbrick));
		int t = j1*(*bbrick);
		int t2 = int(*y+*b-*bbrick-*rball);
		int z = i1*(*abrick);
		int z2 = int(*x+*a-*abrick-*rball);
		if (A[i1][j1]==1){
			A[i1][j1]=0;clearbrick((i1)*(*abrick),(j1)*(*bbrick),*abrick,*bbrick,13,A);
			*b=-*b;
			*a=-*a;
		}
		*x=*x+int(*a);
		*y=*y+int(*b);
		if(kbhit()) break;
		if (*Yflag > *N/2 - *bplato - *rball - 15) break;
	}
}

int main(){
	int N=1200;
	initwindow(N,N/2);
	int xpl=N/2,
		xinc=15,
		c,
		abrick=60,
		bbrick=25,
		aplato=100,
		bplato=15,
		rball=10;//abrick=>N/40;bbrick=>N/80 (dlia menu nastroek)

	int A[40][40];
	int ypl=N/2-bplato-5;//massiv logi4 peremennyh dlia hraneniia informacii o blokah

	for (int i=0;i<N/abrick;i++)
		for (int j=0;j<5;j++) A[i][j]=1;
	//zapolnenie oblasti s blokami v flagah
	
	for (int i=0;i<N/abrick;i++)
		for (int j=5;j<(N/2)/bbrick;j++) A[i][j]=0; //zapolnenie pustoi oblasti v flagah

	for (int i=0;i<N/abrick;i++)
		for (int j=0;j<5;j++) if(A[i][j]==1) drawbrick(i*abrick,j*bbrick,abrick,bbrick,13);
	//vyvod blokov 4erez flagi

	drawplato(xpl, ypl, aplato, bplato, 9);
	int x=330,
		y=220,
		RX1=x,
		RX2=x+aplato,
		Yflag=0,
		godmod=N/2-bplato-rball+15;//godmod-10=oby4nui mod
	float a=0,
		b=0,
		fi=0;
	while(true){
		moveball(A,&x,&y,&fi,&a,&b,&RX1,&RX2,&Yflag,&N,&abrick,&bbrick,&rball,&bplato,&aplato);
		if (Yflag > godmod) break;
		c=getch();
		if (c == 75 || c == 77){
			switch(c){
				case 77:
					if (xpl+xinc/2+aplato < N){
						clearplato(xpl, ypl, aplato, bplato, 0);
						xpl = xpl+xinc;
						RX1 = xpl;
						RX2 = RX1+aplato;
						drawplato(xpl, ypl, aplato, bplato, 9);
						setfillstyle(SOLID_FILL, BLACK);
						bar(0, N/2, xpl, ypl);
						bar(xpl+aplato, ypl, N, N/2);
					}
				break;

				case 75:
					if (xpl-xinc/2 > 0){
						clearplato(xpl, ypl, aplato, bplato, 0);
						xpl = xpl-xinc;
						RX1 = xpl;
						RX2 = RX1+aplato;
						drawplato(xpl, ypl, aplato, bplato, 9);
						setfillstyle(SOLID_FILL, BLACK);
						bar(0, N/2, xpl, ypl);
						bar(xpl+aplato, ypl, N, N/2);
					}
				break;
				default:; break;
			}
		}
	}
	return 0;
}
