#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define QUANTITY_POINTS 4
#define START_VALUE_Z 1.69
#define START_VALUE_X 1
#define STEP_X 0.5
#define STEP_Z 0.5
#define COEFFICIENT_FOR_LENGTH_GRAPHICH 50

#define PRINT_ERROR_MESSEGE_DONT_OPEN_FILE_OUT \
	printf("Error: file out.txt dont open\n");

#define PRINT_ERROR_MESSEGE_DONT_OPEN_FILE_POINT \
	printf("Error: file point.txt dont open\n");

#define PRINT_VALUE_IN_FIND_POINT(value) \
    printf("Value interpolation polinomial in find point %f\n", value);

double Function_Polinomial(double *x, double *y, double z)
{
	double* array_result = NULL;
	array_result = (double*) calloc (QUANTITY_POINTS,sizeof(double));
	for(short int i = 0; i < QUANTITY_POINTS; i++)
	{
		array_result[i] = y[i];
	}
	for(short int i = 1; i < QUANTITY_POINTS; i++)
	{
		// for (short int j = 0; j < QUANTITY_POINTS - i; j++)
		for(short int j = QUANTITY_POINTS - i - 1; j >= 0; j--)
		{
			array_result[j] = (array_result[j] * (z - x[j + i]) - array_result[j + 1] * (z - x[j]));
			array_result[j] = (array_result[j] / (x[j] - x[j + i]));
		}
	}
	PRINT_VALUE_IN_FIND_POINT(array_result[0]);
	return array_result[0];
}

int main()
{
	FILE *out = NULL; 
	FILE *point = NULL;
	double *x = NULL;
	double *y = NULL;
	double z = START_VALUE_Z;
	x = (double*) calloc (QUANTITY_POINTS, sizeof(double));
	y = (double*) calloc (QUANTITY_POINTS, sizeof(double));
	x[0] = START_VALUE_X;
	y[0] = sqrt(x[0]);
	printf("\n%.4f \t %.4f\n",x[0],y[0]);
	for(short int i = 1; i < QUANTITY_POINTS; i++)
	{
		x[i] = x[i-1] + STEP_X;
		y[i] = sqrt((x[i]));
		printf("\n%.4f \t %.4f\n",x[i],y[i]);
	}
	out = fopen("picture/out.txt", "w");
	if(out == NULL)
	{
		PRINT_ERROR_MESSEGE_DONT_OPEN_FILE_OUT;
		return -1;
	}
	point = fopen("picture/point.txt", "w");
	if(point == NULL)
	{
		PRINT_ERROR_MESSEGE_DONT_OPEN_FILE_POINT;
		return -1;
	}
	for (short int i = 0; i < QUANTITY_POINTS * COEFFICIENT_FOR_LENGTH_GRAPHICH; i++) {
		if(i < QUANTITY_POINTS)
		{
			fprintf(point, "%.3f %.3f\n", z, Function_Polinomial(x, y, z));
		}
		fprintf(out, "%.3f %.3f\n", z, Function_Polinomial(x, y, z));
		z += STEP_Z;
	}
	free(x);
	free(y);
	fclose(point);
	fclose(out);
	return 0;
}