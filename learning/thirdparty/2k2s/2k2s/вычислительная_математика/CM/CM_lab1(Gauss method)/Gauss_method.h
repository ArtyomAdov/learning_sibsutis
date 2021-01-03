#ifndef GAUSS_METHOD_H
#define GAUSS_METHOD_H

void Matrix_Print(float *a, int n);
int Matrix_max_first_elem(float *a, int j, int n);
void Matrix_swap_line(float *a, int j, int k, int n);
void Matrix_answer(float *arr_arg, float *arr, int n);
void Matrix_print_answer(float *arr_arg, int n);

#endif