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

#define PRINT_TASK_THREE                                                \
    printf("Task number three:\n");                                     \
    printf("Create process tree with help fork and find him with help " \
           "pstree\n\n");

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
    PRINT_TASK_THREE;
    pid_t pid_task_three;
    char* index = NULL;
    char* search_process = NULL;
    int error_flag = 0b0;
    int temp = 0;
    temp = (int)getpid();
    error_flag = (error_flag | Convert_Index(&index, temp));
    pid_task_three = fork();
    if (pid_task_three == -1) {
        exit(1);
    }
    pid_task_three = fork();
    if (pid_task_three == -1) {
        exit(1);
    }
    pid_task_three = fork();
    if (pid_task_three == -1) {
        exit(1);
    } else {
        if (pid_task_three != 0) {
            asprintf(&search_process, "pstree -p %s", index);
            system(search_process);
            free(search_process);
            asprintf(&search_process, "ls /proc/%s/task", index);
            system(search_process);
            free(search_process);
            kill(pid_task_three,SIGKILL);
            return 0;
        }
    }
    return error_flag;
}