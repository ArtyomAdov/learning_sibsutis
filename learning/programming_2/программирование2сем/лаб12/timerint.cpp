#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include "SelectSortInt.cpp"
#include "BubbleSortInt.cpp"
#include "ShakerSortInt.cpp"
#include "InsertSortInt.cpp"

void timerint(int (*f)(int A[], int N), int A[], int N)
{
	clock_t time;
	time = clock();
	f(A,N);
	time = clock() - time;
	time= time*1000;
	printf("%f msec\n", (double)time/CLOCKS_PER_SEC);
}
