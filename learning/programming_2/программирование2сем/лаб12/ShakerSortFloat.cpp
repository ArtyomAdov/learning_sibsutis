#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>

int ShakerSortFloat(float B[], int N){
	int i, j, L=0, R=N-1, k=N-1; 
	float temp;
	while(L<R){
	    for(j=R;j>=L+1;j--){
	    	if(B[j]<B[j-1]){
	    		temp=B[j];
	    		B[j]=B[j-1];
	    		B[j-1]=temp;
	    		k=j;
	    	}
	    	
	    }
	    L=k;
	    for(j=L;j<R;j++){
	    	if(B[j]>B[j+1]){
	    		temp=B[j];
	    		B[j]=B[j+1];
	    		B[j+1]=temp;
	    		k=j;
	    	}
	    	
	    }
	    R=k;
    }
    return 0;
}
