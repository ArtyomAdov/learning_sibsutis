#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>

int BubbleSortFloat(float B[], int N){
	int i, j, min, r; 
	float temp;
    for (j=0;j<N-1;j++){
	for (i=0;i<N-j-1;i++){
		if (B[i+1]<B[i]) {
		temp=B[i];
		B[i]=B[i+1];
		B[i+1]=temp;
		}
	}
}
return 0;		
}