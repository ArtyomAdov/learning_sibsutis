#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
int M=0,C=0,h[500],m;
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
void SelectSort(int a[], int n) {
     int k,i,j,q;
     M=C=0;
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

void InsertSort(int a[], int n) {
     int i,j,t;
     M=C=0;
     for (i=1;i<n;i++) {
		t=a[i];
        j=i-1;
		while ((j>=0)&(t < a[j])) {
              C++;
			  a[j+1]=a[j];
			  j--;
        }
		a[j+1]=t;
		M++;
     }
}
void BubbleSort(int a[], int n) {
     int i,j,q;
     M=C=0;
     for (i=0;i<n-1;i++) {
         for (j=n-1;j>i;j--) {
             C++;
             if (a[j]<a[j-1]) {
                M++;
                q=a[j];
                a[j]=a[j-1];
                a[j-1]=q;
             }
         }
     }
}
void ShakerSort(int a[], int n) {
     int i,j,q,R,L,k;
     L=0; R=n-1; k=R;
     M=C=0;
     do {
       for (j=R;j>=L+1;j--) {
           C++;
           if (a[j]<a[j-1]) {
              M++;
              q=a[j];
              a[j]=a[j-1];
              a[j-1]=q;
              k=j;
           }
       }
       L=k;
       for (j=L;j<=R-1;j++) {
           C++;
           if (a[j]<a[j+1]) {
              M++;
              q=a[j];
              a[j]=a[j+1];
              a[j+1]=q;
              k=j;
           }
       }
       R=k;
     } while (L<R);
}
void FillRand (int a[], int n) {
     for (int i=0; i<n; i++) a[i]=rand()%500-250;
}

float st(float x, int n) {
      if(n==0) return 1;
      return x*st(x,n-1);
}

main()
{ 
      int A[1000],i;
      srand((unsigned)time(NULL));
      printf("|   n|  Select  |  Bubble  |  Shaker  |  Insert  |\n");
      for (i=100;i<1001;i+=100) {
          printf("|%4d|",i);
          FillRand(A,i);
          SelectSort(A,i);
          printf(" %8d |",M+C); 
          FillRand(A,i);
          BubbleSort(A,i);
          printf(" %8d |",M+C);  
          FillRand(A,i);
          ShakerSort(A,i);
          printf(" %8d |",M+C);
          FillRand(A,i);
          InsertSort(A,i);
          printf(" %8d |",M+C);   
          printf("\n");                                                
      }
      printf("\n");    
      h[0]=1;
      printf("|   n|  q  |  H  |   M+C   |\n");
      int j;
      for (i=100;i<1001;i+=100) {
          m=int(log(i)/log(2))-1;
          for (j=1;j<m;j++) h[j]=(st(3,j+1)-1)/2;                            
          printf("|%4d|",i);
          printf("%4d |",m);
          printf("  ?  |");
          FillRand(A,i);
          ShellSort(A,i);
          printf(" %7d |",M+C); 
          printf("\n");                                                
      }
      printf("\n");
      printf("n=1000\n|      h      |    M+C    |\n");
      m=1000/2;
      for (j=1;j<m;j++) h[j]=j*2;                            
      printf("| 1,2,4,6...  |");
      FillRand(A,1000);
      ShellSort(A,1000);
      printf("  %7d  |",M+C); 
      printf("\n");                
      m=1000/3;
      for (j=1;j<m;j++) h[j]=j*3;                            
      printf("| 1,3,9,27... |");
      FillRand(A,1000);
      ShellSort(A,1000);
      printf("  %7d  |",M+C); 
      printf("\n"); 
      m=10; 
      for (j=1;j<m;j++) h[j]=h[j-1]*2;                            
      printf("| 1,2,4,8...  |");
      FillRand(A,1000);
      ShellSort(A,1000);
      printf("  %7d  |",M+C);       
      printf("\n");                                                      
      system("pause");
      initwindow(1100,750);
      int select=0,bubble=0,shaker=0,insert=0;
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
      outtextxy(0,550,"SelectSort");
      setcolor(3);
      outtextxy(0,600,"BubbleSort"); 
      setcolor(14);
      outtextxy(0,650,"ShakerSort");
      setcolor(8);
      outtextxy(0,700,"InsertSort");                
      for (i=1;i<1000;i+=1) {
          FillRand(A,i);
          SelectSort(A,i);
          setcolor(4);
          line(i-1,500-(select/1000),i,500-((M+C)/1000));
          select=M+C;
          FillRand(A,i);
          BubbleSort(A,i);
          setcolor(3);
          line(i-1,500-(bubble/1000),i,500-((M+C)/1000));
          bubble=M+C;
          FillRand(A,i);
          ShakerSort(A,i);
          setcolor(14);
          line(i-1,500-(shaker/1000),i,500-((M+C)/1000));
          shaker=M+C;
          FillRand(A,i);
          InsertSort(A,i);
          setcolor(8);
          line(i-1,500-(insert/1000),i,500-((M+C)/1000));
          insert=M+C;
      }
      system("pause");
      closegraph;
}
