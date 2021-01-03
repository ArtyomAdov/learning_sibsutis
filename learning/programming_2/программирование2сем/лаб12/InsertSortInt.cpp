#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int InsertSortInt(int A[], int N){
	int i, j, k, t;
	for(i=1;i<N;i++){
		t=A[i];
		j=i-1;
		while(j>=0 && t<A[j]){
			A[j+1]=A[j];
			j=j-1;
		}
		A[j+1]=t;
	}
	return 0;
}
