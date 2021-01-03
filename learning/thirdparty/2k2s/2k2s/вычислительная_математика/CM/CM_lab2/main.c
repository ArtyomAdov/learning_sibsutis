#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Divider_Matrix_on_center_item(float **Matrix, float *Vector, int line)
{
	float divider = 0;
	for (int i = 0; i < line; i++) {
		divider = Matrix[i][i];
		if (divider == 0) {
			continue;
		}
		for (int j = 0; j < line; j++) {
			Matrix[i][j] /= divider;
		}
		Vector[i] /= divider;
	}
}

void Zero_Main_Diagonal_Matrix(float ***Matrix, int line)
{
	for (int i = 0; i < line; i++) {
		(*Matrix)[i][i] = 0;
	}
}

float Get_Max_sum_str_abs_of_Matrix(float **Matrix, int line)
{
	if (!Matrix) {
		return -1;
	}

	float max = 0;
	float sum;

	for (int i = 0; i < line; i++) {
		sum = 0;
		for (int j = 0; j < line; j++) {
			sum += fabsf(Matrix[i][j]);
		}

		if (sum > max) {
			max = sum;
		}
	}

	return max;
}

float Get_Max_item_of_Vector(float *Vector, int line)
{
	if (!Vector) {
		return -1;
	}

	float max = 0;

	for (int i = 0; i < line; i++) {
		if (fabsf(Vector[i]) > max) {
			max = fabsf(Vector[i]);
		}
	}

	return max;
}

float Get_N(float max_C, float max_B)
{
	return (log((0.0001 * (1 - max_C)) / (max_B)) / log(max_C)) + 1;
}

float Get_Iteration(float **C, float *B, float line)
{
	float max_C = Get_Max_sum_str_abs_of_Matrix(C, line);
	printf("max_C = %.3f\n", max_C);

	if (max_C >= 1) {
		printf("Error, nan(kek)\n");
		exit(1);
	}

	float max_B = Get_Max_item_of_Vector(B, line);
	printf("max_B = %.3f\n", max_B);

	return Get_N(max_C, max_B);
}

int Get_Matrix(float ***Matrix, float **Vector, int *line, int *column)
{
	FILE *stream = fopen("Matrix.txt", "r");
	if (!stream) {
		return -1;
	}

	char *str = NULL;
	size_t len = 0;
	int count;

	while (getline(&str, &len, stream) != -1) {
		count = 0;
		for (int i = 0; str[i] != 0; i++) {
			if (str[i] == ' ') {
				count++;
			}
		}
		count++;

		if (count > *column) {
			*column = count;
		}
		(*line)++;
	}

	fseek(stream, 0, SEEK_SET);

	*Matrix = malloc(sizeof(float) * *line);
	*Vector = malloc(sizeof(float) * *line);

	for (int i = 0; i < *line; i++) {
		(*Matrix)[i] = malloc(sizeof(float) * *column);
		for (int j = 0; j < *column - 1; j++) {
			fscanf(stream, "%f", &(*Matrix)[i][j]);
		}
		fscanf(stream, "%f", &(*Vector)[i]);
	}

	free(str);
	fclose(stream);
	return 0;
}

void Print_Matrix(float **Matrix, int line)
{
	printf("\n");
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < line; j++) {
			printf("%.3f\t", Matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void Print_Vector(float *Vector, int line)
{
	for (int i = 0; i < line; i++) {
		printf("x%d = %.3f\t", i + 1, Vector[i]);
	}
	printf("\n\n");
}

void Zero_Vector(float *Vector, int line)
{
	for (int i = 0; i < line; i++) {
		Vector[i] = 0;
	}
}

void umnozenie_Matrix_Vector(float *Result, float **Matrix, float *Vector, int line)
{
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < line; j++) {
			Result[i] += Matrix[i][j] * Vector[j];
		}
	}
}

void Difference_Vector(float *Result, float *Vector1, float *Vector2, int line)
{
	for (int i = 0; i < line; i++) {
		Result[i] = Vector1[i] - Vector2[i];
	}
}

void Method_Simple_Iteration(float **C, float *B, int line, int column)
{
	Divider_Matrix_on_center_item(C, B, line);

	Zero_Main_Diagonal_Matrix(&C, line);

	Print_Matrix(C, line);

	int N = Get_Iteration(C, B, line);
	printf("N = %d\n", N);

	float *Cx = malloc(sizeof(float) * line);

	float *X = malloc(sizeof(float) * line);
	Zero_Vector(X, line);

	for (int k = 0; k < N; k++) {
		//printf("k = %d\n", k);
		Zero_Vector(Cx, line);
		umnozenie_Matrix_Vector(Cx, C, X, line);

		Zero_Vector(X, line);
		Difference_Vector(X, B, Cx, line);

		//Print_Vector(X, line);
	}

	Print_Vector(X, line);

	free(Cx);
	free(X);
}

void Method_Seedel(float **C, float *B, int line, int column)
{
	Divider_Matrix_on_center_item(C, B, line);

	Zero_Main_Diagonal_Matrix(&C, line);

	Print_Matrix(C, line);

	int N = Get_Iteration(C, B, line);
	printf("N = %d\n", N);

	float *Cx = malloc(sizeof(float) * line);

	float *X = malloc(sizeof(float) * line);
	Zero_Vector(X, line);

	for (int i = 0; i < 3; i++) {
		Zero_Vector(Cx, line);
		//printf("k = %d\n", i);
		for (int i = 0; i < line; i++) {
			for (int j = 0; j < line; j++) {
				Cx[i] += C[i][j] * X[j];
				//printf("Cx[%d] += %.3f * %.3f = %.3f\n", i, C[i][j], X[j], Cx[i]);
			}
			X[i] = B[i] - Cx[i];
			//printf("X[%d] = %.3f - %.3f = %.3f\n\n", i, B[i], Cx[i], X[i]);
		}
		//Print_Vector(X, line);
	}

	Print_Vector(X, line);

	free(Cx);
	free(X);
}

int main()
{
	int line = 0;
	int column = 0;
	float **C = NULL;
	float *B = NULL;

	Get_Matrix(&C, &B, &line, &column);

	Method_Simple_Iteration(C, B, line, column);
	//Method_Seedel(C, B, line, column);

	for (int i = 0; i < line; i++) {
		free(C[i]);
	}
	free(C);
	free(B);

	return 0;
}