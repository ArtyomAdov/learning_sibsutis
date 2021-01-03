#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float P(float *X, float *Y, float x, int i, int n)
{
	if ((n - i) == 1) {
		return (Y[i] * (x - X[n]) - Y[n] * (x - X[i])) / (X[i] - X[n]);
	} else {
		float P1 = P(X, Y, x, i, n - 1);
		float P2 = P(X, Y, x, i + 1, n);
		return (P1 * (x - X[n]) - P2 * (x - X[i])) / (X[i] - X[n]);
	}

	return 0;
}

int main()
{
	int n = 3;
	float Y[3] = { 1.7321, 2.0, 2.2361 };
	float X[3] = { 3.0, 4.0, 5.0 };

	FILE *out = fopen("out.txt", "w");

	float x = 3.0;

	for (int i = 0; i < 20; i++) {
		fprintf(out, "%.3f %.3f\n", x, P(X, Y, x, 0, n));
		x += 0.2;
	}

	fclose(out);

	//gnuplot "scen.plt"

	return 0;
}