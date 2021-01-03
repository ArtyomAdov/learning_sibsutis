#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define ERROR_OPEN_TABLE_FILE 0b00000001
#define ERROR_OPEN_TEMP_FILE 0b00000010

#define MAXIMUM_LENGTH_KEY_OPTIMIZATION_NAME 4
#define COEFFICIENT_FOR_RAND 10
#define COEFFICIENT_FOR_CONVERT_IN_PERCENT 100
#define QUANTITY_ITERATION_FOR_ONE_TEST 10000

#define FILE_NAME_TABLE_CVS "table.csv"
#define FILE_NAME_TEMP_KEY "temp_key.txt"
#define ADDITIONAL_RECORDING "a"
#define READ_ONLY "rt"

int Test_By_Sinus_Int()
{
	double result = 0.0;
	int test_value = 0;
	int time_before_work = 0;
	int time_work = 0;
	for(int i = 0; i < QUANTITY_ITERATION_FOR_ONE_TEST; i++)
	{
		test_value = rand()%COEFFICIENT_FOR_RAND;
		time_before_work = clock();
		result = sin(test_value);
		time_work = time_work + (clock() - time_before_work);
	}
	return time_work;
}

int Test_By_Sinus_Float()
{
	double result = 0.0;
	float test_value = 0;
	int time_before_work = 0;
	int time_work = 0;
	for(short int i = 0; i < QUANTITY_ITERATION_FOR_ONE_TEST; i++)
	{
		test_value = ((float)(rand()%COEFFICIENT_FOR_RAND) / (float)(rand()%COEFFICIENT_FOR_RAND));
		time_before_work = clock();
		result = sin(test_value);
		time_work = time_work + (clock() - time_before_work);
	}
	return time_work;
}

int Test_By_Sinus_Double()
{
	double result = 0.0;
	int test_value = 0;
	int time_before_work = 0;
	int time_work = 0;
	for(short int i = 0; i < QUANTITY_ITERATION_FOR_ONE_TEST; i++)
	{
		test_value = ((double)(rand()%COEFFICIENT_FOR_RAND) / (double)(rand()%COEFFICIENT_FOR_RAND));
		time_before_work = clock();
		result = sin(test_value);
		time_work = time_work + (clock() - time_before_work);
	}
	return time_work;
}

int Test_By_Cosinus_Int()
{
	double result = 0.0;
	int test_value = 0;
	int time_before_work = 0;
	int time_work = 0;
	for(short int i = 0; i < QUANTITY_ITERATION_FOR_ONE_TEST; i++)
	{
		test_value = rand()%COEFFICIENT_FOR_RAND;
		time_before_work = clock();
		result = cos(test_value);
		time_work = time_work + (clock() - time_before_work);
	}
	return time_work;
}

int Test_By_Cosinus_Float()
{
	double result = 0.0;
	float test_value = 0;
	int time_before_work = 0;
	int time_work = 0;
	for(short int i = 0; i < QUANTITY_ITERATION_FOR_ONE_TEST; i++)
	{
		test_value = ((float)(rand()%COEFFICIENT_FOR_RAND) / (float)(rand()%COEFFICIENT_FOR_RAND));
		time_before_work = clock();
		result = cos(test_value);
		time_work = time_work + (clock() - time_before_work);
	}
	return time_work;
}

int Test_By_Cosinus_Double()
{
	double result = 0.0;
	int test_value = 0;
	int time_before_work = 0;
	int time_work = 0;
	for(short int i = 0; i < QUANTITY_ITERATION_FOR_ONE_TEST; i++)
	{
		test_value = ((double)(rand()%COEFFICIENT_FOR_RAND) / (double)(rand()%COEFFICIENT_FOR_RAND));
		time_before_work = clock();
		result = cos(test_value);
		time_work = time_work + (clock() - time_before_work);
	}
	return time_work;
}

int Test_By_Tangens_Int()
{
	double result = 0.0;
	int test_value = 0;
	int time_before_work = 0;
	int time_work = 0;
	for(short int i = 0; i < QUANTITY_ITERATION_FOR_ONE_TEST; i++)
	{
		test_value = rand()%COEFFICIENT_FOR_RAND;
		time_before_work = clock();
		result = tan(test_value);
		time_work = time_work + (clock() - time_before_work);
	}
	return time_work;
}

int Test_By_Tangens_Float()
{
	double result = 0.0;
	float test_value = 0;
	int time_before_work = 0;
	int time_work = 0;
	for(short int i = 0; i < QUANTITY_ITERATION_FOR_ONE_TEST; i++)
	{
		test_value = ((float)(rand()%COEFFICIENT_FOR_RAND) / (float)(rand()%COEFFICIENT_FOR_RAND));
		time_before_work = clock();
		result = tan(test_value);
		time_work = time_work + (clock() - time_before_work);
	}
	return time_work;
}

int Test_By_Tangens_Double()
{
	double result = 0.0;
	int test_value = 0;
	int time_before_work = 0;
	int time_work = 0;
	for(short int i = 0; i < QUANTITY_ITERATION_FOR_ONE_TEST; i++)
	{
		test_value = ((double)(rand()%COEFFICIENT_FOR_RAND) / (double)(rand()%COEFFICIENT_FOR_RAND));
		time_before_work = clock();
		result = tan(test_value);
		time_work = time_work + (clock() - time_before_work);
	}
	return time_work;
}

double Calculate_Dispersion(double* array_time, int size_array)
{
    	double dispersion_value = 0.0, mean = 0.0;
	for(short int i = 0; i < size_array; i++)
	{
		mean += array_time[i];
	}
	mean /= size_array;
	for(short int i = 0; i < size_array; i++)
	{
       		dispersion_value = (dispersion_value + pow((array_time[i] - mean), 2));
	}
	dispersion_value = (dispersion_value / (size_array - 1));
	return dispersion_value;
}

void Print_Array(double* arr, int size_arr)
{
	for(short int i = 0; i < size_arr; i++)
	{
		printf("%f ",arr[i]);
	}
}

char* Get_Key_Optimization(char* key_optimization)
{
	FILE* file = NULL;
	key_optimization = (char*) calloc (MAXIMUM_LENGTH_KEY_OPTIMIZATION_NAME,sizeof(char));
	file = fopen(FILE_NAME_TEMP_KEY,READ_ONLY);
	if(file == NULL)
	{
		return NULL;
	}
	for(short int i = 0; ((i < 4) && (!feof(file))); i++)
	{
		key_optimization[i] = getc(file);
		if(key_optimization[i] == '\n')
		{
			key_optimization[i] = '\0';
			break;
		}
	}
	fclose(file);
	return key_optimization;
}

int main()
{
    FILE* file = NULL;
	double* array_time = NULL;
	char* key_optimization = NULL;
	char* system_command = NULL;
	double performance = 0.0;
	double time_before_test = 0.0;
	double average_time = 0.0;
    double accuracy = 0.0;
	double absolute_oversight = 0.0;
    double relativity_oversight = 0.0;
    int error_flag = 0b0;
	int quantity_test = 0;
	srand(time(NULL));
	printf("Please write need quantity tests\n");
	scanf("%d",&quantity_test);
	key_optimization = Get_Key_Optimization(key_optimization);
	if(key_optimization == NULL)
	{
		return ERROR_OPEN_TEMP_FILE;
	}
	file = fopen(FILE_NAME_TABLE_CVS,ADDITIONAL_RECORDING);
	if(file == NULL)
	{
		return ERROR_OPEN_TABLE_FILE;
	}
	array_time = (double*) calloc (quantity_test, sizeof(double));
	asprintf(&system_command,"lscpu | grep 'Имя' | awk '{for(i = 3; i <= NF; i++){printf $i; printf(\" \");}}' >> table.csv");
	//sin int
	for(short int i = 0; i < quantity_test; i++)
	{
		array_time[i] = Test_By_Sinus_Int(); 
		average_time = average_time + array_time[i];
	}
	average_time = (average_time / quantity_test);
	performance = (QUANTITY_ITERATION_FOR_ONE_TEST / (average_time / CLOCKS_PER_SEC));
	accuracy = Calculate_Dispersion(array_time, quantity_test);
	absolute_oversight = sqrt(accuracy);
	relativity_oversight = (absolute_oversight / average_time * COEFFICIENT_FOR_CONVERT_IN_PERCENT);
	fprintf(file,"| ");
	fflush(file);
	system(system_command);
	fprintf(file,"| sin | int | %s | %d | %d | clock() | %lf | %lf | %lf | %lf |\n", 
			key_optimization, quantity_test, (QUANTITY_ITERATION_FOR_ONE_TEST / quantity_test), 
			(average_time / CLOCKS_PER_SEC), (absolute_oversight / CLOCKS_PER_SEC), (relativity_oversight / CLOCKS_PER_SEC), performance);
	fflush(file);
	average_time = 0.0;
	performance = 0.0;
	//sin float
	for(short int i = 0; i < quantity_test; i++)
	{
		array_time[i] = Test_By_Sinus_Float(); 
		average_time = average_time + array_time[i];;
	}
	average_time = (average_time / quantity_test);
	performance = (QUANTITY_ITERATION_FOR_ONE_TEST / (average_time / CLOCKS_PER_SEC));
	accuracy = Calculate_Dispersion(array_time, quantity_test);
	absolute_oversight = sqrt(accuracy);
	relativity_oversight = (absolute_oversight / average_time * COEFFICIENT_FOR_CONVERT_IN_PERCENT);
	fprintf(file,"| ");
	fflush(file);
	system(system_command);
	fprintf(file,"| sin | float | %s | %d | %d | clock() | %lf | %lf | %lf | %lf |\n", 
			key_optimization, quantity_test, (QUANTITY_ITERATION_FOR_ONE_TEST / quantity_test), 
			(average_time / CLOCKS_PER_SEC), (absolute_oversight / CLOCKS_PER_SEC), (relativity_oversight / CLOCKS_PER_SEC), performance);
	fflush(file);
	average_time = 0.0;
	performance = 0.0;
	//sin double
	for(short int i = 0; i < quantity_test; i++)
	{
		array_time[i] = Test_By_Sinus_Double(); 
		average_time = average_time + array_time[i];
	}
	average_time = (average_time / quantity_test);
	performance = (QUANTITY_ITERATION_FOR_ONE_TEST / (average_time / CLOCKS_PER_SEC));
	accuracy = Calculate_Dispersion(array_time, quantity_test);
	absolute_oversight = sqrt(accuracy);
	relativity_oversight = (absolute_oversight / average_time * COEFFICIENT_FOR_CONVERT_IN_PERCENT);
	fprintf(file,"| ");
	fflush(file);
	system(system_command);
	fprintf(file,"| sin | double | %s | %d | %d | clock() | %lf | %lf | %lf | %lf |\n", 
			key_optimization, quantity_test, (QUANTITY_ITERATION_FOR_ONE_TEST / quantity_test), 
			(average_time / CLOCKS_PER_SEC), (absolute_oversight / CLOCKS_PER_SEC), (relativity_oversight / CLOCKS_PER_SEC), performance);
	fflush(file);
	average_time = 0.0;
	performance = 0.0;
	//cos int
	for(short int i = 0; i < quantity_test; i++)
	{
		array_time[i] = Test_By_Cosinus_Int(); 
		average_time = average_time + array_time[i];
	}
	average_time = (average_time / quantity_test);
	performance = (QUANTITY_ITERATION_FOR_ONE_TEST / (average_time / CLOCKS_PER_SEC));
	accuracy = Calculate_Dispersion(array_time, quantity_test);
	absolute_oversight = sqrt(accuracy);
	relativity_oversight = (absolute_oversight / average_time * COEFFICIENT_FOR_CONVERT_IN_PERCENT);
	fprintf(file,"| ");
	fflush(file);
	system(system_command);
	fprintf(file,"| cos | int | %s | %d | %d | clock() | %lf | %lf | %lf | %lf |\n", 
			key_optimization, quantity_test, (QUANTITY_ITERATION_FOR_ONE_TEST / quantity_test), 
			(average_time / CLOCKS_PER_SEC), (absolute_oversight / CLOCKS_PER_SEC), (relativity_oversight / CLOCKS_PER_SEC), performance);
	fflush(file);
	average_time = 0.0;
	performance = 0.0;
	//cos float
	for(short int i = 0; i < quantity_test; i++)
	{
		array_time[i] = Test_By_Cosinus_Float(); 
		average_time = average_time + array_time[i];
	}
	average_time = (average_time / quantity_test);
	performance = (QUANTITY_ITERATION_FOR_ONE_TEST / (average_time / CLOCKS_PER_SEC));
	accuracy = Calculate_Dispersion(array_time, quantity_test);
	absolute_oversight = sqrt(accuracy);
	relativity_oversight = (absolute_oversight / average_time * COEFFICIENT_FOR_CONVERT_IN_PERCENT);
	fprintf(file,"| ");
	fflush(file);
	system(system_command);
	fprintf(file,"| cos | float | %s | %d | %d | clock() | %lf | %lf | %lf | %lf |\n", 
			key_optimization, quantity_test, (QUANTITY_ITERATION_FOR_ONE_TEST / quantity_test), 
			(average_time / CLOCKS_PER_SEC), (absolute_oversight / CLOCKS_PER_SEC), (relativity_oversight / CLOCKS_PER_SEC), performance);
	fflush(file);
	average_time = 0.0;
	performance = 0.0;
	//cos double
	for(short int i = 0; i < quantity_test; i++)
	{
		array_time[i] = Test_By_Cosinus_Double(); 
		average_time = average_time + array_time[i];
	}
	average_time = (average_time / quantity_test);
	performance = (QUANTITY_ITERATION_FOR_ONE_TEST / (average_time / CLOCKS_PER_SEC));
	accuracy = Calculate_Dispersion(array_time, quantity_test);
	absolute_oversight = sqrt(accuracy);
	relativity_oversight = (absolute_oversight / average_time * COEFFICIENT_FOR_CONVERT_IN_PERCENT);
	fprintf(file,"| ");
	fflush(file);
	system(system_command);
	fprintf(file,"| cos | double | %s | %d | %d | clock() | %lf | %lf | %lf | %lf |\n", 
			key_optimization, quantity_test, (QUANTITY_ITERATION_FOR_ONE_TEST / quantity_test), 
			(average_time / CLOCKS_PER_SEC), (absolute_oversight / CLOCKS_PER_SEC), (relativity_oversight / CLOCKS_PER_SEC), performance);
	fflush(file);
	average_time = 0.0;
	performance = 0.0;
	//tan int
	for(short int i = 0; i < quantity_test; i++)
	{
		array_time[i] = Test_By_Tangens_Int(); 
		average_time = average_time + array_time[i];
	}
	average_time = (average_time / quantity_test);
	performance = (QUANTITY_ITERATION_FOR_ONE_TEST / (average_time / CLOCKS_PER_SEC));
	accuracy = Calculate_Dispersion(array_time, quantity_test);
	absolute_oversight = sqrt(accuracy);
	relativity_oversight = (absolute_oversight / average_time * COEFFICIENT_FOR_CONVERT_IN_PERCENT);
	fprintf(file,"| ");
	fflush(file);
	system(system_command);
	fprintf(file,"| tan | int | %s | %d | %d | clock() | %lf | %lf | %lf | %lf |\n", 
			key_optimization, quantity_test, (QUANTITY_ITERATION_FOR_ONE_TEST / quantity_test), 
			(average_time / CLOCKS_PER_SEC), (absolute_oversight / CLOCKS_PER_SEC), (relativity_oversight / CLOCKS_PER_SEC), performance);
	fflush(file);
	average_time = 0.0;
	performance = 0.0;
	//tan float
	for(short int i = 0; i < quantity_test; i++)
	{
		array_time[i] = Test_By_Tangens_Float(); 
		average_time = average_time + array_time[i];
	}
	average_time = (average_time / quantity_test);
	performance = (QUANTITY_ITERATION_FOR_ONE_TEST / (average_time / CLOCKS_PER_SEC));
	accuracy = Calculate_Dispersion(array_time, quantity_test);
	absolute_oversight = sqrt(accuracy);
	relativity_oversight = (absolute_oversight / average_time * COEFFICIENT_FOR_CONVERT_IN_PERCENT);
	fprintf(file,"| ");
	fflush(file);
	system(system_command);
	fprintf(file,"| tan | float | %s | %d | %d | clock() | %lf | %lf | %lf | %lf |\n", 
			key_optimization, quantity_test, (QUANTITY_ITERATION_FOR_ONE_TEST / quantity_test), 
			(average_time / CLOCKS_PER_SEC), (absolute_oversight / CLOCKS_PER_SEC), (relativity_oversight / CLOCKS_PER_SEC), performance);
	fflush(file);
	average_time = 0.0;
	performance = 0.0;
	//tan double
	for(short int i = 0; i < quantity_test; i++)
	{
		array_time[i] = Test_By_Tangens_Double(); 
		average_time = average_time + array_time[i];
	}
	average_time = (average_time / quantity_test);
	performance = (QUANTITY_ITERATION_FOR_ONE_TEST / (average_time / CLOCKS_PER_SEC));
	accuracy = Calculate_Dispersion(array_time, quantity_test);
	absolute_oversight = sqrt(accuracy);
	relativity_oversight = (absolute_oversight / average_time * COEFFICIENT_FOR_CONVERT_IN_PERCENT);
	fprintf(file,"| ");
	fflush(file);
	system(system_command);
	fprintf(file,"| tan | double | %s | %d | %d | clock() | %lf | %lf | %lf | %lf |\n", 
			key_optimization, quantity_test, (QUANTITY_ITERATION_FOR_ONE_TEST / quantity_test), 
			(average_time / CLOCKS_PER_SEC), (absolute_oversight / CLOCKS_PER_SEC), (relativity_oversight / CLOCKS_PER_SEC), performance);
	fflush(file);
	//
	fclose(file);
	free(array_time);
	array_time = NULL;
	return error_flag;
}
