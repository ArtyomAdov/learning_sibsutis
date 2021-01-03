#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>

int SelectSortFloat(float B[], int N){int i, j, r; 
	float temp, min;
    for (j=0;j<N-1;j++){
    r=j;
	for (i=j+1;i<N;i++){
		if (B[i]<B[j]) {
		r=i;
		}
	}
	if(r!=j){
	temp=B[j];
	B[j]=min;
	B[r]=temp;
	}
}
return 0;		
}