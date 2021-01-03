#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 #define N 7//N-2 elementov
 
struct tree {
  int score;
  int weight;
  tree *l, *r;
};
struct versh {
  int weight;
  int value;
};
int print_tree(tree *q){           
    if(!q)   return 0;      
    print_tree(q->l);
    printf("%d ",q->score);
    print_tree(q->r);
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
void CrTree(int L,int R,versh *V1,int Ar[][N],tree *&root){
           if(L<R){
                   int k=Ar[L][R];
                   add(root,V1[k].value,V1[k].weight);
                   
                   CrTree(L,
                   k-1,
                   V1,
                   Ar,
                   root);
                   
                   CrTree(k,R,
                   V1,
                   Ar,
                   root);
                   }
           }
void Fillrand(versh *V1){
               for (int i=0;i<N;i++){V1[i].weight=rand()%100;V1[i].value=rand()%500;}
               }

float CDP(tree *p, int L){ 
    float s1=0, s2=0;
    if(!p)  return 0; 
	else{                                                           
    	if (p->l)s1=(p->l->weight)*CDP(p->l, L+1);
    	if (p->r)s2=(p->r->weight)*CDP(p->r, L+1);
    	return (L+s1+s2);
	}
}
//////////////////////////
int razmer(tree *p){  
    int r=0, r1=0, r2=0;                                               
    if(p==NULL)  return 0;                                                           
    else{
	    r1=razmer(p->l);
    	r2=razmer(p->r);
    	return (1+r1+r2);
	}
}
/////////////////////////
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

/////
int main(){
    srand((unsigned)time(NULL));
 versh V1[N];
 Fillrand(V1);
 
 
 int Aw[N][N];
 int Ap[N][N];
 int Ar[N][N];
 for (int i=0;i<N;i++)
 {for(int j=0;j<N;j++)
 {Aw[i][j]=0;Ap[i][j]=0;Ar[i][j]=0;}}//obnull 3 matr
 
 for (int i=0;i<N-1;i++)
 {for(int j=i+1;j<N-1;j++)
 Aw[i][j]=Aw[i][j-1]+V1[j].weight;}//matrica vesov dlia poddereva i,j
 
 /////////////////////////
 
 for(int i=0;i<N-1;i++)
 {for(int j=0;j<N-1;j++)
 {if((j-i)==0){Ap[i][j+1]=Aw[i][j+1];Ar[i][j+1]=j+1;}}}//1 diag dlia m vzveshannyh vesov i vershin
 
 //h=0;

 
  for(int i=0;i<N-2;i++)
 {for(int j=0;j<N-2;j++)
 {if((j-i)==1){Ap[i][j+1]=Aw[i][j+1];Ar[i][j+1]=i+1;}}}//2diag dlia m vzveshannyh vesov i vershin

  int j=0,m=0,min=100,x=0;
 
 for (int h=2;h<N-1;h++){
     for (int i=0;i<(N-1-h);i++){
         j=i+h;
         printf("i)%d j)%d\n",i,j);
         m=Ar[i][j-1];
         min=Ap[i][m-1]+Ap[m][j];
         for(int k=m+1;k<Ar[i+1][j];k++)
         {x=Ap[i][k-1]+Ap[k][j];
         if(x<min){m=k;min=x;}}
         Ap[i][j]=min+Aw[i][j];
         Ar[i][j]=m;
         }
     
     }
     
     
     
     for (int i=0;i<N-1;i++)
 {for(int j=0;j<N-1;j++){
 printf("%4d ",Aw[i][j]);}printf("\n");}
 printf("\n");printf("\n");
 for (int i=0;i<N-1;i++)
 {for(int j=0;j<N-1;j++){
 printf("%4d ",Ap[i][j]);}printf("\n");}
 printf("\n");printf("\n");
 for (int i=0;i<N-1;i++)
 {for(int j=0;j<N-1;j++){
 printf("%4d ",Ar[i][j]);}printf("\n");}
 tree *root=NULL;
 CrTree(0, N-2,V1,Ar,root);
float key=0;
float sum=0;
for (int z=0;z<N-2;z++)sum=sum+V1[z].weight;
int key1;
key1=CDP(root,1)/sum;
int raz=razmer(root);
 print_tree(root);
   printf("\n%d",raz);
   int s=Sum(root);
   printf("\n%d",s);
   key=Ap[0][N-2]/sum;
   printf("\n%f",key);
   printf("\n%f",key1);
 
 system("PAUSE");    

}
