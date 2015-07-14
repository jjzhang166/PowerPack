// PowerDlg.h : header file
//

#if !defined(AFX_POWERDLG_H__863C2841_6749_4C20_9EC6_B2D41783B047__INCLUDED_)
#define AFX_POWERDLG_H__863C2841_6749_4C20_9EC6_B2D41783B047__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PanelDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CPowerDlg dialog

#ifndef WS_EX_LAYERED //需要为窗体添加WS_EX_LAYERED属性
	#define WS_EX_LAYERED 0x80000
	#define LWA_COLORKEY 	0x1	//Use crKey as the transparency color. 
	#define LWA_ALPHA 	0x2	//Use bAlpha to determine the opacity of the layered window.
#endif

#define PWRDLG_BKCLR		RGB(0,0,0)	//背景颜色
#define PWRDLG_ALPHA		150	//默认窗口透明度
#define PWRDLG_TIMERPERIOD	300

#define SuspendTime(_min) (60000*(_min))
#define IsTimer(_x) (nIDEvent == (_x))

class CPowerDlg : public CDialog
{
public:
typedef list<CPanelDlg*> PanelDlgList;
typedef BOOL (WINAPI * SetTransFunction)(HWND, COLORREF, BYTE, DWORD);
	static SetTransFunction _SetLayeredWindowAttributes;
// list
private:
	CFont tipFont;
	CSize scr_size;
	CBrush background_brush;
	PanelDlgList panel_list;
	CPanelDlg* sliderDlg;
	UINT save_alpha;
	BOOL presuspend;
	static CPowerDlg* s_pMainDlg;
// User define
public:
	enum {InputTimer = 11011, SuspendTimer = 12011};

	BOOL ShowPanel(BOOL bShow);
	CPanelDlg* AddPanel(CPoint pos, CSize size, CPanelDlg::PanelFunction lpfunction = NULL, LPCTSTR lpszCaption = NULL);
	BOOL OnMostBottomRight(void);
	BOOL SetTransparent(UINT alpha);
	void RemoveAllPanel(void);
	BOOL HaveScreenWindow();
	BOOL ShowWindow(int nCmdShow);
	BOOL LoadSave(BOOL bLoad);
	static CPowerDlg* GetMainDlg();
	static BOOL IsGame(HWND hWnd);
	static void OnAlwayForAWhile(LPVOID lpParam);
	static void OnAlwayToHaveLunch(LPVOID lpParam);
	static void OnAlwayForBusy(LPVOID lpParam);

private:
	BOOL PrepareDialog();

// Construction
public:
	CPowerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPowerDlg)
	enum { IDD = IDD_POWER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPowerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPowerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnNcPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POWERDLG_H__863C2841_6749_4C20_9EC6_B2D41783B047__INCLUDED_)
