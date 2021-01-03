#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "hpctimer.h"




void matrix_vector_reshenie(double *a, double *b, double *c, int m, int n);
void matrix_vector_prodreshenie_omp(double *a, double *b, double *c, int m, int n, int test_count_thread_stream);
double serial(int m, int n);
double parallel(int m, int n, int test_count_thread_stream);
    void inicilisation___serial (double *a, double *b, double *c, int m, int n);







enum { 
    N = 15000
};







int main(int argc, char **argv)
{
    int border = 25000;
    int step = 5000;

    for (int j = N; j <= border ; j += step)
    {
		printf("%d\n", j);
		double t1 = serial(j, j);
		printf("Time serial = %.6f\n", t1);



		for (int i = 2; i <= 8; i += 2)
        {

		    double t2 = parallel(j, j, i);
            printf("Time parallel%d = %.6f\t", i, t2);

            printf("Speedup = %.6lf\n", t1 / t2);
	    }
		printf("\n");
    }

    return 0;
}

double serial(int m, int n)
{
    double *a, *b, *c;

    a = malloc(sizeof(*a) * m * n);
    b = malloc(sizeof(*b) * n);
    c = malloc(sizeof(*c) * m);

    inicilisation___serial(a, b, c, m, n);

    double t = hpctimer_getwtime();
    matrix_vector_reshenie(a, b, c, m, n);
    t = hpctimer_getwtime() - t;

    free(a);
    free(b);
    free(c);

    return t;
}
    void inicilisation___serial (double *a, double *b, double *c, int m, int n)
    {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                a[i * n + j] = i + j;
            }
            c[i] = 0.0;
        }

        for (int j = 0; j < n; j++) {
            b[j] = j;
        } 
    }
    void matrix_vector_reshenie(double *a, double *b, double *c, int m, int n)
    {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                c[i] += a[i * n + j] * b[j];
            }
        }
    }
double parallel(int m, int n, int test_count_thread_stream)
{
    double *a, *b, *c;

    a = malloc(sizeof(*a) * m * n);
    b = malloc(sizeof(*b) * n);
    c = malloc(sizeof(*c) * m);

    #pragma omp parallel num_threads(test_count_thread_stream)
    {
        int count_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        int count_strings_for_thread = m / count_threads;
        int start_branch = thread_id * count_strings_for_thread;
        int end_branch = (thread_id == count_threads - 1) ? (m - 1) : (start_branch + count_strings_for_thread - 1);

        for (int i = start_branch; i <= end_branch; i++) {
            for (int j = 0; j < n; j++)
                a[i * n + j] = i + j;
            c[i] = 0.0;
        }
    }

    for (int j = 0; j < n; j++) {
        b[j] = j;
    }

    double t = hpctimer_getwtime();
    matrix_vector_prodreshenie_omp(a, b, c, m, n, test_count_thread_stream);
    t = hpctimer_getwtime() - t;

    free(a);
    free(b);
    free(c);

    return t;
}
    void matrix_vector_prodreshenie_omp(double *a, double *b, double *c, int m, int n, int test_count_thread_stream)
    {
        #pragma omp parallel num_threads(test_count_thread_stream)
        {
            int count_threads = omp_get_num_threads();
            int thread_id = omp_get_thread_num();
            int count_strings_for_thread = m / count_threads;
            int start_branch = thread_id * count_strings_for_thread;
            int end_branch = (thread_id == count_threads - 1) ? (m - 1) : (start_branch + count_strings_for_thread - 1);

            for (int i = start_branch; i < end_branch; i++) {
                c[i] = 0.0;
                for (int j = 0; j < n; j++) {
                    c[i] = c[i] + a[i * n + j] * b[j];
                }
            }
        }
    }