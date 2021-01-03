#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define PRINT_TASK_ONE            \
    printf("Task number one:\n"); \
    printf("Test programm from lecture 3\n\n");

int main()
{
    PRINT_TASK_ONE;
    pid_t child_pid, parent_pid;
    double s = 0.0;
    child_pid = fork();
    if (child_pid != 0) {
        s += 3.14;
        fprintf(stdout, "CHILD: %i s=%g &s=%u\n", (int)getpid(), s, &s);
    } else {
        s += 2.72;
        fprintf(stdout, "PARENT: %i s=%g &s=%u\n", (int)getpid(), s, &s);
    }
    return 0;
}
