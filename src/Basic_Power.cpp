
#include "StdAfx.h"
#include "Basic_Power.h"

CBasic_Power::CBasic_Power()
{
}

CBasic_Power::~CBasic_Power()
{
}

BOOL CBasic_Power::Shell(UINT nCommand,BOOL bForce)
{
	switch(nCommand){
	case CBasic_Power::LOCK:
		return Lock();
	case CBasic_Power::LOGOFF:
		return LogOff(bForce);
	case CBasic_Power::REBOOT:
		return Reboot(bForce);
	case CBasic_Power::POWEROFF:
		return PowerOff(bForce);
	case CBasic_Power::SUSPENDED:
		return Suspended(bForce);
	case CBasic_Power::HIBERNATES:
		return Hibernates(bForce);
	default:
		return FALSE;
	};
}

UINT CBasic_Power::GetBootMode()
{
	return ::GetSystemMetrics(SM_CLEANBOOT);
}

BOOL CBasic_Power::GetStatus(LPSYSTEM_POWER_STATUS lpSystemPowerStatus)
{
	if (!lpSystemPowerStatus){
		return FALSE;
	}
	return ::GetSystemPowerStatus(lpSystemPowerStatus);
}

BOOL CBasic_Power::GetShutdownPrivileges(HANDLE &hToken,TOKEN_PRIVILEGES &uTokenPrivileges)
{
	if (!::OpenProcessToken(::GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &hToken)){
		return FALSE;
	}
	::LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &uTokenPrivileges.Privileges->Luid);
	uTokenPrivileges.PrivilegeCount = 0x1;
	uTokenPrivileges.Privileges->Attributes = SE_PRIVILEGE_ENABLED;
	::AdjustTokenPrivileges(hToken, FALSE, &uTokenPrivileges, 0x0, NULL, NULL);
	if (ERROR_SUCCESS != ::GetLastError()){
		return FALSE;
	}
	return TRUE;
}

BOOL CBasic_Power::GetRemoteShutdownPrivileges(HANDLE &hToken,TOKEN_PRIVILEGES &uTokenPrivileges)
{
	if (!::OpenProcessToken(::GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &hToken)){
		return FALSE;
	}
	::LookupPrivilegeValue(NULL, SE_REMOTE_SHUTDOWN_NAME, &uTokenPrivileges.Privileges->Luid);
	uTokenPrivileges.PrivilegeCount = 0x1;
	uTokenPrivileges.Privileges->Attributes = SE_PRIVILEGE_ENABLED;
	::AdjustTokenPrivileges(hToken, FALSE, &uTokenPrivileges, 0x0, NULL, NULL);
	if (ERROR_SUCCESS != ::GetLastError()){
		return FALSE;
	}
	return TRUE;
}

BOOL CBasic_Power::Lock()
{
	typedef BOOL (WINAPI *LPLOCKWORKSTATION)(void);
	HMODULE hModule = ::LoadLibrary(TEXT("User32.dll"));
	if (!hModule){
		return FALSE;
	}
	LPLOCKWORKSTATION LockWorkStation = (LPLOCKWORKSTATION)::GetProcAddress(hModule, TEXT("LockWorkStation"));
	if (!LockWorkStation){
		::FreeLibrary(hModule);
		return FALSE;
	}
	BOOL bRet = LockWorkStation();
	::FreeLibrary(hModule);
	return bRet;
}

BOOL CBasic_Power::LogOff(BOOL bForce)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES uTokenPrivileges;
	if (!GetShutdownPrivileges(hToken, uTokenPrivileges)){
		return FALSE;
	}
	UINT nExitCmd = EWX_LOGOFF;
	if (bForce){
		nExitCmd |= EWX_FORCE;
	}
	if (!::ExitWindowsEx(nExitCmd,0x0)){
		return FALSE;
	}
	return TRUE;
}

BOOL CBasic_Power::Reboot(BOOL bForce)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES uTokenPrivileges;
	if (!GetShutdownPrivileges(hToken, uTokenPrivileges)){
		return FALSE;
	}
	UINT nExitCmd = EWX_REBOOT;
	if (bForce){
		nExitCmd |= EWX_FORCE;
	}
	if (!::ExitWindowsEx(nExitCmd,0x0)){
		return FALSE;
	}
	return TRUE;
}

BOOL CBasic_Power::PowerOff(BOOL bForce)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES uTokenPrivileges;
	if (!GetShutdownPrivileges(hToken, uTokenPrivileges)){
		return FALSE;
	}
	UINT nExitCmd = EWX_POWEROFF;
	if (bForce){
		nExitCmd |= EWX_FORCE;
	}
	if (!::ExitWindowsEx(nExitCmd,0x0)){
		return FALSE;
	}
	return TRUE;
}

BOOL CBasic_Power::Suspended(BOOL bForce)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES uTokenPrivileges;
	if (!GetShutdownPrivileges(hToken, uTokenPrivileges)){
		return FALSE;
	}
	return ::SetSystemPowerState(TRUE,bForce);
}

BOOL CBasic_Power::Hibernates(BOOL bForce)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES uTokenPrivileges;
	if (!GetShutdownPrivileges(hToken, uTokenPrivileges)){
		return FALSE;
	}
	return ::SetSystemPowerState(FALSE,bForce);
}
