/*============================
Drvier Control (SCM way)
============================*/
#include "../include/common.h"
//////////////////
//
//
SC_HANDLE scm = NULL;
SC_HANDLE service = NULL;
//////////////////

DWORD m_dwLastError;
PCHAR m_pServiceName;
HANDLE m_hDriver;
SC_HANDLE m_hSCManager;
SC_HANDLE m_hService;

BOOL Start();
BOOL Stop();
BOOL Remove();
BOOL Open(PCHAR pLinkName);
BOOL IoControl(DWORD dwIoCode, PVOID InBuff, DWORD InBuffLen, PVOID OutBuff, DWORD OutBuffLen, DWORD *RealRetBytes);
BOOL GetSvcHandle(PCHAR pServiceName);
DWORD CTL_CODE_GEN(DWORD lngFunction);

//////////////////////////
//DWORD _install(PCHAR pSysPath,PCHAR pServiceName,PCHAR pDisplayName)
//{
	scm = OpenSCManager(
			NULL,//LOCAL PC
			NULL,//DUMMY
			SC_MANAGER_ALL_ACCESS);//MAX
	if (!scm) { return GetLastError(); }

	service = CreateService(
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
			NULL);//ignored pwd
	if (!service)
	{
		m_dwLastError = GetLastError();
		if (ERROR_SERVICE_EXISTS == m_dwLastError)
		{
			m_hService = OpenServiceA(m_hSCManager,m_pServiceName,SERVICE_ALL_ACCESS);
			if (NULL == m_hService)
			{
				CloseServiceHandle(m_hSCManager);
				return FALSE;
			}
		}
		else
		{
			CloseServiceHandle(m_hSCManager);
			return FALSE;
		}
	}
////}
//












	cDrvCtrl()
	{
		m_pServiceName = NULL;
		m_pDisplayName = NULL;
		m_hSCManager = NULL;
		m_hService = NULL;
		m_hDriver = INVALID_HANDLE_VALUE;
	}

	~cDrvCtrl()
	{
		CloseServiceHandle(m_hService);
		CloseServiceHandle(m_hSCManager);
		CloseHandle(m_hDriver);
	}


BOOL cDrvCtrl::GetSvcHandle(PCHAR pServiceName)
{
	m_pServiceName = pServiceName;
	m_hSCManager = OpenSCManagerA(NULL,NULL,SC_MANAGER_ALL_ACCESS);
	if (NULL == m_hSCManager)
	{
		m_dwLastError = GetLastError();
		return FALSE;
	}
	m_hService = OpenServiceA(m_hSCManager,m_pServiceName,SERVICE_ALL_ACCESS);
	if (NULL == m_hService)
	{
		CloseServiceHandle(m_hSCManager);
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


BOOL cDrvCtrl::Start()
{
	if (!StartServiceA(m_hService,NULL,NULL))
	{
		m_dwLastError = GetLastError();
		return FALSE;
	}
	return TRUE;
}

BOOL cDrvCtrl::Stop()
{
	SERVICE_STATUS ss;
	GetSvcHandle(m_pServiceName);
	if (!ControlService(m_hService,SERVICE_CONTROL_STOP,&ss))
	{
		m_dwLastError = GetLastError();
		return FALSE;
	}
	return TRUE;

}

BOOL cDrvCtrl::Remove()
{
	GetSvcHandle(m_pServiceName);
	if (!DeleteService(m_hService))
	{
		m_dwLastError = GetLastError();
		return FALSE;
	}
	return TRUE;
}

BOOL cDrvCtrl::Open(PCHAR pLinkName)//example: \\\\.\\xxoo
{
	if (m_hDriver != INVALID_HANDLE_VALUE)
		return TRUE;
	m_hDriver = CreateFileA(pLinkName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if(m_hDriver != INVALID_HANDLE_VALUE)
		return TRUE;
	else
		return FALSE;
}

BOOL cDrvCtrl::IoControl(DWORD dwIoCode, PVOID InBuff, DWORD InBuffLen, PVOID OutBuff, DWORD OutBuffLen, DWORD *RealRetBytes)
{
	DWORD dw;
	BOOL b=DeviceIoControl(m_hDriver,CTL_CODE_GEN(dwIoCode),InBuff,InBuffLen,OutBuff,OutBuffLen,&dw,NULL);
	if(RealRetBytes)
		*RealRetBytes=dw;
	return b;
}

DWORD cDrvCtrl::CTL_CODE_GEN(DWORD lngFunction)
{
	return (FILE_DEVICE_UNKNOWN * 65536) | (FILE_ANY_ACCESS * 16384) | (lngFunction * 4) | METHOD_BUFFERED;
}
