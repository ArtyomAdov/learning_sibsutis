#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>

int SelectSortInt(int A[], int N){int i, j, min, r, temp;
    for (j=0;j<N-1;j++){
    r=j;
	for (i=j+1;i<N;i++){
		if (A[i]<A[j]) {
		r=i;
		}
	}
	if(r!=j){
	temp=A[j];
	A[j]=min;
	A[r]=temp;
	}
}
return 0;		
}