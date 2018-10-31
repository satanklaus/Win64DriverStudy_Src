#include "../include/common.h"

SC_HANDLE scm = NULL;
SC_HANDLE service = NULL;

if (!(scm = OpenSCManager(
	NULL,//LOCAL PC
	NULL,//DUMMY
	SC_MANAGER_ALL_ACCESS)))//MAX
	{ printf("["DRVNAME"]: cannot open SCM\n");
	return GetLastError(); }

if(!(service = CreateService(
	scm,
	DRVNAME,
	"["DRVNAME"]",
        SERVICE_ALL_ACCESS,//MAX
	SERVICE_KERNEL_DRIVER,
	SERVICE_DEMAND_START,
	SERVICE_ERROR_NORMAL,
        driverpath,
	NULL,//no load group
	NULL,//no tag
	NULL,//no deps
	NULL,//def obj name
	NULL)))//ignored pwd
	{
	if ((err = GetLastError()) == ERROR_SERVICE_EXISTS)
		{
		printf("["DRVNAME"]: service exists, lets try to open\n");
		if (!(service = OpenSerivce(
			scm,
			DRVNAME,
			SERVICE_ALL_ACCESS))) 
		{ 
			printf("["DRVNAME"]:totally failed\n");
			CloseServiceHandle(scm);
			return GetLastError(); 
		}
		else 
		{
			printf("["DRVNAME"]: last resort succeed\n");
		}
		return err;
	}
	else {
		return NULL;
	}
printf("["DRVNAME"]: service successfully created\n");
	


/////////////////

	if (!StartServiceA(m_hService,NULL,NULL))
	{
		m_dwLastError = GetLastError();
		return FALSE;
	}
	return TRUE;

	SERVICE_STATUS ss;
	if (!ControlService(m_hService,SERVICE_CONTROL_STOP,&ss))
	{
		m_dwLastError = GetLastError();
		return FALSE;
	}
	return TRUE;


	if (!DeleteService(m_hService))
	{
		m_dwLastError = GetLastError();
		return FALSE;
	}
	return TRUE;
}

	m_hDriver = CreateFileA(pLinkName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if(m_hDriver != INVALID_HANDLE_VALUE)
		return TRUE;
	else
		return FALSE;
}

	BOOL b=DeviceIoControl(m_hDriver,CTL_CODE_GEN(dwIoCode),InBuff,InBuffLen,OutBuff,OutBuffLen,&dw,NULL);
	if(RealRetBytes)
		*RealRetBytes=dw;
	return b;
}
