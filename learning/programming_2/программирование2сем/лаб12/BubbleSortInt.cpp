#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>

int BubbleSortInt(int A[], int N){
	int i, j, min, r, temp;
    for (j=0;j<N-1;j++){
	for (i=0;i<N-j-1;i++){
		if (A[i+1]<A[i]) {
		temp=A[i];
		A[i]=A[i+1];
		A[i+1]=temp;
		}
	}
}
return 0;		
}