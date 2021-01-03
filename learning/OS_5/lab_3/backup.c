#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define TRIGGER_VARIABLE 0

#define MAX_CATEGORY_NUMBER_INT 11
#define QUANTITY_DIGIT 10

#define PRINT_TASK_ONE            \
    printf("Task number one:\n"); \
    printf("Test programm from lecture 3\n");

#define PRINT_TASK_TWO                                                      \
    printf("Task number two:\n");                                           \
    printf("Create process with help fork and get information for process " \
           "parent and process child with help command \"ps\" and "         \
           "\"grep\"\n");                                                   \
    printf("Kill parent process and check work child process\n");

#define PRINT_TASK_THREE                                                \
    printf("Task number three:\n");                                     \
    printf("Create process tree with help fork and find him with help " \
           "pstree\n");

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

int main() // родитель раньше т.е. 15-парент 16-чайлд
{
    PRINT_TASK_TWO;
    // pid_t parent_pid;
    // pid_t child_pid;
    pid_t pid;
    char* index = NULL;
    char* search_process = NULL;
    char* temp_search = NULL;
    int error_flag = 0b0;
    int temp = 0;
    // system("ps");
    // printf("\n");
    child_pid = fork();
    system("ps");
    printf("\n");
    fflush(stdout);
    // child_pid = fork();
    if (child_pid == 0) { //если не равен нулю то это парент
        // system("ps");
        // printf("\n");
        fprintf(stdout,"CHILD:");
        fflush(stdout);
        printf("\n");
        fflush(stdout);
        temp = (int)getpid();
        printf("!!%d",temp);
        fflush(stdout);
        printf("\n");
        fflush(stdout);
        error_flag = (error_flag | Convert_Index(&index, temp));
        asprintf(&search_process, "ps | grep %s", index);
        system(search_process);
        fflush(stdout);
        printf("\n");
        fflush(stdout);
        free(search_process);
    } else {
        // system("ps");
        // printf("\n");
        // printf("PARENT:");
        // fflush(stdout);
        temp = (int)getpid();
        error_flag = (error_flag | Convert_Index(&index, temp));
        asprintf(&search_process, "ps | grep %s", index);
        system(search_process);
        free(search_process);
    }
    // printf("\n"); //сделать вывод пс греп процесса дочернего по его ай ди (мб придется запоминать дочерний процесс или не освобождать память под команду а освобождать после мутя две коммы)
    // system("ps");
    // kill(parent_pid, SIGTERM);
    // printf("\n");
    // temp = (int)getpid();
    // error_flag = (error_flag | Convert_Index(&index, temp));
    // asprintf(&search_process, "ps | grep %s", index);
    // system(search_process);
    // free(search_process);
    // fflush(stdin);
    // fflush(stdout);
    return error_flag;
}
