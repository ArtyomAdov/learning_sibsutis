#include<stdio.h>
#include<stdlib.h>
#include <time.h>
 
/* void SheikerSort(int *a, const int n)
    {
       int l, r, i, k, buf;
       k = l = 0;
       r = n - 2;
       while(l <= r)
       {
          for(i = l; i <= r; i++)
             if (a[i] > a[i+1])
             {
                buf = a[i]; a[i] = a[i+1]; a[i+1] = buf;
                k = i;
             }
          r = k - 1;
          for(i = r; i >= l; i--)
             if (a[i] > a[i+1])
             {
                buf = a[i]; a[i] = a[i+1]; a[i+1] = buf;
                k = i;
             }
          l = k + 1;
       }
    }*/
     int C,M;  
void shakersort(int n, int *A){
     int l=0,t,r;
     r=n;
     C=0;M=0;
     while (l<=r){//M++;?
     for (int j=r-1;j>l;j--){C++;
         if (A[j-1]>A[j])
         {t=A[j-1];A[j-1]=A[j];A[j]=t;M=M+3;}}
         l++;//M++;//?
         for (int j=l+1;j<r;j++){C++;
         if (A[j]<A[j-1]) {t=A[j-1];A[j-1]=A[j];A[j]=t;M=M+3;}}
         r--;//M++;//?
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
    int t,r,c,B[1000];
   for (c=100;c<=500;c=c+100){
    Fillrand(c,B);
sortbubble(c,B);
int c1=(c*c-c)/2;
int m1sred=3*c1/2;
//printf("praktika %d %d ",C,M);
int T=C+M;
printf("%d  ",T);}
//printf("teoriia shakera %d %d ",c1,m1sred);
//printf("teoriia bubble %d %d ",c1,m1sred);
//PrintMas(c,B);
system("PAUSE");
}
    
    
