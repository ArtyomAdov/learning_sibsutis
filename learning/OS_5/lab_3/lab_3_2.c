#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_CATEGORY_NUMBER_INT 11
#define QUANTITY_DIGIT 10

#define PRINT_TASK_TWO                                                      \
    printf("Task number two:\n");                                           \
    printf("Create process with help fork and get information for process " \
           "parent and process child with help command \"ps\" and "         \
           "\"grep\"\n");                                                   \
    printf("Kill parent process and check work child process\n\n");

int Determination_Quantity_Digit(int temp)
{
    int variable_comparison = 1;
    for (short int i = 1; i < MAX_CATEGORY_NUMBER_INT; i++) {
        variable_comparison = (variable_comparison * QUANTITY_DIGIT);
        if (temp < variable_comparison) {
            return i;
        }
    }
    return 0;
}

int Convert_Index(char** index, int temp)
{
    int category_number = 0;
    category_number = Determination_Quantity_Digit(temp);
    *index = (char*)calloc(category_number, sizeof(char));
    for (short int i = category_number - 1; i >= 0; i--) {
        for (short int j = 0; j < QUANTITY_DIGIT; j++) {
            if ((temp % QUANTITY_DIGIT) == j) {
                (*index)[i] = ('0' + j);
                break;
            }
        }
        temp = (temp / QUANTITY_DIGIT);
    }
    return 0;
}

int main()
{
    PRINT_TASK_TWO;
    pid_t pid_task_two;
    char* index = NULL;
    char* search_process = NULL;
    int error_flag = 0b0;
    int temp = 0;
    pid_task_two = fork();
    for (short int i = 0; i < 3; i++) {
        if (pid_task_two == -1) {
            exit(1);
        } else {
            if (pid_task_two != 0) {
                temp = (int)getpid();
                error_flag = (error_flag | Convert_Index(&index, temp));
                asprintf(&search_process, "ps | grep %s", index);
                system(search_process);
                free(search_process);
                if (i == 1) {
                    kill(pid_task_two, SIGTERM);
                }
                if (i == 2) {
                    kill(pid_task_two, SIGKILL);
                }
            } else {
                temp = (int)getpid();
                error_flag = (error_flag | Convert_Index(&index, temp));
                asprintf(&search_process, "ps | grep %s", index);
                system(search_process);
                free(search_process);
            }
        }
    }
    return error_flag;
}