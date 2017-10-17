#include "test_api.h"
#include "test.h"

void myprint(int x)
{
    CTest test(x);
    test.print();
}
