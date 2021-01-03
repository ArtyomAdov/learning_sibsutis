/* 
 * dgemm.c: DGEMM - Double-precision General Matrix Multiply.
 *
 */
 
#include <stdio.h>
#include <stdlib.h>

#include "hpctimer.h"

enum { 
    N = 512,
    NREPS = 3
};

double A[N * N], B[N * N], C[N * N];

void dgemm_def(double *a, double *b, double *c, int n)
{
    int i, j, k;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                *(c + i * n + j) += *(a + i * n + k) * *(b + k * n + j);
			}
		}
	}
}

void dgemm_transpose(double *a, double *b, double *c, int N)
{
    int n = N;
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            for (int j = 0; j < N; j++) {
                *(c + i * n + j) += *(a + i * n + k) * *(b + k * n + j);
            }
        }
    }
}

void dgemm_block(double *a, double *b, double *c, int n)
{
    /* TODO */
}

void init_matrix(double *a, double *b, double *c, int n)
{
	int i, j, k;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++) {
                *(a + i * n + j) = 1.0;
                *(b + i * n + j) = 2.0;
                *(c + i * n + j) = 0.0;
			}
		}
	}
}

void print_matrix(double *a, int n)
{
	int i, j;
	
	printf("Matrix:\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%12.2f", *(a + i * n + j));
		}
		printf("\n");
	}
}

int main(int argc, char **argv)
{
    int i;
    double t;
    		
    init_matrix(A, B, C, N);


    printf("dgemm_def\n");        
    t = hpctimer_getwtime();
    for (i = 0; i < NREPS; i++) {
        dgemm_def(A, B, C, N);
        // dgemm_transpose(A, B, C, N);
        //dgemm_transpose2(A, B, C, N);
        //dgemm_block(A, B, C, N);
    }
    t = hpctimer_getwtime() - t;
    t = t / NREPS;
    printf("Elapsed time: %.6f sec.\n", t);





    printf("dgemm_transpose\n");
    t = hpctimer_getwtime();
    for (i = 0; i < NREPS; i++) {
        // dgemm_def(A, B, C, N);
        dgemm_transpose(A, B, C, N);
        //dgemm_transpose2(A, B, C, N);
        //dgemm_block(A, B, C, N);
    }
    t = hpctimer_getwtime() - t;
    t = t / NREPS;
    printf("Elapsed time: %.6f sec.\n", t);




    
    /*print_matrix(C, N);*/
    
    
    return 0;
}

