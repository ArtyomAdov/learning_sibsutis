#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 #define N 51

struct tree {
  int score;
  int weight;
  tree *l, *r;
} r2;
 struct versh {
  int weight;
  int value;
};
void Fillrand(versh *V1){
                
               for (int i=0;i<N;i++){V1[i].weight=rand()%200;V1[i].value=i;}
               }
               
void add (tree * &t,int score,int weight) {
if ( t==NULL ) {
t = new tree; 

t->score=score;
t->weight=weight;
t->l = t->r = NULL;

}else{
if (score < t->score )
add( t->l, score,weight );
else add( t->r,score,weight );
}}

void quicksort1weight(versh *a, int n,int c,int b) {
    for (int i = 1; i < n; i++) {
        for (int j = n - 1; j > i; j--) {
            if (a[j].weight > a[j - 1].weight) {
                int t = a[j].value;
                int t1=a[j].weight;
                a[j].value = a[j - 1].value;
                a[j].weight = a[j - 1].weight;
                a[j - 1].value = t;
                a[j - 1].weight = t1;
            }
        }
    }
}
void BubbleSortscore(versh *a, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = n - 1; j > i; j--) {
            if (a[j].value < a[j - 1].value) {
                int t = a[j].value;
                int t1=a[j].weight;
                a[j].value = a[j - 1].value;
                a[j].weight = a[j - 1].weight;
                a[j - 1].value = t;
                a[j - 1].weight = t1;
            }
        }
    }
}
void quicksortscore(versh *A,int l,int r){
int x,t,i,j,t1;

x=A[(l+r)/2].value;i=l;j=r;
while (i<=j){
      while(A[i].value<x){i++;}
      while(A[j].value>x){j--;}
      if(i<=j)
      {t=A[i].value;
      t1=A[i].weight;
	  A[i].value=A[j].value;
	  A[i].weight=A[j].weight;
	  A[j].value=t;
	  i++;
	  j--;}
      }
      if(l<j) {quicksortscore(A, l, j);}
      if(i<r) {quicksortscore(A, i, r);}
      }
      
	  void quicksortweight(versh *A,int l,int r){
int x,t,i,j,t1;

x=A[(l+r)/2].weight;i=l;j=r;
while (i<=j){
      while(A[i].weight<x){i++;}
      while(A[j].weight>x){j--;}
      if(i<=j)
      {t=A[i].weight;
      t1=A[i].value;
	  A[i].weight=A[j].weight;
	  A[i].value=A[j].value;
	  A[j].weight=t;
	  i++;
	  j--;}
      }
      if(l<j) {quicksortscore(A, l, j);}
      if(i<r) {quicksortscore(A, i, r);}
      }
      
void A1(versh* ver, 
tree* &roota1) {
   quicksort1weight(ver,N,1,N-1);
    
    for (int i = 1; i < N; i++) 
    add(roota1, ver[i].value,ver[i].weight);
}
void A2(versh* ver, 
tree* &roota1,int L,int R) {
    quicksortscore(ver,1,N-1);
	 int wes = 0, sum = 0, i = 0;
      if (L <= R) {
        for (i = L; i < R; i++) wes += ver[i].weight;
        for (i = L; i < R; i++) {
            if (sum < wes/2 && sum + ver[i].weight > wes/2) break;
            sum += ver[i].weight;
        }
        add(roota1, ver[i].value,ver[i].weight);
        A2(ver, roota1, L, i - 1);
        A2(ver, roota1, i + 1, R);
    }
      }
int print_tree(tree *q){           
    if(!q)   return 0;      
    print_tree(q->l);
    printf("%d ",q->score);
     printf("%d\n",q->weight);
    print_tree(q->r);
}
////
int razmer(tree *p){  
    int r=0, r1=0, r2=0;                                               
    if(p==NULL)  return 0;                                                           
    else{
	    r1=razmer(p->l);
    	r2=razmer(p->r);
    	return (1+r1+r2);
	}
}////
int Sum(tree *p){ 
    int sum=0, sum1=0, sum2=0;
    if(!p)  return 0; 
	else{                                                            
    	sum1=Sum(p->l);
    	sum=p->score;
    	sum2=Sum(p->r);
    	return (sum+sum1+sum2);
	}
}
////
float ves(tree *p){  
    int r=0, r1=0, r2=0;                                               
    if(p==NULL)  return 0;                                                           
    else{
	    r1=ves(p->l);
    	r2=ves(p->r);
    	return (p->weight+r1+r2);
	}
}
////
float CDP(tree *p, int L){ 
    int s1=0, s2=0;
    if(!p)  return 0; 
	else{                                                           
    	s1=CDP(p->l, L+1);
    	s2=CDP(p->r, L+1);
    	return (L*p->weight+s1+s2);
	}
}
int main(){

versh V1[N];
Fillrand(V1);

tree *r1=NULL,*r2=NULL;
A1(V1,r1);
int a1raz=razmer(r1);
int s1=Sum(r1);
float key1=CDP(r1,1)/ves(r1);
 print_tree(r1);
 
 A2(V1,r2,1,N-1);
 int a2raz=razmer(r2);
 int s2=Sum(r2);
 float key2=CDP(r2,1)/ves(r2);
 print_tree(r2);
 printf("razmer %d summa %d vysota %f\n",a1raz,s1,key1);
 printf("\n razmer %d summa %d vysota %f",a2raz,s2,key2);

 system("PAUSE");


}
