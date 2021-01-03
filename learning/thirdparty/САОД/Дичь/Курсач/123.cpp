#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define N 4000
#define n 256

int *day,*w,*dateb,pointer;
unsigned long int number;
float entr,srdl;
char key_search[8];
FILE *f,*f2;

struct enterprise
       {
       char fio[33];
       int number;
       char job[23];
       char dob[9];
       } *mas[N];

struct spisok
       {
       spisok *next;
       enterprise *data;
       } *dop[1000];

struct vertex
       {
       vertex *l;
       vertex *r;
       enterprise *data;
       int ves;
       } *root;

struct kod
       {
       unsigned char a;
       float p;
       char code[50];
       int l;
       } mascode[n];

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

void FillRandW(int mas[],int count)
     {
     for (int i=0;i<count;i++) mas[i]=random(100)+1;
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

int CompareDate(char s1[],char s2[])
    {
    char p1[2],p2[2];
    int i=7,k;
    while (1)
       {
       p1[0]=s1[i-1];
       p1[1]=s1[i];
       p2[0]=s2[i-1];
       p2[1]=s2[i];
       k=Compare(p1,p2,2);
       if (k==1 || k==0) break;
          else i-=3;
       if (i==1 && k==2) break;
       }
    return k;
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

void Print_tree(vertex *p)
     {
     if (p==NULL) return;
     Print_tree(p->l);
     printf("%s",p->data->fio);
     printf("%03d\t",p->data->number);
     printf("%s\t",p->data->job);
     printf("%s\n",p->data->dob);
     Print_tree(p->r);
     if (kbhit()) { getch(); getch(); }
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

int LessDate(int p,int q)
    {
    if (CompareDate(dop[p]->data->dob,dop[q]->data->dob)==1) return 1;
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

void QuickSort_tree(int L,int R)
{
 int x,i,j,t;
 x=dateb[L]; i=L; j=R;
 while (i<=j)
       {
       while (LessDate(dateb[i],x)) i++;
       while (LessDate(x,dateb[j])) j--;
       if (i<=j)
          {
          t=dateb[i];
          dateb[i]=dateb[j];
          dateb[j]=t;
          i++; j--;
          }
       }
 if (L<j) QuickSort_tree(L,j);
 if (R>i) QuickSort_tree(i,R);
}

void PrintMas(void)
     {
     int i;
     char h;
     clrscr();
     for (i=0;i<N;i++)
         {
         printf("%4.d).%s  %03d  %s  %s\n",i+1,mas[day[i]]->fio,mas[day[i]]->number,mas[day[i]]->job,mas[day[i]]->dob);
         if (kbhit()) { h=getch(); if (h==27) break; else getch(); }
         }
     }

void Add(char s[],int x,int index)
{
   vertex **p;
   p=&root;
   while (*p!=NULL)
         {
         if (CompareDate(s,(*p)->data->dob)==1) p=&((*p)->l);
            else p=&((*p)->r);
         }
   if (*p==NULL)
      {
      (*p)=(vertex*)malloc(sizeof(vertex));
      (*p)->data=dop[dateb[index]]->data;
      (*p)->r=(*p)->l=NULL;
      (*p)->ves=x;
      }
}

void A2(int L,int R)
     {
     int i,wes=0,sum=0;
     if (L<=R)
        {
        for (i=L;i<=R;i++) wes+=w[i];
        for (i=L;i<=R-1;i++)
            {
            if ((sum<wes/2) && (sum+w[i]>=wes/2)) break;
            sum+=w[i];
            }
        Add(dop[dateb[i]]->data->dob,w[i],i);
        A2(L,i-1);
        A2(i+1,R);
        }
     }

void Search_tree(vertex *p)
     {
     spisok *t;
     if (p==NULL) return;
     while (p!=NULL)
           {
           if (CompareDate(key_search,p->data->dob)==1) p=p->l;
              else if (CompareDate(key_search,p->data->dob)==0) p=p->r;
                   else if (CompareDate(key_search,p->data->dob)==2)
                       {
                       printf("%s%03d\t%s\t%s\n",p->data->fio,p->data->number,p->data->job,p->data->dob);
                       p=p->r;
                       while (CompareDate(key_search,p->data->dob)==2)
                             {
                             printf("%s%03d\t%s\t%s\n",p->data->fio,p->data->number,p->data->job,p->data->dob);
                             p=p->r;
                             }
                       pointer=1;
                       return;
                       }
           }
     }

void Search()
     {
     spisok *p,*head,*tail;
     int i,m,left,right,j,index=0;
     char s[3];
     clrscr();
     head=(spisok*)malloc(sizeof(spisok));
     head=NULL;
     tail=(spisok*)&head;
     Read();
     QuickSort(0,N-1);
     s[0]='\0';
     printf("Vvedite den' rozhdeniya:");
     scanf("%s",s);
     left=0; right=N-1;
     while (left<right)
           {
           m=(int)((left+right)/2);
           if (Compare(mas[day[m]]->dob,s,2)==1) left=m+1;
              else right=m;
           }
     if (Compare(mas[day[right]]->dob,s,2)==2)
        {
        for (j=right+1;j<N;j++) if (Compare(mas[day[j]]->dob,s,2)!=2) break;
        for (i=right;i<j;i++)
            {
            p=(spisok*)malloc(sizeof(spisok));
            p->data=mas[day[i]];
            tail->next=p;
            tail=p;
            dop[index]=(spisok*)malloc(sizeof(spisok));
            dop[index]->data=mas[day[i]];
            index++;
            }
        tail->next=NULL;
        Print(head);
        getch();
        w=(int*)malloc(index*sizeof(int));
        FillRandW(w,index);
        dateb=(int*)malloc(index*sizeof(int));
        for (i=0;i<index;i++) dateb[i]=i;
        QuickSort_tree(0,index-1);
        root=NULL;
        A2(0,index-1);
        printf("\n\n");
        Print_tree(root);
        pointer=0; key_search[0]='\0';
        printf("\nVvedite datu rozdeniya (format: dd-mm-gg):");
        scanf("%s",key_search);
        if (strlen(key_search)!=8)
           {
           printf("ERROR! Nevernaya dlina stroki!");
           return;
           }
        Search_tree(root);
        if (pointer==0) printf("Net cheloveka s takoi datoi rozhdeniya!");
        }
        else printf("Net cheloveka, rodivshegosya v etot den'!");
     }

void Paintmenu(void)
{ window(1,1,80,25);
  textbackground(0);
  clrscr();
  textcolor(10);
  gotoxy(16,1); cprintf("Rabotu vypolnil student gruppy P-71 Chuchelin Kirill");
  textcolor(12);
  gotoxy(32,3); cprintf("Fail bazy: BASE2.dat");
  window(21,5,63,19);
  textbackground(7);
  textcolor(15);
  /*cprintf(" ษออออออออออออออออออออออออออออออออออออออ" \n\r");
  cprintf(" บ                                      บ \n\r");
  cprintf(" บ                                      บ \n\r");
  cprintf(" บ                                      บ \n\r");
  cprintf(" บ                                      บ \n\r");
  cprintf(" บ                                      บ \n\r");
  cprintf(" บ                                      บ \n\r");
  cprintf(" บ                                      บ \n\r");
  cprintf(" บ                                      บ \n\r");
  cprintf(" บ                                      บ \n\r");
  cprintf(" บ                                      บ \n\r");
  cprintf(" บ                                      บ \n\r");
  cprintf(" ศออออออออออออออออออออออออออออออออออออออผ ");*/
}

void Printmenu(int index)
{ char menu[5][22]=
  {
  {' ',' ',' ',' ','P','r','o','s','m','o','t','r',' ','b','a','z','y',' ',' ',' ',' ','\0'},
  {' ',' ',' ',' ',' ',' ','S','o','r','t','i','r','o','v','k','a',' ',' ',' ',' ',' ','\0'},
  {' ',' ',' ',' ',' ',' ',' ',' ','P','o','i','s','k',' ',' ',' ',' ',' ',' ',' ',' ','\0'},
  {' ',' ',' ',' ',' ','K','o','d','i','r','o','v','a','n','i','e',' ',' ',' ',' ',' ','\0'},
  {' ',' ',' ',' ',' ',' ',' ',' ','V','y','h','o','d',' ',' ',' ',' ',' ',' ',' ',' ','\0'}
  };
  int k;
  window(27,6,59,16);
  textbackground(7);
  clrscr();
  textcolor(0);
  for (k=1;k<6;k++)
      {
      gotoxy(1,k*2);
      if (k==index)
         {
         textbackground(3);
         cprintf(">>  ");
         cputs(menu[k-1]);
         cprintf("  <<");
         }
      else
          {
          textbackground(15);
          cprintf("    ");
          cputs(menu[k-1]);
          }
      }
}

Number(void)
{ int index; char key;
  index=1;
  Paintmenu();
  while (1)
        {
        switch(key)
                   {
                   case 80: {if (index==5) index=1; else index++;} break;
                   case 72: {if (index==1) index=5; else index--;} break;
                   case 13: return(index); break;
                   }
        Printmenu(index);
        key=getch();
        }
}

void Clean(void)
{ window(1,1,80,25);
  textbackground(0);
  clrscr();
  textcolor(95);
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

void DelBlank()
{
   int i,j,k;
   kod temp;
   for (i=0;i<n-1;i++)
       {
       k=1;
       if (mascode[i].p==(float)(0))
       for (j=i+1;j<n;j++)
           if (k)
              if (mascode[j].p!=(float)(0))
                 {
                 temp=mascode[i];
                 mascode[i]=mascode[j];
                 mascode[j]=temp;
                 k=0;
                 }
       }
   i=0;
   while (mascode[i].p!=0.0) i++;
   number=(unsigned long int)(i);
}

void Gilbert_Mur()
     {
     float q[n],s=0.0;
     int i,j=0;
     q[0]=mascode[0].p/2; mascode[0].l=(int)(-log(mascode[0].p)/log(2)+2);
     s=mascode[0].p;
     for (i=1;i<number;i++)
         {
         q[i]=s+mascode[i].p/2;
         mascode[i].l=(int)(-log(mascode[i].p)/log(2)+2);
         s+=mascode[i].p;
         }
         for (i=0;i<number;i++)
             for (j=0;j<mascode[i].l;j++)
                 {
                 q[i]*=2;
                 mascode[i].code[j]=(int)(q[i]);
                 if (q[i]>1) q[i]--;
                 }
     for (i=0;i<number;i++)
         {
         entr+=-mascode[i].p*log(mascode[i].p)/log(2);
         srdl+=mascode[i].l*mascode[i].p;
         }
     }

void Table()
     {
     gotoxy(1,1); printf("Simvol");
     gotoxy(20,1); printf("Veroyatnost'");
     gotoxy(40,1); printf("Kodovoe slovo");
     gotoxy(60,1); printf("Dlina kodovogo slova");
     }

void PrintKod()
     {
     int i,j,k=2;
     Table();
     for (i=0;i<number;i++)
         {
         gotoxy(3,k);
         printf("%c ",mascode[i].a);
         gotoxy(20,k);
         printf("%f",mascode[i].p);
         gotoxy(40,k);
         for (j=0;j<mascode[i].l;j++) printf("%d",mascode[i].code[j]);
         gotoxy(70,k);
         printf("%d",mascode[i].l);
         if (k-20==0) { getch(); k=1; clrscr(); Table(); }
         k++;
         }
     printf("\n\nEntropiya=%f\n",entr);
     printf("Srednyaya dlina=%f",srdl);
     }

main()
{ int i,key,index;
  unsigned char ch;
  randomize();
  while (1)
  {
  textbackground(0);
  clrscr();
  textcolor(0);
  _setcursortype(_NOCURSOR);
  index=Number();
  switch(index)
           {
           case 1:
                {
                Clean();
                clrscr();
                Read();
                PrintMas();
                getch();
                clrscr();
                break;
                }
           case 2:
                {
                Clean();
                Read();
                clrscr();
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
           case 4:
                {
                Clean();
                clrscr();
                number=0; entr=(float)(0); srdl=(float)(0);
                OpenFile();
                DelBlank();
                Gilbert_Mur();
                PrintKod();
                f=fopen("BASE2.dat","rb");
                f2=fopen("Kod.dat","wb");
                if (f==NULL || f2==NULL) { printf("ERROR!"); getch(); exit(0); }
                while (!feof(f))
                      {
                      fscanf(f,"%c",&ch);
                      for (i=0;i<number;i++)
                          if (ch==mascode[i].a)
                             for (int j=0;j<mascode[i].l;j++)
                                 fprintf(f2,"%c",mascode[i].code[j]);
                      }
                fcloseall();
                getch();
                break;
                }
           case 5:return 0;
           }
  }
  free(mas);
  free(day);
  free(dop);
  free(w);
  free(dateb);
  free(mascode);
}

