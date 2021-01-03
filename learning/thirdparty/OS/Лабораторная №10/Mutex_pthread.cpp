#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"
#include <conio.h>

pthread_mutex_t Mutex;//=PTHREAD_MUTEX_INITIALIZER;
char sh[6];
void* Thread(void* pParams);

int main(void) 
{
 	pthread_t thread_id;
 	pthread_mutex_init(&Mutex, NULL);
  	pthread_create(&thread_id, NULL, &Thread, NULL);
 
	while (1)
	{
 		pthread_mutex_lock(&Mutex);
 		printf("%s\n", sh);
 		pthread_mutex_unlock(&Mutex);
 	}
 	return 0;
}
 
void* Thread(void* pParams)
{
 	int counter = 0;
 	while (1)
	{
 		pthread_mutex_lock(&Mutex);
 		if (counter % 2)
		{
 			sh[0]='H';
			sh[1]='e';
			sh[2]='l';
			sh[3]='l';
			sh[4]='o';
			sh[5]='\0';
 		}
 		else
		{
 			sh[0]='B';
			sh[1]='y';
			sh[2]='e';
			sh[3]='_';
			sh[4]='u';
			sh[5]='\0';
 		}
 		pthread_mutex_unlock(&Mutex);
 		counter++;
 	}
 	return NULL;
}
