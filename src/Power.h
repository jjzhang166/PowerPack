// Power.h : main header file for the POWER application
//

#if !defined(AFX_POWER_H__23C7E446_AC7A_4D6F_970C_8A59BF022AAB__INCLUDED_)
#define AFX_POWER_H__23C7E446_AC7A_4D6F_970C_8A59BF022AAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPowerApp:
// See Power.cpp for the implementation of this class
//

class CPowerApp : public CWinApp
{
public:
	HINSTANCE hLib;
	void SetDlgColor(COLORREF bkColor, COLORREF textColor);
	CPowerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPowerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPowerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POWER_H__23C7E446_AC7A_4D6F_970C_8A59BF022AAB__INCLUDED_)
