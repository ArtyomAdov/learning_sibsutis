#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STEP_X 0.5
#define STEP_Z 0.5

double Function_Polinomial(double z, double *x, double *y, int n)
{
	double *polynomial_x = NULL;
	double fz = 0.0, multiple;
	polynomial_x = (double*) calloc (n, sizeof(double));
	for (int i = 0; i < n; i++) {
		multiple = 1.0;
		for (int j = 0; j < n; j++) {
			if (i != j) {
				multiple *= (z - x[j]) / (x[i] - x[j]);
			}
		}
		polynomial_x[i] = multiple * y[i];
	}
	for (int i = 0; i < n; i++) {
		// for(short int i = n-1; i >= 0; i--) {
		fz += polynomial_x[i];
		//}
	}
	free(polynomial_x);
	return fz;
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
	double z = 1.0;
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
			fprintf(point, "%.3f %.3f\n", z, Function_Polinomial(z, x, y, n));
		}
		fprintf(out, "%.3f %.3f\n", z, Function_Polinomial(z, x, y, n));
		z += STEP_Z;
	}
	fclose(out);
	return 0;
}