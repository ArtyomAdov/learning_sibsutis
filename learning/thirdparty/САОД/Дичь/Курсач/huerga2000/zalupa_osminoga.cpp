#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#define N 4000
#define n 256

int *day,*w,*dateb,pointer;
unsigned long int number;
float entr,srdl;
char key_search[8];
FILE *f,*f2;
int N=4000;

struct enterprise
       {
       char fio[33];
       int number;
       char job[23];
       char dob[9];
       } *mas[4000];

struct spisok
       {
       spisok *next;
       enterprise *data;
       } *dop[1000];

void Read()
     {
     int i;
     f=fopen("BASE2.dat","rb");
     day=(int*)realloc(day,N*sizeof(int));
     for (i=0;i<N;i++) free(mas[i]);
     for (i=0;i<N;i++)
           {
           mas[i]=(enterprise*)malloc(sizeof(enterprise));
           fgets(mas[i]->fio,33,f);
           mas[i]->number=fgetc(f);
           fgetc(f);
           fgets(mas[i]->job,23,f);
           fgets(mas[i]->dob,9,f);
           day[i]=i;
           }
     fclose(f);
     }


int Compare(char s1[],char s2[],int number)
    {
    int i;
    i=0;
    do
      {
      if (s1[i]<s2[i]) return 1;
         else if (s1[i]>s2[i]) return 0;
              else i++;
      }
    while (i<number);
    return 2;
    }



void Print(spisok *p)
     {
     char h;
     while (p!=NULL)
           {
           printf("%s",p->data->fio);
           printf("%03d\t",p->data->number);
           printf("%s\t",p->data->job);
           printf("%s\n",p->data->dob);
           p=p->next;
           if (kbhit()) { h=getch(); if (h==27) break; else getch(); }
           }
     }



int LessDayAndFio(int p,int q)
    {
    if (mas[p]->dob[0]<mas[q]->dob[0]) return 1;
       else if (mas[p]->dob[0]>mas[q]->dob[0]) return 0;
            else if (mas[p]->dob[1]<mas[q]->dob[1]) return 1;
                 else if (mas[p]->dob[1]>mas[q]->dob[1]) return 0;
                      else if (Compare(mas[p]->fio,mas[q]->fio,33)==1) return 1;
                           else return 0;
    }



void QuickSort(int L,int R)
{
 int x,i,j,t;
 x=day[L]; i=L; j=R;
 while (i<=j)
       {
       while (LessDayAndFio(day[i],x)) i++;
       while (LessDayAndFio(x,day[j])) j--;
       if (i<=j)
          {
          t=day[i];
          day[i]=day[j];
          day[j]=t;
          i++; j--;
          }
       }
 if (L<j) QuickSort(L,j);
 if (R>i) QuickSort(i,R);
}


void PrintMas(void)
     {
     int i;
     char h;
     system("cls");
     for (i=0;i<N;i++)
         {
         printf("%4.d).%s  %03d  %s  %s\n",i+1,mas[day[i]]->fio,mas[day[i]]->number,mas[day[i]]->job,mas[day[i]]->dob);
         if (kbhit()) { h=getch(); if (h==27) break; else getch(); }
         }
     }


int BinSearch(struct Record **x,int N,int *pointers,char *key){
		int m,L,R;
		int i; char y[2];
		L=0;
		R=N;
		while(L<R){
				m=(L+R)/2;
				for(i=0;i<2;i++) y[i]=x[pointers[m]]->hd[i+6];
				if (strncmp(y,key,2)<0) L=m+1;
				else R=m;
		}
      for(i=0;i<2;i++) y[i]=x[pointers[R]]->hd[i+6];	
		if(strncmp(y,key,2)==0)return R;
		else return -1;
}

void OpenFile()
     {
     int i,j=0;
     unsigned char ch;
     f=fopen("BASE2.dat","rb");
     if (f==NULL) { printf("ERROR!"); getch(); exit(0); }
     for (i=0;i<n;i++)
         {
         mascode[i].a=i;
         mascode[i].p=(float)(0);
         mascode[i].l=0;
         }
     while (!feof(f))
           {
           fscanf(f,"%c",&ch);
           mascode[ch].p+=1.0;
           number++;
           }
     fclose(f);
     for (i=0;i<n;i++)
         if (mascode[i].p!=(float)(0))
            {
            mascode[i].p/=(float)number;
            j++;
            }
     number=(unsigned long int)(j);
     }

void info(){
     printf("\n");
	 printf("  [ 1 ] Print base\n");
	 printf("  [ 2 ] Sort base\n");
	 printf("  [ 3 ] Search in base\n");
	 printf("  [ESC] Exit\n");
}

main()
{ int i,key,index;
  unsigned char ch;
  while (1)
  {
	system("cls");
	info();
    ch=getch();
        switch (ch)
           {
           case 1:
                {
                Clean();
                system("cls");
                Read();
                PrintMas();
                getch();
                system("cls");
                break;
                }
           case 2:
                {
                Clean();
                Read();
                system("cls");
                QuickSort(0,N-1);
                PrintMas();
                getch();
                break;
                }
           case 3:
                {

                Clean();
                Search();
                getch();
                break;
                }
           case 4:return 0;
           }
  }
  free(mas);
  free(day);
  free(dop);
  free(w);
  free(dateb);
  free(mascode);
}

