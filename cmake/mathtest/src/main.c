#include <stdio.h>
#include "my_math.h"

int main()
{
	printf("%d + %d = %d\n", 3, 2, myadd(3, 2));
	printf("%d - %d = %d\n", 3, 2, myminus(3, 2));
	printf("%d * %d = %d\n", 3, 2, mymulti(3, 2));

	return 0;
}