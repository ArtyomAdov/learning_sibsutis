#include <stdio.h>
#include <math.h>
#include "Gauss_method.h"

int main()
{
	int n = 4;
	float mult;
	float arr[][5] = {
		{1, 2,  3,  8, 4},
		{2, 6,  7,  8, 8},
		{3, 15, 11, 8, 12},
		{5, 11, 6, 100, 12}
	};
	/*{-1, -1, 1, -1},
	{2, -1, 2, 3},
	{3, -1, 1, 3}};*/
	float arr_arg[n];

	for (int i = 0; i < n; i++) {
		arr_arg[i] = 0;
	}

	for (int j = 0; j < n - 1; j++) {

		int num_ind = Matrix_max_first_elem(arr, j, n);
		Matrix_swap_line(arr, j, num_ind, n);

		for (int i = j + 1; i < n; i++) {
			if (arr[j][j] != 0) {
				mult = -(arr[i][j] / arr[j][j]);
			} else {
				break;
			}

			for (int k = j; k < n + 1; k++) {
				arr[i][k] += mult * arr [j][k];
			}
		}
	}

	printf("End\n");
	Matrix_Print(arr, n);
	printf("\n");

	Matrix_answer(arr_arg, arr, n);

	Matrix_print_answer(arr_arg, n);

	return 0;
}