#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void divider_exp_matrix(float **Matrix, float *Vector, int line);
void zero_main_diagonal_matrix(float ***Matrix, int line);
float get_max_matrix(float **Matrix, int line);
float get_max_vector(float *Vector, int line);
float get_n(float max_C, float max_B);
float get_iteration(float **C, float *B, float line);
int get_matrix(float ***Matrix, float **Vector, int *line, int *column);
void print_matrix(float **Matrix, int line);
void print_vector(float *Vector, int line);
void zero_vector(float *Vector, int line);
void mult_matrix_vector(float *Result, float **Matrix, float *Vector, int line);
void difference_vector(float *Result, float *Vector1, float *Vector2, int line);
void method_simple_iteration(float **C, float *B, int line, int column);
void method_seedel(float **C, float *B, int line, int column);




int main()
{
	int line = 0;
	int column = 0;
	float **C = NULL;
	float *B = NULL;

	get_matrix(&C, &B, &line, &column);

	//method_simple_iteration(C, B, line, column);
	method_seedel(C, B, line, column);

	for (int i = 0; i < line; i++) {
		free(C[i]);
	}
	free(C);
	free(B);

	return 0;
}




int get_matrix(float ***Matrix, float **Vector, int *line, int *column)
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

//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo

	void divider_exp_matrix(float **Matrix, float *Vector, int line)
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


	void zero_main_diagonal_matrix(float ***Matrix, int line)
	{
		for (int i = 0; i < line; i++) {
			(*Matrix)[i][i] = 0;
		}
	}
	void print_matrix(float **Matrix, int line)
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

	float get_iteration(float **C, float *B, float line)
	{
		float max_C = get_max_matrix(C, line);
		printf("max_C = %.3f\n", max_C);

		if (max_C >= 1) {
			printf("Error, nan(kek)\n");
			exit(1);
		}

		float max_B = get_max_vector(B, line);
		printf("max_B = %.3f\n", max_B);

		return get_n(max_C, max_B);
	}

		float get_max_matrix(float **Matrix, int line)
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


		float get_max_vector(float *Vector, int line)
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

		float get_n(float max_C, float max_B)
		{
			return (log((0.001 * (1 - max_C)) / (max_B)) / log(max_C)) + 1;
		}

	void zero_vector(float *Vector, int line)
	{
		for (int i = 0; i < line; i++) {
			Vector[i] = 0;
		}
	}

	void print_vector(float *Vector, int line)
	{
		for (int i = 0; i < line; i++) {
			printf("x%d = %.3f\t", i + 1, Vector[i]);
		}
		printf("\n\n");
	}


void method_seedel(float **C, float *B, int line, int column)
{
	divider_exp_matrix(C, B, line);

	zero_main_diagonal_matrix(&C, line);

	print_matrix(C, line);

	int N = get_iteration(C, B, line);
	printf("N = %d\n", N);

	float *Cx = malloc(sizeof(float) * line);

	float *X = malloc(sizeof(float) * line);
	zero_vector(X, line);

	for (int i = 0; i < N; i++) {
		zero_vector(Cx, line);
		//printf("k = %d\n", i);
		for (int i = 0; i < line; i++) {
			for (int j = 0; j < line; j++) {
				Cx[i] += C[i][j] * X[j];
				//printf("Cx[%d] += %.3f * %.3f = %.3f\n", i, C[i][j], X[j], Cx[i]);
			}
			X[i] = B[i] - Cx[i];
			//printf("X[%d] = %.3f - %.3f = %.3f\n\n", i, B[i], Cx[i], X[i]);
		}
		//print_vector(X, line);
	}

	print_vector(X, line);

	free(Cx);
	free(X);
}










void method_simple_iteration(float **C, float *B, int line, int column)
{
	divider_exp_matrix(C, B, line);

	zero_main_diagonal_matrix(&C, line);

	print_matrix(C, line);

	int N = get_iteration(C, B, line);
	printf("N = %d\n", N);

	float *Cx = malloc(sizeof(float) * line);

	float *X = malloc(sizeof(float) * line);
	zero_vector(X, line);

	for (int k = 0; k < N; k++) {
		//printf("k = %d\n", k);
		zero_vector(Cx, line);
		mult_matrix_vector(Cx, C, X, line);

		zero_vector(X, line);
		difference_vector(X, B, Cx, line);

		//print_vector(X, line);
	}

	print_vector(X, line);

	free(Cx);
	free(X);
}

	void mult_matrix_vector(float *Result, float **Matrix, float *Vector, int line)
	{
		for (int i = 0; i < line; i++) {
			for (int j = 0; j < line; j++) {
				Result[i] += Matrix[i][j] * Vector[j];
			}
		}
	}





	void difference_vector(float *Result, float *Vector1, float *Vector2, int line)
	{
		for (int i = 0; i < line; i++) {
			Result[i] = Vector1[i] - Vector2[i];
		}
	}