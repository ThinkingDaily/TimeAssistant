#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

int main()
{
    const char *NOT_EXIST_FILE = "./not_exist_file_name.nefn";
    struct stat st;
    int ret;

    ret = stat(NOT_EXIST_FILE, &st);
    if (-1 == ret) {
        printf("Error(%d): %s\n", errno, strerror(errno));
    } else {
        printf("Stat ok\n");
    }

    return 0;
}
