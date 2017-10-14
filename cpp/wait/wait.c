#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

/*
Usage: ./a.out signal_code
e.g. ./a.out 5
*/
int main(int argc, const char* argv[])
{
    pid_t child_pid;

    child_pid = fork();

    if (child_pid == 0) {
        printf("child process is sleeping.\n");
        sleep(100);
        return 0; 
    }

    sleep(2); // Give a chance for child process to print a line.
    kill(child_pid, atoi(argv[1]));

    int status;
    waitpid(child_pid, &status, 0);

    if (WIFEXITED(status)) {
        printf("exited, status=%d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("killed by signal %d\n", WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
        printf("stopped by signal %d\n", WSTOPSIG(status));
    } else {
        printf("unknown\n");
    }

    return 0;
}

