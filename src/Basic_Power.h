
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
	static BOOL Lock();																	//����
	static BOOL LogOff(BOOL bForce = TRUE);												//ע��
	static BOOL Reboot(BOOL bForce = TRUE);												//����
	static BOOL PowerOff(BOOL bForce = TRUE);												//�ػ�
	static BOOL Suspended(BOOL bForce = TRUE);												//����
	static BOOL Hibernates(BOOL bForce = TRUE);											//����
	static BOOL GetShutdownPrivileges(HANDLE &hToken,TOKEN_PRIVILEGES &uTokenPrivileges);	//��ȡShutdownȨ��
	static BOOL GetRemoteShutdownPrivileges(HANDLE &hToken,TOKEN_PRIVILEGES &uTokenPrivileges);	//��ȡԶ��ShutdownȨ��
};
