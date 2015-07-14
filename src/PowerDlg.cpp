// PowerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Power.h"
#include "PowerDlg.h"
#include "PowerControl.h"
#include <TLHELP32.H>

/////////////////////////////////////////////////////////////////////////////
// CPowerDlg dialog

#define FONT_ERROR_STRING _T("����ϵͳ��δ��װ���壺΢���ź�\n����Ҫ���ڰ�װ�𣿷����˳�������")

CPowerDlg* CPowerDlg::s_pMainDlg = NULL;
CPowerDlg::SetTransFunction CPowerDlg::_SetLayeredWindowAttributes = NULL;

CPowerDlg::CPowerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPowerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPowerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	sliderDlg = NULL;
	presuspend = FALSE;
	CPowerDlg::s_pMainDlg = this;
	background_brush.CreateSolidBrush(PWRDLG_BKCLR);
	scr_size.cx = ::GetSystemMetrics(SM_CXSCREEN);
	scr_size.cy = ::GetSystemMetrics(SM_CYSCREEN);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_MAINICON);
}

void CPowerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPowerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPowerDlg, CDialog)
	//{{AFX_MSG_MAP(CPowerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_CLOSE()
	ON_WM_RBUTTONUP()
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPowerDlg message handlers

BOOL CPowerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	return PrepareDialog();  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPowerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect rcWnd;
		CClientDC dc(this);
		GetClientRect(&rcWnd);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(255, 255, 255));
		dc.SelectObject(&tipFont);
		dc.SelectObject(&background_brush);
		dc.Rectangle(&rcWnd);
		dc.DrawText(_T("��������������Ҽ��˳�������"),
			CRect(scr_size.cx - 300, scr_size.cy - 30, scr_size.cx, scr_size.cy),
			DT_CENTER|DT_VCENTER);
		CDialog::OnPaint();
	}
}

void CPowerDlg::OnNcPaint() 
{
	// TODO: Add your message handler code here
	static BOOL s_init = true;
	// �״���ʾ�Ի���ʱ��ѡ�����ظöԻ���
	if (s_init)
	{
		s_init = FALSE;
		ShowWindow(SW_HIDE);
	}
	else
		CDialog::OnNcPaint();
	// Do not call CDialog::OnNcPaint() for painting messages
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPowerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPowerDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ShowPanel(FALSE);
	ShowWindow(SW_HIDE);
	CDialog::OnLButtonUp(nFlags, point);
}

void CPowerDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SendMessage(WM_CLOSE);
	CDialog::OnRButtonUp(nFlags, point);
}

void CPowerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	static bool s_timer_lock = false;
	static CPoint s_last_pos(0, 0);
	if (IsTimer(InputTimer) && !HaveScreenWindow())
	{
		if (!s_timer_lock)
		{
			CPoint cur_pos;
			
			s_timer_lock = true;
			GetCursorPos(&cur_pos);

			if (presuspend && 
				s_last_pos.x != cur_pos.x &&
				s_last_pos.y != cur_pos.y )
			{
				presuspend = FALSE;
				KillTimer(SuspendTimer);
			}
			
			s_last_pos = cur_pos;
			if (cur_pos.x + 1 >= scr_size.cx &&
				cur_pos.y + 1 >= scr_size.cy )
			{
				OnMostBottomRight();
			}
			s_timer_lock = false;
		}
	}
	else if (IsTimer(SuspendTimer))
	{
		CPowerControl::Shell(CPowerControl::suspended);
	}
	CDialog::OnTimer(nIDEvent);
}

BOOL CPowerDlg::PrepareDialog()
{
	// �������
	if (!tipFont.CreatePointFont(100, _T("΢���ź�")))
	{
		if (IDYES == AfxMessageBox(FONT_ERROR_STRING, MB_YESNO))
		{
			STARTUPINFO si = {0};
			PROCESS_INFORMATION pi = {0};
			si.cb = sizeof(si);
			//��װ����
			if (!CreateProcess(
				NULL, _T("vista_font.exe"), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
			{
				//���尲װʧ��
				AfxMessageBox(_T("��Ǹ�����尲װʧ�ܣ����򼴽��˳���"));
				ExitProcess(0);
			}
			else
			{
				WaitForSingleObject(pi.hProcess, INFINITE);	//�ȴ����尲װ���
				DeleteFile(_T("vista_font.exe"));//ɾ�����尲װ�ļ�
			}
		}
		else
			ExitProcess(0);
	}
	// ��������
	if (!LoadSave(TRUE))
	{
		AfxMessageBox(_T("Load error"));
		return FALSE;
	}
	// ��������
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW, SWP_DRAWFRAME);
	LONG lWndLong = GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE);
	if (!(lWndLong & WS_EX_LAYERED))
		SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, lWndLong|WS_EX_LAYERED);
	// ǰ�ô���
	SetForegroundWindow();
	// ������ʱ��
	SetTimer(CPowerDlg::InputTimer, PWRDLG_TIMERPERIOD, NULL);
	ShowWindow(SW_HIDE);	//���ش���
	ModifyStyle(WS_VISIBLE, 0, SWP_HIDEWINDOW);
	SetTransparent(save_alpha);	//����͸��
	// ���Panel���뿪һ�ᣬ�Է������ţ�
	AddPanel(CPoint(scr_size.cx - 250, scr_size.cy - 100*1 - 50), CSize(200, 100), OnAlwayForBusy, _T("���ž���"));
	AddPanel(CPoint(scr_size.cx - 250, scr_size.cy - 100*2 - 50 - 20), CSize(200, 100), OnAlwayForAWhile, _T("�뿪һ��"));
	AddPanel(CPoint(scr_size.cx - 250, scr_size.cy - 100*3 - 50 - 40), CSize(200, 100), OnAlwayToHaveLunch, _T("�Է�ȥ��"));
	// ��ӻ���Panel������Alphaֵ��
	if (sliderDlg = AddPanel(CPoint(scr_size.cx - 250, scr_size.cy - 100*4 - 25), CSize(200, 25)))
	{
		CRect rcSlider;
		CSliderCtrl* slider = new CSliderCtrl;
		
		sliderDlg->GetClientRect(&rcSlider);
		slider->Create(TBS_HORZ|TBS_NOTICKS, rcSlider, sliderDlg, IDC_SLIDER_ALPHA);
		slider->ShowWindow(SW_SHOW);
		slider->SetRange(0, 255);
		slider->SetPos(save_alpha);
		sliderDlg->SetSlider();
	}
	return TRUE;
}

BOOL CPowerDlg::OnMostBottomRight()
{
	ShowWindow(SW_SHOWMAXIMIZED);
	ShowPanel(TRUE);
	return TRUE;
}

BOOL CPowerDlg::ShowWindow(int nCmdShow)
{
	return CDialog::ShowWindow(nCmdShow);
}

BOOL CPowerDlg::SetTransparent(UINT alpha)
{
	save_alpha = alpha;
	if (_SetLayeredWindowAttributes)
		return _SetLayeredWindowAttributes(GetSafeHwnd(), 0, (BYTE)alpha, LWA_ALPHA);
	return FALSE;
}

CPowerDlg* CPowerDlg::GetMainDlg()
{
	return s_pMainDlg;
}

#define PWRDLG_ISGAME_OPENGL_ID		_T("GLUT.DLL")
#define PWRDLG_ISGAME_DIRECTX_ID	_T("D3D8THK.DLL")

BOOL CPowerDlg::IsGame(HWND hWnd)
{
	DWORD dwProcessId;
	GetWindowThreadProcessId(hWnd, &dwProcessId);
	HANDLE hSnapshot = 
		CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
	if (INVALID_HANDLE_VALUE == hSnapshot || !hSnapshot)
		return NULL;

	BOOL bSnap;
	MODULEENTRY32 modEntry;	
	modEntry.dwSize = sizeof(MODULEENTRY32);
	for (bSnap = Module32First(hSnapshot, &modEntry);bSnap;
		bSnap = Module32Next(hSnapshot, &modEntry)){
		_tcsupr(modEntry.szModule);
		if (!_tcscmp(modEntry.szModule, PWRDLG_ISGAME_DIRECTX_ID) ||
			!_tcscmp(modEntry.szModule, PWRDLG_ISGAME_OPENGL_ID) ){
			CloseHandle(hSnapshot);
			return TRUE;
		}
	}
	CloseHandle(hSnapshot);
	return FALSE;
}

BOOL CPowerDlg::HaveScreenWindow()
{
	static HWND s_lastWnd = NULL;
	static BOOL s_lastResult = FALSE;

	if (HWND hWnd = ::GetForegroundWindow())
	{
		if (hWnd == s_lastWnd)
			return s_lastResult;
		else
			s_lastWnd = hWnd;

		s_lastResult = IsGame(hWnd)? TRUE: FALSE;
	}
	return FALSE;
}

CPanelDlg* CPowerDlg::AddPanel(CPoint pos, CSize size, CPanelDlg::PanelFunction lpfunction, LPCTSTR lpszCaption)
{
	if (CPanelDlg* panel = CPanelDlg::CreatePanel(
			pos, size, lpfunction, lpszCaption))
	{
		panel_list.push_back(panel);
		return panel;
	}
	return NULL;
}

BOOL CPowerDlg::ShowPanel(BOOL bShow)
{
	PanelDlgList::iterator itr;
	int nCmdShow = bShow? SW_SHOW: SW_HIDE;
	for (itr = panel_list.begin(); itr != panel_list.end(); itr++)
	{
		(*itr)->ShowWindow(nCmdShow);
	}
	return TRUE;
}

void CPowerDlg::RemoveAllPanel()
{
	PanelDlgList::iterator itr;
	for (itr = panel_list.begin(); itr != panel_list.end(); itr++)
	{
		CPanelDlg::FinishPanel(*itr);
	}
	panel_list.clear();
}

void CPowerDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	RemoveAllPanel();
	LoadSave(FALSE);
	CDialog::OnClose();
}

BOOL CPowerDlg::LoadSave(BOOL bLoad)
{
	if (bLoad)
	{
		save_alpha = ::GetPrivateProfileInt(_T("UI"), _T("alpha"), 1000, _T("pwrconfig.ini"));
		if (1000 == save_alpha)
		{
			CString fmt;
			save_alpha = PWRDLG_ALPHA;
			fmt.Format(_T("%u"), PWRDLG_ALPHA);
			::WritePrivateProfileString(_T("UI"), _T("alpha"), fmt, _T("pwrconfig.ini"));
		}
		SetTransparent(save_alpha);
	}
	else
	{
		CString fmt;
		fmt.Format(_T("%u"), save_alpha);
		::WritePrivateProfileString(_T("UI"), _T("alpha"), fmt, _T("pwrconfig.ini"));
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
///// Panel Handler

void CPowerDlg::OnAlwayForBusy(LPVOID lpParam)
{
	CPowerControl::Shell(CPowerControl::lock);// ���������
	Sleep(2000);	//����2�� �ȴ��û���ȫ�뿪�������
	// �ر���ʾ��
	::SendMessage(
		AfxGetMainWnd()->GetSafeHwnd(),
		WM_SYSCOMMAND,
		SC_MONITORPOWER,
		2);
}

void CPowerDlg::OnAlwayForAWhile(LPVOID lpParam)
{
	CPowerControl::Shell(CPowerControl::lock);// ���������
	Sleep(2000);	//����2�� �ȴ��û���ȫ�뿪�������
	// �ر���ʾ��
	::SendMessage(
		AfxGetMainWnd()->GetSafeHwnd(),
		WM_SYSCOMMAND,
		SC_MONITORPOWER,
		2);
	CPowerDlg::GetMainDlg()->presuspend = TRUE;//Ԥ������ָʾ��Ҫ����
	CPowerDlg::GetMainDlg()->SetTimer(SuspendTimer, SuspendTime(15), NULL);//15���Ӻ����
}

void CPowerDlg::OnAlwayToHaveLunch(LPVOID lpParam)
{
	CPowerControl::Shell(CPowerControl::lock);// ���������
	Sleep(2000);	//����2�� �ȴ��û���ȫ�뿪�������
	// �ر���ʾ��
	::SendMessage(
		AfxGetMainWnd()->GetSafeHwnd(),
		WM_SYSCOMMAND,
		SC_MONITORPOWER,
		2);
	CPowerControl::Shell(CPowerControl::suspended);//ֱ�Ӵ���
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////





