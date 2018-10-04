#include <windows.h>
//WDM.H

typedef dbgprint

//void nullproc()
void main()
{
	HANDLE ntdll = LoadLibrary("ntdll.dll");
	GetProcAddress(ntdll, "DbgPrint");
//	DbgPrint("nullproc\n");
	FreeLibrary(ntdll);

}
