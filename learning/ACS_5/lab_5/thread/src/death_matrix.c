#include "death_error.h"
#include "death_matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Print_Square_Matrix(double matrix[], int length)
{
    for(short int i = 0, l = (i * length); i < length; i++, l = (i * length))
    {
        for(short int j = 0; j < length; j++)
        {
            printf("%10.4lf",matrix[l+j]);
        }
        printf("\n\n");
    }
}

int Fill_Rand_Square_Matrix(double* matrix[], int length)
{
    *matrix = (double*)calloc((length*length),sizeof(double));
    if(*matrix == NULL)
    {
        return ERROR_ALLOCATION_MEMORY;
    }
    for(short int i = 0; i < length; i++)
    {
        for(short int j = 0; j < length; j++)
        (*matrix)[i*length+j] = (((double)(rand()%10))/1.5);
    }
    return 0;
}