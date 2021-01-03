#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

const int threshold = 1000;

void swap(int *vi, int *vj)
{
	int buf = *vi;
	*vi = *vj;
	*vj = buf;
}

void partition(int *v, int *i, int *j, int low, int high) {
	*i = low;
	*j = high;
	int pivot = v[(low + high) / 2];
	do {
		while (v[*i] < pivot) (*i)++;
		while (v[*j] > pivot) (*j)--;
		if (*i <= *j) {
			swap(&v[*i], &v[*j]);
			(*i)++;
			(*j)--;
		}
	} while ((*i) <= (*j));
}

void quicksort_tasks(int *v, int low, int high) {
	int i, j;
	partition(v, &i, &j, low, high);
	if (high - low < threshold || (j - low < threshold || high - i < threshold)) {
		if (low < j)
			quicksort_tasks(v, low, j);
		if(i < high)
			quicksort_tasks(v, i, high);
		} else {
			#pragma omp task untied
			{
				quicksort_tasks(v, low, j);
			}
		quicksort_tasks(v, i, high);
	}
}

void init_arr(int *arr, int n)
{
	for (int i = 0; i < n; i++) {
		arr[i] = rand() / (RAND_MAX + 1.0) * (100000 - 1) + 1;
	}
}

int main(int argc, char const *argv[])
{
	int nthreads[7] = {1, 2, 4, 6, 8, 10, 12};

	for (int i = 0, n = 1000; i < 4; i++, n *= 10) {
		int *v = malloc(sizeof(int) * n);
		int *v_cp = malloc(sizeof(int) * n);

		init_arr(v, n);

		printf("Size array = %d\n", n);

		for (int j = 0; j < 3; j++) {
			memcpy(v_cp, v, sizeof(int) * n);

			double t = omp_get_wtime();
			#pragma omp parallel num_threads(nthreads[j])
			{
				#pragma omp single
				quicksort_tasks(v_cp, 0, n - 1);
			}
			t = omp_get_wtime() - t;

			printf("Threads: %d T%d = %f\n", nthreads[j], nthreads[j], t);
		}
	}

	return 0;
}