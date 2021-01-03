#include <stdio.h>
#include <math.h>

#define METHOD_OF_RUNGE_KUTT_DERIVATIVE 1
#define CLEAR_SCREEN 9
#define EXIT_FROM_PROGRAMM 0
#define EPS 0.01//001//-4 0.0-3//00001 //-8 0.0-7
#define START_VALUE_PACE 0.5
#define START_VALUE_Y 1
#define START_VALUE_Y_DIFF 1
#define START_LEFT_LIMIT 0
#define START_RIGHT_LIMIT 1
#define COEFFICIENT 3
#define FLAG_PRINT_X_FOR_ALL_ITERATION_IN_LAST_STEP 0

#define FUNCTION(y,y_diff,x) \
	(((exp(x)) + (y) + (y_diff)) / (3))

#define SYSTEM_CLEAR \
    printf("\E[H\E[J");

#define PRINT_MESSEGE_FOR_PRINT_ALL_X \
	printf("all value x for last iteration:\n");

#define MESSEGE_BY_INCORRECT_CHOICE \
    printf("\nError: Needed choice correct value in menu\n");

#define PRINT_QUANTITY_STEPS(quantity_step) \
    printf("\tSteps number %d\n", quantity_step);

#define PRINT_PACE_FUNCTION(value_pace) \
    printf("Pace of function      h : %.8f\n", value_pace);

#if FLAG_PRINT_X_FOR_ALL_ITERATION_IN_LAST_STEP

#define PRINT_VALUE_X(x) \
	printf("\tx : %.8f",x);

#define PRINT_VALUE_FUNCTION(value) \
	printf("\ty : %.8f",value.top_value); \
	printf("\ty_diff: %.8f\n\n",value.low_value);

#else
    
#define PRINT_VALUE_X(x) \
	printf("                      x : %.8f\n",x);

#define PRINT_VALUE_FUNCTION(value) \
	printf("Value function equall y : %.8f\n",value.top_value); \
	printf("                      y': %.8f\n\n",value.low_value);

#endif

#define DIFERENCE_BY_TWO_VALUE(right_limit, left_limit) \
        ((right_limit) - (left_limit));

#define ABSOLUT_OF_DIFFERENCE(difference)   \
    if ((difference) < 0.0) {               \
        (difference) = ((difference) * (-1)); \
    }

#define DRAW_MENU                      \
    printf("1) Method of Runge\n"); \
    printf("9) Clear Screen\n");       \
    printf("0) Exit from Programm\n");

typedef struct value_y
{
	double top_value;
	double low_value;
} val_y;

val_y Method_Runge_Kutt_Derivative(double left_limit, double right_limit, val_y value_function, val_y helping_value)
{
	val_y difference;
	double value_pace = START_VALUE_PACE;
	double i = 0.0;
	int quantity_step = 0;
	difference.top_value = 0.0;
	difference.low_value = 0.0;
	while(1)
	{
		#if !FLAG_PRINT_X_FOR_ALL_ITERATION_IN_LAST_STEP
		quantity_step++;
		PRINT_QUANTITY_STEPS(quantity_step);
		PRINT_PACE_FUNCTION(value_pace);
		#endif
		for (i = left_limit; i <= (right_limit - value_pace + (1 / 5)); i = (i + value_pace))
		{
			helping_value.top_value = (value_function.low_value + (value_function.low_value + (value_pace * value_function.low_value)));
			helping_value.low_value = ((FUNCTION(value_function.top_value,value_function.low_value,i)) + (FUNCTION((value_function.top_value + (value_pace * value_function.low_value)),(helping_value.top_value - value_function.low_value),(i + value_pace))));
			value_function.top_value = (value_function.top_value + ((value_pace / 2) * helping_value.top_value));
			value_function.low_value = (value_function.low_value + ((value_pace / 2) * helping_value.low_value));
		}
		difference.top_value = DIFERENCE_BY_TWO_VALUE(difference.top_value, value_function.top_value);
		difference.low_value = DIFERENCE_BY_TWO_VALUE(difference.low_value, value_function.low_value);
		ABSOLUT_OF_DIFFERENCE(difference.top_value);
		ABSOLUT_OF_DIFFERENCE(difference.low_value);
		#if !(FLAG_PRINT_X_FOR_ALL_ITERATION_IN_LAST_STEP)
		PRINT_VALUE_X(i);
		PRINT_VALUE_FUNCTION(value_function);
		#endif
		if((difference.top_value < (COEFFICIENT * EPS)) && (difference.low_value < (COEFFICIENT * EPS)))
		{
			#if FLAG_PRINT_X_FOR_ALL_ITERATION_IN_LAST_STEP
				PRINT_MESSEGE_FOR_PRINT_ALL_X;
				value_function.top_value = START_VALUE_Y;
				value_function.low_value = START_VALUE_Y_DIFF;
				for (i = left_limit; i <= (right_limit - value_pace + (1 / 5)); i = (i + value_pace))
				{
					PRINT_VALUE_X(i);
					PRINT_VALUE_FUNCTION(value_function);
					helping_value.top_value = (value_function.low_value + (value_function.low_value + (value_pace * value_function.low_value)));
					helping_value.low_value = ((FUNCTION(value_function.top_value,value_function.low_value,i)) + (FUNCTION((value_function.top_value + (value_pace * value_function.low_value)),(helping_value.top_value - value_function.low_value),(i + value_pace))));
					value_function.top_value = (value_function.top_value + ((value_pace / 2) * helping_value.top_value));
					value_function.low_value = (value_function.low_value + ((value_pace / 2) * helping_value.low_value));
				}
			#endif
			break;
		} else {
		value_pace = (value_pace / 2);
		difference.top_value = value_function.top_value;
		difference.low_value = value_function.low_value;
		value_function.top_value = START_VALUE_Y;
		value_function.low_value = START_VALUE_Y_DIFF;
		}
	}
	printf("Answer:\n");
	PRINT_VALUE_X(i);
	return value_function;
}

int main()
{
	val_y value_function;
	val_y helping_value;
	double left_limit = START_LEFT_LIMIT;
	double right_limit = START_RIGHT_LIMIT;
	short int key_choice = 0;
	value_function.top_value = START_VALUE_Y;
	value_function.low_value = START_VALUE_Y_DIFF;
	helping_value.top_value = 0.0;
	helping_value.low_value = 0.0;
	 while (1) {
        DRAW_MENU;
        scanf("%hd", &key_choice);
        switch (key_choice) {
        case (METHOD_OF_RUNGE_KUTT_DERIVATIVE): {
			val_y answer;
			answer = Method_Runge_Kutt_Derivative(left_limit, right_limit, value_function, helping_value);
            PRINT_VALUE_FUNCTION(answer);
			break;
        }
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
