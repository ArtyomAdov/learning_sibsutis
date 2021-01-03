#include <stdio.h>
#include <stdlib.h>

typedef struct List
{
	int data;
	struct List* next;
} list;

void Print_All_List(list* head)
{
	list* temp_head = NULL;
	temp_head = head;
	while(temp_head!=NULL)
	{
		printf("%d ",temp_head->data);
		temp_head = temp_head->next;
	}	
}

list* Add_Note_In_List(list** head)
{
	list* temp_head = NULL;
	list* temp_note = NULL;
	list* temp_tail = NULL;
	list* temp_temp = NULL;
	char continue_key = '1';
	if(*head!=NULL)
	{
		temp_temp = (*head);
		while((temp_temp)->next!=NULL)
		{
			temp_temp = temp_temp->next;
		}	
	}
	while(continue_key == '1')
	{
		temp_note = (list*) malloc (1 * sizeof(list));
		temp_note->next = NULL;
		printf("Write need note\n");
		scanf("%d",&temp_note->data);
		if(temp_head==NULL)
		{
			temp_tail = temp_head = temp_note;
		} 
		else 
		{
			temp_tail->next = temp_note;
			temp_tail = temp_note;
		}
		printf("If you want add new note write 1\n");
		scanf(" %c",&continue_key);	
	}
	if(*head==NULL)
	{
		*head = temp_head;
	} 
	else 
	{
		temp_temp->next = temp_head;	
	}
	return NULL;
}

int main()
{
	list* head = NULL;
	Add_Note_In_List(&head);
	Print_All_List(head);
	free(head);
	head = NULL;
	return 0;
}
