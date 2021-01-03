#include <stdio.h>
#include<time.h>
#include <stdlib.h>
#include<iostream>

struct tree {
  int score;
  tree *l, *r;
} m;
using namespace std;
 void PrintTree1(tree * root,int Elem_Space)
        {
           if(root!=NULL)
           {
                PrintTree1(root->r,Elem_Space+1);
                for(int i=0;i<Elem_Space;i++){printf("____");}
                cout<<root->r<<"\n";
                PrintTree1(root->l,Elem_Space+1);
           }
        }
void add (tree * &t,int score) {
if ( !t ) {
t = new tree; 

t->score=score;
t->l = t->r = NULL;
return;
}
if (score < t->score )
add( t->l, score );
else add( t->r,score );
}

void Fillrand(int n,int *A){
int i,b=0;
srand((unsigned int) time(NULL));
for (i=0;i<n;i++) A[i]=rand()%1000;
}
void print_tree(tree *t)
{
if ( !t ) return; 
print_tree(t->l); 
printf("%d ", t->score);
print_tree(t->r);
}

int path(tree *t,int *z)
{

if ( t!=NULL ) 
{*z=*z+1;
path(t->l,z); 
*z=*z+1;
path(t->r,z);
*z=*z+1;}
return *z;


}


int sum(tree *t,int *s)

{
    
if ( t!=NULL ){
*s=*s+t->score-1;
sum(t->l,s); 

sum(t->r,s);}

return *s;
}
int Checksumm(int n,int *A){
int i,s=0;
for (i=0;i<n;i++) s+=A[i];
return s;
}
void PrintMas(int n,int *A){
int i;
for (i=0;i<n;i++) printf("%d  ",A[i]);

}
tree *ISDP(int l,int r,int A[]){
     int m;tree *p;
         if(l>r) return NULL;
         else {
         m=(l+r)/2;
         p=new tree;
         p->score=A[m];
         p->l=ISDP(l,m-1,A);
         p->r=ISDP(m+1,r,A);
         return p;}
         }
         void quicksort(int *A,int l,int r){
int x,t,i,j;

x=A[(l+r)/2];i=l;j=r;
while (i<=j){
      while(A[i]<x){i++;}
      while(A[j]>x){j--;}
      if(i<=j)
      {t=A[i];A[i]=A[j];A[j]=t;i++;j--;}
      }
      if(l<j) {quicksort(A, l, j);}
      if(i<r) {quicksort(A, i, r);}
      }
      
int HeightOfTree(tree * node)
{
    if(node == 0)
        return 0;
    int left, right;
    if (node->l != NULL) {
        left = HeightOfTree(node->l);
    }else 
        left = -1;
    if (node->r != NULL) {
        right = HeightOfTree(node->r);
    }else 
        right = -1;
    int max = left > right ? left : right;
    return max+1;

}

tree* search(tree* t,int chislo){
      if(!t)return NULL;
      if (chislo==t->score ) return t; 
if (chislo<(t->score) ) 
   return search ( t->l, chislo );
return search ( t->r, chislo );
} 


tree* delfromsdp(int x,tree *&root){
tree **p;
tree *q,*r,*s;
p=&root;
while (*p!=NULL)
{
if  ((*p)->score <x) p=&(*p)->r;
else{
    if ((*p)->score >x) p=&(*p)->l;
else break;}}



if(*p!=NULL){
q=*p;
if(q->l==NULL) *p=q->r;
else if(q->r==NULL) *p=q->l;
else{
    r=q->l;
     s=q;
if (r->r==NULL){r->r=q->r;*p=r;}
else {
while (r->r!=NULL){s=r;r=r->r;}
      s->r=r->l;
      r->l=q->l;
      r->r=q->r;
      *p=r;
      }
      }
      }
      free(q);
      }

float summHEIGHT(tree *p, float L){ 
    float s1=0, s2=0;
    if(!p)  return 0; 
	else{                                                           
    	s1=summHEIGHT(p->l, L+1);
    	s2=summHEIGHT(p->r, L+1);
    	return (L+s1+s2);
	}
}
int razmer(tree *p){  
    int r=0, r1=0, r2=0;                                                
    if(p==NULL)  return 0;                                                          
    else{
	    r1=razmer(p->l);
    	r2=razmer(p->r);
    	return (1+r1+r2);
	}
}
int main(){
 int A[100];
     struct tree *p=NULL,*d=NULL,*kluch=NULL;
     int h=0,c=0,re;
    Fillrand(100,A);
    for(int z=0;z<10;z++) add(p,A[z]);
    print_tree(p);
    //printf("max%d\n",__LINE__);
    
//for(int kek=0;kek<10;kek++)
//{
        //scanf("%d",&re);
                //delfromsdp(re,p);
//printf("\n");
     //print_tree(p);
//}
     
    //int e=sum(p,&e);
    //printf("kontr summa%d ",e);
    //int e=Checksumm(100,A);
    
    //printf("kontr summa %d ",e);
    //quicksort(A,0,9);
    //PrintMas(10,A);
    //printf("\n");
    //d=ISDP(0,99,A);//00print_tree(d);//ISDP
    //float sred=summHEIGHT(d,1)/razmer(d);
    //h=HeightOfTree(p);
    //printf("\n %d",h);
    //h=HeightOfTree(d);
    //printf("\n %f",sred);
    //int r=0,k;
    //k=path(d,&r);
    //printf("\n %d",k);
    //printf("\n");
    //scanf("%d",&c);
    //printf("\n");
    //kluch=search(d,c);
    //if (kluch) printf("nashelsia rodnenk`kii %d \n",kluch->score);else printf("ne nashel");
    //PrintTree1(p,9);

    system("PAUSE");
    }
