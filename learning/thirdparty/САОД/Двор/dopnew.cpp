#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 #define N 11//N-1 elementov
 struct versh {
  int weight;
  int value;
};
void Fillrand(versh *V1){
                
               for (int i=0;i<N;i++){V1[i].weight=rand()%200;V1[i].value=i;}
               }
               
               
               void BubbleSort(versh *a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j > i; j--) {
            if (a[j].value < a[j - 1].value) {
                int t = a[j].value;
                int t1=a[j].weight;
                a[j].value = a[j - 1].value;
                a[j].weight = a[j - 1].weight;
                a[j - 1].value = t;
                a[j - 1].weight = t1;
            }
        }
    }
}

               
int main(){
    int Aw[N][N];
 int Ap[N][N];
 int Ar[N][N];
versh V1[N];
Fillrand(V1);
 for (int i=0;i<N;i++)
 {for(int j=0;j<N;j++)
 {Aw[i][j]=0;Ap[i][j]=0;Ar[i][j]=0;}}
  
  for (int i=0;i<N;i++)
 {for(int j=i+1;j<N;j++)
 Aw[i][j]=Aw[i][j-1]+V1[j].weight;}
  //zapoln 1 diag vesov i indexov
  
  
  for(int i=0;i<N-1;i++)
 {for(int j=0;j<N-1;j++)
 {if((j-i)==0){Ap[i][j+1]=Aw[i][j+1];Ar[i][j+1]=j+1;}}}

   ////
 BubbleSort(V1, 10);
//////////ostaln diag
int j=0,m=0,min=201,x=0;
 
 for (int h=2;h<N;h++){
     for (int i=0;i<N-h;i++){
         j=i+h;
         //printf("i)%d j)%d\n",i,j);
         m=Ar[i][j-1];
         min=Ap[i][m-1]+Ap[m][j];
         for(int k=m+1;k<=Ar[i+1][j];k++)
         {x=Ap[i][k-1]+Ap[k][j];
         if(x<min){m=k;min=x;}
         }
         Ap[i][j]=min+Aw[i][j];
         Ar[i][j]=m;
         }
     
     }
     
     /*for (int h=2;h<N;h++){
        for (int i=0;i<N-h;i++){
         j=i+h;
             m=Ar[i][j-1];
         min=Ap[i][m-1]+Ap[m][j];
            for (int k = m + 1; k <= Ar[i + 1][j]; k++) 
            {
                 x = Ap[i][k - 1] + Ap[k][j];
                if (x < min) {
                    m = k;
                    min = x;
                }
            }
            Ap[i][j] = min + Aw[i][j];
            Ar[i][j] = m;
        }
    }*/

printf("matriva vesov \n");
 for (int l=1;l<N;l++){
     printf("%d ",V1[l].value);}
     printf("\n");
     for (int l=1;l<N;l++){
     printf("%d ",V1[l].weight);}
      printf("\n");
      printf("matrica height \n");
           for (int i=0;i<N;i++)
 {for(int j=0;j<N;j++){
 printf("%4d ",Aw[i][j]);}printf("\n");}
 printf("\n");printf("\n");
 printf("matrica indexov \n");
 for (int i=0;i<N;i++)
 {for(int j=0;j<N;j++){
 printf("%4d ",Ap[i][j]);}printf("\n");}
 printf("\n");printf("\n");
 for (int i=0;i<N;i++)
 {for(int j=0;j<N;j++){
 printf("%4d ",Ar[i][j]);}printf("\n");}
      system("PAUSE");    
    
    }
 
