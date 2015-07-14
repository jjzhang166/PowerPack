
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBasic_Power
{
public:
	enum{
		LOCK,
		LOGOFF,
		REBOOT,
		POWEROFF,
		SUSPENDED,
		HIBERNATES
	};
	enum{
		lock,
		logoff,
		reboot,
		poweroff,
		suspended,
		hibernates
	};
public:
	CBasic_Power();
	~CBasic_Power();
	static BOOL Shell(UINT nCommand,BOOL bForce = TRUE);
	static UINT GetBootMode();//0 - Normal Mode    1 - Safe Mode    2 - NetSafe Mode
	static BOOL GetStatus(LPSYSTEM_POWER_STATUS lpSystemPowerStatus);
private:
	static BOOL Lock();																	//锁定
	static BOOL LogOff(BOOL bForce = TRUE);												//注销
	static BOOL Reboot(BOOL bForce = TRUE);												//重启
	static BOOL PowerOff(BOOL bForce = TRUE);												//关机
	static BOOL Suspended(BOOL bForce = TRUE);												//待机
	static BOOL Hibernates(BOOL bForce = TRUE);											//休眠
	static BOOL GetShutdownPrivileges(HANDLE &hToken,TOKEN_PRIVILEGES &uTokenPrivileges);	//获取Shutdown权限
	static BOOL GetRemoteShutdownPrivileges(HANDLE &hToken,TOKEN_PRIVILEGES &uTokenPrivileges);	//获取远程Shutdown权限
};
