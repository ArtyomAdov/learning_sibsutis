#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float f(float x)
{
	return powf(x, 2);
}

float NIntegr(float a, float b)
{
	float n0 = 1000000; 
	float n = n0;
	float h;

	float S0 = 0;
	float delta = 1;
	float eps = 1E-2;

	for (;delta >= eps; n *= 2) {
		float S1 = 0;
		h = (b - a) / n;
		for (int i = 0; i < n; i++) {
			S1 += (f(a + i * h) + f(a + (i + 1) * h)) / 2;

			// if (i == 0 || i == n - 1) {
			// 	S1 += f(a + i * h) / 2;
			// } else {
			// 	S1 += f(a + i * h);
			// }
		}
		S1 *= h;

		delta = fabsf(S1 - S0);

		S0 = S1;
	}

	return S0;
}

float SimpsonIntegr(float a, float b)
{
	float n0 = 1000000; 
	float n = n0;
	float h;

	float S0 = 0;
	float delta = 1;
	float eps = 1E-2;

	for (;delta >= eps; n *= 2) {
		float S1 = 0;
		h = (b - a) / n;
		for (int i = 0, k = 0; i < n; i++, k ^= 1) {
			if (i == 0 || i == n - 1) {
				S1 += f(a + i * h);
			} else if (k == 0) {
				S1 += f(a + i * h) * 2;
			} else if (k == 1) {
				S1 += f(a + i * h) * 4;
			}
		}
		S1 *= h / 3;

		delta = fabsf(S1 - S0);

		S0 = S1;
	}

	return S0;
}

int main()
{
	float a = 0;
	float b = 2;

	float S1 = NIntegr(a, b);
	float S2 = SimpsonIntegr(a, b);
	printf("S1 = %.12f\n", S1);
	printf("S2 = %.12f\n", S2);

	return 0;
}