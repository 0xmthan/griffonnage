#include <stdio.h>
#include <string.h>

int main(void)
{
	char *tt2 = "💀";
	printf("%02X\n", (unsigned char) *tt2);
	printf("%02X\n", (unsigned char) *(tt2 + 1));
	printf("%02X\n", (unsigned char) *(tt2 + 2));
	printf("%02X\n", (unsigned char) *(tt2 + 3));

	char tt[8];
	memset(tt, 0, sizeof(tt));
	memset(tt, 0x80, 4);
	memset(tt, 0x92, 3);
	memset(tt, 0x9F, 2);
	memset(tt, 0xF0, 1);
	printf("%s\n", tt);
	return (0);
}
