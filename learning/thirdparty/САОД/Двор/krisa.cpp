#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>

int M = 0, C = 0, MQ = 0, CQ = 0, MS = 0, CS = 0;
struct spis {
    spis *next;
	int num;
};

struct tle {
    spis *head; 
	spis *tail;
};

void FillInc(int *a,int n) {
	for (int i=0;i<n;i++) {
		a[i]=i+i;
	}
}

void FillDec(int *a,int n) {
	for (int i=0;i<n;i++) {
		a[i]=n-i;
	}
}

void FillRand(int *a,int n) {
    srand(time(NULL));
	for (int i=1;i < (n + 1); i++) {
		a[i]=rand()%500;
	}
}

void Split(spis* S, spis* &a, spis* &b, int &n) {    
    spis *p,*q;
    a = S,
    b = S->next,
    n = 1;
    p = a,
    q = b;
    while (q) {
        n++;
        p->next=q->next;
        p=q;
        q=q->next;
        }
}

void MergeSort(spis* &S) {
    int m, n; 
    spis *a,*b; 
    tle c[2];
    int p, q, r, i;
    Split(S, a, b, n);
    p = 1;
    while (p < n) {
        c[0].tail = (spis *)&c[0].head;
        c[1].tail = (spis *)&c[1].head; 
        i = 0; 
        m = n;
    while (m > 0) {
       if (m >= p) q = p; 
       else q = m;
       m -= q;
       if (m >= p) r = p; 
       else r = m;
       m -= r;
       
     
       while (q && r) {
          CS++;
          if (a->num <= b->num) {
             MS++;
             c[i].tail->next = a;
             c[i].tail = a;
             a = a->next;
             q--;
            }
          else {
             MS++;
             c[i].tail->next = b;
             c[i].tail = b;
             b = b->next;
             r--;
            }
          }
       while (q > 0) {
          MS++;
          c[i].tail->next = a;
          c[i].tail = a;
          a = a->next;
          q--;
         }
       while (r > 0) {
          MS++;
          c[i].tail->next = b;
          c[i].tail = b;
          b = b->next;
          r--;
         }
       
       
       i = 1-i;
      }
        a = c[0].head;
        b = c[1].head;
        p = 2*p;
    }
    c[0].tail->next = NULL;
    S = c[0].head;
}

void QuickSort(int *array, int L, int R) {
    int X=array[L], i=L, j=R;
    MQ++;
    while (i<=j) {
        CQ++;
        while (array[i]<X) { CQ++; i++; }
        CQ++;
        while (array[j]>X) { CQ++; j--; }
        if (i<=j) {
            int t=array[i];
            MQ++;
            array[i]=array[j];
            MQ++;
            array[j]=t;
            MQ++;
            i++;
            j--; }
    }
    if (L<j) QuickSort (array, L, j);
    if (i<R) QuickSort (array, i, R);
}

void HeapBuild(int *a,int L,int R) {
    int X=a[L],i=L;
    M++;
    do {
        int j=2*i;
        if (j>R) break;
        C++;
        if (j<R && a[j+1]<=a[j]) j=j+1;
        C++;
        if (X<=a[j]) break;
        a[i]=a[j];
        M++;
        i=j;
    }
    while (1);
    a[i]=X;
    M++;
}

void HeapSort(int *a,int N,int L,int R) {
    L=N/2;
    while (L>0) {
        HeapBuild(a,L,N);
        L=L-1;
    }
    R=N;
    while (R>1) {
        int t=a[1];
        a[1]=a[R];
        a[R]=t;
        M = M + 3;
        R=R-1;
        HeapBuild(a,1,R);
    }
}

spis *Spis_up(int n) {
	spis *p = NULL, *head = NULL;
	int i, S = n;
	for(i = 0; i < n; i++)	{
		S--;
		p = new spis;
		p->num = S;
		p->next = head;
		head = p;
	}
	return head;
}

spis *Spis_down(int n) {
     spis *p = NULL, *head = NULL;
     int i, S = 0;
     for(i = 0; i < n; i++) {
     	S++;
     	p = new spis;
     	p->num = S;
     	p->next = head;
     	head = p;
     }
     return head;
}

spis *Spis_rand(int n) {
	int i;
	spis *p = NULL, *head = NULL;
	for(i = 1; i < (n + 1); i++) {
		p = new spis;
		p->num = rand()%100;
		p->next = head;
		head = p;
	}
	return head;
}

void PrintSpis(spis *head) {
     spis *p;
     printf("\n");
     for(p = head; p; p = p->next) printf("%d ", p->num);
     printf("\n\n");
}	  

int graphic() {
    int i, n, A[502];
    spis *p;
    initwindow(1000, 640); 
    setcolor(RED);
    moveto(0, 640);
    for(n = 1; n <= 500; n++) {
      FillRand(A, n);
      HeapSort(A, n, 1, n);
      int ch1 = C + M;
      lineto((n*40)-20, 640-ch1);
      C = 0, M = 0;
    }
    setcolor(BLUE);
    moveto(0, 640);
    for(n = 1; n <= 500; n++) {
      FillRand(A, n); 
      QuickSort(A, 1, n);
      int ch2 = CQ + MQ;
      lineto((n*40)-20, 640-ch2);
      CQ = 0, MQ = 0;
    }
    setcolor(WHITE);
    moveto(0, 640);
    for(n = 2; n <= 500; n++) {
      p = Spis_rand(n);
      MergeSort(p);
      int ch3 = MS + CS;
      lineto((n*40)-20, 640-ch3);
      CS = 0, MS = 0;
    }
    setcolor(RED); outtextxy(850,20,"HeapSort - Red");
    setcolor(BLUE); outtextxy(850,40,"QuickSort - Blue");
    setcolor(WHITE); outtextxy(850,60,"MergeSort - White");
    setcolor(15);
    outtextxy(950,610,"N");
    outtextxy(25,30,"M + C");    
}

int main() {
	struct spis *q;
	int n, i, M = 0, C = 0, ch = 0;
	printf("Enter number of spis: ");
	scanf("%d", &n);
	q = Spis_rand(n);
    PrintSpis(q);
	printf("Sorted spis: ");
    MergeSort(q);
    PrintSpis(q);
	printf ("   n          M+C MergeSort          \n");
	printf ("          Dec     Random    Inc    \n");
	for(i = 1; i <= 5; i++) {
		int y, m, a;
		spis *p, *t, *q;
		n = i * 100;
		int	A[n];
		printf("  %d", n);
		p = Spis_down(n);
		MergeSort(p);
		ch = CS + MS;
		printf("%9d", ch);
		CS = 0, MS = 0;
		t = Spis_rand(n);
		MergeSort(t);
		ch = CS + MS;
		printf("%9d", ch);
		CS = 0, MS = 0;
		q = Spis_up(n);
		MergeSort(q);
		ch = CS + MS;
		printf("%9d", ch);
		CS = 0, MS = 0;
		printf("\n");
	}
	graphic();
    system("pause");
    return 0; 
}    
