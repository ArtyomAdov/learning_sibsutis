#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define EXP 0.001

float f(int num, float x, float y, float z)
{
	if (num == 0) {
		return x * x + y * y + z * z - 1;
	} else if (num == 1) {
		return 2 * x * x + y * y - 4 * z;
	} else if (num == 2) {
		return 3 * x * x - 4 * y + z * z;
	}
	exit(1);
}

float df(int num, float x, float y, float z)
{

	if (num == 0) {
		return 2 * x + 2 * y + 2 * z;
	} else if (num == 1) {
		if (z != 0) {
			return -4;
		}
		return 4 * x + 2 * y;
	} else if (num == 2) {
		if (y != 0) {
			return -4;
		}
		return 6 * x + 2 * z;
	}
	exit(1);
}

void Vector_print(float *x, int n)
{
	for (int i = 0; i < n; i++) {
		printf("%3f\n", x[i]);
	}
}

void Matrix_print(float *x, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%3f ", x[i * n + j]);
		}
		printf("\n");
	}
	printf("\n");
}

int Matrix_max_first_elem(float *W, int j, int n)
{
	float num = 0;
	int ind_str = 0;

	for (int z = j; z < n; z++) {
		if (fabsf(W[z * n + j]) > num) {
			num = W[z * n + j];
			ind_str = z;
		}
	}

	return ind_str;
}

void Matrix_swap_line(float *W, int j, int k, int n)
{
	float buf;
	for (int i = 0; i < n; i++) {
		buf = W[j * n + i];
		W[j * n + i] = W[k * n + i];
		W[k * n + i] = buf;
	}
}

void Create_matrix_jacobi(float *W, float *Wj, int n)
{
	//Matrix_print(W, n);
	//Matrix_print(Wj, n);
	//printf("//////////\n");

	float mult = 0;
	for (int j = 0; j < n; j++) {

		int ind_str = Matrix_max_first_elem(W, j, n);
		//printf("%d\n", ind_str);
		Matrix_swap_line(W, j, ind_str, n);
		Matrix_swap_line(Wj, j, ind_str, n);

		//Matrix_print(W, n);
		//Matrix_print(Wj, n);

		for (int i = j + 1; i < n; i++) {
			if (W[i * n + j] != 0) {
				mult = -(W[i * n + j] / W[j * n + j]);
			} else {
				break;
			}
			//printf("%3f\n", mult);

			for (int k = j; k < n; k++) {
				W[i * n + k] += mult * W[j * n + k];
				Wj[i * n + k] += mult * Wj[j * n + k];
			}
		}

		//Matrix_print(W, n);
		//Matrix_print(Wj, n);
	}
	//Matrix_print(W, n);

	//printf("///////\n");
	//Matrix_print(W, n);
	//Matrix_print(Wj, n);

	for (int i = 0; i < n; i++) {
		mult = W[i * n + i];
		for (int j = 0; j < n; j++) {
			W[i * n + j] /= mult;
			Wj[i * n + j] /= mult;
		}
	}

	//Matrix_print(W, n);
	//Matrix_print(Wj, n);
	//printf("///////\n");

	for (int j = n - 1; j >= 0; j--) {
		//printf("j = %d\n", j);
		//Matrix_print(W, n);
		//Matrix_print(Wj, n);

		for (int i = j - 1; i >= 0; i--) {
			//printf("i = %d\n", i);
			//printf("%3f\n", W[i * n + j]);
			//printf("%3f\n", W[j * n + j]);
			if (W[i * n + j] != 0) {
				mult = -(W[i * n + j] / W[j * n + j]);
			} else {
				break;
			}
			//printf("%3f\n", mult);

			for (int k = j; k >= 0; k--) {
				W[i * n + k] += mult * W[j * n + k];
				Wj[i * n + k] += mult * Wj[j * n + k];
			}

			//Matrix_print(W, n);
			//Matrix_print(Wj, n);
		}
	}
}

void Mult_Matrix_Vector(float *Result, float *Matrix, float *Vector, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			Result[i] += Matrix[i * n + j] * Vector[j];
		}
	}
}

int main()
{
	int n = 3;
	float max;
	float *X = calloc(n, sizeof(float));
	float *Xold = calloc(n, sizeof(float));
	float *Y = calloc(n, sizeof(float));
	float *MAX = calloc(n, sizeof(float));
	float *Fx = calloc(n, sizeof(float));
	float *W = calloc(n * n, sizeof(float));
	float *Wj = calloc(n * n, sizeof(float));

	for (int i = 0; i < n; i++) {
		X[i] = 0.5;
	}

	//Matrix_print(W, n);
	//Matrix_print(Wj, n);

	//Create_matrix_jacobi(W, Wj, n);

	//Matrix_print(W, n);
	//Matrix_print(Wj, n);

	//Wj[2] = Wj[1];
	do {
		max = INT_MIN;

		for (int i = 0; i < n; i++) {
			Xold[i] = X[i];
		}

		for (int i = 0; i < n; i++) {
			Fx[i] = f(i, X[0], X[1], X[2]);
		}

		for (int i = 0; i < n; i++) {
			Wj[i * n + i] = 1;
		}

		for (int i = 0; i < n; i++) {
			W[i * n + 0] = df(i, X[0], 0, 0);
			W[i * n + 1] = df(i, 0, X[1], 0);
			W[i * n + 2] = df(i, 0, 0, X[2]);
		}

		// /Matrix_print(W, n);

		Create_matrix_jacobi(W, Wj, n);
		//Wj[2] = Wj[1];//супер костыль

		Mult_Matrix_Vector(Y, Wj, Fx, n);

		for (int i = 0; i < n; i++) {
			X[i] = X[i] - Y[i];
		}
		//Vector_print(X, n);
		//Vector_print(Y, n);
		//printf("\n");
		//Vector_print(X, n);
		//printf("\n");

		for (int i = 0; i < n; i++) {
			MAX[i] = X[i] - Xold[i];
		}
		//Vector_print(MAX, n);
		//printf("//////////////////////////\n");
		for (int i = 0; i < n; i++) {
			if (fabsf(MAX[i]) > max) {
				max = fabsf(MAX[i]);
			}
		}
		//printf("%3f\n", max);
		//printf("//////////////////////////\n");

		for (int i = 0; i < n; i++) {
			Y[i] = 0;
			for (int j = 0; j < n; j++) {
				//Y[i * n + j] = 0;
				Wj[i * n + j] = 0;
			}
		}

	} while (max > EXP);

	Vector_print(X, n);

	free(X);
	free(Xold);
	free(Y);
	free(MAX);
	free(Fx);
	free(W);
	free(Wj);
	return 0;
}