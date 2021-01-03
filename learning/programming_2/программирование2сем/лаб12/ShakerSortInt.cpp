#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>

int ShakerSortInt(int A[], int N){
	int i, j, L=0, R=N-1, k=N-1, temp;
	while(L<R){
	    for(j=R;j>=L+1;j--){
	    	if(A[j]<A[j-1]){
	    		temp=A[j];
	    		A[j]=A[j-1];
	    		A[j-1]=temp;
	    		k=j;
	    	}
	    	
	    }
	    L=k;
	    for(j=L;j<R;j++){
	    	if(A[j]>A[j+1]){
	    		temp=A[j];
	    		A[j]=A[j+1];
	    		A[j+1]=temp;
	    		k=j;
	    	}
	    	
	    }
	    R=k;
    }
    return 0;
}
