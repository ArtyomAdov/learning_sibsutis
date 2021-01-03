#include <iostream>
#include <string>
#include "gaus.cpp"

#define WIDTH_MATRIX 5
#define HEIGHT_MATRIX 4

	void filling_the_vector___main (double* array_matrixDouble);
	void print_answer_matrix___main (std::vector<double>* answer_matrix);
	std::vector<std::vector<double>>* translate_array_double_in_vector___main (double* array_matrixDouble);
	void OTLADKA_print_matrix_after_find_answer__main (std::vector<std::vector<double>>* array_matrix2dVectorDouble);


double random_double(double min, double max)
{
	return (double)(rand())/RAND_MAX*(max - min) + min;
}


int main ()
{
	/*
	ПРОБЛЕММА ПЕРЕПОЛНЕНИЯ ТИПА ЧИСЛА!!!!
	*/


	double array_matrixDouble[WIDTH_MATRIX* HEIGHT_MATRIX] = {
		8,	1,	3,	17, 28,
		6,	4,	26,	22,	12,
		13,	10, 17, 28,	7,
		26,	9,	24,	23, 20
	};
	filling_the_vector___main(array_matrixDouble);
	std::vector<std::vector<double>>* array_matrix2dVectorDouble = translate_array_double_in_vector___main(array_matrixDouble);





	OTLADKA_print_matrix_after_find_answer__main(array_matrix2dVectorDouble);

	std::vector<double>* answer_of_matrix = matrix__anwer(array_matrix2dVectorDouble);
	std::cout << "NEW___________________________________" << std::endl;
	OTLADKA_print_matrix_after_find_answer__main(array_matrix2dVectorDouble);
	std::cout << std::endl;
	std::cout << std::endl;
	print_answer_matrix___main(answer_of_matrix);
	delete answer_of_matrix;







	delete array_matrix2dVectorDouble;










	return 0;
}
	void filling_the_vector___main (double* array_matrixDouble)
	{
/*		for (int i = 0; i < HEIGHT_MATRIX; ++i)
		{
			for (int j = 0; j < WIDTH_MATRIX; ++j)
			{
				array_matrixDouble[i * WIDTH_MATRIX + j] = random_double(0, 400);
			}
		}*/
	}
	std::vector<std::vector<double>>* translate_array_double_in_vector___main (double* array_matrixDouble)
	{
		std::vector<std::vector<double>>* res_translate_vector = new std::vector<std::vector<double>>;


		for (int i = 0; i < HEIGHT_MATRIX; ++i)
		{
			std::vector<double> temp_lineVectorDouble;
			for (int j = 0; j < WIDTH_MATRIX; ++j)
			{
				temp_lineVectorDouble.push_back(array_matrixDouble[i * WIDTH_MATRIX + j]);
			}
			res_translate_vector->push_back(temp_lineVectorDouble);
		}

		return res_translate_vector;
	}
	void OTLADKA_print_matrix_after_find_answer__main (std::vector<std::vector<double>>* array_matrix2dVectorDouble)
	{
		std::cout.precision(3);




		for (auto&& line_double_number :  *(array_matrix2dVectorDouble))
		{
			for (auto&& double_number : line_double_number)
			{
				std::cout << double_number << "\t";
			}
			std::cout << std::endl;
		}
	}
	void print_answer_matrix___main (std::vector<double>* answer_matrix)
	{
		if (answer_matrix == NULL)
			return ;


		std::cout << "ANSWER OF MATRIX" << std::endl;
		for (auto&& number_of_otvet :  *(answer_matrix))
		{
			std::cout << number_of_otvet << " ";
		}
	}