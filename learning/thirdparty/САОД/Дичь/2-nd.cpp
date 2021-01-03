#include <stdio.h>
#include <stdlib.h>
int M=0,C=0;
void SelectSort(int a[], int n) {
     int k,i,j,q;
     for (i=0; i<n-1;i++) {
         k=i;
         for (j=i+1;j<n;j++) {
             C++;
             if (a[j]<a[k]) k=j;
         }
         if (i==k) continue;
         M++;
         q=a[i];
         a[i]=a[k];
         a[k]=q;
     }
}
void FillRand (int a[], int n) {
     for (int i=0; i<n; i++) a[i]=rand()%20-10;
}
void FillInc (int a[], int n) {
     a[0]=rand()%20-10;
     for (int i=1; i<n; i++) a[i]=a[i-1]+rand()%4;
}
void FillDec (int a[], int n) {
     a[0]=rand()%20+10;
     for (int i=1; i<n; i++) a[i]=a[i-1]-rand()%4;
}
int CheckSum (int a[], int n) {
     if (n<0) return 0; else return a[n-1]+CheckSum(a,n-1);
}
int RunNumber (int a[], int n) {
     int p,c;
     p=a[0];
     c=0;
     for (int i=1; i<n; i++) {
         if (a[i]<p) c++;
         p=a[i];
     }
     c++;
     return(c);
}
void PrintMas (int a[], int n) {
     for (int i=0; i<n; i++) printf("%3d",a[i]);
     printf("\n");
}
main()
{ 
      int A[256],n;
      scanf("%d",&n);  
      FillRand(A,n); 
      PrintMas(A,n); 
      printf("CheckSum = %d\n",CheckSum(A,n));                 
      printf("RunNumber = %d\n\n",RunNumber(A,n));
      SelectSort(A,n);
      PrintMas(A,n);
      printf("CheckSum = %d\n",CheckSum(A,n));                 
      printf("RunNumber = %d\n\n",RunNumber(A,n));   
      printf("fact C = %d, (n^2-n)/2 = %d\n",C,(n*n-n)/2); 
      printf("fact M = %d,    3(n-1) = %d\n\n",M,3*(n-1)); 
      printf("-----------------------------------------------------\n");  
      C=M=0;
      FillInc(A,n);
      PrintMas(A,n); 
      printf("CheckSum = %d\n",CheckSum(A,n));                 
      printf("RunNumber = %d\n\n",RunNumber(A,n));
      SelectSort(A,n);
      PrintMas(A,n);
      printf("CheckSum = %d\n",CheckSum(A,n));                 
      printf("RunNumber = %d\n\n",RunNumber(A,n));   
      printf("fact C = %d, (n^2-n)/2 = %d\n",C,(n*n-n)/2); 
      printf("fact M = %d,    3(n-1) = %d\n\n",M,3*(n-1)); 
      printf("-----------------------------------------------------\n");  
      C=M=0;
      FillDec(A,n);
      PrintMas(A,n); 
      printf("CheckSum = %d\n",CheckSum(A,n));                 
      printf("RunNumber = %d\n\n",RunNumber(A,n));
      SelectSort(A,n);
      PrintMas(A,n);
      printf("CheckSum = %d\n",CheckSum(A,n));                 
      printf("RunNumber = %d\n\n",RunNumber(A,n));   
      printf("fact C = %d, (n^2-n)/2 = %d\n",C,(n*n-n)/2); 
      printf("fact M = %d,    3(n-1) = %d\n\n",M,3*(n-1));               
      system("pause");
}
