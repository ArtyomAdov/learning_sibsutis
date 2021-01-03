#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
int M=0,C=0;
void PrintMas(int n,int *A){
int i;
for (i=0;i<n;i++) printf("%d  ",A[i]);

}
void Fillinc(int n,int *A){
int i,b=0;
for (i=0;i<n;i++) {b=b+2;A[i]=b;}
}

void Filldec(int n,int *A){
int i,b=0;
for (i=n-1;i>=0;i--) {b=b+2;A[i]=b;}
}
void Fillrand(int n,int *A){
int i,b=0;
srand((unsigned int) time(NULL));
for (i=0;i<n;i++) A[i]=rand()%100;
}
void quicksort(int *A,int l,int r){
int x,t,i,j;

M++;x=A[(l+r)/2];i=l;j=r;
while (i<=j){
      C++;while(A[i]<x){C++;i++;}
      C++;while(A[j]>x){C++;j--;}
      if(i<=j)
      {M=M+3;t=A[i];A[i]=A[j];A[j]=t;i++;j--;}
      }
      if(l<j) {quicksort(A, l, j);}
      if(i<r) {quicksort(A, i, r);}
      }
      
      int main(){int A[1000],s,i;
      for(i=100;i<501;i=i+100){
      Fillrand(i,A);
      M=0;C=0;s=0;
      quicksort(A,0,i);
      s=M+C;
      printf("%d ",s);}
      //}
      //shell 2108 5033 8246 11578 15446
      //heap 1889  4375 7118 9910 12890
      //qsort 1464 3233 5398 7795 10074
      //PrintMas(100,A);
      initwindow(1000, 800);
     setcolor(15);
      moveto(0, 800);
      outtextxy(400,400,"shell");
     lineto(160,695);
     lineto(320,550);
     lineto(480,388);
     lineto(640,222);
     lineto(800,30);
     setcolor(14);
      moveto(0, 800);
      outtextxy(550,400,"heap");
      lineto(160,705);
     lineto(320,581);
     lineto(480,445);
     lineto(640,305);
     lineto(800,155);
     setcolor(13);
      moveto(0, 800);
      outtextxy(700,400,"qsort");
      lineto(160,727);
     lineto(320,638);
     lineto(480,530);
     lineto(640,410);
     lineto(800,300);
      system("PAUSE");
      }
