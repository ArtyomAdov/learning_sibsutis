#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PRINT_TASK_ONE            \
    printf("Task number one:\n"); \
    printf("Test programm from lecture 3\n\n");

void oldman()
{
    fprintf(stdout, "I'm not yet dead! My ID is %i\n", (int)getpid());
}

void recreation()
{
    fprintf(stdout, "Who I am? My ID is %i\n", (int)getpid());
}

int main()
{
    pid_t child_pid, parent_pid;
    int i = 0;
    fprintf(stdout, "Before RECREATION %i\n", parent_pid = (int)getpid());
    child_pid = fork();
    while (i++ < 5) {
        if (child_pid != 0) {
            oldman();
        } else {
            recreation();
        }
    }
    return 0;
}