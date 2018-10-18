#define __INTRINSIC_DEFINED__InterlockedAdd64
#include <ntddk.h>
#define DRVNAME "InKrnlHW64"

VOID DriverUnload(PDRIVER_OBJECT pDriverObj)
{	
	DbgPrint("["DRVNAME"]ByeBye, Kernel!\n");
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObj, PUNICODE_STRING pRegistryString)
{
	pDriverObj->DriverUnload = DriverUnload;
	DbgPrint("["DRVNAME"]KrnlHW64]Hello, Kernel!\n");
	return STATUS_SUCCESS;
}
