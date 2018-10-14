#define __INTRINSIC_DEFINED__InterlockedAdd64
#include <ntddk.h>
#include <windef.h>
#include <stdlib.h>

VOID DriverUnload(PDRIVER_OBJECT pDriverObj)
{	
	DbgPrint("[KrnlHW64]ByeBye, Kernel!\n");
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObj, PUNICODE_STRING pRegistryString)
{
	pDriverObj->DriverUnload = DriverUnload;
	DbgPrint("[KrnlHW64]Hello, Kernel!\n");
	return STATUS_SUCCESS;
}
