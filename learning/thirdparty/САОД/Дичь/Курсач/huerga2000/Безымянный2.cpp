#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;
struct enterprise { // ��������� ��������� ��� ����������
	char FIO[30];// ������� ��� �������� 32 �������
	short int number; // �����
	char rang[22]; // ����� ����
	char date[10]; // ���� ���������
}ent[4000] = {0}; // ������ 4000 ����� ��������
struct spis {
	char FIO[30];// ������� ��� �������� 32 �������
	short int number; // �����
	char rang[22]; // ����� ����
	char date[10]; // ���� ���������
	char key[7];
	spis *next;
};
char f[4000][7]; // ������ ����� ��� ���������� 
unsigned short int index[4000]; // ��������� ������
struct tle {spis *head; spis *tail; bool b;};
void conversion(int n) { // ��������������
     for (int i=0; i<n; i++) {
         f[i][0]=ent[i].date[6];
         f[i][1]=ent[i].date[7];
         f[i][2]=ent[i].date[3];                  
         f[i][3]=ent[i].date[4];                  
         f[i][4]=ent[i].date[0];
         f[i][5]=ent[i].date[1];          
         f[i][6]=0;
     }
}
spis *DigitalSort(spis *S, int L){
 int j,i;
 int d;
 spis *p,*t;
 tle Q[4000];
 bool b;
 // ������������� �������� Q
 for (j=L-1;j>=0;j--) {
     for (i=0;i<256;i++) Q[i].b=false;
     p=S;         
     //����������� ��������� �� ������ S � ������� Q �� j - �� ����� 
     while (p!=NULL) {
           d=int(p->key[j])+128;         
           if (!Q[d].b) {
              Q[d].head=Q[d].tail=p;
              Q[d].b=true;
           } else {
             Q[d].tail->next=p;
             Q[d].tail=p;
           }
           p=p->next; 
     }
     b=false;
     // ���������� �������� Q � ������ S 
     for (i=175;i<186;i++) {
         if (Q[i].b) {
            if (!b) {
               t=Q[i].head;
               b=true;
            } else p->next=Q[i].head;
            p=Q[i].tail;            
         }
     }
     p->next=NULL;
     S=t;
 }
 return S;
}
int cmp(char s1[], char s2[]) {
    if (s1[0]<s2[0]) return -1;
    if (s1[0]>s2[0]) return  1;    
    if (s1[1]<s2[1]) return -1;
    if (s1[1]>s2[1]) return  1;        
    return 0;
}
int BSearch(int n, char x[4]) { // �������� �����
     int l=0; // ����� ������� - 0
     int r=n-1,m; // ������ ������� - n-1
     while (l<r) { // ���� ����� ������� ����� ������
           	m=(l+r)/2; // ������� ������ ������������ ��������
           	if (cmp(f[index[m]],x)<0) l=m+1; else r=m; // ���� ����������� ������� ������ �����(�����) �� ������� ����� ������� � �����
           	   // ����� ������� ������ ������� � �����
     }
     if (cmp(f[index[r]],x)==0) return r; // ���� � ����� ������ ������� ������� ������ �����(�������� ����� ����� ������� ��������������� �����) ���������� ��� �����
     return -1; // ����� �������� -1
}
int main() {
    int i,n,num;
    FILE *fp;
    spis *S,*t,*p;
    fp=fopen("testBase2.dat", "rb"); // ��������� ���� ��� ��������� ������
    n=fread((enterprise*)ent, sizeof(enterprise), 4000, fp); // ���������� � n ���������� ��������� ����� � ��������� ���� � ��������� loc
     // ��� ��� ��� �������� ���������� �������, ��������� 4000 �����
    fclose(fp);  // ��������� ����    
    for (i=0;i<n;i++) index[i]=i; // ���������� ������� �� ������� ��� ����������
    conversion(n); // ����������� ������ ��� ����������
    p=new spis;
    strcpy(p->FIO,ent[0].FIO);
    strcpy(p->rang,ent[0].rang);
    p->number=ent[0].number;
    strcpy(p->key,f[0]);
    strcpy(p->date,ent[0].date);
    t=S=p;
    for (i=1;i<n;i++) {
        p=new spis;
        strcpy(p->FIO,ent[i].FIO);
        strcpy(p->rang,ent[i].rang);
        p->number=ent[i].number;
        strcpy(p->key,f[i]);
        strcpy(p->date,ent[i].date);
        t->next=p;
        t=p;
    } 
    t->next=NULL; 
    S=DigitalSort(S,6);    
    p=S;  
    i=1;  
    while (p!=NULL) {
          printf("%4d %30s %4d %12s %10s\n",i,p->FIO,p->number,p->rang,p->date); // ������� i-��� ������
          p=p->next;
          if (i%200==0) getchar(); // ���� ������ ������ �� ���� ������� enter
          i++;          
    }
    p=S;
    char x[4];
    printf("Search for year: ");
    scanf("%s",x); // ��������� ���� ��� ������ �� ������
    for (i=0;i<n;i++) {
        strcpy(ent[i].FIO,p->FIO);
        strcpy(ent[i].rang,p->rang);
        ent[i].number=p->number;
        strcpy(f[i],p->key);
        strcpy(ent[i].date,p->date);
        p=p->next;
    }    
    num=BSearch(n,x); // ��������� ����� � ���������� ��������� � num
    if (num==-1) { // ���� ��������� -1 ������ ������� �� ������ � ������� ����������
       printf("Not found!\n");
       system("pause"); // �����
       return 0; // � �����
    }
    i=num; // i = ������ ������ ������ ���������� �������� ���������������� �����
    while (cmp(ent[i].date+6,x)==0) { // ���� i��� ������� ������������� �����
          printf("%4d %30s %4d %12s %10s\n",i+1,ent[i].FIO,ent[i].number,ent[i].rang,ent[i].date); // ������� ������
          i++; // ����������� i
          if ((i-num+1)%100==0) getchar(); // ������ 100 ��������� ���� ������� enter
    }
    system("pause"); // ����� 
	return 0;// �����
} 

