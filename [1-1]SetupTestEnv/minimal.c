#include "../include/common.h"
#include "../include/dirty.h"
#include <ntddk.h>

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
