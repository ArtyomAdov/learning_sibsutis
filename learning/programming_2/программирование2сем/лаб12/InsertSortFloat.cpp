#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int InsertSortFloat(float B[], int N){
	int i, j, k; 
	float t;
	for(i=1;i<N;i++){
		t=B[i];
		j=i-1;
		while(j>=0 && t<B[j]){
			B[j+1]=B[j];
			j=j-1;
		}
		B[j+1]=t;
	}
	return 0;
}