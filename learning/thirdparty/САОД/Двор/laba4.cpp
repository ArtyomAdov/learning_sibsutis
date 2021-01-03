#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <graphics.h>
#include <math.h>
int M=0,C=0;
void shakersort(int n, int *A){
     int l=0,t,r,k;
     k=n-1;
     
     r=n-1;
     C=0;M=0;
     while (l<r){//M++;?
     for (int j=r;j>l;j--){C++;
         if (A[j-1]>A[j])
         {t=A[j-1];A[j-1]=A[j];A[j]=t;M=M+3;k=j;}}
         l=k;//M++;//?
         for (int j=l+1;j<=r;j++){C++;
         if (A[j]<A[j-1]) {t=A[j-1];A[j-1]=A[j];A[j]=t;M=M+3;k=j-1;}}
         r=k;//M++;//?
         } }
void sortbubble(int n,int *A){int t;
  C=0;M=0;  
for (int i=0;i<n-1;i++){
    for (int e=0;e<n-i-1;e++){
        C++;if (A[e]>A[e+1])
    {t=A[e+1];A[e+1]=A[e];A[e]=t;M=M+3;}
    }
    }
}
void SelectSort(int n,int *A){
   int j,i,t,temp=0;
   C=0;M=0;  
     for (j=0;j<n-1;j++){
         t=j;
     for (i=j+1;i<n;i++) {C++;if (A[i]<A[t]) t=i;}
     //if(t!=j){
     temp=A[j];
     A[j]=A[t];
     A[t]=temp;
     M=M+3;}
     //}
}
void PrintMas(int n,int *A){
int i;
for (i=0;i<n;i++) printf("\n %d ",A[i]);}
void insertsort(int n,int *A){
int i;
for (int j=1;j<n;j++){int key=A[j];i=j-1;M++;;// i пред. эл. для смены местами
while ((i>=0)&&(A[i]>key)) {A[i+1]=A[i];i--;M++;C++;}
A[i+1]=key;M++;
}
}
void shellsort(int n,int *A){
int e=1,i,B[100];
int h=n;//int (log2(n));
B[0]=1;

while (h>0) {B[e]=B[e-1]*2+1;e++;h=h/2;/*printf("%d ",h);*/}//h делить на 3 на 1000 эл дает чуть меньше C+M
e=e-2;
//printf("\n %d \n",e);
for (i=e-1;i>=0;i--) printf("%d ",B[i]);

for(e;e>0;e--){//printf("%d ",e);
for (int j=B[e-1];j<n;j++){int key=A[j];i=j-B[e-1];M++;;// i пред. эл. для смены местами
while ((i>=0)&&(A[i]>key)) {A[i+B[e-1]]=A[i];i=i-B[e-1];M++;C++;}
A[i+B[e-1]]=key;M++;
}
}
}
void Fillrand(int n,int *A){
int i,b=0;
srand((unsigned int) time(NULL));
for (i=0;i<n;i++) A[i]=rand()%1000;
}
int main(){int A[1100];
int j,s,c=1000;
int N=1000;
    
    /*initwindow(1000, 630);
    moveto(0, 630);
setcolor(15);
outtextxy(400,400,"insert");
lineto(50,627);
lineto(100,620);
lineto(250,567);
lineto(500,378);
moveto(0, 630);
setcolor(14);
outtextxy(300,250,"bubble");
lineto(50,624);
lineto(100,604);
lineto(250,471);
lineto(500,3);
moveto(0, 630);
setcolor(13);
outtextxy(400,250,"shaker");
lineto(50,624);
lineto(100,604);
lineto(250,470);
lineto(500,90);
moveto(0, 630);
setcolor(12);
outtextxy(475,400,"select");
lineto(50,627);
lineto(100,620);
lineto(250,568);
lineto(500,381);*/
Fillrand(c,A);
//PrintMas(c,A);
printf("\n");
shellsort(c,A);
//PrintMas(c,A);
s=M+C;
//printf("\n %d %d \n", M, C);
printf("\n %d \n",s);
system("PAUSE");
}
