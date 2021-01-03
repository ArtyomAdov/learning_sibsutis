#include <stdio.h>
#include <omp.h>

int main()
{
    printf("Maximal quantity threads == %d",omp_get_max_threads());
    return 0;
}