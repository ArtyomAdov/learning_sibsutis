#include <stdio.h>
#include <time.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#define n2 5
using namespace std;
void Fillrand(int n,int *A){
int i,b=0;
srand((unsigned int) time(NULL));
for (i=0;i<n;i++) A[i]=rand()%1000;
}
void sortbubble(int n,int *A,int *B){int t;
for (int i=0;i<n-1;i++){
    for (int e=0;e<n-i-1;e++){
        if ((A[B[e]])>(A[B[e+1]]))
    {t=B[e+1];B[e+1]=B[e];B[e]=t;}
    }
    }
}
int main(){
    
 struct tov {int nomer;char str[15] ;};
 struct tov all[n2];
 int B[n2];
 for (int k=0;k<n2;k++)B[k]=k;
 printf("\n vvedite informaciyu ob abonentah \n");
   for (int i=0;i<n2;i++){scanf("%d %s",&all[i].nomer,all[i].str);
   }
   int j;
   
int m=0;
printf("vvedite nomer polia po kotoromu sortirovat`: 1)nomer telefona 2)imia ");
scanf("%d",&m);
   int i;
    switch(m){
              case 1 :
                   
           
                   int t2;
for (int j=1;j<n2;j++)
{
    t2=all[B[j]].nomer;
    int key2=B[j];i=j-1;
    while ((i>=0)&&(all[B[i]].nomer>t2)) {
          B[i+1]=B[i];i--;
    }
    B[i+1]=key2;
}

break;

case 2 :
      char t[15];
      for (int j=1;j<n2;j++){
           strcpy(t,all[B[j]].str);int key2=B[j];i=j-1;
while ((i>=0)&&strcmp(all[B[i]].str,t)>0) {B[i+1]=B[i];i--;}
B[i+1]=key2;
}
break;      
 }
 
 
for (int k=0;k<n2;k++)printf("%d %s \n ",all[B[k]].nomer,all[B[k]].str);
   printf("vvedite nomer polia po kotoromu iskat` 1)nomer telefona 2)imia \n");
      int m2;int n=n2;        
      scanf("%d",&m2);
      
      switch(m2){
                 case 1 : int x;
                      printf("vvedite klu4 poiska \n");
scanf("%d",&x);   
                 int l,r,t,c,r1;                              
              l=0;r=n-1;
              while (l<r){t=(l+r)/2; 
              if (all[B[t]].nomer<x) 
              l=t+1;else r=t;
                    }
                    if (all[B[r]].nomer==x){r1=r;while (all[B[r]].nomer==all[B[r1+1]].nomer) {r1++;}}
                    if (all[B[r]].nomer==x) {for (int i=r;i<=r1;i++)printf("nomer po spisku v otsortirovannom spravo4nike= %d,nomer po spisku v ishodnom spravo4nike=%d, 4elovek %s ",i,B[i],all[B[i]].str);}else printf("4eloveka s takim nomerom netu");               
                 break;
            
            case 2 : {char x[15];
                 printf("vvedite klu4 poiska \n");
gets(x);
gets(x);
                 l=0;r=n-1;
              while (l<r){t=(l+r)/2; if (strcmp(all[B[t]].str,x)<0) l=t+1;else r=t;
                    }
                    if (strcmp(all[B[r]].str,x)==0){r1=r;while (strcmp(all[B[r]].str,all[B[r1+1]].str)==0) {r1++;}}
                    if (strcmp(all[B[r]].str,x)==0) {for (int i=r;i<=r1;i++)printf("nomer po spisku v otsortirovannom spravo4nike= %d,nomer po spisku v ishodnom spravo4nike=%d, 4elovek %s ",i,B[i],all[B[i]].str);}else printf("4eloveka s takim nomerom netu");
      break;}
      }
      
 system("PAUSE");
} 
