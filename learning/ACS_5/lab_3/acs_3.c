#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ERROR_QUANTITY_ARGUMENT_IN_MAIN 0b00000001
#define ERROR_PARAMETR_MEMORY_TYPE 0b00000010
#define ERROR_PARAMETR_BLOCK_SIZE 0b00000100
#define ERROR_PARAMETR_QUANTITY_TEST 0b0001000
#define ERROR_ALLOCATION_MEMORY_TEST_ARRAY 0b00010000
#define ERROR_OPEN_FILE_TEST 0b00100000
#define ERROR_OPEN_FILE_CSV 0b01000000
#define ERROR_ALLOCATION_MEMORY_ARRAY_TIME 0b10000000

#define FIRST_CODE_SYMBOL_BY_DIGIT 0x30
#define LAST_CODE_SYMBOL_BY_DIGIT 0x39
#define CONVERT_CODE_SYMBOL_BY_DIGIT_IN_NUMBER 0x0F

#define CORRECT_QUANTITY_ARGUMENT_IN_MAIN 4
#define COEFFICIENT_CONVERT_IN_BYTE 1024
#define SIZE_TYPE_DOUBLE 8
#define COEFFICIENT_FOR_RAND 10
#define QUANTITY_OPERATION_OF_MEMORY 2
#define COEFFICIENT_FOR_CONVERT_IN_PERCENT 100

#define STEP_SIZE_MEMORY_BY_TEST 524288

#define INDEX_MEMORY_TYPE_FROM_ARGV 1
#define INDEX_BLOCK_SIZE_FROM_ARGV 2
#define INDEX_QUANTITY_TEST_FROM_ARGV 3

#define INDEX_WRITE_FOR_ARRAY_TIME 0
#define INDEX_READ_FOR_ARRAY_TIME 1

#define FILE_NAME_FOR_HDD "/home/deathangel/Desktop/test_file.txt"
#define FILE_NAME_FOR_SSD "/home/deathangel/Desktop/file_test.txt"
#define FILE_NAME_FOR_FLASH "/media/deathangel/ANNA/file_test.txt"
#define FILE_NAME_TABLE_CVS "table.csv"

#define WRITE_AND_READ "w+"
#define ADDITIONAL_RECORDING "a"
#define READ_ONLY "r"

#define WRITE "write"
#define READ "read"
#define NAME_TYPE_DOUBLE "double"
#define NAME_FUNCTION_CALL_FOR_TIME "clock()"

int Check_Argc(int argc)
{
    if(argc == CORRECT_QUANTITY_ARGUMENT_IN_MAIN)
    {
        return 0;
    }
    return ERROR_QUANTITY_ARGUMENT_IN_MAIN;
}

int Check_Memory_Type(char argv[])
{
    if((argv[0] == 'R') && (argv[1] == 'A') && (argv[2] == 'M') && (argv[3] == '\0'))
    {
        return 0;
    }
    if((argv[0] == 'H') && (argv[1] == 'D') && (argv[2] == 'D') && (argv[3] == '\0'))
    {
        return 0;
    }
    if((argv[0] == 'S') && (argv[1] == 'S') && (argv[2] == 'D') && (argv[3] == '\0'))
    {
        return 0;
    }
    if((argv[0] == 'f') && (argv[1] == 'l') && (argv[2] == 'a') && (argv[3] == 's') && (argv[4] == 'h') && (argv[5] == '\0'))
    {
        return 0;
    }
    return ERROR_PARAMETR_MEMORY_TYPE;
}

int Convert_Block_Size(unsigned long int* quantity_element_in_array, char argv[])
{
    for(short int i = 0; argv[i] != '\0'; i++)
    {
        if((argv[i] >= FIRST_CODE_SYMBOL_BY_DIGIT) && (argv[i] <= LAST_CODE_SYMBOL_BY_DIGIT))
        {
            (*quantity_element_in_array) = ((*quantity_element_in_array) + (int)(argv[i] & CONVERT_CODE_SYMBOL_BY_DIGIT_IN_NUMBER));
            (*quantity_element_in_array) = ((*quantity_element_in_array) * 10);
            if(argv[i+1] == '\0')
            {
                (*quantity_element_in_array) = (((*quantity_element_in_array) / 10) / SIZE_TYPE_DOUBLE);
            }
        }
        else
        {
            (*quantity_element_in_array) = ((*quantity_element_in_array) / 10);
            if((argv[i] == 'K') && (argv[i+1] == 'b') && (argv[i+2] == '\0'))
            {
                (*quantity_element_in_array) = ((*quantity_element_in_array) * (COEFFICIENT_CONVERT_IN_BYTE / SIZE_TYPE_DOUBLE));
                return 0;            
            }
            else
            {
                if((argv[i] == 'M') && (argv[i+1] == 'b') && (argv[i+2] == '\0'))
                {
                    (*quantity_element_in_array) = ((*quantity_element_in_array) * (COEFFICIENT_CONVERT_IN_BYTE / SIZE_TYPE_DOUBLE) * COEFFICIENT_CONVERT_IN_BYTE);
                    return 0;
                }
                else
                {
                    return ERROR_PARAMETR_BLOCK_SIZE;
                }
            }
        }
    }
    if((*quantity_element_in_array) > 0)
    {
        return 0;
    }
    return ERROR_PARAMETR_BLOCK_SIZE;
}

int Convert_Quantity_Test(int* quantity_test, char argv[])
{
    for(short int i = 0; argv[i] != '\0'; i++)
    {
        if((argv[i] >= FIRST_CODE_SYMBOL_BY_DIGIT) && (argv[i] <= LAST_CODE_SYMBOL_BY_DIGIT))
        {
            (*quantity_test) = ((*quantity_test) + (int)(argv[i] & CONVERT_CODE_SYMBOL_BY_DIGIT_IN_NUMBER));
            (*quantity_test) = ((*quantity_test) * 10);
        }
        else
        {
            return ERROR_PARAMETR_QUANTITY_TEST;
        } 
    }
    (*quantity_test) = ((*quantity_test) / 10);
    if((*quantity_test) > 0)
    {
        return 0;
    }
    return ERROR_PARAMETR_QUANTITY_TEST;
}

int Fill_Rand_Test_Array(double** test_array, int quantity_element_in_array)
{
    double temp = 0.0;
    (*test_array) = (double*)calloc(quantity_element_in_array, sizeof(double));
    if((*test_array) == NULL)
    {
        return ERROR_ALLOCATION_MEMORY_TEST_ARRAY;
    }
    for(unsigned long int i = 0; i < quantity_element_in_array; i++)
    {   
        temp = (double)(rand()%COEFFICIENT_FOR_RAND) + 0.5;
        (*test_array)[i] = ((double)(rand()%COEFFICIENT_FOR_RAND) / temp);
    }
    return 0;
}

int Write_In_Csv_File(char* argv[], double* array_time[], double absolute_oversight[], double relativity_oversight[], unsigned long int quantity_element_in_array, int number_test)
{
    FILE* file = NULL;
    double* average_time = NULL;
    average_time = (double*)calloc(QUANTITY_OPERATION_OF_MEMORY,sizeof(double));
    if(average_time == NULL)
    {
        return ERROR_ALLOCATION_MEMORY_ARRAY_TIME;
    }
    file = fopen(FILE_NAME_TABLE_CVS,ADDITIONAL_RECORDING);
    if(file == NULL)
    {
        return ERROR_OPEN_FILE_CSV;
    }
    for(short int i = 0; i < QUANTITY_OPERATION_OF_MEMORY; i++)
    {
        for(short int j = 0; j < number_test; j++)
        {
            average_time[i] = average_time[i] + array_time[i][j];
        }
        average_time[i] = (average_time[i] / number_test);
    }
    fprintf(file,"%s, %lu, %s, %lu, %d, %s, %f, %f, %Lf, %f, %f, %f, %f, %Lf, %f, %f\n", 
    argv[INDEX_MEMORY_TYPE_FROM_ARGV],
    (quantity_element_in_array * SIZE_TYPE_DOUBLE), 
    NAME_TYPE_DOUBLE, 
    quantity_element_in_array,
    number_test, 
    NAME_FUNCTION_CALL_FOR_TIME,
    array_time[INDEX_WRITE_FOR_ARRAY_TIME][number_test - 1],
    average_time[INDEX_WRITE_FOR_ARRAY_TIME],
    ((long double)(quantity_element_in_array * SIZE_TYPE_DOUBLE) / (long double)average_time[INDEX_WRITE_FOR_ARRAY_TIME]),
    absolute_oversight[INDEX_WRITE_FOR_ARRAY_TIME],
    relativity_oversight[INDEX_WRITE_FOR_ARRAY_TIME],
    array_time[INDEX_READ_FOR_ARRAY_TIME][number_test - 1],
    average_time[INDEX_READ_FOR_ARRAY_TIME],
    ((long double)(quantity_element_in_array * SIZE_TYPE_DOUBLE) / (long double)average_time[INDEX_READ_FOR_ARRAY_TIME]),
    absolute_oversight[INDEX_READ_FOR_ARRAY_TIME],
    relativity_oversight[INDEX_READ_FOR_ARRAY_TIME]);
    fclose(file);
    return 0;
}

int Find_Oversight(double* array_time[], double* absolute_oversight[], double* relativity_oversight[], int size_array)
{
    double dispersion_value = 0.0;
    double mean = 0.0;
    //write
    (*absolute_oversight) = (double*)calloc(QUANTITY_OPERATION_OF_MEMORY,sizeof(double));
    if(absolute_oversight == NULL)
    {
        return ERROR_ALLOCATION_MEMORY_ARRAY_TIME;
    }
    (*relativity_oversight) = (double*)calloc(QUANTITY_OPERATION_OF_MEMORY,sizeof(double));
    if(relativity_oversight == NULL)
    {
        return ERROR_ALLOCATION_MEMORY_ARRAY_TIME;
    }
    for(short int i = 0; i < size_array; i++)
	{
		mean = mean + array_time[INDEX_WRITE_FOR_ARRAY_TIME][i];
	}
	mean = (mean / (double)size_array);
	for(short int i = 0; i < size_array; i++)
	{
		dispersion_value = (dispersion_value + pow((array_time[INDEX_WRITE_FOR_ARRAY_TIME][i] - mean), 2));
	}
	dispersion_value = (dispersion_value / (double)size_array);
    (*absolute_oversight)[INDEX_WRITE_FOR_ARRAY_TIME] = sqrt(dispersion_value);
    (*relativity_oversight)[INDEX_WRITE_FOR_ARRAY_TIME] = ((*absolute_oversight)[INDEX_WRITE_FOR_ARRAY_TIME] / mean * COEFFICIENT_FOR_CONVERT_IN_PERCENT);
    //read
    dispersion_value = 0.0;
    mean = 0.0;
    for(short int i = 0; i < size_array; i++)
	{
		mean = mean + array_time[INDEX_READ_FOR_ARRAY_TIME][i];
	}
	mean = (mean / (double)size_array);
	for(short int i = 0; i < size_array; i++)
	{
		dispersion_value = (dispersion_value + pow((array_time[INDEX_READ_FOR_ARRAY_TIME][i] - mean), 2));
	}
	dispersion_value = (dispersion_value / (double)size_array);
    (*absolute_oversight)[INDEX_READ_FOR_ARRAY_TIME] = sqrt(dispersion_value);
    (*relativity_oversight)[INDEX_READ_FOR_ARRAY_TIME] = ((*absolute_oversight)[INDEX_READ_FOR_ARRAY_TIME] / mean * COEFFICIENT_FOR_CONVERT_IN_PERCENT);
    return 0;
}

int Benchmark_For_Memory(unsigned long int quantity_element_in_array, int quantity_test, char* argv[])
{
    double** array_time = NULL;
    double start_time = 0, final_time = 0;
    FILE* file = NULL;
    double* test_array = NULL;
    double* absolute_oversight = NULL;
    double* relativity_oversight = NULL;
    double value = 0.0;
    array_time = (double**)calloc(QUANTITY_OPERATION_OF_MEMORY,sizeof(double*));
    for(short int i = 0; i < QUANTITY_OPERATION_OF_MEMORY; i++)
    {
        array_time[i] = (double*)calloc(quantity_test,sizeof(double));
    }
    if(array_time == NULL)
    {
        return ERROR_ALLOCATION_MEMORY_ARRAY_TIME;
    }
    if(argv[INDEX_MEMORY_TYPE_FROM_ARGV][0] == 'R')
    {
        for(short int i = 0; i < quantity_test; i++)
        {
            //write
            if(Fill_Rand_Test_Array(&test_array, quantity_element_in_array) != 0)
            {
                return ERROR_ALLOCATION_MEMORY_TEST_ARRAY;
            }
            for(unsigned long int j = 0; j < quantity_element_in_array; j++)
            {
                start_time = clock();
                value = test_array[j];
                final_time = (clock() - start_time) / CLOCKS_PER_SEC;
                array_time[INDEX_WRITE_FOR_ARRAY_TIME][i] = (array_time[INDEX_WRITE_FOR_ARRAY_TIME][i] + final_time);
            }
            //read
            for(unsigned long int j = 0; j < quantity_element_in_array; j++)
            {
                value = ((double)(rand()%COEFFICIENT_FOR_RAND) / (double)(rand()%COEFFICIENT_FOR_RAND));
                start_time = clock();
                test_array[j] = value;
                final_time = (clock() - start_time) / CLOCKS_PER_SEC;
                array_time[INDEX_READ_FOR_ARRAY_TIME][i] = (array_time[INDEX_READ_FOR_ARRAY_TIME][i] + final_time);
            }
            Find_Oversight(array_time, &absolute_oversight, &relativity_oversight, i + 1);
            if(Write_In_Csv_File(argv, array_time, absolute_oversight, relativity_oversight, quantity_element_in_array, (i+1)) != 0)
            {
                return ERROR_OPEN_FILE_CSV;
            }
        }
        return 0;
    }
    if(argv[INDEX_MEMORY_TYPE_FROM_ARGV][0] == 'H')
    {
        file = fopen(FILE_NAME_FOR_HDD,WRITE_AND_READ);
    }
    if(argv[INDEX_MEMORY_TYPE_FROM_ARGV][0] == 'S')
    {
        file = fopen(FILE_NAME_FOR_SSD,WRITE_AND_READ);
    }
    if(argv[INDEX_MEMORY_TYPE_FROM_ARGV][0] == 'f')
    {   
        file = fopen(FILE_NAME_FOR_FLASH,WRITE_AND_READ);
    }
    if(file == NULL)
    {
        return ERROR_OPEN_FILE_TEST;
    }
    for(short int i = 0; i < quantity_test; i++)
    {
        if(Fill_Rand_Test_Array(&test_array, quantity_element_in_array) != 0)
        {
            return ERROR_ALLOCATION_MEMORY_TEST_ARRAY;
        }
        for(unsigned long int j = 0; j < quantity_element_in_array; j++)
        {
            start_time = clock();
            fprintf(file,"%lf",test_array[j]);
            final_time = (clock() - start_time) / CLOCKS_PER_SEC;
            array_time[INDEX_WRITE_FOR_ARRAY_TIME][i] = (array_time[INDEX_WRITE_FOR_ARRAY_TIME][i] + final_time);
        }
        //read
        for(unsigned long int j = 0; j < quantity_element_in_array; j++)
        {
            value = ((double)(rand()%COEFFICIENT_FOR_RAND) / (double)(rand()%COEFFICIENT_FOR_RAND));
            start_time = clock();
            fscanf(file,"%lf",&test_array[j]);
            final_time = (clock() - start_time) / CLOCKS_PER_SEC;
            array_time[INDEX_READ_FOR_ARRAY_TIME][i] = (array_time[INDEX_READ_FOR_ARRAY_TIME][i] + final_time);
        }
        Find_Oversight(array_time, &absolute_oversight, &relativity_oversight, i + 1);
        if(Write_In_Csv_File(argv, array_time, absolute_oversight, relativity_oversight, quantity_element_in_array, (i+1)) != 0)
        {
            return ERROR_OPEN_FILE_CSV;
        }
        quantity_element_in_array = quantity_element_in_array + STEP_SIZE_MEMORY_BY_TEST;//
    }
    fclose(file);
    return 0;
}

int Create_Table_Csv()
{
    FILE* file = NULL;
    file = fopen(FILE_NAME_TABLE_CVS,READ_ONLY);
    {
        if(file != NULL)
        {
            fclose(file);
            file = NULL;
            return 0;
        }
    }
    file = fopen(FILE_NAME_TABLE_CVS,WRITE_AND_READ);
    if(file == NULL)
    {
        return ERROR_OPEN_FILE_CSV;
    }
    fprintf(file, "MemoryType, BlockSize, ElementType, BufferSize, LaunchNum, Timer, WriteTime, AverageWriteTime, WriteBandwidth, AbsError(write), RelError(write), ReadTime, AverageReadTime, ReadBandwidth, AbsError(read), RelError(read)\n");
    fclose(file);
    return 0;
}

int main(int argc, char* argv[])
{
    printf("%d",argc);
    int error_flag = 0b0;
    unsigned long int quantity_element_in_array = 0;
    int quantity_test = 0;
    srand(time(NULL));    
    error_flag = (error_flag | Check_Argc(argc));
    // printf("ERR:%d\n",error_flag);
    error_flag = (error_flag | Create_Table_Csv());
    error_flag = (error_flag | Check_Memory_Type(argv[INDEX_MEMORY_TYPE_FROM_ARGV]));
    // printf("ERR:%d\n",error_flag);
    error_flag = (error_flag | Convert_Block_Size(&quantity_element_in_array, argv[INDEX_BLOCK_SIZE_FROM_ARGV]));
    // printf("ERR:%d\n",error_flag);
    error_flag = (error_flag | Convert_Quantity_Test(&quantity_test, argv[INDEX_QUANTITY_TEST_FROM_ARGV]));
    // printf("ERR:%d\n",error_flag);
    error_flag = (error_flag | Benchmark_For_Memory(quantity_element_in_array, quantity_test, argv));
    printf("ERR:%d\n",error_flag);
    return error_flag;
}
