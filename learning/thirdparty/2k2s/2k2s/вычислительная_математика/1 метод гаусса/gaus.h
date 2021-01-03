#pragma once /* Защита от двойного подключения заголовочного файла */









std::vector<double>* matrix__anwer (std::vector<std::vector<double>>* inputVectorInt);
	int validation___matrix__anwer (std::vector<std::vector<double>>* inputVectorInt);
	void bringing_to_the_triangle___matrix__anwer (std::vector<std::vector<double>>* inputVectorInt);
		void sorting_cols___bringing_to_the_triangle___matrix__anwer (std::vector<std::vector<double>>* inputPtrVectorDouble,
																  int num_row_zanulenie_and_line_deformador);
		void deformirovanie_line___bringing_to_the_triangle___matrix__anwer (std::vector<std::vector<double>>* inputPtrVectorDouble,
																			 std::vector<double>* line_objectPtrVectorDouble,
																			 int num_row_zanulenie_and_line_deformador,
																			 double k_deformator,
																			 double number_deformator
																			);
		int test_zero_line___bringing_to_the_triangle___matrix__anwer (std::vector<double>* line_objectPtrVectorDouble);
	std::vector<double>* the_solution_of_the_triangle (std::vector<std::vector<double>>* inputPtrVectorDouble);
		double substituting_leading_variables (std::vector<double>* resVectorInt, std::vector<double>* line_objectPtrVectorDouble);