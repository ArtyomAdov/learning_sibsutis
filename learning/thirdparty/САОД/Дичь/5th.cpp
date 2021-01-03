#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
int C=0;
void FillInc (int a[], int n) {
     for (int i=0; i<n; i++) a[i]=i;
}

int BSearch1(int a[], int n, int x) {
     int l=0;
     int r=n-1,m;
     C=0;
     bool b=false;
     while (l<=r) {
           	m=(l+r)/2;
           	C++;
           	if (a[m]==x) return C;;
           	C++;
           	if (a[m]<x) l=m+1; else r=m-1;
     }
}

int BSearch2(int a[], int n, int x) {
     int l=0;
     int r=n-1,m;
     C=0;
     bool b=false;
     while (l<r) {
           	m=(l+r)/2;
           	C++;
           	if (a[m]<x) l=m+1; else r=m;
     }
     C++;
     if (a[r]==x) return C;
}

int main()
{ 
      int A[1000],i,f;
      srand(time(NULL));      
      printf("|    n |  C 1st  |  C 2nd  |\n");
      for (i=100;i<1001;i+=100) {
          printf("| %4d |",i); 
          f=i/10;   
          FillInc(A,i);
          printf(" %6d  |",BSearch1(A,i,f));
          printf(" %6d  |",BSearch2(A,i,f));
          printf("\n");
      }
      printf("\n");                                             
      system("pause");
//      initwindow(1100,750);
//      int b1=0,b2=0;
//      line(0,500,1100,500);
//      line(0,0,0,750);
//      outtextxy(0,0,"500");
//      outtextxy(0,100,"400");
//      outtextxy(0,200,"300");
//      outtextxy(0,300,"200");
//      outtextxy(0,400,"100");
//      outtextxy(100,500,"100");
//      outtextxy(200,500,"200");
//      outtextxy(300,500,"300");
//      outtextxy(400,500,"400");
//      outtextxy(500,500,"500");  
//      outtextxy(600,500,"600");  
//      outtextxy(700,500,"700");  
//      outtextxy(800,500,"800");  
//      outtextxy(900,500,"900");  
//      outtextxy(1000,500,"1000");  
//      setcolor(4);
//      outtextxy(0,550,"BSearch1");
//      setcolor(3);
//      outtextxy(0,600,"BSearch2");  
//      FillInc(A,1000);                    
//      for (i=1;i<1000;i++) {
//          setcolor(4);
//          line(i-1,500-b1,i,500-BSearch1(A,i,i/3));
//          b1=C;
//          setcolor(3);
//          line(i-1,500-b2,i,500-BSearch2(A,i,i/3));
//          b2=C;          
//      }
//      system("pause");
//      closegraph;
}
