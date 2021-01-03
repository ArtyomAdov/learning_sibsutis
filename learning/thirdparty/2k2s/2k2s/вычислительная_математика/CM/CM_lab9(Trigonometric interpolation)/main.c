#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#if 1
float TrigInter(float *X, float *Y, float x, int n)
{
	int lb = -(n/2) + 1;
	int ub = (n/2);
	float h = X[1] - X[0];
	float complex y = 0;

	for (int j = lb; j <= ub; j++) {
		float complex Aj = 0;
		for (int k = 0; k < n; k++) {
			// printf("Ai%d\n", k);
			float ex1 = -2 * M_PI * (((float)(j * k)) / n);
			float complex Ai = Y[k] * cexp(ex1 * I);
			Aj += Ai;
			// printf("%f %f\n", creal(Ai), cimag(Ai));
		}
		Aj /= n;
		// printf("Aj%d\n", j);
		// printf("%f %f\n", creal(Aj), cimag(Aj));

		float ex2 = 2 * M_PI * j * ((x - X[0]) / (n * h));
		y += Aj * cexp(ex2 * I);
	}
	
	return creal(y);
}
#endif

#if 0
float TrigInter(float *x, float *y, float x_find, int n)
{
	float complex res = 0.0 + 0.0 * I;

	float h = x[1] - x[0];

	// printf("%.3lf :: %.3lf\n", -((float)n/2) + 1, (float)n / 2);

	for (float j = -((float)n/2) + 1; j <= (float)n / 2; j++) {
	// for (float j = 0; j < n - 1; j++) {
		float complex tmp = 0.0 + 0.0 * I;
		for (float i = 0.0; i < n - 1; i++) {
			float complex y_ = y[(int)i];
			tmp += y_ * cexp((-2) * M_PI * I * ((i * j) / (float)n));
		}
		tmp /= n;

		res += tmp * cexp(2 * M_PI * I * j * ((x_find - x[0]) / ((float)n * h)));
		// res += tmp * cexp(2 * M_PI * I * j * x_find);
	}

	return creal(res);
}
#endif

#if 0
void mult_complex(float* y_real, float* y_imag, 
					float real1, float imag1, 
					float real2, float imag2)
{
	*y_real += (real1 + real2) - (imag1 * imag2);
	*y_imag += (real1 * imag2) + (real2 * imag1);
}

float TrigInter(float *X, float *Y, float x, int n)
{
	int lb = -(n/2) + 1;
	int ub = (n/2);
	float h = X[1] - X[0];
	float y_real = 0;
	float y_imag = 0;

	for (int j = lb; j <= ub; j++) {
		float real = 0;
		float imag = 0;
		for (int k = 0; k < n; k++) {
			float ex1 = -2 * M_PI * (((float)(j * k)) / n);
			real += Y[k] * cos(ex1);
			imag += Y[k] * sin(ex1);
			// printf("%.3f %.3f\n", real, imag);
		}

		real /= n;
		imag /= n;
		// printf("%.3f %.3f\n", real, imag);
		float ex2 = 2 * M_PI * j * ((x - X[0]) / (n * h));
		// y_real += real * cos(ex2);
		// y_imag += imag * sin(ex2);
		mult_complex(&y_real, &y_imag, real, imag, cos(ex2), sin(ex2));
	}

	return y_real;
}
#endif

int main()
{
	#if 0
	int n = 6;
	float Y[6] = { 0.0, 1.0, 1.414, 1.7321, 2.0, 2.2361 };
	float X[6] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0 };
	#endif

	#if 1
	int n = 4;
	// float Y[4] = { 1.413, 1.7321, 2.0, 2.2361 };
	float X[4] = { 2.0, 3.0, 4.0, 5.0 };

	float Y[4] = { 0 };
	for (int i = 0; i < n; i++) {
		Y[i] = sin(X[i]);
	}
	#endif

	#if 0
	int n = 4;
	float X[4] = { 3.0, 5.0, 7.0, 9.0 };
	float Y[4] = { 1.0, 0.0, 1.0, 4.0 };
	#endif

	#if 0
	float x = 3.6;
	printf("x = %.3f y = %.3f\n", x, TrigInter(X, Y, x, n));
	#endif

	#if 0
	float x = 4;
	printf("x = %.3f y = %.3f\n", x, TrigInter(X, Y, x, n));
	#endif

	#if 1
	FILE *out = fopen("out.txt", "w");

	float x = 2.0;

	for (int i = 0; i < 20; i++) {
		fprintf(out, "%.3f %.3f\n", x, TrigInter(X, Y, x, n));
		x += 0.2;
	}

	fclose(out);
	#endif

	// gnuplot "scen.plt"

	return 0;
}