#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

#define ERROR_OPEN_BASE 0b00000001
#define ERROR_INCORECT_EXIT_FROM_PROGRAMM 0b00000010
#define ERROR_ALLOCATION_MEMORY 0b00000100
#define ERROR_NOT_FOUND_NOTE 0b00001000

#define DB_SIZE 4000
#define START_QUANTITY_RECORD_PRINT 20
#define SIZE_KEY_SORT 18
#define SIZE_KEY_SEARCH 3
#define LESS 0
#define EQUALLY 1
#define LARGE 2

#define FILE_NAME "testBase4.dat"
#define READ_BINARY_ONLY "rb"

typedef struct Record
{
    char citizen[32];
    char street_name[18];
    short int number_of_house;
    short int number_of_k;
    char date_of_[10];
} record;

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

void Draw_Menu()
{
	printf("1) Read Data Base\n");
    printf("2) Print Data Base\n");
    printf("3) Sort Data Base\n");
    printf("4) Find in Data Base\n");
    printf("9) Clear Screen\n");
    printf("0) Exit\n");
}

void Print_Head_Table()
{
	printf("\n\t\tFIO\t\t\t"); \
	printf("Street\t\t      "); \
	printf("House  "); \
	printf("Apartment "); \
	printf("Check in date\n");
}

void Print_Variant_Choice()
{
	printf("\nNext page - n\t");
	printf("Back page - b\t");
	printf("Choice specific page - s\t");
	printf("Close - c\n");	
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
		printf("%d\t", find->tail->data->number_of_k);
		printf("%s", find->tail->data->date_of_);
		i++;
		find->tail=find->tail->next;
	} while(find->tail!=NULL);
	printf("\n");
}

int Less(char* A, char* x)
{
	for(int i = 0; i < 18; i++)
	{
		if(A[i] < x[i])
		{
			return -1;
		}
		if(A[i] > x[i])
		{
			return 1;
		}
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
			while (Less(A[i]->street_name,x->street_name)==-1) {i++;}
           while (Less(A[j]->street_name,x->street_name)==1) {j--;}
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

void Print_Data_Base(record *index[])
{
    int Number = 0;
    int quantity_record_print = START_QUANTITY_RECORD_PRINT;
    char key_continue = '1';
	while (1)
	{
		Print_Head_Table();
		for (int i = Number; ((i < Number + quantity_record_print) && (i <DB_SIZE)); i++)
		{
			printf("\n%d) %s\t", i + 1, index[i]->citizen);
			printf("%s\t", index[i]->street_name);
			printf("%d\t", index[i]->number_of_house);
			printf("%d\t", index[i]->number_of_k);
			printf("%s", index[i]->date_of_);
		}
		Print_Variant_Choice();
		scanf(" %c", &key_continue);
		switch(key_continue)
		{
			case('n'):
			{
				Number = Number + quantity_record_print;
				if(Number >= DB_SIZE)
				{
					Number = DB_SIZE - quantity_record_print;
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
				printf("Write number page\n");
				scanf("%d",&key_specific);
				key_specific = key_specific - 1;
				Number = (key_specific * quantity_record_print);
				if(Number < 0 || Number >=DB_SIZE)
				{
					printf("Enter first tree letters of the street\n");
					Number = 0;
				}
				break;
			}
		/*Number = Number + QUANTITY_RECORD_PRINT;
		if (Number >= DB_SIZE)
		{
			break;
		}
		printf("\n\nContinue-?  Yes-1\n\n");
		scanf(" %c", &key_continue);                                              
		if (key_continue != '1')
		{
			break;
		}*/
		}
		printf("\n");
	}
}

int Read_Data_Base_To_Array(record **note)
{
	FILE *file = NULL;
	file = fopen(FILE_NAME, READ_BINARY_ONLY);
	if(file == NULL)
	{
		return ERROR_OPEN_BASE;
	}
	*note = (record *) malloc (DB_SIZE * sizeof(record));
	fread(*note, sizeof(record), DB_SIZE, file);
	fclose(file);
	return 0;
}

int Comparison_For_Search_Char_Field(char check_data[], char search_data[])
{
	for(short int i = 0; i < SIZE_KEY_SEARCH; i++)
	{
		if(search_data[i] > check_data[i])
		{
			return LARGE;
		}
		if(search_data[i] < check_data[i])
		{
			return LESS;
		}
	}
	return EQUALLY;
}

int Search_In_Data_Base(record** index, char search_data[], int* index_first_need_note)
{
	short int left_limit = 0;
	short int right_limit = (DB_SIZE - 1);
	short int index_midle = 0;
	do
	{
		index_midle = ((left_limit + right_limit) / 2);
		if(Comparison_For_Search_Char_Field(index[index_midle]->street_name, search_data) != LARGE)
		{
			printf("LESS:%s == %s\n",index[index_midle]->street_name, search_data);
			right_limit = index_midle;
		}
		else
		{
			printf("LARGE:%s == %s\n",index[index_midle]->street_name, search_data);
			left_limit = (index_midle + 1);
		}
	} while(left_limit < right_limit);
	if(Comparison_For_Search_Char_Field(index[index_midle]->street_name, search_data) == EQUALLY)
	{
		printf("EQUALLY:%s == %s\n",index[index_midle]->street_name, search_data);
		*index_first_need_note = right_limit;
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
		printf("^^^%s^^^\n",(*find)->tail->data->street_name);
		(*find)->tail = le;
		number++;
    } while((true == continue_flag) && (number < DB_SIZE));
	return 0;
}

int main()
{
    record** index = NULL;
    record* note = NULL;
    queue *find = NULL;
	char* search_data = NULL;
    int error_flag = 0b0;
    int index_first_need_note = 0;
	char key_choice = '0';
	bool sort_flag = false;
	bool read_flag = false;
    do
    {
        Draw_Menu();
        scanf(" %c", &key_choice);
        switch (key_choice)
		{
		case ('1'):
		{
			error_flag = (error_flag | Read_Data_Base_To_Array(&note));
			index = (record** ) malloc (DB_SIZE * sizeof(record));
			for (short int i = 0; i < DB_SIZE; i++)
			{
				index[i] = &note[i];
			}
			break;
		}
		case ('2'):
        {
            if (note != NULL)
			{
				Print_Data_Base(index);
			}
			else
			{
				printf("Data Base is not Read\n");
			}
			break;      
        }
        case ('3'):
        {
        	Quick_Sort(index,0,DB_SIZE-1);
        	sort_flag = true;
			break;
		}
		/*case('3'):
        {
        	if((sort_flag == false) && (read_flag == true))
        	{
        		//error_flag | Quick_Sort(index,0,DB_SIZE-1);
        		Quick_Sort(index,0,DB_SIZE-1);
        		sort_flag = true;
			}
			else
			{
				printf("The database has already been sorted or database has not read\n");
			}
			break;
		}*/
		case('4'):
		{
			if(sort_flag == true)
			{
				printf("Enter first three letters of the street\n");
				search_data = (char*)calloc(SIZE_KEY_SEARCH,sizeof(char));
				if(search_data == NULL)
				{
					return (error_flag | ERROR_ALLOCATION_MEMORY);
				}
				fflush(stdin);
				fread(search_data,sizeof(char),(SIZE_KEY_SEARCH + 1),stdin);
				printf("!!!%s\n",search_data);
				error_flag = (error_flag | Search_In_Data_Base(index, search_data,&index_first_need_note));
				free(search_data);
				search_data = NULL;
				if(index_first_need_note != -1)
				{
					error_flag = (error_flag | Create_Queue_Found_Note(index, &find, index_first_need_note));
					printf("***%s***\n",find->head->data->street_name);
					Print_Queue(find);
				}
			}
			else
			{
				printf("Need sort base\n");
			}
			break;
		}
        case ('0'):
        {
            return error_flag;
        }
        case ('9'):
        	{
        		system("CLS");
			break;
			}
        }
    }
	while (key_choice!='0');
    return error_flag;
}
