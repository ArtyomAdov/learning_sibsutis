#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float Fz(float z, float *x, float *y, int n)
{
	float *Px = calloc(n, sizeof(float));
	float fz = 0.0, mult;

	for (int i = 0; i < n; i++) {
		mult = 1.0;
		for (int j = 0; j < n; j++) {
			if (i != j)
				mult *= (z - x[j]) / (x[i] - x[j]);
		}
		Px[i] = mult * y[i];
	}

	for (int i = 0; i < n; i++) {
		fz += Px[i];
	}

	free(Px);

	return fz;
}

int main()
{
	int n = 4;
	float x[4] = { 3.0, 5.0, 7.0, 9.0 };
	float y[4] = { 1.0, 0.0, 1.0, 4.0 };
	// float y[3] = { 1.7321, 2.0, 2.2361 };
	// float x[3] = { 3.0, 4.0, 5.0 };
	float z = 3.0;

	FILE *out = fopen("out.txt", "w");

	for (int i = 0; i < 20; i++) {
		fprintf(out, "%.3f %.3f\n", z, Fz(z, x, y, n));
		z += 0.2;
	}

	fclose(out);

	return 0;
}