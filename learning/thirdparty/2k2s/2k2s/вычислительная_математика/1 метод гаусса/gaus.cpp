#pragma once /* Защита от двойного подключения заголовочного файла */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>


#include "gaus.h"

	void OTLADKA_print_matrix_after_find_answer__main (std::vector<std::vector<double>>* array_matrix2dVectorDouble);

std::vector<double>* matrix__anwer (std::vector<std::vector<double>>* inputPtrVectorDouble)
{
	//DANGER изменяет оригинал
	/*НЕТУ ПРОВЕРКИ ДЕЛЕНИЯ НА 0*/






	if (!validation___matrix__anwer (inputPtrVectorDouble))
		return NULL;




	//РЕШЕНИЕ МАТРИЦЫ
	std::vector<double>* resVectorInt = NULL;
	try
	{
		bringing_to_the_triangle___matrix__anwer(inputPtrVectorDouble); //приведение к треугольнику
		resVectorInt = the_solution_of_the_triangle(inputPtrVectorDouble); //решение треугольника
	}
	catch (std::bad_alloc)
	{
		std::cout << "throw -> matrix__anwer - bad_alloc" << std::endl;
	}
	catch (std::string info)
	{
		std::cout << "throw -> matrix__anwer - " << info << std::endl;
	}
	catch (...)
	{
		std::cout << "bout_suka";
		//experiment
	}






	return resVectorInt;
}
	int validation___matrix__anwer (std::vector<std::vector<double>>* inputPtrVectorDouble)
	{
		if (inputPtrVectorDouble == NULL)
		{
			std::cout << ("pointer (ptr) is NULL") << std::endl;
			return 0;
		}



		int size_first_item = inputPtrVectorDouble->at(0).size();
		for (auto&& list_numberVectorInt :  *(inputPtrVectorDouble))
		{
			if (size_first_item != list_numberVectorInt.size())
			{
				std::cout << ("neodnorodnaia size matrix") << std::endl;
				return 0;
			}
		}


		int width_of_matrix = (size_first_item - 1);
		int height_of_matrix = inputPtrVectorDouble->size();
		int kvadratnost_of_matrix = width_of_matrix == height_of_matrix;
		if (!kvadratnost_of_matrix)
		{
			std::cout << ("matrix variation is no kvadrato") << std::endl;
			return 0;
		}



		return 1;
	}
	void bringing_to_the_triangle___matrix__anwer (std::vector<std::vector<double>>* inputPtrVectorDouble)
	{
		for (int num_row_zanulenie_and_line_deformador = 0;
			 num_row_zanulenie_and_line_deformador < inputPtrVectorDouble->size() - 1;
			 ++num_row_zanulenie_and_line_deformador
			)
		{ //зануление столбика n
			double number_deformator = inputPtrVectorDouble->at(num_row_zanulenie_and_line_deformador).at(num_row_zanulenie_and_line_deformador);


			std::cout << "before_deforamation================================  num_row_zanulenie_and_line_deformador " << num_row_zanulenie_and_line_deformador << std::endl;
			OTLADKA_print_matrix_after_find_answer__main(inputPtrVectorDouble);

			sorting_cols___bringing_to_the_triangle___matrix__anwer(inputPtrVectorDouble,
																	num_row_zanulenie_and_line_deformador);	//сортировка line

			std::cout << "after_deforamation================================  num_row_zanulenie_and_line_deformador " << num_row_zanulenie_and_line_deformador << std::endl;
			OTLADKA_print_matrix_after_find_answer__main(inputPtrVectorDouble);


			for (int num_line_obj = num_row_zanulenie_and_line_deformador + 1;
				 num_line_obj < inputPtrVectorDouble->size();
				 ++num_line_obj
				)
			{ //обработка нижестоящих строк от строки-деформатора, зануление там элемента столбика и деформация остального
				std::vector<double>* line_objectPtrVectorDouble = &inputPtrVectorDouble->at(num_line_obj);
				double* number_of_row_zanulenie_in_line_obj = &line_objectPtrVectorDouble->at(num_row_zanulenie_and_line_deformador);




				double k_deformator = *number_of_row_zanulenie_in_line_obj/(-number_deformator);




				// *number_of_row_zanulenie_in_line_obj += number_deformator * k_deformator; //L здесь можно просто 0 записать, но это для проверки
				*number_of_row_zanulenie_in_line_obj = 0;




				deformirovanie_line___bringing_to_the_triangle___matrix__anwer(inputPtrVectorDouble,
																				line_objectPtrVectorDouble,
																				num_row_zanulenie_and_line_deformador,
																				k_deformator,
																				number_deformator);


				if (!test_zero_line___bringing_to_the_triangle___matrix__anwer(line_objectPtrVectorDouble))
				{
					std::string error_text = "zero_line_in_matrix";
					throw error_text;
				}
			}



			std::cout << "end_deforamation================================  num_row_zanulenie_and_line_deformador " << num_row_zanulenie_and_line_deformador << std::endl;
			OTLADKA_print_matrix_after_find_answer__main(inputPtrVectorDouble);
		}
	}
		void sorting_cols___bringing_to_the_triangle___matrix__anwer (std::vector<std::vector<double>>* inputPtrVectorDouble,
																	  int num_row_zanulenie_and_line_deformador)
		{
			std::vector<std::vector<double>> :: iterator iter__inputPtrVectorDouble;
			std::map<double, std::vector<double>> double_vectorMap;




			for (int i = num_row_zanulenie_and_line_deformador; i < inputPtrVectorDouble->size(); ++i)
			{ //сортируем в мапу
				iter__inputPtrVectorDouble = inputPtrVectorDouble->begin() + i;


				double number_for_zanulenieDouble = iter__inputPtrVectorDouble->at(num_row_zanulenie_and_line_deformador); 
				number_for_zanulenieDouble = abs(number_for_zanulenieDouble);
				double_vectorMap.emplace( number_for_zanulenieDouble, inputPtrVectorDouble->at(i) );
			}








			int i = inputPtrVectorDouble->size() - 1;


			for (auto iter_double_vectorMap = double_vectorMap.begin(); iter_double_vectorMap != double_vectorMap.end(); ++iter_double_vectorMap)
			{ //записываем обратно, но по порядку
				inputPtrVectorDouble->erase(inputPtrVectorDouble->begin() + i);
				inputPtrVectorDouble->insert(inputPtrVectorDouble->begin() + i, (*iter_double_vectorMap).second);
std::cout << "***********" << (*iter_double_vectorMap).first << " ------ " << (*iter_double_vectorMap).second.at(0) << std::endl;

				--i;
				if (i < num_row_zanulenie_and_line_deformador)
					break;
			}

		}
		void deformirovanie_line___bringing_to_the_triangle___matrix__anwer (std::vector<std::vector<double>>* inputPtrVectorDouble,
																			 std::vector<double>* line_objectPtrVectorDouble,
																			 int num_row_zanulenie_and_line_deformador,
																			 double k_deformator,
																			 double number_deformator
																			)
		{
			std::vector<double> :: iterator iterator_line_obj;


			int width_of_matrix = line_objectPtrVectorDouble->size();
			for (int num_double_obj = num_row_zanulenie_and_line_deformador + 1;
				 num_double_obj < width_of_matrix;
				 ++num_double_obj
				)
			{ //деформирование строки
				double subject_deformator = inputPtrVectorDouble->at(num_row_zanulenie_and_line_deformador).at(num_double_obj);
				iterator_line_obj = line_objectPtrVectorDouble->begin() + num_double_obj;
				*iterator_line_obj += subject_deformator * k_deformator;
			}
		}
		int test_zero_line___bringing_to_the_triangle___matrix__anwer (std::vector<double>* line_objectPtrVectorDouble)
		{
			int sum_test = 0;
			for (auto&& item_last_deformating_line :  *(line_objectPtrVectorDouble))
			{
				if (abs(item_last_deformating_line) > 0.000001)
					sum_test += 1;
			}

			return sum_test;
		}
	std::vector<double>* the_solution_of_the_triangle (std::vector<std::vector<double>>* inputPtrVectorDouble)
	{
		std::vector<double>* resVectorInt = new std::vector<double>;
		
		for (int number_variable = inputPtrVectorDouble->size() - 1;
			 number_variable >= 0;
			 --number_variable
			)
		{
			std::vector<double>* line_objectPtrVectorDouble = &(inputPtrVectorDouble->at(number_variable));
			double k_find_variable = line_objectPtrVectorDouble->at(number_variable);
			double b_after_znaka_ravno = line_objectPtrVectorDouble->at(line_objectPtrVectorDouble->size() - 1);



			b_after_znaka_ravno -= substituting_leading_variables(resVectorInt, line_objectPtrVectorDouble);



			double find_variable = b_after_znaka_ravno / k_find_variable;
			resVectorInt->push_back(find_variable);
		}
		//в последней строке находим последнюю переменную
		//поднимаемся выше и подставляя известные переменные узнаю текущую


		return resVectorInt;
	}
		double substituting_leading_variables (std::vector<double>* resVectorInt, std::vector<double>* line_objectPtrVectorDouble)
		{
			double res_sum = 0;

			int width_variables_of_matrix = line_objectPtrVectorDouble->size() - 2; //позиция и обычные числа после знака равно
			int i = 0;
			for (auto&& before_answer :  *(resVectorInt))
			{
				res_sum += line_objectPtrVectorDouble->at(width_variables_of_matrix - i) * before_answer;
				i++;
			}


			return res_sum;
		}