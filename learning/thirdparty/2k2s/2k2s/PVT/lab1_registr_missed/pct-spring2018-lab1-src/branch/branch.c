/*
 * branch.c:
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hpctimer.h"

enum { 
    n = 100000,
    nreps = 20 
};

double x[n], y[n], z[n];

void blend_map(double *dest, double *a, double *b, int size, int blend)
{
    int i = 0;
    
    for (i = 0; i < size; i++) {
        if (blend == 255) {
            dest[i] = a[i];
        } else if (blend == 0) {
            dest[i] = b[i];
        } else {
            dest[i] = a[i] * blend + b[i] * (255 - blend) / 256.0;
        }
    }
}

void blend_map_opt(double *dest, double *a, double *b, int size, int blend)
{
    /* TODO: Implement optimized version of blend_map */
}

int main()
{
    double tfirst, t;
    int i;
        
    /* First run: warmup */
    tfirst = hpctimer_wtime();
    blend_map(z, x, y, n, 0);
    tfirst = hpctimer_wtime() - tfirst;

    /* Measures */
    t = hpctimer_wtime();
    for (i = 0; i < nreps; i++) {
        blend_map(z, x, y, n, 0);
    }
    t = (hpctimer_wtime() - t) / nreps;

    printf("First run (sec.): %.6f\n", tfirst);
    printf("Mean of %d runs (sec.): %.6f\n", nreps, t);
    
    return 0;
}
