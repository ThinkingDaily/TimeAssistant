#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "crc.h"

int main(int argc, const char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s filename\n", argv[0]);
		return 1;
	}

	FILE* fp = fopen(argv[1], "rb");
	if (NULL == fp) {
		printf("ERROR: %s\n", strerror(errno));
		return 1;
	}

	unsigned char buffer[1024] = {0};
	unsigned int count = 0;
	uint32_t crc = 0;

	for (;;) {
		count = fread(buffer, 1, 1024, fp);
		if (count == 0) break;

		crc = crc32(crc, buffer, count);
	}

	fclose(fp);

	printf("%08x\n", crc);

	return 0;
}