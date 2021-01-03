#include <stdio.h>
#include <stdlib.h>
void FillInc (int a[], int n) {
     a[0]=rand()%20-10;
     for (int i=1; i<n; i++) a[i]=a[i-1]+rand()%4;
}
void FillDec (int a[], int n) {
     a[0]=rand()%20+10;
     for (int i=1; i<n; i++) a[i]=a[i-1]-rand()%4;
}
void FillRand (int a[], int n) {
     for (int i=0; i<n; i++) a[i]=rand()%20-10;
}
int CheckSum (int a[], int n) {
    int c=0;
     for (int i=0; i<n; i++) {c+=a[i];}
     return c;
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
     printf("SR DLINA SERII = %2.2f\n",float(n)/float(c));
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
      FillInc(A,n); 
      PrintMas(A,n);
      printf("CheckSum = %d\n",CheckSum(A,n));
      printf("RunNumber = %d\n\n",RunNumber(A,n));      
      FillDec(A,n);       
      PrintMas(A,n);
      printf("CheckSum = %d\n",CheckSum(A,n));  
      printf("RunNumber = %d\n\n",RunNumber(A,n));    
      FillRand(A,n); 
      PrintMas(A,n); 
      printf("CheckSum = %d\n",CheckSum(A,n));                 
      printf("RunNumber = %d\n\n",RunNumber(A,n));      
      system("pause");
}
