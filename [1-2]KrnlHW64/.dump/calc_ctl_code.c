#include <stdio.h>
#include <stdint.h>

typedef int32_t 		DWORD;
#define FILE_DEVICE_UNKNOWN 	0x22
#define METHOD_BUFFERED 	0x0
#define FILE_ANY_ACCESS 	0x0

#define CTL_CODE_GEN(FCODE) (FILE_DEVICE_UNKNOWN << 16 | FILE_ANY_ACCESS << 14 | FCODE << 2 | METHOD_BUFFERED)

int main(DWORD argc, char *argv[])
{
	DWORD function_code = 0x0;
	if (argc ==2 && sscanf(argv[1],"%X", &function_code)) 
		printf("Output: %ld(0x%X)\n",CTL_CODE_GEN(function_code),CTL_CODE_GEN(function_code));
	else 
		printf("pass hex number as argument\n");
}
