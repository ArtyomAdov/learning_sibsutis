#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>



double Runge(int stream);
	double func_zadanie1(double x);
double MonteCarlo(int n, int stream);
	double getrand(unsigned int *seed);
	double func_zadanie2(double x, double y);




int main(int argc, char **argv);
{
	#if 1
	double t1 = Runge(1);
	printf("T1 = %.6f\n", t1);

	for (int i = 2; i <= 8; i += 2) {
		double t2 = Runge(i);
		printf("Time%d = %.6f\t", i, t2);
		printf("Speedup = %.6f\n", t1 / t2);
	}
	#endif
/*

	int n = 10000000;

	for (int i = 0; i < 2; i++, n *= 10) {
		printf("n = %d\n", n);

		double t1 = MonteCarlo(n, 1);
		printf("T1 = %.6f\n", t1);

		for (int i = 2; i <= 8; i += 2) {
			double t2 = MonteCarlo(n, i);
			printf("Time%d = %.6f\t", i, t2);
			printf("Speedup = %.6f\n", t1 / t2);
		}
	}*/


	return 0;
}


double Runge(int stream)
{
	double t = omp_get_wtime();

	const double eps = 1E-5;
	const double a = -1;
	const double b = 1;
	const int n0 = 100000000;

	double sq[2];
	#pragma omp parallel num_threads(stream)
	{
		int n = n0, k;
		double delta = 1;
		for (k = 0; delta > eps; n *= 2, k ^= 1) {
			double h = (b - a) / n;
			double s = 0.0;
			sq[k] = 0;

			#pragma omp barrier

			#pragma omp for nowait
			for (int i = 0; i < n; i++)
				s += func_zadanie1(a + h * (i + 0.5));

			#pragma omp atomic
			sq[k] += s * h;

			#pragma omp barrier
			if (n > n0)
				delta = fabs(sq[k] - sq[k ^ 1]) / 3.0;
		}

		#pragma omp master
		printf("Stream:%d\tRes = %.6f\t", omp_get_num_threads(), sq[k] * sq[k]);
	}

	t = omp_get_wtime() - t;

	return t;
}
	double func_zadanie1(double x)
	{
		return (sin(x + 2)) / (0.4 + cos(x));
	}

double MonteCarlo(int n, int stream)
{
	#if 1
	double t = omp_get_wtime();

	int in = 0;
	double s = 0;

	#pragma omp parallel num_threads(stream)
	{
		#pragma omp master
		printf("Stream: %d\t", omp_get_num_threads());

		double s_loc = 0;
		int in_loc = 0;
		unsigned int seed = omp_get_thread_num();

		#pragma omp for nowait
		for (int i = 0; i < n; i++) {
			double x = getrand(&seed);
			double y = getrand(&seed) * 5;

			if (y >= 2) {
				in_loc++;
				s_loc += func_zadanie2(x, y);
			}
		}

		#pragma omp atomic
		s += s_loc;

		#pragma omp atomic
		in += in_loc;
	}

	double v = (5.0 * in) / n;
	double res = (v * s) / in;
	printf("Result: %.6f\t", res);

	t = omp_get_wtime() - t;
	#endif

	return t;
}
	double getrand(unsigned int *seed)
	{
		return (double)rand_r(seed) / RAND_MAX;
	}
	double func_zadanie2(double x, double y)
	{
		return x / pow(y, 2);
	}