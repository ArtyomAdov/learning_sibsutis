#include <stdio.h>
#include <stdlib.h>
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
	printf("6) Coding by Gilbert-Mur\n");
	printf("8) Clear Display\n");
	printf("0) Exit\n");
}

void Print_Data_Base(list_entry *head,short int number) 
{
    for(list_entry *it = head; it != NULL; it = it->next) 
	{
        if (it->data != NULL) 
		{
            printf("\n%d) %s\t", number+1 , it->data->author);
            printf("%s\t", it->data->title);
            printf("%s\t", it->data->publishing);
        	printf("%d\t", it->data->year);
			printf("%d", it->data->page);
			number++;
      		if(number%20==0)
			{
				printf("\n\nContinue-?  Yes-1\n\n");
				short int key_for_print=0;
				scanf("%hu", &key_for_print);
				if(key_for_print!=1)
				{
					break;
				}
			}
		} 
		else 
		{
            printf("NULL\n");
        }
    }
    printf("\n");
}

void *Read_Data_Base_To_List(const char *file_name, list_entry **head)
{
	FILE *file = fopen(file_name, "rb");
	*head=(list_entry *) malloc(sizeof(list_entry));
	list_entry *it = *head;
    for (int i = 0; i < DB_SIZE; i++) 
	{
        it->data = (record *) malloc(sizeof(record));
        fread(it->data, sizeof(record), 1, file);
        if (i != DB_SIZE - 1) 
		{
            it->next = (list_entry *) malloc(sizeof(list_entry));
        }
		else
		{
            it->next = NULL;
        }
        it = it->next;
    }
}

void *Radix_Sort(list_entry **(head)) {
    list_entry *it;
    queue *radix_queue[256];

    for (int i = 3; i >= 0; i--)
    {
		for (int j = 0; j < 256; j++) 
		{
            radix_queue[j] = (queue *)malloc(sizeof(queue));
            radix_queue[j]->head = NULL;
            radix_queue[j]->tail = NULL;
        }

        for (it = *head; it != NULL; it = it->next) 
		{
			unsigned char rad = it->data->author[i];
		    if (radix_queue[rad]->head == NULL) 
			{
                radix_queue[rad]->head = (list_entry *) malloc(sizeof(list_entry));
                radix_queue[rad]->tail = radix_queue[rad]->head;
                radix_queue[rad]->tail->next = NULL;
            } 
			else
			{
                radix_queue[rad]->tail->next = (list_entry *) malloc(sizeof(list_entry));
                radix_queue[rad]->tail = radix_queue[rad]->tail->next;
            }
            radix_queue[rad]->tail->data = it->data;
        }

        it = *head;
        int first = 1;
        for (int j = 0; j < 256; j++) 
		{
            if (radix_queue[j]->head != NULL) 
			{
                if (first) 
				{
                    *head = radix_queue[j]->head;
                    first = 0;
                } 
				else 
				{
                    it->next = radix_queue[j]->head;
                }
                it = radix_queue[j]->tail;
            }
        }
        it->next = NULL;
    }
}

bool Less_for_Search(char *A, char *X)
{
	for (short int i=0; i < 3;  i++)
	{
		if(X[i]<A[i])
		{
			return true;
		}
		else
		{
			if(X[i]>A[i])
			{
				return false;
			}
		}
	}
	return true;
}

bool Equally(char *A, char *X)
{
	for (short int i=0; i < 3; i++)
	{
		if (A[i] != X[i])
		{
			return false;
		}
	}
	return true;
}

short int Search_in_Data_Base(record **index,char *X)
{
	short int L = 0, R = DB_SIZE-1, midle = 0;
	while (L < R-1)
	{
		int midle =(R+L)/2;
		if (Less_for_Search(index[midle]->author, X) == true)
		{
			R = midle;
		}
		else
		{
			L = midle+1;
		}
	}
	if (Equally(index[R]->author, X) == true)
	{
		return R;
	}
	else
	{
		printf("Need Note not Found\n");
		return -1;
	}
}

void *Create_Find_Queue(list_entry *db,short int Number,short int first_queue_note, queue**find,char *X)
{
	while(Number<first_queue_note)
	{
		Number++;
		db=db->next;
	}
	bool continue_queue_flag=true;
	list_entry *le = NULL;
	le=(list_entry*) malloc (sizeof(list_entry));
	(*find)=(queue*) malloc (sizeof(queue));
    le->data = db->data;
    le->next = NULL;
    (*find)->head=le;
    (*find)->tail=le;
    Number++;
    db=db->next;
    while(continue_queue_flag==true&&Number<DB_SIZE)
	{
		if(Equally(db->data->author,X)==false)
		{
			continue_queue_flag=false;
			break;
		}
		le=(list_entry*) malloc (sizeof(list_entry));
		le->data = db->data;
    	le->next = NULL;
		(*find)->tail->next=le;
		(*find)->tail=le;
		Number++;
		db=db->next;
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

void Print_AVL(vertex *p)
{
	if (p!=NULL)
	{
		Print_AVL(p->left);
		iterator1++;
		printf("\n %hu) %s\t" ,iterator1 , p->data->author);
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

void Fill_Chance_Meet_of_Symbols(char a, double **A, int as)
{
	for(int i=0; i<as; i++)
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

void Quick_Sort_For_Symbol(double **A, int L, int R)
{
	int j=R,i=L;
	double X=A[(L+R)/2][0];
	double t,m;
	while(i<=j)
	{
		while(A[i][0]<X) 
		{
			i++;
		}
		while(A[j][0]>X)
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
		Quick_Sort_For_Symbol(A,L,j);
	}
	if(i<R)
	{
		Quick_Sort_For_Symbol(A,i,R);	
	}
	return;
}

void Gilbert_Mur(double probability[], double length[],bool code_word[][20], int n)
{
	double pr=0;
	double *Q=NULL;
	Q=(double*) malloc (n * sizeof(double));
	for(short int i=0; i<n; i++)
	{
		Q[i]=0;
	}
	for(short int i=0;i<n+1;i++)
	{
		Q[i]=pr+probability[i]/2;
		pr=pr+probability[i];
		length[i]=ceil(-log2(probability[i])) + 1;
	}
	for(short int i=1,j=0;i<=n;i++,j=0)
	{
		for (;j<length[i];j++)
		{
			Q[i]=Q[i]*2;
			code_word[i][j]=(int)Q[i];
			if(Q[i]>=1)
			{
				Q[i]=Q[i]-1;
			}
		}
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
	for(short int i=0;i<n;i++)
	{
		for(short int j=0;j<n;j++)
		{
			code_word[i][j]=false;
		}
	}
	Quick_Sort_For_Symbol(A,0,n-1);
	for(int i=1;i<n+1;i++)
	{
		probability[i]=A[i-1][1];
	}
	Gilbert_Mur(probability,length,code_word,n);
	printf("Symbol\tProbability\t\tCode word\tStake word length\n");
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
	char a=0;
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
	printf("Sum of the probability of characters : %f\n",g);
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
	bool sort_flag=false;
	list_entry *db=NULL;
	record **index = NULL;
	queue *find=NULL;
	vertex *root=NULL;
	while(1)
	{
		short int key=0;
		Menu();
		scanf("%hu",&key);
		switch (key)
		{
		case 1:
		{
				Read_Data_Base_To_List("testBase1.dat",&db);
				break;
			}
		case 2:
			{
				if((db!=NULL)&&(sort_flag==false))
				{
					Radix_Sort(&db);
					sort_flag=true;
				}
				else
				{
					printf("Need Read Data Base or Data Base Already Sorting\n");
				}
				break;
			}
		case 3:
			{
				if(db!=NULL)
				{
					Print_Data_Base(db,0);
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
					printf("Need Search Note by Surname\n");
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
						iterator2=0;
					}
					root=NULL;
					iterator1=0;
					iterator2=0;
				}
				break;
			}
		case 5:
			{
				if(sort_flag==true)
				{
					char X[3];
					SetConsoleCP(866);
					printf("Write What Note Need Find\n");
					scanf("%s", &X);
					index=(record **) malloc(DB_SIZE *sizeof(record));
					list_entry *buffer=NULL;
					buffer=db;
					for (short int i = 0; i < DB_SIZE; i++)
					{
					   	index[i] = buffer->data;
					  	buffer=buffer->next;
					}
					short int first_queue_note=Search_in_Data_Base(index ,X);
					Create_Find_Queue(db,0,first_queue_note,&find,X);
					if(first_queue_note==-1)
					{
						break;
					}
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
