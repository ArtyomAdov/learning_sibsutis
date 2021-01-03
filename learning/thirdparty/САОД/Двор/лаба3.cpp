#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <graphics.h>
     int C,M;  
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
void PrintMas(int n,int *A){
int i;
for (i=0;i<n;i++) printf("\n %d ",A[i]);}
void Filldec(int n,int *A){
int i,b=0;
for (i=n-1;i>=0;i--) {b=b+2;A[i]=b;}
}

void Fillrand(int n,int *A){
int i,b=0;
srand((unsigned int) time(NULL));
for (i=0;i<n;i++) A[i]=rand()%1000;
}
void Fillinc(int n,int *A){
int i,b=0;
for (i=0;i<n;i++) {b=b+2;A[i]=b;}
}
void sortbubble(int n,int *A){int t;
  C=0;M=0;  
for (int i=0;i<n-1;i++){
    for (int e=0;e<n-i-1;e++){
        C++;if (A[e]>A[e+1])
    {t=A[e+1];A[e+1]=A[e];A[e]=t;M=M+3;}
    }
    }
}
int main(){

    int N=1000;
    
    initwindow(N, N);
    moveto(0, 1000);
    
    int t,r,c=10,B[1000];
   
    Fillrand(c,B);
shakersort(c,B);
PrintMas(c,B);
//int c1=(c*c-c)/2;
//int m1sred=3*c1/2;
//printf("praktika %d %d ",C,M);
//int T=C+M;
//printf("%d  ",T);
setcolor(15);
outtextxy(200,500,"puzyrek");
lineto(100,964);
lineto(200,849);
lineto(300,658);
lineto(400,397);
lineto(500,49);
setcolor(12);
outtextxy(450,500,"shaker");
moveto(0, 1000);
lineto(100,964);
lineto(200, 847);
lineto(300, 660);
lineto(400, 403);
lineto(500, 70);
//printf("teoriia shakera %d %d ",c1,m1sred);
//printf("teoriia bubble %d %d ",c1,m1sred);
//PrintMas(c,B);

system("PAUSE");
}

    
    
