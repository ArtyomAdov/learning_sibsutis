#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STEP_X 0.5
#define STEP_Z 0.5

double Delta_Y(double *Y, int j, int i)
{
	if (i == 1) {
		return Y[j + 1] - Y[j];
	} else if (i == 0) {
		return Y[0];
	} else {
		return Delta_Y(Y, j + 1, i - 1) - Delta_Y(Y, j, i - 1);
	}
	return 0;
}

double Factorial(int n)
{
	if (n == 0) {
		return 1.0;
	} else {
		return n * Factorial(n - 1);
	}
	return 0;
}

double Function_Polinomial(double *X, double *Y, double z, int n)
{
	double y, step;
	double *dy;
	y = 0;
	step = X[1] - X[0];
	dy = (double*) calloc (n,sizeof(double));
	for (int i = 0; i < n; i++) {
		dy[i] = Delta_Y(Y, 0, i);
	}
	for (int i = 0; i < n; i++) {
		double mult = 1;
		for (int j = 0; j < i; j++) {
			mult *= (z - X[0]) / step - j;
		}
		y += (dy[i] / Factorial(i)) * mult;
	}
	free(dy);
	return y;
}

int main()
{
	double *x = NULL;
	double *y = NULL;
	int n = 3;
	x = (double*) calloc (n, sizeof(double));
	y = (double*) calloc (n, sizeof(double));
	x[0] = 1;
	y[0] = sqrt(x[0]);
	printf("\n%.4f \t %.4f\n",x[0],y[0]);
	for(short int i = 1; i < n; i++)
	{	
		x[i] = x[i-1] + STEP_X;
		y[i] = sqrt((x[i]));
		printf("\n%.4f \t %.4f\n",x[i],y[i]);
	}
	double z = 1.69;
	FILE *out = NULL; 
	FILE *point = NULL;
	out = fopen("picture/out.txt", "w");
	if(out == NULL)
	{
		printf("error: file out.txt dont open\n");
		return -1;
	}
	point = fopen("picture/point.txt", "w");
	if(out == NULL)
	{
		printf("error: file point.txt dont open\n");
		return -1;
	}
	for (int i = 0; i < n*50; i++) {
		if(i < n)
		{
			fprintf(point, "%.3f %.3f\n", z, Function_Polinomial(x, y, z, n));
		}
		fprintf(out, "%.3f %.3f\n", z, Function_Polinomial(x, y, z, n));
		z += STEP_Z;
	}
	fclose(out);
	return 0;
}
