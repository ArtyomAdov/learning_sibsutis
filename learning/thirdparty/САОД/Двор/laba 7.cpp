#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>

void PrintMas(int n,int *A){
int i;
for (i=0;i<n;i++) printf("%d  ",A[i]);

}
int C=0,M=0;
void shellsort(int n,int *A){
int e=1,i,B[100];
int h=n;//int (log2(n));
B[0]=1;

while (h>0) {B[e]=B[e-1]*2+1;e++;h=h/2;/*printf("%d ",h);*/}//h делить на 3 на 1000 эл дает чуть меньше C+M
e=e-2;
//printf("\n %d \n",e);
//for (i=e-1;i>=0;i--) printf("%d ",B[i]);

for(e;e>0;e--){//printf("%d ",e);
for (int j=B[e-1];j<n;j++){int key=A[j];i=j-B[e-1];M++;// i пред. эл. для смены местами
C++;while ((i>=0)&&(A[i]>key)) {A[i+B[e-1]]=A[i];i=i-B[e-1];M++;C++;}
A[i+B[e-1]]=key;M++;
}
}
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
void Fillinc(int n,int *A){
int i,b=0;
for (i=0;i<n;i++) {b=b+2;A[i]=b;}
}

void heap(int *A,int l,int r){int x,i,j;M++;x=A[l];i=l;do {j=2*(i+1)-1; if (j>r-1) break;
C++;if ((j<r-1)&&(A[j+1]<=A[j])) j=j+1;
C++;if (x<=A[j]) break;
M++;A[i]=A[j];
i=j;
} while (1);
M++;A[i]=x; 
     }
     void heapsort(int *B,int n){int l,t,r;
     l=n/2;
     while (l>=0) {heap(B,l,n);
     l=l-1;}
     r=n-1;
     while (r>0){M=M+3;t=B[0];B[0]=B[r];B[r]=t;r=r-1;heap(B,0,r);}
     
          }
     int main() {for (int n=100;n<501;n=n+100){
         int A[n],s=0;
     Fillrand(n,A);
    //for (int i=0;i<25;i++) printf("%d ",A[i]);printf("\n");
     s=0;C=0;M=0;
     heapsort(A,n);
     /*A[0]=5;
     A[1]=1;
     A[2]=2;
     A[3]=3;
     A[4]=6;
     A[5]=7;
     A[6]=8;
     A[7]=9;  1879 6252 13350 23386 36289 heap
     A[8]=10; 1638 5414 11936 21046 32548 shell */
     
      
     //heap(A,0,8);
     //for (int i=0;i<25;i++) printf("%d ",A[i]);printf("\n");
     
     s=C+M;
     printf("%d ",s);}
     //PrintMas(100,A);
     
     /*initwindow(1000, 800);
     setcolor(15);
      moveto(0, 800);
      outtextxy(600,400,"heapsort");
     lineto(200,762);
     lineto(400,675);
     lineto(600,539);
     lineto(800,339);
     lineto(1000,79);
     setcolor(14);
      moveto(0, 800);
      outtextxy(900,400,"shell");
      lineto(200,767);
     lineto(400,692);
     lineto(600,560);
     lineto(800,380);
     lineto(1000,149);*/
     
     system("PAUSE");
         }
