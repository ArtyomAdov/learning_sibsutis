/*
 * loop.c:
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hpctimer.h"

enum { n = 64 * 1024 * 1024 };

int main()
{
    int *v, i, sum;
	int t1 = 0, t2 = 0;
	int t3 = 0, t4 = 0;
	int t5 = 0, t6 = 0, t7 = 0, t8 = 0;
	int t9 = 0, t10 = 0, t11 = 0, t12 = 0, t13 = 0, t14 = 0, t15 = 0, t16 = 0;
    double t;
    
    if ( (v = malloc(sizeof(*v) * n)) == NULL) {
        fprintf(stderr, "No enough memory\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++)
        v[i] = 1;
   
    t = hpctimer_wtime();
    /* TODO: Unroll this loop */
    for (sum = 0, i = 0; i < n; i += 16) {
		//sum += v[i];
		
  		t1 += v[i];
		t2 += v[i + 1];
		
		t3 += v[i + 2];
		t4 += v[i + 3];
		
		t5 += v[i + 4];
		t6 += v[i + 5];
		t7 += v[i + 6];
		t8 += v[i + 7];
		
		t9 += v[i + 8];
		t10 += v[i + 9];
		t11 += v[i + 10];
		t12 += v[i + 11];
		t13 += v[i + 12];
		t14 += v[i + 13];
		t15 += v[i + 14];
		t16 += v[i + 15];
		
    }
	sum = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + t9 + t10 + t11 + t12 + t13 + t14 + t15 + t16;
    t = hpctimer_wtime() - t;

    printf("Sum = %d\n", sum);
    printf("Elapsed time (sec.): %.6f\n", t);

    free(v);
    return 0;
}
