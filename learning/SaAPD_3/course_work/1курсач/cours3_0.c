#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define ERROR_OPEN_BASE 0b00000001
#define ERROR_INCORECT_EXIT_FROM_PROGRAMM 0b00000010
#define ERROR_ALLOCATION_MEMORY 0b00000100
#define ERROR_NOT_FOUND_NOTE 0b00001000

#define SIZE_DATA_BASE 4000
#define START_RECORD_PRINT 20
#define SIZE_KEY_SORT 18
#define SIZE_KEY_SEARCH 3
#define LESS 0
#define EQUALLY 1
#define LARGE 2
#define QUANTITY_SYMBOL_IN_ALPHABET 166

#define FILE_NAME "testBase4.dat"
#define READ_BINARY_ONLY "rb"

bool height = false;

struct Record
{
    char citizen[32];
    char street_name[18];
    short int number_of_house;
    short int number_of_flat;
    char check_in_date[10];
};

typedef struct Record record;

struct List_Entry
{
	struct List_Entry* next;
	record* data;
};

typedef struct List_Entry list_entry;

struct Queue
{
	list_entry* head;
	list_entry* tail;
};

typedef struct Queue queue;

struct Vertex
{
	list_entry* head_set;
	int balance;
	struct Vertex *left;
	struct Vertex *right;
};

typedef struct Vertex vertex;

bool VR,HR;

void Draw_Menu()
{
	printf("1) Read Data Base\n");
    printf("2) Print Data Base\n");
    printf("3) Sort Data Base\n");
    printf("4) Find in Data Base by Street Name\n");
    printf("5) Find in Data Base by Number of House\n");
    printf("6) Encode Data Base by Shannon\n");
    printf("9) Clear Screen\n");
    printf("0) Exit\n");
}

void Print_Head_Table()
{
	printf("\nFIO\t\t\t\t\t");
	printf("Street name\t");
	printf("Number of house\t");
	printf("Number of flat\t");
	printf("Check in date\n");
}

void Print_Variant_Choice()
{
	printf("\nNext page - n\t");
	printf("Back page - b\t");
	printf("Choice specific page - s\t");
	printf("Change quantity record in one page - q\n");
	printf("Close - c\n");	
}

void Print_Data_Base(record *index[])
{
    int Number = 0;
    int quantity_record_print = START_RECORD_PRINT;
    char key_continue = '1';
	while(1)
	{
		Print_Head_Table();
		for(short int i = Number; ((i < Number + quantity_record_print) && (i <SIZE_DATA_BASE)); i++)
		{
			printf("\n%d) %s\t", i + 1, index[i]->citizen);
			printf("%s\t", index[i]->street_name);
			printf("%d\t", index[i]->number_of_house);
			printf("%d\t", index[i]->number_of_flat);
			printf("%s", index[i]->check_in_date);
		}
		Print_Variant_Choice();
		scanf(" %c", &key_continue);
		switch(key_continue)
		{
		case('n'):
		{
			Number = Number + quantity_record_print;
			if(Number >= SIZE_DATA_BASE)
			{
				Number = SIZE_DATA_BASE - quantity_record_print;
			}
			break;
		}
		case('b'):
		{
			Number = Number - quantity_record_print;
			if(Number < 0)
			{
				Number = 0;
			}
			break;
		}
		case('c'):
		{
			return (void)NULL;
		}
		case('s'):
		{
			int key_specific = 0;
			printf("Write need number page\n");
			scanf("%d",&key_specific);
			key_specific = key_specific - 1;
			Number = (key_specific * quantity_record_print);
			if(Number < 0 || Number >=SIZE_DATA_BASE)
			{
				printf("Need page not exist\n");
				Number = 0;
			}
			break;
		}
		case('q'):
		{
			printf("Write need quantity note in one page\n");
			scanf("%d",&quantity_record_print);
			break;
		}
		}
	}
	printf("\n");
}

void Print_Queue(queue* find)
{
	short int i = 1;
	find->tail = find->head;
	do
	{
		printf("\n%d) %s\t", i, find->tail->data->citizen);
		printf("%s\t", find->tail->data->street_name);
		printf("%d\t", find->tail->data->number_of_house);
		printf("%d\t", find->tail->data->number_of_flat);
		printf("%s", find->tail->data->check_in_date);
		i++;
		find->tail=find->tail->next;
	} while(find->tail!=NULL);
	printf("\n");
}

int Read_Data_Base_To_Array(record** note)
{
	FILE* file = NULL;
	file = fopen(FILE_NAME, READ_BINARY_ONLY);
	if(file == NULL)
	{
		return ERROR_OPEN_BASE;
	}
	*note = (record *) malloc (SIZE_DATA_BASE * sizeof(record));
	if(*note == NULL)
	{
		return ERROR_ALLOCATION_MEMORY;
	}
	fread(*note, sizeof(record), SIZE_DATA_BASE, file);
	fclose(file);
	return 0;
}

int Less(record* A, record* x)
{
	for(int i = 0; i < 18; i++)
	{
		if(A->street_name[i] < x->street_name[i])
		{
			return -1;
		}
		if(A->street_name[i] > x->street_name[i])
		{
			return 1;
		}
	}
	if(A->number_of_house < x->number_of_house)
	{
		return -1;
	}
	if(A->number_of_house > x->number_of_house)
	{
		return 1;
	}
	if(A->number_of_flat < x->number_of_flat)
	{
		return -1;
	}
	if(A->number_of_flat > x->number_of_flat)
	{
		return 1;
	}
	return 0;
}

void Quick_Sort(record** A,int L, int R)
{
	record* x;
	record* q;
	int i=L,j=R;
	 x=A[L];
     while (i<=j) 
	 {
		while (Less(A[i],x)==-1) {i++;}
        while (Less(A[j],x)==1) {j--;}
		   if (i<=j) {
              q=A[i];
              A[i]=A[j];
              A[j]=q;
              i++;
              j--;
           }
     }
     if (L<j) Quick_Sort(A,L,j);
     if (i<R) Quick_Sort(A,i,R);
}

int Comparison_For_Search_Char_Field(char check_data[], char search_data[])
{
	for(short int i = 0; i < SIZE_KEY_SEARCH; i++)
	{
		if(check_data[i] < search_data[i])
		{
			return LESS;
		}
		if(check_data[i] > search_data[i])
		{
			return LARGE;
		}
	}
	return EQUALLY;
}

int Search_In_Data_Base(record** index, char search_data[], int* index_first_need_note)
{
	short int left_limit = 0;
	short int right_limit = (SIZE_DATA_BASE - 1);
	short int index_midle = 0;
	do
	{
		index_midle = ((left_limit + right_limit) / 2);
		if(Comparison_For_Search_Char_Field(index[index_midle]->street_name, search_data) == LESS)
		{
			left_limit = (index_midle + 1);
		}
		else
		{
			right_limit = (index_midle - 1);
		}
	} while(left_limit <= right_limit);
	right_limit++;
	if(Comparison_For_Search_Char_Field(index[right_limit]->street_name, search_data) == EQUALLY)
	{
		*index_first_need_note = (right_limit);
		return 0;
	}
	*index_first_need_note = -1;
	printf("Need note not founded\n");
	return ERROR_NOT_FOUND_NOTE;
}

int Create_Queue_Found_Note(record** index, queue** find, int first_index)
{
	bool continue_flag = true;
	int number = 0;
	number = first_index;
	list_entry* le = NULL;
	le = (list_entry*)malloc(1 * sizeof(list_entry));
	*find = (queue*)malloc(1 * sizeof(queue));
    le->data = index[number];
    le->next = NULL;
    (*find)->head = le;
    (*find)->tail = le;
    number++;
    do
	{
		if(Comparison_For_Search_Char_Field(index[first_index]->street_name, index[number]->street_name) != EQUALLY)
		{
			continue_flag = false;
			break;
		}
		le = (list_entry*)malloc(1 * sizeof(list_entry));
		le->data = index[number];
    	le->next = NULL;
		(*find)->tail->next = le;
		(*find)->tail = le;
		number++;
    } while((true == continue_flag) && (number < SIZE_DATA_BASE));
	return 0;
}

void Print_Tree(vertex *root)
{
	list_entry* temp = NULL;
	if(root != NULL)
	{
		Print_Tree(root->left);
		{
			temp = root->head_set;
			do
			{
				printf("\n%s\t", temp->data->citizen);
				printf("%s\t", temp->data->street_name);
				printf("%d\t", temp->data->number_of_house);
				printf("%d\t", temp->data->number_of_flat);
				printf("%s", temp->data->check_in_date);	
				temp = temp->next;
			}while(temp != NULL);
		}
		Print_Tree(root->right);
	}
}

void Print_List(list_entry* head_set)
{
	int i = 0;
	do
	{
		i++;
		printf("\n%d)%s\t", i, head_set->data->citizen);
		printf("%s\t", head_set->data->street_name);
		printf("%d\t", head_set->data->number_of_house);
		printf("%d\t", head_set->data->number_of_flat);
		printf("%s", head_set->data->check_in_date);
		head_set = head_set->next;
	}while(head_set != NULL);
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

void Search_In_Tree(vertex* root, int data)
{
	if(root != NULL)
	{
		if(root->head_set->data->number_of_house < data)
		{
			Search_In_Tree(root->right,data);	
		}
		if(root->head_set->data->number_of_house > data)
		{
			Search_In_Tree(root->left,data);
		}
		if(root->head_set->data->number_of_house == data)
		{
			Print_List(root->head_set);
			return (void)0;
		}
	}
}

void* Add_in_AVL(record *d,vertex **p)
{
	list_entry* temp = NULL;
	if((*p)==NULL)
	{
		(*p) = (vertex*)calloc(1,sizeof(vertex));
        (*p)->head_set = (list_entry*)calloc(1,sizeof(list_entry));
        (*p)->head_set->data = d;
        (*p)->left = NULL;
        (*p)->right = NULL;
        (*p)->balance = 0;
		height=true;
		return NULL;
	}
	else
	{
		if((*p)->head_set->data->number_of_house == d->number_of_house)
		{
			temp = (list_entry*)calloc(1,sizeof(list_entry));
		    temp->data = d;
		    temp->next = (*p)->head_set;
		    (*p)->head_set = temp;
		    return NULL;
		}
		if((*p)->head_set->data->number_of_house>d->number_of_house)
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
			if ((*p)->head_set->data->number_of_house<=d->number_of_house)
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

void Fill_Chance_Meet_of_Symbols(char symbol, double** array_chance, int symbol_alphabet)
{
    for(short int i = 0; i < symbol_alphabet; i++)
	{
        if(array_chance[i][0] == symbol)
		{
            array_chance[i][1]++;
            return;
        }
		if(array_chance[i][1] == 0)
		{
            array_chance[i][0] = symbol;
            array_chance[i][1]++;
            return;
        }
    }
}

void Quick_Sort_For_Chance(double** array_chance, int left_limit, int right_limit)
{
    int j = right_limit, i = left_limit;
    double X = array_chance[(left_limit + right_limit) / 2][1];
    double temp, m;
    while (i <= j)
	{
        while(array_chance[i][1] > X)
		{
            i++;
        }
        while(array_chance[j][1] < X)
		{
            j--;
        }
        if(i <= j)
		{
            m = array_chance[j][0];
            array_chance[j][0] = array_chance[i][0];
            array_chance[i][0] = m;
            temp = array_chance[j][1];
            array_chance[j][1] = array_chance[i][1];
            array_chance[i][1] = temp;
            i++;
            j--;
        }
    }
    if(left_limit < j)
	{
        Quick_Sort_For_Chance(array_chance, left_limit, j);
    }
    if(i < right_limit)
	{
        Quick_Sort_For_Chance(array_chance, i, right_limit);
    }
    return;
}

void Shennon(int size, double p[], double length[] ,bool code_word[][20])
{
    float Q[size];
    Q[0] = 0;
    length[0] = (int)ceilf(-log2f(p[0]));
    for (int i = 1; i < size; i++) {
        Q[i] = Q[i - 1] + p[i - 1];
        length[i] = (int)ceilf(-log2f(p[i]));
    }
    for(int i = 0; i < size; i++)
	{
        for (int j = 0; j < length[i]; j++) {
            Q[i] *= 2;
            int dig = (int)Q[i];
            if (dig == 0) code_word[i][j] = 0;
            if (dig == 1) code_word[i][j] = 1;
            if (Q[i] > 1)Q[i]--;
        }
    }
}

void Coding_Symbols(double** array_chance, int symbol_alphabet)
{
    double average_code_length = 0.0;
    double probability[symbol_alphabet + 1], length[symbol_alphabet + 1];
    bool code_word[symbol_alphabet + 1][20];
	for(short int i = 0; i < symbol_alphabet + 1; i++)
	{
        probability[i] = 0;
        length[i] = 0;
    }
    for(short int i = 0; i < symbol_alphabet + 1; i++)
	{
        for(short int j = 0; j < 20; j++)
		{
            code_word[i][j] = false;
        }
    }
    Quick_Sort_For_Chance(array_chance, 0, symbol_alphabet - 1);
    for(short int i = 1; i < symbol_alphabet + 1; i++)
	{
        probability[i] = array_chance[i - 1][1];
    }
    printf("so good\n");
    Shennon(symbol_alphabet, probability, length, code_word);
    printf("\nSymbol\tProbability\t\tCode word\tWord length\n");
    for(short int i = 1; i < symbol_alphabet + 1; i++)
	{
        average_code_length += array_chance[i - 1][1] * length[i];
        printf("%hu)%c\t%f\t\t", i, (char)array_chance[i - 1][0], array_chance[i - 1][1]);
        for(short int j = 0; j < length[i]; j++)
		{
            printf("%d", code_word[i][j]);
        }
        printf("\t\t%0.f\n", length[i]);
    }
    printf("Average length of code words: %f\n", average_code_length);
}

int Reading_Symbols()
{
	double** array_chance;
    FILE* file;
	double entropy = 0.0;
	int symbol_alphabet = QUANTITY_SYMBOL_IN_ALPHABET;
	int sum = 0;
	char symbol = '\0';
	file = fopen(FILE_NAME, READ_BINARY_ONLY);
	if(file == NULL)
	{
		return ERROR_OPEN_BASE;
	}
    array_chance = (double**)calloc(symbol_alphabet, sizeof(double*));
    if(array_chance == NULL)
    {
    	return ERROR_ALLOCATION_MEMORY;
	}
    for(short int i = 0; i < symbol_alphabet; i++)
	{
        array_chance[i] = (double*)calloc(2,sizeof(double));
        if(array_chance[i] == NULL)
        {
        	return ERROR_ALLOCATION_MEMORY;
		}
    }
    while(fread(&symbol, sizeof(char), 1, file) && (!feof(file)))
	{
        Fill_Chance_Meet_of_Symbols(symbol, array_chance, symbol_alphabet);
    }
    fclose(file);
    for(short int i = 0; i < symbol_alphabet; i++)
	{
        sum = (sum + array_chance[i][1]);
    }
    for(short int i = 0; i < symbol_alphabet; i++)
	{
        array_chance[i][1] = (array_chance[i][1] / sum);
    }
    for(short int i = 0; i < symbol_alphabet; i++)
	{
        entropy = (entropy + log(array_chance[i][1]) / log(2) * array_chance[i][1]);
    }
    entropy = entropy * -1;
    Coding_Symbols(array_chance, symbol_alphabet);
    printf("Entropy: %f\n", entropy);
    for(short int i = 0; i < symbol_alphabet; i++)
	{
        free(array_chance[i]);
        array_chance[i] = NULL;
    }
    free(array_chance);
    array_chance = NULL;
    return 0;
}

int main()
{
	vertex* root = NULL;
	queue *find = NULL;
    record** index = NULL;
    record* note = NULL;
    char* search_data = NULL;
    int error_flag = 0b0;
    int index_first_need_note = 0;
    int find_house = 0;
	char key_choice = '0';
	bool sort_flag = false;
	bool read_flag = false; 
    do
    {
        Draw_Menu();
        scanf(" %c", &key_choice);
        switch (key_choice)
		{
		case('1'):
		{
			error_flag = (error_flag | Read_Data_Base_To_Array(&note));
			index = (record** )malloc(SIZE_DATA_BASE * sizeof(record));
			if(index == NULL)
			{
				error_flag = (error_flag | ERROR_ALLOCATION_MEMORY);
				return error_flag;
			}
			for(short int i = 0; i < SIZE_DATA_BASE; i++)
			{
				index[i] = &note[i];
			}
			read_flag = true;
			sort_flag = false;
			break;
		}
		case('2'):
        {
            if(note != NULL)
			{
				Print_Data_Base(index);
			}
			else
			{
				printf("Data Base is not Read\n");
			}
			break;      
        }
        case('3'):
        {
        	if((sort_flag == false) && (read_flag == true))
        	{
        		Quick_Sort(index,0,SIZE_DATA_BASE-1);
        		sort_flag = true;
			}
			else
			{
				printf("The database has already been sorted or database has not read\n");
			}
			break;
		}
		case('4'):
		{
			if(sort_flag == true)
			{
				printf("Write need note to found\n");
				search_data = (char*)calloc(SIZE_KEY_SEARCH,sizeof(char));
				if(search_data == NULL)
				{
					return (error_flag | ERROR_ALLOCATION_MEMORY);
				}
				fflush(stdin);
				fread(search_data,sizeof(char),(SIZE_KEY_SEARCH + 1),stdin);
				error_flag = (error_flag | Search_In_Data_Base(index, search_data,&index_first_need_note));
				free(search_data);
				search_data = NULL;
				if(index_first_need_note != -1)
				{
					error_flag = (error_flag | Create_Queue_Found_Note(index, &find, index_first_need_note));
					Print_Queue(find);
				}
			}
			else
			{
				printf("Need sort base\n");
			}
			break;
		}
		case('5'):
		{
			if(find == NULL)
			{
				printf("Need Search by street name\n");
				break;
			}
			find->tail = find->head;
			do
			{
				Add_in_AVL(find->tail->data,&root);
				find->tail=find->tail->next;
			} while(find->tail != NULL);
			Print_Tree(root);
			printf("\nWrite need number of house\n");
			scanf("%d",&find_house);
			Search_In_Tree(root, find_house);
			printf("\n");
			if(root != NULL)
			{
				free(root);
				root = NULL;
			}
			break;
		}
		case('6'):
		{
			error_flag = (error_flag | Reading_Symbols());
			break;
		}
		case('9'):
		{
			system("CLS");
			break;
		}
        case('0'):
        {
            return error_flag;
        }
        default:
        {
        	printf("Incorrect choice\n");
        	break;
		}
        }
    } while(key_choice != '0');
    error_flag = (error_flag | ERROR_INCORECT_EXIT_FROM_PROGRAMM);
    for(short int i = 0; i < SIZE_DATA_BASE; i++)
	{
		free(index[i]);
		index[i] = NULL;
	}
	free(index);
	index = NULL;
	free(note);
	note = NULL;
	free(find);
	find = NULL;
    free(root);
    root = NULL;
	return error_flag;
}
