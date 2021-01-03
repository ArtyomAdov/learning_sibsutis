#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE_ARRAY 5
#define NUMBER_PI 3.1416
#define COEFFICIENT_DIRECT -2.0
#define COEFFICIENT_INVERSE 2.0

typedef struct Complex_Type
{
	double real;
	double imaginary;
} complex;

complex Addition_Complex_Number(complex first, complex second)
{
    complex result;
    result.real = (first.real + second.real);
    result.imaginary = (first.imaginary + second.imaginary);
    return result;
}

complex Subtraction_Complex_Number(complex first, complex second)
{
    complex result;
    result.real = (first.real - second.real);
    result.imaginary = (first.imaginary - second.imaginary);
    return result;
}

complex Multiplication_Complex_Number(complex first, complex second)
{
    complex result;
    result.real = ((first.real * second.real) - (first.imaginary * second.imaginary));
    result.imaginary = ((first.real * second.imaginary) + (first.imaginary * second.real));
    return result;
}

complex Division_Complex_Number(complex first, complex second)
{
    complex result;
    result.real = (((first.real * second.real) + (first.imaginary * second.imaginary))/((second.real * second.real) + (second.imaginary * second.imaginary)));
    result.imaginary = (((first.real * second.imaginary)-(first.imaginary * second.real))/((second.real * second.real)+(second.imaginary * second.imaginary)));
    return result;
}

complex* Fill_Inc(complex* array)
{
	array = (complex*)calloc(SIZE_ARRAY, sizeof(complex));
	for(short int i = 0; i < SIZE_ARRAY; i++)
	{
		array[i].real = (double)i;
		array[i].imaginary = 0.0;
	}
	return array;
}

void Print_Complex_Array(complex* array)
{
	for(short int i = 0; i < SIZE_ARRAY; i++)
	{
		printf("Arr[%d]:(%lf + %lf * i)\n", i, array[i].real, array[i].imaginary);
	}
	printf("\n");
}

complex* Fill_Zero(complex* convert_array)
{
	convert_array = (complex*)calloc(SIZE_ARRAY, sizeof(complex));
	for(short int i = 0; i < SIZE_ARRAY; i++)
	{
		convert_array[i].real = 0.0;
		convert_array[i].imaginary = 0.0;
	}
	return convert_array;
}

complex Convert_Real_In_Complex(double number_real)
{
	complex number_complex;
	number_complex.real = number_real;
	number_complex.imaginary = 0.0;
	return number_complex;
}

complex Find_Exponent_For_Complex(complex number)
{
	complex result;
	result.real = (exp(number.real) * cos(number.imaginary));
	result.imaginary = (exp(number.real) * sin(number.imaginary));
	return result;
}

complex* Direct_Discrete_Conversion(complex* array)
{
	complex* convert_array = NULL;
	complex temp = {0.0,0.0};
	complex number_i = {0.0,1.0};
	complex intermediate = {0.0,0.0};
	convert_array = Fill_Zero(convert_array);
	for(short int i = 0; i < SIZE_ARRAY; i++)
	{
		for(short int j = 0; j < SIZE_ARRAY; j++)
		{
			temp.real = 0.0;
			temp.imaginary = 0.0;
			intermediate = Convert_Real_In_Complex(COEFFICIENT_DIRECT);
			temp = Addition_Complex_Number(intermediate,temp);
			intermediate = Convert_Real_In_Complex(NUMBER_PI);
			temp = Multiplication_Complex_Number(intermediate,temp);
			intermediate = Convert_Real_In_Complex((double)i);
			temp = Multiplication_Complex_Number(intermediate,temp);
			intermediate = Convert_Real_In_Complex((double)j);
			temp = Multiplication_Complex_Number(intermediate,temp);
			temp = Multiplication_Complex_Number(number_i,temp);
			intermediate = Convert_Real_In_Complex((double)SIZE_ARRAY);
			temp = Division_Complex_Number(temp, intermediate);
			temp = Find_Exponent_For_Complex(temp);
			temp = Multiplication_Complex_Number(array[j],temp);
			convert_array[i] = Addition_Complex_Number(temp,convert_array[i]);
		}
		temp = Convert_Real_In_Complex((double)SIZE_ARRAY);
		convert_array[i] = Division_Complex_Number(convert_array[i],temp);
	}
	return convert_array;
}

complex* Inverse_Discrete_Conversion(complex* array)
{
	complex* convert_array = NULL;
	complex temp = {0.0,0.0};
	complex number_i = {0.0,1.0};
	complex intermediate = {0.0,0.0};
	convert_array = Fill_Zero(convert_array);
	for(short int i = 0; i < SIZE_ARRAY; i++)
	{
		for(short int j = 0; j < SIZE_ARRAY; j++)
		{
			temp.real = 0.0;
			temp.imaginary = 0.0;
			intermediate = Convert_Real_In_Complex(COEFFICIENT_DIRECT);
			temp = Addition_Complex_Number(intermediate,temp);
			intermediate = Convert_Real_In_Complex(NUMBER_PI);
			temp = Multiplication_Complex_Number(intermediate,temp);
			intermediate = Convert_Real_In_Complex((double)i);
			temp = Multiplication_Complex_Number(intermediate,temp);
			intermediate = Convert_Real_In_Complex((double)j);
			temp = Multiplication_Complex_Number(intermediate,temp);
			temp = Multiplication_Complex_Number(number_i,temp);
			intermediate = Convert_Real_In_Complex((double)SIZE_ARRAY);
			temp = Division_Complex_Number(temp, intermediate);
			temp = Find_Exponent_For_Complex(temp);
			temp = Multiplication_Complex_Number(array[j],temp);
			convert_array[i] = Addition_Complex_Number(temp,convert_array[i]);
		}
	}
	return convert_array;
}

int main()
{
	complex* array = NULL;
	array = Fill_Inc(array);
	printf("ORIGINAL:\n");
	Print_Complex_Array(array);
	array = Direct_Discrete_Conversion(array);
	printf("DIRECT:\n");
	Print_Complex_Array(array);
	array = Inverse_Discrete_Conversion(array);
	printf("INVERSE:\n");
	Print_Complex_Array(array);
	free(array);
	array = NULL;
	return 0;
}
