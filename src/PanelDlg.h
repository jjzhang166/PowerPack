#if !defined(AFX_PANELDLG_H__670CE87A_5E7F_4ADD_B826_AE88BF477011__INCLUDED_)
#define AFX_PANELDLG_H__670CE87A_5E7F_4ADD_B826_AE88BF477011__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PanelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPanelDlg dialog

class CPanelDlg : public CDialog
{
public:
	typedef void (*PanelFunction)(LPVOID lpParam);
private:
	BOOL bSlider;
	CBrush background_brush;
	PanelFunction _function;
public:
	void SetTitle(LPCTSTR lpszTitle);
	void SetFunction(PanelFunction lpfunction);
	static CPanelDlg* CreatePanel(CPoint pos, CSize size, CPanelDlg::PanelFunction lpfunction = NULL, LPCTSTR lpszCaption = NULL);
	static void FinishPanel(CPanelDlg* pDlg);

// Construction
public:
	void SetSlider();
	CPanelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPanelDlg)
	enum { IDD = IDD_PANEL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPanelDlg)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANELDLG_H__670CE87A_5E7F_4ADD_B826_AE88BF477011__INCLUDED_)
