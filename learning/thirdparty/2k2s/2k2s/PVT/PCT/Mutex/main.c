#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t mutex;

double wtime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + tv.tv_usec * 1E-6;
}

void *sum(void *arg)
{
	pthread_mutex_lock(&mutex);
	for (int i = 0; i < 1024 * 1024; i++) {
		counter++;
	}
	printf("%d\n", counter);
	pthread_mutex_unlock(&mutex);
	return;
}

int main()
{
	//double time;
	pthread_t test;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&test, NULL, sum, NULL);

	pthread_mutex_lock(&mutex);
	for (int i = 0; i < 1024 * 1024; i++) {
		counter++;
	}
	pthread_mutex_unlock(&mutex);

	pthread_join(test, NULL);
	pthread_mutex_destroy(&mutex);

	printf("%d\n", counter);

	return 0;
}
