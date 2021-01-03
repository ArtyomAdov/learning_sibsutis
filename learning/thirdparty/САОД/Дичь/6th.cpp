#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <string.h>
int N=10;
char A[4][100][15];
int Index[100],col=0;
void QSort(int n, int l, int r);
void Read() {
     FILE *f;
     f=fopen("tele.txt","r");
     while (!feof(f)) {
           fscanf(f,"%s %s %s %s",A[0][col],A[1][col],A[2][col],A[3][col]);
           Index[col]=col;
           col++;
     }
     fclose(f);
}
void Write(int k) {
     int i;
     system("cls");
     if (k==-1) {for (i=0;i<col;i++) Index[i]=i;} else
        QSort(k,0,col-1);
     for (i=0;i<col;i++) printf("%2d) tel. %s.  h. %4s  st. %s  -  %s\n",i+1,A[0][Index[i]],A[1][Index[i]],A[2][Index[i]],A[3][Index[i]]);
     printf("\n");
}
int BSearch(int k, int n, char x[15]) {
     int l=0;
     int r=n-1,m;
     while (l<r) {
           	m=(l+r)/2;
           	if (strcmp(A[k][Index[m]],x)<0) l=m+1; else r=m;
     }
     if (strcmp(A[k][Index[r]],x)==0) return r; else return -1;
}
void QSort(int n, int l, int r) {
     int i=l,j=r,q;
     char x[15];
     strcpy(x,A[n][Index[l]]);
     while (i<j) {
           while (strcmp(A[n][Index[i]],x)<0) i++;
           while (strcmp(A[n][Index[j]],x)>0) j--;
           if (i<=j) {
              q=Index[i];
              Index[i]=Index[j];
              Index[j]=q;
              i++;
              j--;
           }
     }
     if (l<j) QSort(n,l,j);
     if (i<r) QSort(n,i,r);     
}
void Add() {
     FILE *f;
     f=fopen("tele.txt","a");
     fprintf(f,"\n%s %s %s %s",A[0][N],A[1][N],A[2][N],A[3][N]);
     N++;
}                                         
void Delete(int num) {        
     FILE *f;
     f=fopen("tele.txt","w");
     for (int i=0;i<col;i++) if (i!=num) {
         fprintf(f,"%s %s %s %s",A[0][i],A[1][i],A[2][i],A[3][i]);
         if ((col-i)!=1) 
            if (num==col-1) {
               if (col-1-i!=1)
                  fprintf(f,"\n");
            } else fprintf(f,"\n");
     }
     fclose(f);
     exit(0);
}
main() { 
      char c,s[15],key;
      int i,num;
      setlocale(LC_ALL,".866");
      Read();
      Menu:
      printf("1) Print\n");      
      printf("2) Search\n");
      printf("3) Add\n");
      printf("4) Delete\n");
      printf("5) Exit\n");  
      key=getchar();
      c=getchar();  
      switch (atoi(&key)) {
             case 1: {printf("Who search?\n0-Tel\n1-Num\n2-Street\n3-SecName\n");
                     c=getchar();                    
                     Write(atoi(&c));
                     break;}
             case 2: {printf("Who search?\n0-Tel\n1-Num\n2-Street\n3-SecName\n");
                     c=getchar();
                     printf("Key for search: "); 
                     scanf("%s",s);
                     QSort(atoi(&c),0,col-1);
                     num = BSearch(atoi(&c),col,s); 
                     if (num==-1) printf("Not found\n"); else
                        printf("tel. %s.  h. %4s  st. %s  -  %s\n",A[0][Index[num]],A[1][Index[num]],A[2][Index[num]],A[3][Index[num]]);
                     break;}
             case 3: {
                     printf("[tel num street fam]: \n");
                     scanf("%s %s %s %s",A[0][N],A[1][N],A[2][N],A[3][N]);
                     Add();
                     break;}
             case 4: {
                     Write(-1);
                     printf("Number: \n");
                     scanf("%d",&num);
                     Delete(num-1);
                     break;}                     
             case 5: {return 0; break;}
             default: {goto Menu; break;}
      }        
      system("pause");
}
