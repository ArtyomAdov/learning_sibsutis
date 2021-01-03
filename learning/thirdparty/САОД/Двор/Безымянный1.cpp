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

void Fillrand(int n,int *A){
int i,b=0;
srand((unsigned int) time(NULL));
for (i=0;i<n;i++) A[i]=rand()%1000;
}

int Checksumm(int n,int *A){
int i,s=0;
for (i=0;i<n;i++) s+=A[i];
return s;
}

int RunNumber(int n,int *A){
int i,b=1;
for (i=0;i<n-1;i++) {if (A[i+1]<A[i]) b++;}
//printf("serii %d ",b);
return b;
}

void PrintMas(int n,int *A){
int i;
for (i=0;i<n;i++) printf("%d  ",A[i]);

}

int main(){
    int B[1000];
    int serii,c=10;
    double s,e;
    int i;
    //Fillinc(c,B);
    //serii=RunNumber(c,B);
    //PrintMas(c,B);
    //printf("%d ",serii);
    //Filldec(c,B);
    //PrintMas(c,B);
    //serii=RunNumber(c,B);
    //printf("%d ",serii);
    
    Fillrand(c,B);
    serii=RunNumber(c,B);
    PrintMas(c,B);
    e=double (c)/serii;
    printf("\n %lf ",e);
    printf("\n %d ",serii);
    
system("PAUSE");
}
    
    
