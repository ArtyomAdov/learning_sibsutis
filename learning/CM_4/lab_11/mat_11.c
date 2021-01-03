#include <stdio.h>

#define METHOD_OF_GOLDEN_RELATION 1
#define CLEAR_SCREEN 9
#define EXIT_FROM_PROGRAMM 0
#define EPS 0.0000001 // 10^-7 == 0.6-0
#define COEFFICIENT 0.382

#define FUNCTION(x) (((x) * (x)) - (6 * (x)))

#define FIND_MEDIANA(right_limit, left_limit) \
    (((right_limit) + (left_limit)) / 2);

#define SYSTEM_CLEAR printf("\E[H\E[J");

#define PRINT_ANSWER(answer) \
    printf("\nAnswer by Golden Relation: %.8f\n", answer);

#define MESSEGE_BY_INCORRECT_CHOICE \
    printf("\nError: Needed choice correct value in menu\n");

#define PRINT_QUANTITY_STEPS(quantity_step) \
    printf("Steps number %d\n", quantity_step);

#define PRINT_INTERVAL(left_limit, right_limit) \
    printf("Interval (%.8f;%.8f)\n", left_limit, right_limit);

#define PRINT_POINT(point) \
	printf("Point %.8f\n", point);

#define PRINT_VALUE_FUNCTION_IN_POINT(value) \
    printf("Value function %.8f\n", value);

#define DIFERENCE_BY_TWO_VALUE(right_limit, left_limit) \
        ((right_limit) - (left_limit));

#define ABSOLUT_OF_DIFFERENCE(difference)   \
    if ((difference) < 0.0) {               \
        difference = ((difference) * (-1)); \
    }

#define DRAW_MENU                             \
    printf("1) Method of Golden Relation\n"); \
    printf("9) Clear Screen\n");              \
    printf("0) Exit from Programm\n");

double Method_Golden_Relation(double left_limit, double right_limit)
{
    double difference = 0.0;
    double min = 0;
    double F = 0;
    double X1 = (left_limit + COEFFICIENT * (right_limit - left_limit));
    double X2 = (right_limit - COEFFICIENT * (right_limit - left_limit));
    double F1 = FUNCTION(X1);
    double F2 = FUNCTION(X2);
    int quantity_step = 0;
    while (1) {
        quantity_step++;
        if (F1 < F2) {
            right_limit = X2;
            difference = DIFERENCE_BY_TWO_VALUE(right_limit, left_limit);
			ABSOLUT_OF_DIFFERENCE(difference);
            if (difference <= EPS) {
                break;
            } else {
                X2 = X1;
                F2 = F1;
                X1 = left_limit + COEFFICIENT * (right_limit - left_limit);
                F1 = FUNCTION(X1);
            }
        } else {
            left_limit = X1;
            difference = DIFERENCE_BY_TWO_VALUE(right_limit, left_limit);
            ABSOLUT_OF_DIFFERENCE(difference);
            if (difference <= EPS) {
                break;
            } else {
                X1 = X2;
                F1 = F2;
                X2 = right_limit - COEFFICIENT * (right_limit - left_limit);
                F2 = FUNCTION(X2);
            }
        }
        PRINT_QUANTITY_STEPS(quantity_step);
        PRINT_INTERVAL(left_limit, right_limit);
        PRINT_POINT(X1);
        PRINT_VALUE_FUNCTION_IN_POINT(F1);
        PRINT_POINT(X2);
        PRINT_VALUE_FUNCTION_IN_POINT(F2);
    }
	printf("\nminimal:\n");
    min = FIND_MEDIANA(right_limit, left_limit);
    F = FUNCTION(min);
    PRINT_INTERVAL(left_limit, right_limit);
    PRINT_POINT(min);
    PRINT_VALUE_FUNCTION_IN_POINT(F);
    return min;
}

int main()
{
    double left_limit = 0.0, right_limit = 5.0;
    short int key_choice = 0;
    while (1) {
        DRAW_MENU;
        scanf("%hd", &key_choice);
        switch (key_choice) {
        case (METHOD_OF_GOLDEN_RELATION): {
            double answer = 0.0;
            answer = Method_Golden_Relation(left_limit, right_limit);
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