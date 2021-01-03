#include <stdio.h>
#include <stdlib.h>

#define METHOD_OF_EULER 1
#define METHOD_OF_RUNGE_KUTT_TIME 2
// #define METHOD_OF_RUNGE_KUTT_DERIVATIVE 3
#define CLEAR_SCREEN 9
#define EXIT_FROM_PROGRAMM 0
#define EPS 0.001 // 10^-3 == 0.2-0
#define COEFFICIENT 3
#define SIZE 2
#define PREVIOS 0
#define CURRENT 1

#define FUNCTION(x,y) ((2 * (x)) - (y))

#define SYSTEM_CLEAR printf("\E[H\E[J");

#define DIFERENCE_BY_TWO_VALUE(right_limit, left_limit) \
        ((right_limit) - (left_limit));

#define ABSOLUT_OF_DIFFERENCE(difference)   \
    if ((difference) < 0.0) {               \
        difference = ((difference) * (-1)); \
    }

#define PRINT_VALUE_FUNCTION(value) \
    printf("Value function %.8f\n", value);

#define PRINT_ANSWER(answer) \
    printf("\nAnswer by Method: %0.8f\n", answer);

#define MESSEGE_BY_INCORRECT_CHOICE \
    printf("\nError: Needed choice correct value in menu\n");

#define PRINT_QUANTITY_STEPS(quantity_step) \
    printf("Steps number %d\n", quantity_step);

#define PRINT_PACE_FUNCTION(value_pace) \
    printf("Pace of function %.8f\n", value_pace);

#define DRAW_MENU                             \
    printf("1) Method of Euler\n"); \
    printf("9) Clear Screen\n");              \
    printf("0) Exit from Programm\n");

double Method_Euler(double start_x, double start_y, double left_limit, double right_limit, double value_pace)
{
	double *array_y = NULL;
	double difference = 0.0;
	int quantity_step = 0;
	array_y = (double*) calloc (SIZE,sizeof(double));
	array_y[CURRENT] = start_y;
	start_y = 0;
	while (1)
	{
		quantity_step++;
		PRINT_QUANTITY_STEPS(quantity_step);
		for (double i = (left_limit + value_pace); i <= right_limit + 0.01; i = (i + value_pace)) 
		{
			array_y[PREVIOS] = array_y[CURRENT];
			array_y[CURRENT] = (array_y[PREVIOS] + ((FUNCTION((i - value_pace), array_y[PREVIOS])) * value_pace));
		}
		difference = DIFERENCE_BY_TWO_VALUE(start_y,array_y[PREVIOS]);
		ABSOLUT_OF_DIFFERENCE(difference);
		PRINT_VALUE_FUNCTION(array_y[PREVIOS]);
		if (difference < (COEFFICIENT * EPS))
		{
			break;
		}
		else
		{
			start_y = array_y[PREVIOS];
			value_pace = (value_pace / 2);
		}		
	}
	return array_y[CURRENT];//hmm
}

int main()
{
	double x = 1, y = 3;
	double left_limit = 1, right_limit = 1.6;
	double value_pace = 0.2;
	short int key_choice = 0;
    while (1) {
        DRAW_MENU;
        scanf("%hd", &key_choice);
        switch (key_choice) {
        case (METHOD_OF_EULER): {
            double answer = 0.0;
            answer = Method_Euler(x, y, left_limit, right_limit, value_pace);
            PRINT_ANSWER(answer);
            break;
        }
		// case (METHOD_OF_RUNGE_KUTT_TIME): {
        //     double answer = 0.0;
        //     answer = Method_Runge_Kutt_Time(x, y, left_limit, right_limit, value_pace);
        //     PRINT_ANSWER(answer);
        //     break;
        // }
		// case (METHOD_OF_RUNGE_KUTT_DERIVATIVE): {
        //     double answer = 0.0;
        //     answer = Method_Runge_Kutt_Derivative(x, y, left_limit, right_limit, value_pace);
        //     PRINT_ANSWER(answer);
        //     break;
        // }
        case (CLEAR_SCREEN): {
            SYSTEM_CLEAR;
            break;
        }
        case (EXIT_FROM_PROGRAMM): {
            return 0;
        }
        default: {
            MESSEGE_BY_INCORRECT_CHOICE;
            break;
        }
        }
    }
	return 0;
}