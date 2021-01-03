#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include "SelectSortFloat.cpp"
#include "BubbleSortFloat.cpp"
#include "ShakerSortFloat.cpp"
#include "InsertSortFloat.cpp"

void timerfloat(int (*f)(float B[], int N), float B[], int N){
	clock_t time;
	time = clock();
	f(B,N);
	time = clock() - time;
	time= time*1000;
	printf("%f msec\n", (double)time/CLOCKS_PER_SEC);
}
