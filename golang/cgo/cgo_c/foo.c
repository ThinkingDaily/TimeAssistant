#include <stdio.h>
#include "foo.h"

extern void go_foo(int x);

void c_foo(int x) {
    printf("foo() in C...\n");
    go_foo(x);
}
