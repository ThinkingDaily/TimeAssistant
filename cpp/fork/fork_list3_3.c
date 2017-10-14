#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t child_pid;

    printf("the main program process ID is %d\n", (int)getpid());

    child_pid = fork();
    if (child_pid != 0) {
        printf("this is the parent process, with id %d\n", (int)getpid());
        printf("the child's process ID is %d\n", (int)child_pid);
        sleep(10);
    } else {
        printf("this is the child process, with id %d\n", (int)getpid());
        sleep(20);
    }

    return 0;
}

