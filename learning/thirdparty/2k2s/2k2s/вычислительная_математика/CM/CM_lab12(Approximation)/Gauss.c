#include "Gauss.h"

int get_intdex(int i, int j, int n) { return i * n + j; }

void GaussMethod(float *C, float *b, float *a, int p)
{
	for (int k = 0; k < p; k++) {
		for (int i = k + 1; i < p; i++) {
			if (C[k * p + k] == 0)
				return;
			float M = C[i * p + k] / C[k * p + k];
			for (int j = k; j < p; j++)
				C[i * p + j] -= M * C[k * p + j];
			b[i] -= M * b[k];
		}
	}

	for (int i = p - 1; i >= 0; i--) {
		float s = 0;
		for (int j = i; j < p; j++)
			s = s + C[i * p + j] * a[j];
		a[i] = (b[i] - s) / C[i * p + i];
	}
}