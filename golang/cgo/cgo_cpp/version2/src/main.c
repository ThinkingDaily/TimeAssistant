#include <stdio.h>
#include "file_api.h"

int main()
{
    bool ok;

    ok = split(NULL);
    printf("ok: %d\n", ok);

    ok = split("c:/a/b/c.txt");
    printf("ok: %d\n", ok);

    return 0;
}