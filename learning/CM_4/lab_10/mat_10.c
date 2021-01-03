#include <stdio.h>

#define METHOD_OF_TRAPEZES 1
#define METHOD_OF_SIMPSONS 2
#define CLEAR_SCREEN 9
#define EXIT_FROM_PROGRAMM 0
#define EPS 0.00000001 // 10^-8 == 0.7-0
#define COEFFICIENT_FOR_TRAPEZES 3
#define COEFFICIENT_FOR_SIMPSONS 15

#define FUNCTION(i) (1 / (i))

#define FIND_MEDIANA(right_limit, left_limit) \
    (((right_limit) - (left_limit)) / 2)

#define SYSTEM_CLEAR \
    printf("\E[H\E[J");

#define MESSEGE_BY_INCORRECT_CHOICE \
    printf("\nError: Needed choice correct value in menu\n");

#define PRINT_QUANTITY_STEPS(quantity_step) \
    printf("Steps number %d\n", quantity_step);

#define PRINT_PACE_FUNCTION(value_pace) \
    printf("Pace of function %.8f\n", value_pace);

#define PRINT_DIFFERENCE(difference) \
    printf("%.8f\n", difference);

#define PRINT_ANSWER(answer) \
    printf("\nAnswer by Method: %0.8f\n", answer);

#define ABSOLUT_OF_DIFFERENCE(difference)   \
    if ((difference) < 0.0) {               \
        difference = ((difference) * (-1)); \
    }

#define DRAW_MENU                      \
    printf("1) Method of Trapezes\n"); \
    printf("2) Method of Simpsons\n"); \
    printf("9) Clear Screen\n");       \
    printf("0) Exit from Programm\n");

double
Function_Trapezes(double left_limit, double right_limit, double value_pace)
{
    double difference = 0, current_sum_y = 0, previous_sum_y = 0;
    int quantity_step = 0;
    value_pace = ((right_limit - left_limit) / 2);
    while (1) {
        quantity_step++;
        PRINT_QUANTITY_STEPS(quantity_step);
        PRINT_PACE_FUNCTION(value_pace);
        for (double i = left_limit; i <= (right_limit - value_pace);
             i = (i + value_pace)) {
            current_sum_y = current_sum_y
                    + (value_pace
                       * (0.5 * FUNCTION(i) + 0.5 * FUNCTION(i + value_pace)));
        }
        difference = previous_sum_y - current_sum_y;
        ABSOLUT_OF_DIFFERENCE(difference);
        PRINT_DIFFERENCE(difference);
        if (difference < COEFFICIENT_FOR_TRAPEZES * EPS) {
            break;
        } else {
            previous_sum_y = current_sum_y;
            value_pace = (value_pace / 2);
            current_sum_y = 0;
        }
    }
    return current_sum_y;
}

double
Function_Simpsons(double left_limit, double right_limit, double value_pace)
{
    double difference = 0, current_sum_y = 0, previous_sum_y = 0;
    int quantity_step = 0;
    value_pace = FIND_MEDIANA(right_limit, left_limit);
    while (1) {
        quantity_step++;
        PRINT_QUANTITY_STEPS(quantity_step);
        PRINT_PACE_FUNCTION(value_pace);
        for (double i = left_limit; i <= (right_limit - value_pace);
             i = (i + (2 * value_pace))) {
            current_sum_y = current_sum_y
                    + (2 * value_pace
                       * (FUNCTION(i) / 6 + 2 * FUNCTION(i + value_pace) / 3
                          + FUNCTION(i + 2 * value_pace) / 6));
        }
        difference = previous_sum_y - current_sum_y;
        ABSOLUT_OF_DIFFERENCE(difference);
        PRINT_DIFFERENCE(difference);
        if (difference < COEFFICIENT_FOR_SIMPSONS * EPS) {
            break;
        } else {
            previous_sum_y = current_sum_y;
            value_pace = (value_pace / 2);
            current_sum_y = 0;
        }
    }
    return current_sum_y;
}

int main()
{
    double left_limit = 1, right_limit = 2;
    double start_value_pace = 0.1;
    short int key_choice = 0;
    while (1) {
        DRAW_MENU;
        scanf("%hd", &key_choice);
        switch (key_choice) {
        case (METHOD_OF_TRAPEZES): {
            double answer = 0.0;
            answer = Function_Trapezes(
                    left_limit, right_limit, start_value_pace);
            PRINT_ANSWER(answer);
            break;
        }
        case (METHOD_OF_SIMPSONS): {
            double answer = 0.0;
            answer = Function_Simpsons(
                    left_limit, right_limit, start_value_pace);
            PRINT_ANSWER(answer);
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