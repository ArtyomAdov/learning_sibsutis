#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <math.h>

#define DB_SIZE 4000

typedef struct
{
	char author[12];
	char title[32];
	char publishing[16];
	short int year;
	short int page;
} record;

typedef struct le_s
{
	struct le_s *next;
	record *data;
} list_entry;

typedef struct
{
	list_entry *head;
	list_entry *tail;
} queue;

typedef struct tree
{
	record *data;
	int balance;
	struct tree *left;
	struct tree *right;
} vertex;

bool height;

short int iterator1=0;

short int iterator2=0;

void Menu()
{
	printf("1) Read Data Base in list \n");
	printf("2) Sorting Data Base\n");
	printf("3) Print Data Base\n");
	printf("4) Create AVL-tree for Data Base\n");
	printf("5) Find in Data Base\n");
	printf("6) Coding elements by Huffman\n");
	printf("8) Clear Display\n");
	printf("0) Exit\n");
}

void Print_Data_Base(record *index[], int Number)
{
	while (1)
	{
		short int key = 1;
		for (int i = Number; i < Number + 20; i++)
		{
			printf("\n%d) %s\t", i + 1, index[i]->author);
			printf("%s\t", index[i]->title);
			printf("%s\t", index[i]->publishing);
			printf("%d\t", index[i]->year);
			printf("%d", index[i]->page);
		}
		Number = Number + 20;
		if (Number >= DB_SIZE)
		{
			return;
		}
		printf("\n\nContinue-?  Yes-1\n\n");
		scanf("%hu", &key);
		if (key != 1)
		{
			return;
		}
	}
	printf("\n");
}

int Less(record a[], record b[])
{
	short int f1 = 0, f2 = 0;
	for (short int i = 0, j = 0; i < 32; i++, j++)
	{
		if (f1 == 2)
		{
			i--;
		}
		else
		{
			if (a->title[i] == ' ')
			{
				f1++;
			}
		}
		if (f2 == 2)
		{
			j--;
		}
		else
		{
			if (b->title[j] == ' ')
			{
				f2++;
			}
		}
		if (f1 == 2 && f2 == 2)
		{
			if (a->title[i] < b->title[j])
			{
				return 0;
			}
			else
			{
				if (a->title[i] > b->title[j])
				{
					return 2;
				}
				else
				{
					i++;
					j++;
				}
			}
		}
	}
	return 1;
}

void Build_Heap(record *index[], short int L, short int R)
{
	short int i = L, j, z = 0;
	record *p = index[L];
	while (1)
	{
		j = 2 * i;
		if (j > R)
		{
			break;
		}
		z = Less(index[j + 1], index[j]);
		if (j < R && z == 2)
		{
			j = j + 1;
		}
		z = Less(p, index[j]);
		if (z > 0)
		{
			break;
		}
		index[i] = index[j];
		i = j;
	}
	index[i] = p;
}

void Heap_Sort(record **index)
{
	short int L = (DB_SIZE - 1) / 2, R = DB_SIZE - 1;
	record *temp;
	while (L >= 0)
	{
		Build_Heap(index, L, DB_SIZE - 1);
		L--;
	}
	while (R > 0)
	{
		temp = index[0];
		index[0] = index[R];
		index[R] = temp;
		R--;
		Build_Heap(index, 0, R);
	}
}

void *Read_Data_Base_To_Array(const char *file_name, record **note)
{
	*note = (record *)malloc(DB_SIZE * sizeof(record));
	FILE *file = fopen(file_name, "rb");
	fread(*note, sizeof(record), DB_SIZE, file);
	fclose(file);
}

bool Less_for_Search(char *A, char *X)
{
	short int f1 = 0;
	for (short int i = 0; i < 32; i++)
	{
		if (A[i] == ' ')
		{
			f1++;
		}
		if (f1 == 2)
		{
			for (short int j = 0; j < 3; j++, i++)
			{
				if(X[j]<A[i+1])
				{
					return true;
				}
				else
				{
					if(X[j]>A[i+1])
					{
						return false;
					}
				}
			}
			return true;
		}
	}
}

bool Equally(char *A, char *X)
{
	short int f1 = 0;
	for (short int i = 0; i < 32; i++)
	{
		if (A[i] == ' ')
		{
			f1++;
		}
		if (f1 == 2)
		{
			for (short int j = 0; j < 3; j++, i++)
			{
				if (A[i+1] != X[j])
				{
					return false;
				}
			}
			return true;
		}
	}
}

void *Create_Queue_Found_Note(record **index, queue **find,short int Number,char *X)
{
	bool continue_queue_flag=true;
	list_entry *le =NULL;
	le=(list_entry*) malloc (sizeof(list_entry));
	*find=(queue*) malloc (sizeof(queue));
    le->data = index[Number];
    le->next = NULL;
    (*find)->head=le;
    (*find)->tail=le;
    Number++;
    while(continue_queue_flag==true&&Number<DB_SIZE)
	{
		if(Equally(index[Number]->title,X)==false)
		{
			continue_queue_flag=false;
			break;
		}
		le=(list_entry*) malloc (sizeof(list_entry));
		le->data = index[Number];
    	le->next = NULL;
		(*find)->tail->next=le;
		(*find)->tail=le;
		Number++;
    }
}

short int Search_in_Data_Base(record **index,char *X)
{
	short int L = 0, R = DB_SIZE-1, midle = 0;
	while (L < R)
	{
		int midle =(L+R)/2;
		if (Less_for_Search(index[midle]->title, X) == true)
		{
			R = midle;
		}
		else
		{
			L = midle+1;
		}
	}
	if (Equally(index[R]->title, X) == true)
	{
		return R;
	}
	else
	{
		return -1;
	}
}

void *Print_Queue(queue *find,short int Number)
{
	find->tail=find->head;
	while(find->tail!=NULL)
	{
		printf("\n%d) %s\t", Number + 1, find->tail->data->author);
		printf("%s\t", find->tail->data->title);
		printf("%s\t", find->tail->data->publishing);
		printf("%d\t", find->tail->data->year);
		printf("%d", find->tail->data->page);
		Number++;
		find->tail=find->tail->next;
	}
	printf("\n");
}

void *LL_turn(vertex **p)
{
	vertex *q;
	q=(*p)->left;
	q->balance=0;
	(*p)->balance=0;
	(*p)->left=q->right;
	q->right=(*p);
	(*p)=q;
}

void *LR_turn(vertex **p)
{
	vertex *q,*r;
	q=(*p)->left;
	r=q->right;
	if (r->balance<0)
	{
		(*p)->balance=1;	
	}
	else
	{
		(*p)->balance=0;	
	}
	if (r->balance>0)
	{
		q->balance=-1;	
	}
	else q->balance=0;
	r->balance=0;
	(*p)->left=r->right;
	q->right=r->left;
	r->left=q;
	r->right=(*p);
	(*p)=r;	
}

void *RR_turn(vertex **p)
{
	vertex *q;
	q=(*p)->right;
	q->balance=0;
	(*p)->balance=0;
	(*p)->right=q->left;
	q->left=(*p);
	(*p)=q;
}

void *RL_turn(vertex **p)
{
	vertex *q,*r;
	q=(*p)->right;
	r=q->left;
	if (r->balance>0) 
	{
		(*p)->balance=-1;	
	} 
	else
	{
		(*p)->balance=0;	
	} 
	if (r->balance<0)
	{
		q->balance=1;	
	} 
	else
	{
		q->balance=0;	
	} 
	r->balance=0;
	(*p)->right=r->left;
	q->left=r->right;
	r->left=(*p);
	r->right=q;
	(*p)=r;	
}

void Print_AVL(vertex *p)
{
	if (p!=NULL)
	{
		Print_AVL(p->left);
		iterator1++;
		printf("\n%hu) %s\t", iterator1 , p->data->author);
		printf("%s\t", p->data->title);
		printf("%s\t", p->data->publishing);
		printf("%hu\t", p->data->year);
		printf("%hu", p->data->page);
		Print_AVL(p->right);
	}
}

void Print_Found_in_AVL(vertex *p,short int X)
{
	if (p!=NULL)
	{
		Print_Found_in_AVL(p->left,X);
		if(p->data->year==X)
		{
			iterator2++;
			printf("\n%d) %s\t", iterator2 , p->data->author);
			printf("%s\t", p->data->title);
			printf("%s\t", p->data->publishing);
			printf("%d\t", p->data->year);
			printf("%d", p->data->page);	
		}
		Print_Found_in_AVL(p->right,X);
	}
}

void *Find_in_AVL(short int X,vertex *p)
{
	if(p!=NULL)
	{
		if(X>p->data->year)
		{
			Find_in_AVL(X,p->right);
		}
		else
		{
			if(X<p->data->year)
			{
				Find_in_AVL(X,p->left);
			}
			else
			{
				Print_Found_in_AVL(p,X);
			}
		}
	}
	else
	{
		printf("Need Notes not Found\n");
	}
	printf("\n");
}

void *Add_in_AVL(record *d,vertex **p)
{
	if ((*p)==NULL)
	{
		(*p)=(vertex*) malloc (sizeof(vertex));
		(*p)->data=d;
		(*p)->left=NULL;
		(*p)->right=NULL;
		(*p)->balance=0;
		height=true;
	}
	else
	{
		if ((*p)->data->year>d->year)
		{
			vertex *v=NULL;
			v=(*p)->left;
			Add_in_AVL(d,&v);
			(*p)->left=v;
			if (height==true)
			{
				if ((*p)->balance>0) 
				{
					(*p)->balance=0;
					height=false;
				}
				else
				{
					if ((*p)->balance==0)
					{
						(*p)->balance=-1;	
					}
					else
					{
						if ((*p)->left->balance<0) 
						{
							LL_turn(p);
							height=false;
						}
						else
						{
							LR_turn(p);
							height=false;
						}
					}
				}
			}			
		}
		else
		{
			if ((*p)->data->year<=d->year)
			{
				vertex *v=NULL;
				v=(*p)->right;
				Add_in_AVL(d,&v);
				(*p)->right=v;
				if (height==true)
				{
					if ((*p)->balance<0) 
					{
						(*p)->balance=0;
						height=false;
					}
				}
				else
				{
					if ((*p)->balance==0)
					{
						(*p)->balance=1;
					}
					else
					{
						if ((*p)->right->balance>0) 
						{
							RR_turn(p);
							height=false;
						}
						else
						{
							RL_turn(p);
							height=false;
						}
					}
				}
			}
		}	
	}
}

void Fill_Chance_Meet_of_Symbols(char a, double **A, int n)
{
	for(int i=0; i<n; i++)
	{
		if(A[i][0]==a)
		{
			A[i][1]++;
			return;
		}
		else if(A[i][1]==0)
		{
			A[i][0]=a;
			A[i][1]++;
			return;
		}
	}
}

void Quick_Sort_For_Chance(double **A, int L, int R)
{
	int j=R,i=L;
	double X=A[(L+R)/2][1];
	double t,m;
	while(i<=j)
	{
		while(A[i][1]>X)
		{
			i++;
		}
		while(A[j][1]<X)
		{
			j--;
		}
		if(i <= j)
		{
			m=A[j][0];
			A[j][0]=A[i][0];
			A[i][0]=m;
			t=A[j][1];
			A[j][1]=A[i][1];
			A[i][1]=t;
			i++;
			j--;
		}
	}
	if(L<j)
	{
		Quick_Sort_For_Chance(A,L,j);	
	}
	if(i<R)
	{
		Quick_Sort_For_Chance(A,i,R);	
	}
	return;
}

void Down(int n, int j, double length[], bool code_word[][20])
{
	bool S[20]={0};
	for(int i=0;i<20;i++)
	{
		S[i]=code_word[j][i];
	}
	int l=length[j];
	for(int i=j;i<=n-2;i++)
	{
		for(int k=0;k<20;k++)
		{
			code_word[i][k]=code_word[i+1][k];
		}
		length[i]=length[i+1];
	}
	for(int i=0;i<20;i++)
	{
		code_word[n-1][i]=S[i];
		code_word[n][i]=S[i];
	}
	code_word[n-1][l]=0;
	code_word[n][l]=1;
	length[n-1]=l+1;
	length[n]=l+1;
}

int Up(int n, double q, double probability[])
{
	int j=1;
	for(int i=n-1;i>1;i--)
	{
		if(probability[i-1]<=q)
		{
			probability[i]=probability[i-1];	
		} 
		else 
		{
			j=i;
			break;
		}
	}
	probability[j]=q;
	return j;
}

void Huffman(int n, double probability[], bool code_word[][20], double length[])
{
	if(n==2)
	{
		code_word[1][0]=0;
		length[1]=1;
		code_word[2][0]=1;
		length[2]=1;
	}
	else
	{
		double q=probability[n-1]+probability[n];
		int j=Up(n,q,probability);
		Huffman(n-1,probability,code_word,length);
		Down(n,j,length,code_word);
	}
}

void Coding_Symbols(double **A, int n)
{
	double average_code_length=0,kraft_nequality=0;
	double probability[n+1],length[n+1];
	for(short int i=0;i<n+1;i++)
	{
		probability[i]=0;
		length[i]=0;
	}
	bool code_word[n+1][20];
	for(short int i=0;i<n+1;i++)
	{
		for(short int j=0;j<20;j++)
		{
			code_word[i][j]=false;
		}
	}
	Quick_Sort_For_Chance(A,0,n-1);
	for(int i=1;i<n+1;i++)
	{
		probability[i]=A[i-1][1];
	}
	Huffman(n,probability,code_word,length);
	printf("\nSymbol\tProbability\t\tCode word\tStake word length\n");
	for(int i=1;i<n+1;i++)
	{
		average_code_length+=A[i-1][1]*length[i];
		kraft_nequality+=pow(2,(length[i]*-1));
		printf("%hu)%c\t%f\t\t",i,(char)A[i-1][0],A[i-1][1]);
		for(int j=0;j<length[i];j++)
		{
			printf("%d",code_word[i][j]);
		}
		printf("\t\t%0.f\n",length[i]);
	}		
	printf("Average length of code words: %f\n",average_code_length);
	if(kraft_nequality<=1) 
	{
		printf("Kraft-McMillan's nequality: %f <=1\n",kraft_nequality);
	}
	else 
	{
		printf("Kraft-McMillan's nequality: %f >1\n",kraft_nequality);
	}
}

void Reading_Symbols()
{
	FILE *file;
	file=fopen("testBase1.dat","rb");
	int n=257,sum=0;
	double **A,intr=0;
	A=(double**) malloc (n *sizeof(double*));
	for(int i=0;i<n;i++)
	{
		A[i] = (double*) malloc (2 * sizeof(double));
		A[i][0]=0;
		A[i][1]=0;
	}
	char a=0,digit[4]={0};
	short int temp=0;
	while(fread(&a, sizeof(char), 1, file)&&(!feof(file)))
	{
		Fill_Chance_Meet_of_Symbols(a,A,n);
	}
	for(int i=0;i<n;i++)
	{
		sum+=A[i][1];
		if(A[i][1]==0)
		{
			temp=i;
			break;
		}
	}
	for(int i=temp;i<n;i++) 
	{
		free(A[i]);
	}
	n=temp;
	for(int i=0;i<n;i++)
	{
		printf("%c = %f \t--\t",(char)A[i][0],A[i][1]);
		A[i][1]/=sum;
		printf("%f\n",A[i][1]);
	} 
	printf("\nNumber of characters read: %f\n",sum);
	double g=0;
	for(int i=0;i<n;i++)
	{
		g+=A[i][1];	
	}
	printf("Sum of the probability of characters : %f",g);
	for(int i=0;i<n;i++)
	{
		intr+=log(A[i][1])/log(2)*A[i][1];
	}
	intr=intr*-1;
	Coding_Symbols(A,n);
	printf("Entropy: %f\n",intr);
	for(int i=0;i<n;i++)
	{
		free(A[i]);
	}
	free(A);
}

int main()
{
	bool sort_flag = false;
	short int head_for_queue;
	record *note = NULL;
	record **index = NULL;
	queue *find = NULL;
	vertex *root=NULL;
	while (1)
	{
		short int key = 0;
		Menu();
		scanf("%hu", &key);
		switch (key)
		{
		case 1:
		{
			Read_Data_Base_To_Array("testBase1.dat", &note);
			index = (record **)malloc(DB_SIZE * sizeof(record));
			for (short int i = 0; i < DB_SIZE; i++)
			{
				index[i] = &note[i];
			}
			sort_flag = false;
			break;
		}
		case 2:
		{
			if ((index != NULL) && (sort_flag == false))
			{
				Heap_Sort(index);
				sort_flag = true;
			}
			else
			{
				printf("Need Read Data Base or Data Base Already Sorting\n");
			}
			break;
		}
		case 3:
		{
			if (note != NULL)
			{
				Print_Data_Base(index, 0);
			}
			else
			{
				printf("Data Base is not Read\n");
			}
			break;
		}
		case 4:
		{
			if(find==NULL)
			{
				printf("Need Search Note");
			}
			else
			{
				find->tail=find->head;
				while(find->tail!=NULL)
				{
					Add_in_AVL(find->tail->data,&root);
					find->tail=find->tail->next;
				}	
			}
			Print_AVL(root);
			printf("\nDo You Want to Search by Year around found notes? 1-Yes\n");
			short int key_search=0;
			scanf("%hu",&key_search);
			if(key_search==1)
			{
				short int exit_key=1;
				while(exit_key==1)
				{
					printf("Write Need Year\n");
					short int Xy=0;
					scanf("%hu",&Xy);
					Find_in_AVL(Xy,root);
					printf("If You Want Continue - Press 1\n");
					scanf("%hu",&exit_key);
				}
				root=NULL;
				iterator1=0;
				iterator2=0;
			}
			break;
		}
		case 5:
		{
			if (sort_flag == true)
			{
				find=NULL;
				char X[3];
				SetConsoleCP(866);
				printf("Write What Note Need Find\n");
				scanf("%s", &X);
				short int first_queue_note=Search_in_Data_Base(index ,X);
				if(first_queue_note==-1)
				{
					printf("Need Note not Found\n");
					break;
				}
				Create_Queue_Found_Note(index,&find,first_queue_note,X);
				Print_Queue(find,first_queue_note);
			}
			else
			{
				printf("Need Sort Data Base\n");
			}
			break;
		}
		case 6:
		{
			Reading_Symbols();
			break;
		}
		case 8:
		{
			system("CLS");
			break;
		}
		case 0:
		{
			return 0;
		}
		}
	}
}
