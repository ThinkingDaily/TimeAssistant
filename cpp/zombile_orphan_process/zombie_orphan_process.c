#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    if (argc != 3) {
        printf("Usage: %s parent_sleep_length child_sleep_length\n", argv[0]);
        return -1;
    }

    pid_t child_pid;
    int parent_sleep_length = atoi(argv[1]);
    int child_sleep_length = atoi(argv[2]);

    printf("Parent process's pid: %d\n", (int)getpid());

    child_pid = fork();
    if (child_pid != 0) {
        printf("this is the parent process, with id %d\n", (int)getpid());
        printf("the child's process ID is %d\n", (int)child_pid);
        sleep(parent_sleep_length);
        printf("parent process will be terminated.\n");
    } else {
        printf("this is the child process, with id %d\n", (int)getpid());
        sleep(child_sleep_length);
        printf("child process will be terminated.\n");
    }

    return 0;
}

