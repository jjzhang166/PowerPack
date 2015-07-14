// Power.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Power.h"
#include "PowerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPowerApp

BEGIN_MESSAGE_MAP(CPowerApp, CWinApp)
	//{{AFX_MSG_MAP(CPowerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPowerApp construction

CPowerApp::CPowerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPowerApp object

CPowerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPowerApp initialization

BOOL CPowerApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CPowerDlg dlg;
	m_pMainWnd = &dlg;

	HINSTANCE hLib = ::LoadLibrary(_T("user32.dll"));
	if (hLib)
	{
		CPowerDlg::_SetLayeredWindowAttributes = 
			(CPowerDlg::SetTransFunction)GetProcAddress(hLib, "SetLayeredWindowAttributes");
	}
	SetDlgColor(RGB(32, 159, 194), RGB(255, 255, 255));
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CPowerApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (hLib)
	{
		::FreeLibrary(hLib);
	}
	return CWinApp::ExitInstance();
}

void CPowerApp::SetDlgColor(COLORREF bkColor, COLORREF textColor)
{
	SetDialogBkColor(bkColor, textColor);
}

