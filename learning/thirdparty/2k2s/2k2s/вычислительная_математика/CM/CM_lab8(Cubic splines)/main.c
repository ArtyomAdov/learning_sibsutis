#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void set_h(float *h, float *X, int n)
{
	for (int i = 1; i < n; i++)
		h[i] = X[i] - X[i - 1];
}

void print_h(float *h, int n)
{
	for (int i = 1; i < n; i++)
		printf("h[%d] = %.3f\n", i, h[i]);
	printf("\n");
}

void set_d(float *d, float *h, float *Y, int n)
{
	for (int i = 1; i < n - 1; i++)
		d[i] = ((Y[i + 1] - Y[i]) / h[i + 1]) - ((Y[i] - Y[i - 1]) / h[i]);
}

void print_d(float *d, int n)
{
	for (int i = 1; i < n - 1; i++)
		printf("d[%d] = %.3f\n", i, d[i]);
	printf("\n");
}

void set_C(float *C, float *h, int n)
{
	for (int i = 1; i < n - 1; i++) {
		for (int j = 1; j < n - 1; j++) {
			if (i == j) {
				C[i * n + j] = (h[i] + h[i + 1]) / 3;
			} else if (j == i + 1) {
				C[i * n + j] = h[i + 1] / 6;
			} else if (j == i - 1) {
				C[i * n + j] = h[i] / 6;
			} else {
				C[i * n + j] = 0;
			}
		}
	}
}

void print_C(float *C, int n)
{
	for (int i = 1; i < n - 1; i++) {
		for (int j = 1; j < n - 1; j++) {
			printf("%.3f\t", C[i * n + j]);
		}
		printf("\n");
	}
	printf("\n");
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
	for (int i = 1; i < n + 1; i++) {
		buf = a[j * (n + 1) + i];
		a[j * (n + 1) + i] = a[k * (n + 1) + i];
		a[k * (n + 1) + i] = buf;
	}
}

void Matrix_answer(float *arr_arg, float *a, int n)
{
	for (int i = n - 1; i > 0; i--) {
		for (int j = n - 1; j != i; j--) {
			a[i * (n + 1) + n] = a[i * (n + 1) + n] - (a[i * (n + 1) + j] * arr_arg[j]);
			a[i * (n + 1) + j] = 0;
		}

		arr_arg[i] = a[i * (n + 1) + n] / a[i * (n + 1) + i];
	}
}

void set_M(float *M, float *C, float *d, int n)
{
	// M[0] = 0;
	// M[n - 1] = 0;

	// for (int i = 1, j = 1; i < n; i++, j++) {
	// 	float c = C[i * n + j];
	// 	if (j - 1 != 0)
	// 		c += C[i * n + (j - 1)];
	// 	if (j + 1 != 4)
	// 		c += C[i * n + (j + 1)];

	// 	M[i] = d[i] / c;
	// }
	float *arr = malloc(sizeof(float) * n * (n + 1));

	for (int i = 1; i < n - 1; i++) {
		for (int j = 1; j < n; j++) {
			arr[i * n + j] = C[i * n + j];
		}
		arr[i * n + (n - 1)] = d[i];
	}

	// for (int i = 1; i < n - 1; i++) {
	// 	for (int j = 1; j < n; j++) {
	// 		printf("%.3f\t", arr[i * n + j]);
	// 	}
	// 	printf("\n");
	// }

	float mult;

	for (int j = 1; j < n - 2; j++) {

		int num_ind = Matrix_max_first_elem(arr, j, n - 1);
		Matrix_swap_line(arr, j, num_ind, n - 1);

		for (int i = j + 1; i < (n - 1); i++) {
			if (arr[i * (n - 1) + j] != 0) {
				mult = -(arr[i * (n - 1) + j] / arr[j * (n - 1) + i]);
			} else {
				break;
			}

			for (int k = j; k < n; k++) {
				arr[i * (n - 1) + k] += mult * arr[j * (n - 1) + k];
			}
		}
	}

	Matrix_answer(M, arr, (n - 1));
}

void print_M(float *M, int n)
{
	for (int i = 0; i < n; i++)
		printf("M[%d] = %.3f\n", i, M[i]);
}

int set_i(float *X, float x, int n)
{
	int i = 0;
	for (int j = 1; j < n; j++) {
		if (X[j - 1] <= x && x <= X[j])
			i = j;
	}
	// printf("%d\n", i);

	return i;
}

float set_s(float *X, float *Y, float x, float *h, float *M, int i)
{
	float s = M[i - 1] * (pow((X[i] - x), 3) / (6 * h[i]));
	s += M[i] * (pow((x - X[i - 1]), 3) / (6 * h[i]));
	s += (Y[i - 1] - ((M[i - 1] * pow(h[i], 2)) / 6)) * ((X[i] - x) / h[i]);
	s += (Y[i] - ((M[i] * pow(h[i], 2)) / 6)) * ((x - X[i - 1]) / h[i]);

	return s;
}

float CubSpl(float *X, float *Y, float x, int n)
{
	float *h = malloc(sizeof(float) * n);
	float *d = malloc(sizeof(float) * (n - 1));
	float *C = malloc(sizeof(float) * n * n);
	float *M = malloc(sizeof(float) * n);

	set_h(h, X, n);
	// print_h(h, n);

	set_d(d, h, Y, n);
	// print_d(d, n);

	set_C(C, h, n);
	// print_C(C, n);

	set_M(M, C, d, n);
	// print_M(M, n);

	int i = set_i(X, x, n);

	float s = set_s(X, Y, x, h, M, i);

	free(M);
	free(C);
	free(d);
	free(h);

	return s;
}

int main()
{
	int n = 5;
	// float Y[5] = { 1.4142, 1.7321, 2.0, 2.2361, 2.4495 };
	float Y[5] = { 0 };
	float X[5] = { 2.0 , 3.0, 4.0, 5.0, 6.0 };
	for (int i = 0; i < n; i++) {
		Y[i] = exp(X[i]);
	}

	#if 0
	float x = 3.6;
	printf("x = %.3f y = %.3f\n", x, CubSpl(X, Y, x, n));
	#endif

	#if 1
	FILE *out = fopen("out.txt", "w");

	float x = 2.0;

	for (int i = 0; i < 20; i++) {
		fprintf(out, "%.3f %.3f\n", x, CubSpl(X, Y, x, n));
		x += 0.2;
	}

	fclose(out);
	#endif

	// gnuplot "scen.plt"

	return 0;
}