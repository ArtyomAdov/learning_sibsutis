#include <stdio.h>
#include <math.h>
#include "Gauss_method.h"

void Matrix_Print(float *a, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n + 1; j++) {
			printf("%.3f\t", a[i * (n + 1) + j]);
		}
		printf("\n");
	}
}

int Matrix_max_first_elem(float *a, int j, int n)
{
	float num = 0;
	int num_ind = 0;

	for (int z = j; z < n; z++) {
		if (fabsf(a[z * (n + 1) + j]) > num) {
			num = a[z * (n + 1) + j];
			num_ind = z;
		}
	}

	return num_ind;
}

void Matrix_swap_line(float *a, int j, int k, int n)
{
	float buf;
	for (int i = 0; i < n + 1; i++) {
		buf = a[j * (n + 1) + i];
		a[j * (n + 1) + i] = a[k * (n + 1) + i];
		a[k * (n + 1) + i] = buf;
	}
}

void Matrix_answer(float *arr_arg, float *a, int n)
{
	for (int i = n - 1; i >= 0; i--) {
		for (int j = n - 1; j != i; j--) {
			a[i * (n + 1) + n] = a[i * (n + 1) + n] - (a[i * (n + 1) + j] * arr_arg[j]);
			a[i * (n + 1) + j] = 0;
		}

		arr_arg[i] = a[i * (n + 1) + n] / a[i * (n + 1) + i];
	}
}

void Matrix_print_answer(float *arr_arg, int n)
{
	for (int i = 0; i < n; i++) {
		printf("x%d = %.3f\n", i, arr_arg[i]);
	}
}