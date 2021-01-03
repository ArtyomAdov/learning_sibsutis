#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int C=0,M=0;
void Fillinc(int n,int *A){
int i,b=0;
for (i=0;i<n;i++) {b=b+2;A[i]=b;}
}

void Filldec(int n,int *A){
int i,b=0;
for (i=n-1;i>=0;i--) {b=b+2;A[i]=b;}
}
void RunNumber(int n,int *A){
int i,b=1;
for (i=0;i<n-1;i++) {if (A[i+1]<A[i]) b++;}
printf("serii %d ",b);
}
void Checksumm(int n,int *A){
int i,s=0;
for (i=0;i<n;i++) s+=A[i];
printf("kontr summa %d  ",s);
}
void PrintMas(int n,int *A){
int i;
for (i=0;i<n;i++) printf("\n %d ",A[i]);

}
void Fillrand(int n,int *A){
int i,b=0;
srand((unsigned int) time(NULL));
for (i=0;i<n;i++) A[i]=rand()%1000;
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
int main(){
    int B[1000],c=100,i,e,k;
    Fillrand(c,B);
    Checksumm(c,B);
    RunNumber(c,B);
//PrintMas(c,B);
SelectSort(c,B);
Checksumm(c,B);
RunNumber(c,B);
printf("teoriia %d %d ",C ,M);
k=(c*c-c)/2;e=3*(c-1);
printf("\n ");
printf("praktika %d %d",k,e);
printf("\n ");
//PrintMas(c,B);
system("PAUSE");
}
    
