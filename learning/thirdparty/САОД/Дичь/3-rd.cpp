#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
int M=0,C=0;
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
void FillInc (int a[], int n) {
     a[0]=rand()%10-5;
     for (int i=1; i<n; i++) a[i]=a[i-1]+rand()%4;
}
void FillDec (int a[], int n) {
     a[0]=rand()%10+5;
     for (int i=1; i<n; i++) a[i]=a[i-1]-rand()%4;
}
main()
{ 
      int A[500],i;
      srand((unsigned)time(NULL));
      printf("|   n|        M+C Bubble        |       M+C Shaker         | \n");
      printf("|    |  DEC   |  RAND  |   INC  |  DEC   |  RAND  |   INC  | \n"); 
      for (i=100;i<501;i+=100) {
          printf("| %3d|",i);
          FillDec(A,i);
          BubbleSort(A,i);
          printf("%8d|",M+C);
          FillRand(A,i);
          BubbleSort(A,i);
          printf("%8d|",M+C);          
          FillInc(A,i);
          BubbleSort(A,i);
          printf("%8d|",M+C);  
          FillDec(A,i);
          ShakerSort(A,i);
          printf("%8d|",M+C);
          FillRand(A,i);
          ShakerSort(A,i);
          printf("%8d|",M+C);          
          FillInc(A,i);
          ShakerSort(A,i);
          printf("%8d|",M+C);
          printf("\n");                    
      }
      printf("\n");
      printf("|   n|        M+C Bubble        |       M+C Shaker         | \n");
      printf("|    |  DEC   |  RAND  |   INC  |  DEC   |  RAND  |   INC  | \n"); 
      for (i=100;i<501;i+=100) {
          printf("| %3d|",i);
          printf("%8d|",3*(i*i-i)/2+(i*i-i)/2);
          printf("%8d|",3*(i*i-i)/4+(i*i-i)/2);
          printf("%8d|",(i*i-i)/2);
          printf("%8d|",3*(i*i-i)/2+(i*i-i)/2);
          printf("%8d|",3*(i*i-i)/4+(i*i-i)/2);
          printf("%8d|",(i*i-i)/2);
          printf("\n");   
      }      
      system("pause");
      initwindow(600,650);
      int pb=0,ps=0;
      line(0,500,650,500);
      line(0,0,0,600);
      outtextxy(0,0,"250000");
      outtextxy(0,100,"200000");
      outtextxy(0,200,"150000");
      outtextxy(0,300,"100000");
      outtextxy(0,400,"50000");
      outtextxy(100,500,"100");
      outtextxy(200,500,"200");
      outtextxy(300,500,"300");
      outtextxy(400,500,"400");
      outtextxy(500,500,"500");  
      setcolor(4);
      outtextxy(0,550,"BubbleSort");
      setcolor(6);
      outtextxy(0,600,"ShakerSort");          
      for (i=1;i<500;i+=1) {
          FillRand(A,i);
          BubbleSort(A,i);
          setcolor(4);
          line(i-1,500-(pb/500),i,500-((M+C)/500));
          pb=M+C;
          FillRand(A,i);
          ShakerSort(A,i);
          setcolor(6);
          line(i-1,500-(ps/500),i,500-((M+C)/500));
          ps=M+C;          
      }
      system("pause");
}
