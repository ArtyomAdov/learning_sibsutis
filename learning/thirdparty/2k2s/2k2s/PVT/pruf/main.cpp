#include <stdio.h>
#include <stdlib.h>


#include "hpctimer.h"
enum { 
    N = 512,
    NREPS = 99999999
};



int main(int argc, char **argv)
{
    int i;
    double t;
    		


    int rand_num;
    int counter_one;
    printf("vetki: ");        
/*    t = hpctimer_getwtime();
    for (i = 0; i < NREPS; i++) {
    	rand_num = rand() % 2;


    	if (rand_num == 1)
    		counter_one++;
    	else
    		counter_one--;

    }
    t = hpctimer_getwtime() - t;
    // t = t / NREPS;
    printf("Elapsed time: %.6f sec.\n", t);





    printf("main: ");
    t = hpctimer_getwtime();
    for (i = 0; i < NREPS; i++) {
    	rand_num = rand() % 2;

    	counter_one += (rand_num == 1) * 2 - 1;
    }
    t = hpctimer_getwtime() - t;
    // t = t / NREPS;
    printf("Elapsed time: %.6f sec.\n", t);*/




    t = hpctimer_getwtime();
    for (i = 0; i < NREPS; i++) {
    	rand_num = rand() % 10;


    	if (rand_num == 1)
    		counter_one++;
    	else if (rand_num == 2)
    		counter_one--;
    	else if (rand_num == 3)
    		counter_one += 7;
    	else if (rand_num == 4)
    		counter_one -= 7;

    }
    t = hpctimer_getwtime() - t;
    // t = t / NREPS;
    printf("Elapsed time: %.6f sec.\n", t);





    printf("main: ");
    t = hpctimer_getwtime();
    for (i = 0; i < NREPS; i++) {
    	rand_num = rand() % 10;

    	counter_one += (rand_num == 1) * 1 + (rand_num == 2) * (-1) + (rand_num == 3) * 7 + (rand_num == 4) * (-7);
    }
    t = hpctimer_getwtime() - t;
    // t = t / NREPS;
    printf("Elapsed time: %.6f sec.\n", t);
    
    
    return 0;
}

