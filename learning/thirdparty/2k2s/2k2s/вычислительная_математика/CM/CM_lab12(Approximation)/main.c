#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Gauss.h"

float* set_b(float *X, float *Y, int n, int p)
{
	float *b = malloc(sizeof(*b) * p);
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < n; j++) {
			b[i] += pow(X[j], i) * Y[j];
		}
	}
	return b;
}

void print_b(float *b, int p)
{
	for (int i = 0; i < p; i++) {
		printf("b[%d] = %f \n", i, b[i]);
	}
	printf("\n");
}

float* set_C(float *X, int n, int p)
{
	float *C = malloc(sizeof(*C) * p * p);
	for(int i = 0; i < p; i++){
		for(int j = 0; j < p; j++){
			C[get_intdex(i, j, p)] = 0;
			for(int k = 0; k < n; k++)
			   C[get_intdex(i, j, p)] += pow(X[k], i + j);
		}
	}
	return C;
}

void print_C(float *C, int p)
{
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < p; j++)
			printf("%.3f__", C[get_intdex(i, j, p)]);
		printf("\n");
	}
	printf("\n");
}

void print_a(float *a, int p)
{
	for (int i = 0; i < p; i++) {
		printf("a[%d] = %f \n", i, a[i]);
	}
	printf("\n");
}

float* Approximation(float *X, float *Y, int n, int p)
{
	float *b = set_b(X, Y, n, p);
	// print_b(b, p);
	
	float *C = set_C(X, n, p);
	// print_C(C, p);
	
	float *a = malloc(sizeof(*a) * p);
	GaussMethod(C, b, a, p);
	// print_a(a, p);
	
	free(C);
	free(b);

	return a;
}

float F(float *a, float x, int p)
{
	float y = 0;
	for (int i = 0; i <= p; i++)
		y += a[i] * pow(x, i);
	return y;
}

int main()
{
	int n = 6;
	int p = 4;
	float *X = malloc(sizeof(float) * n);
	float *Y = malloc(sizeof(float) * n);

	for (int i = 0; i < n; i++) {
		X[i] = i;
		Y[i] = sqrtf(X[i]);
	}

	#if 0
	for (int i = 0; i < n; i++) {
		printf("X[%d] = %f \t", i, X[i]);
		printf("Y[%d] = %f \n", i, Y[i]);
	}
	printf("\n");
	#endif

	float *a = Approximation(X, Y, n, p + 1);

	for (int i = 0; i < n; i++)
		printf("x = %f y = %f ya = %f\n", X[i], Y[i], F(a, X[i], p));

	#if 1
	FILE *out = fopen("out.txt", "w");
	for (float i = X[0]; i <= X[n - 1]; i += 0.1)
		fprintf(out, "%.3f %.3f\n", i, F(a, i, p));

	fclose(out);
	#endif

	free(a);
	free(Y);
	free(X);

	return 0;
}