#include <stdio.h> //fopen etc
#include <string.h> //strlen
int main() 
{
	const char* s = "hello";
	FILE* fp = NULL;
	fp = fopen("./hello_c.txt", "wb");
	fwrite(s, 1, strlen(s), fp);
	fclose(fp);
	return 0;
}

