#include <windows.h>
#include <stdio.h>
//WDM.H

//void nullproc()
int main()
{
	ULONG __cdecl DbgPrint (
		_In_z_ _Printf_format_string_ PCSTR Format, ...			
			);

	printf("status: %X\n",DbgPrint("nullproc\n"));
//	printf("status: %X\n",STATUS_SUCCESS);
}
