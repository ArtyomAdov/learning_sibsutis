#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Complex_Type
{
	double real;
	double imaginary;
} complex;

void Print_Complex_Array(complex* array, int size_array)
{
	for(short int i = 0; i < size_array; i++)
	{
		printf("Arr[%d]:(%lf + %lf * i)\n", i, array[i].real, array[i].imaginary);
	}
	printf("\n");
}

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

complex* Fill_Zero(complex* convert_array, int size_array)
{
	convert_array = (complex*)calloc(size_array, sizeof(complex));
	for(short int i = 0; i < size_array; i++)
	{
		convert_array[i].real = 0.0;
		convert_array[i].imaginary = 0.0;
	}
	return convert_array;
}

