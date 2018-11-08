#include "../include/common.h"
#include <windef.h>
#include <winsvc.h> 
#include <winbase.h> 
#include <stdio.h> 

#define NO_ERR 		0
#define ERR_SCM 	1
#define ERR_SVC_CREATE	2
#define ERR_SVC_OPEN	3
#define ERR_SVC_START	4

SC_HANDLE scm = NULL;
SC_HANDLE service = NULL;

int err = NO_ERR;

int lasterr = 0;

int main(int argc, char *argv[])
{
scm = OpenSCManager(
  NULL,//LOCAL PC
  NULL,//DUMMY
  SC_MANAGER_ALL_ACCESS);//MAX
if (!scm) 
{
  lasterr = GetLastError();
  printf("["DRVNAME"]: cannot open SCM: %d\n",lasterr);
  err = ERR_SCM;
  goto err_scm;
}
service = CreateService(
  scm,
  DRVNAME,
  "["DRVNAME"]",
  SERVICE_ALL_ACCESS,//MAX
  SERVICE_KERNEL_DRIVER,
  SERVICE_DEMAND_START,
  SERVICE_ERROR_NORMAL,
  //driverpath,
  (LPCSTR)L"TEST",
  NULL,//no load group
  NULL,//no tag
  NULL,//no deps
  NULL,//def obj name
  NULL);//ignored pwd
if (!service)
{
  lasterr = GetLastError(); 
  if (lasterr != ERROR_SERVICE_EXISTS) 
  {
    printf("["DRVNAME"]: cannot create SVC: %d\n",lasterr);
    err = ERR_SVC_CREATE;
    goto err_svc_create;
  }
  else 
  {
    service = OpenService(
      scm,
      DRVNAME,
      SERVICE_ALL_ACCESS);
    if (!service) 
    {
      lasterr = GetLastError();
      printf("["DRVNAME"]: cannot open SCM: %d\n",lasterr);
      err = ERR_SVC_OPEN;
      goto err_svc_open;
    } 
  }
}
printf("["DRVNAME"]: service successfully created\n");
if(!StartServiceA(
  service,
  0,//num of args
  NULL))//args
{
  lasterr = GetLastError();
  printf("["DRVNAME"]: cannot start driver: %d\n",lasterr);
  err = ERR_SVC_START;
  goto err_svc_start;
}

//FINALIZE
err_svc_start:
  DeleteService(service);
err_svc_create:
err_svc_open:
  CloseServiceHandle(scm);
err_scm:
quit:
  return err;
 }

/*////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
  SERVICE_STATUS ss;
  if (!ControlService(m_hService,SERVICE_CONTROL_STOP,&ss))
  {
    m_dwLastError = GetLastError();
    return FALSE;
  }
  return TRUE;


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
*/
