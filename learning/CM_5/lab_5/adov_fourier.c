#include "adov_complex.c"

#define NUMBER_PI 3.14159265
#define COEFFICIENT_DIRECT -2.0
#define COEFFICIENT_INVERSE 2.0

complex* Direct_Discrete_Conversion(complex* array, int size_array)
{
	complex* convert_array = NULL;
	complex temp = {0.0,0.0};
	complex number_i = {0.0,1.0};
	complex intermediate = {0.0,0.0};
	convert_array = Fill_Zero(convert_array, size_array);
	for(short int i = 0; i < size_array; i++)
	{
		for(short int j = 0; j < size_array; j++)
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
			intermediate = Convert_Real_In_Complex((double)size_array);
			temp = Division_Complex_Number(temp, intermediate);
			temp = Find_Exponent_For_Complex(temp);
			temp = Multiplication_Complex_Number(array[j],temp);
			convert_array[i] = Addition_Complex_Number(temp,convert_array[i]);
		}
		temp = Convert_Real_In_Complex((double)size_array);
		convert_array[i] = Division_Complex_Number(convert_array[i],temp);
	}
	return convert_array;
}

complex* Inverse_Discrete_Conversion(complex* array, int size_array)
{
	complex* convert_array = NULL;
	complex temp = {0.0,0.0};
	complex number_i = {0.0,1.0};
	complex intermediate = {0.0,0.0};
	convert_array = Fill_Zero(convert_array, size_array);
	for(short int i = 0; i < size_array; i++)
	{
		for(short int j = 0; j < size_array; j++)
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
			intermediate = Convert_Real_In_Complex((double)size_array);
			temp = Division_Complex_Number(temp, intermediate);
			temp = Find_Exponent_For_Complex(temp);
			temp = Multiplication_Complex_Number(array[j],temp);
			convert_array[i] = Addition_Complex_Number(temp,convert_array[i]);
		}
	}
	return convert_array;
}
