#include<stdio.h>
#include<stdlib.h>
#include <time.h>
//#include <graphics.h>
int C=0;
void Fillrand(int n,int *A){
int i,b=0;
srand((unsigned int) time(NULL));
for (i=0;i<n;i++) A[i]=rand()%100;
}
void insertsort(int n,int *A){
int i;
for (int j=1;j<n;j++){int key=A[j];i=j-1;// i пред. эл. для смены местами
while ((i>=0)&&(A[i]>key)) {A[i+1]=A[i];i--;}
A[i+1]=key;;
}
}
void Fillinc(int n,int *A){
int i,b=0;
for (i=0;i<n;i++) {b=b+2;A[i]=b;}
}
void PrintMas(int n,int *A){
int i;
for (i=0;i<n;i++) printf("%d  ",A[i]);

}
void BinSearch(int n,int *A){
              int l,r,t,c,flag=1,x,l1,r1;
              printf("vvedite elemnt poiska \n");
              scanf("%d",&x);
              l=0;r=n-1;
              while (l<=r) {t=(l+r)/2;/*printf("%d ",t);*/C++;if (A[t]==x) {flag=0;c=t;}//printf("%d ",t);
    C++;if(x>A[t]) {l=t+1;/*printf("%d ",l);*/} else r=t-1;}
    
    if (flag==0){C++;l1=c;r1=c;while(A[c]==A[l1-1]) {C++;l1--;}while(A[c]==A[r1+1]) {C++;r1++;}}
     if (flag==0) for (int i=l1;i<=r1;i++)printf("%d ",i);else printf("takogo elementa netu");
            }
            
            void BinSearch2(int n,int *A){
                 int l,r,t,c,flag=1,x,r1;
                 printf("vvedite elemnt poiska \n");
              scanf("%d",&x);
              l=0;r=n-1;
              while (l<r){t=(l+r)/2; C++;if(A[t]<x) l=t+1;else r=t;
                    }
                    if (A[r]==x){C++;r1=r;while (A[r]==A[r1+1]) {C++;r1++;}}
                    if (A[r]==x) {C++;for (int i=r;i<=r1;i++)printf("%d ",i);}else printf("takogo elementa netu");
                 }
int main(){
    int A[1100],e;
    printf("vvedite sredi skol`kih el massiva iskat`");
    scanf("%d",&e);
    
    
    //printf("%d ",x);
    
    Fillrand(e,A);
    insertsort(e,A);
    //PrintMas(e,A);
    //printf("%d ",A[25]);
    PrintMas(e,A);
    printf( "\n");
    BinSearch2(e,A);
    printf("%d",C);
//    initwindow(1000, 1000);
    /*moveto(0, 1000);
    setcolor(15);
    lineto(100,520);
    lineto(500,220);
    lineto(1000,130);
    setcolor(14);
    moveto(0, 1000);
    lineto(100,730);
    lineto(500,580);
    lineto(1000,460);*/
    system("PAUSE");
}
    
