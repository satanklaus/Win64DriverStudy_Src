#define __INTRINSIC_DEFINED__InterlockedAdd64
#include <ntddk.h>
#include <windef.h>
#include <stdlib.h>

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObj, PUNICODE_STRING pRegistryString)
{
	DbgPrint("[KrnlHW64]HelloBustu\n");
	return STATUS_SUCCESS;
}
