#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
int M=0,C=0,h[500],m,g;
void ShellSort(int a[], int n) {
     int i,j,k,t;
     C=M=0;
     for (k=h[m-1];k>=0;k--) {
         for (i=k+1; i<n; i++) {
             t=a[i];
             j=i-k;
             while ((j>=0)&(t<a[j])) {
                   C++;
                   a[j+k]=a[j];
                   j-=k;
             }
             a[j+k]=t;
             M++;
         }
     }

}
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
void Heap (int a[], int l, int r) {
     int x=a[l],i=l,j;
     while (1) {
    	j=2*i;
    	C++;
    	if (j>r) break;
    	C+=2;
    	if ((j<r)&(a[j+1]>=a[j])) j++;
    	C++;
        if (x>=a[j]) break;
        a[i]=a[j];
        i=j;
        M++;        
     }
     a[i]=x;
}
void HeapSort(int a[], int n) {
     int l=n/2;
     int k;
     M=C=0;
     while (l>=0) {
           Heap(a,l,n-1);
           l--;
     }
     int r=n;
     while (r>0) {
           k=a[0];
           a[0]=a[r-1];
           a[r-1]=k;
           M++;
           r--;
           Heap(a,0,r-1);
     }
}
void QuickSort(int a[], int l, int r, int gg) {
     int i=l,j=r,q,x;
     x=a[l];
     if (gg>g) g=gg;
     while (i<j) {
           while (a[i]<x) {i++; C++;}
           while (a[j]>x) {j--; C++;}
           C++;
           if (i<=j) {
              q=a[i];
              a[i]=a[j];
              a[j]=q;
              M++;
              i++;
              j--;
           }
     }
     C++;
     if (l<j) QuickSort(a,l,j,gg+1);
     C++;
     if (i<r) QuickSort(a,i,r,gg+1);     
}
void QuickSort2(int a[], int l, int r, int gg) {
     int i,j,q,x;
     while (l<r) {     
         i=l;j=r;
         x=a[l];
         if (gg>g) g=gg;
         while (i<j) {
               while (a[i]<x) {i++; C++;}
               while (a[j]>x) {j--; C++;}
               if (i<=j) {
                  q=a[i];
                  a[i]=a[j];
                  a[j]=q;
                  i++;
                  j--;
               }
         }
         if (j-l<r-i) {QuickSort2(a,l,j,gg+1); l=i;} else
                      {QuickSort2(a,i,r,gg+1); r=j;} 
     }
}
float st(float x, int n) {
      if(n==0) return 1;
      return x*st(x,n-1);
}
main()
{ 
      int A[1000],i,j;
      srand((unsigned)time(NULL));
      FillRand(A,20);
      HeapSort(A,20);
      printf("|   n |        QuickSort(M+C)      |\n");
      printf("|     |   inc   |   dec   |  rand  |\n");      
      for (i=100;i<1001;i+=100) {
          printf("|%4d |",i);
          FillInc(A,i);
          M=C=0;
          QuickSort(A,0,i-1,1);   
          printf("%8d |",M+C);
          FillDec(A,i);
          M=C=0;          
          QuickSort(A,0,i-1,1);   
          printf("%8d |",M+C);
          FillRand(A,i);
          M=C=0;          
          QuickSort(A,0,i-1,1);   
          printf("%7d |",M+C);                                                           
          printf("\n");
      }
      printf("\n|   n |    QuickSort1    |    QuickSort2    |\n");
      printf("|     | inc | dec | rand | inc | dec | rand |\n");      
      for (i=100;i<1001;i+=100) {
          printf("|%4d |",i);
          FillInc(A,i);
          g=0;
          M=C=0;          
          QuickSort(A,0,i-1,1);   
          printf("%4d |",g);
          FillDec(A,i);
          g=0;  
          M=C=0;                 
          QuickSort(A,0,i-1,1);   
          printf("%4d |",g);
          FillRand(A,i);
          g=0;  
          M=C=0;                  
          QuickSort(A,0,i-1,1);   
          printf("%5d |",g); 
          FillInc(A,i);
          g=0;
          M=C=0;          
          QuickSort2(A,0,i-1,1);   
          printf("%4d |",g);
          FillDec(A,i);
          g=0;  
          M=C=0;                 
          QuickSort2(A,0,i-1,1);   
          printf("%4d |",g);
          FillRand(A,i);
          g=0;  
          M=C=0;                  
          QuickSort2(A,0,i-1,1);   
          printf("%5d |",g);                                                                     
          printf("\n");
      }      
      printf("\n");  
      system("pause");  
      h[0]=1;
      m=int(log(i)/log(2))-1;
      for (j=1;j<m;j++) h[j]=int(st(3,j+1)-1)/2;                                               
      initwindow(1100,700);
      int shell=0,heap=0,quick=0;
      line(0,500,1100,500);
      line(0,0,0,750);
      outtextxy(0,0,"500000");
      outtextxy(0,100,"400000");
      outtextxy(0,200,"300000");
      outtextxy(0,300,"200000");
      outtextxy(0,400,"100000");
      outtextxy(100,500,"100");
      outtextxy(200,500,"200");
      outtextxy(300,500,"300");
      outtextxy(400,500,"400");
      outtextxy(500,500,"500");  
      outtextxy(600,500,"600");  
      outtextxy(700,500,"700");  
      outtextxy(800,500,"800");  
      outtextxy(900,500,"900");  
      outtextxy(1000,500,"1000");  
      setcolor(4);
      outtextxy(0,550,"HeapSort");
      setcolor(3);
      outtextxy(0,600,"ShellSort");  
      setcolor(5);
      outtextxy(0,650,"QuickSort");                      
      for (i=1;i<1000;i++) {
          FillRand(A,i);
          HeapSort(A,i);
          setcolor(4);
          line(i-1,500-(heap/1000),i,500-((M+C)/1000));
          heap=M+C;
          FillRand(A,i);
          ShellSort(A,i);
          setcolor(3);
          line(i-1,500-(shell/1000),i,500-((M+C)/1000));
          shell=M+C;
          FillRand(A,i);
          M=C=0;          
          QuickSort(A,0,i-1,1);
          setcolor(5);
          line(i-1,500-(quick/1000),i,500-((M+C)/1000));
          quick=M+C;          
      }
      system("pause");
      closegraph;
}
