// PanelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Power.h"
#include "PanelDlg.h"
#include "PowerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPanelDlg dialog


CPanelDlg::CPanelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPanelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPanelDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	background_brush.CreateSolidBrush(RGB(255, 159, 194));
	bSlider = FALSE;
}


void CPanelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPanelDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPanelDlg, CDialog)
	//{{AFX_MSG_MAP(CPanelDlg)
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPanelDlg message handlers


void CPanelDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (!bSlider)
	{
		if (_function)
			_function(NULL);
		if (CPowerDlg::GetMainDlg())
		{
			CPowerDlg::GetMainDlg()->ShowPanel(FALSE);
			CPowerDlg::GetMainDlg()->ShowWindow(SW_HIDE);
		}
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CPanelDlg::SetTitle(LPCTSTR lpszTitle)
{
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(lpszTitle);
}

void CPanelDlg::SetFunction(PanelFunction lpfunction)
{
	_function = lpfunction;
}

CPanelDlg* CPanelDlg::CreatePanel(
	CPoint pos, CSize size,
	CPanelDlg::PanelFunction lpfunction,
	LPCTSTR lpszCaption)
{
	if (CPanelDlg* panel = new CPanelDlg)
	{
		CRect rcDlg;

		if (!lpszCaption)
			lpszCaption = _T("");
		panel->Create(CPanelDlg::IDD);
		panel->SetTitle(lpszCaption);
		panel->SetFunction(lpfunction);
		panel->ShowWindow(SW_HIDE);
		panel->SetWindowPos(
			&CWnd::wndTopMost,
			pos.x,
			pos.y,
			size.cx,
			size.cy,
			SW_HIDE);
		panel->GetClientRect(&rcDlg);
		panel->GetDlgItem(IDC_STATIC_TITLE)->MoveWindow(rcDlg, TRUE);
		return panel;
	}
	return NULL;
}

void CPanelDlg::FinishPanel(CPanelDlg *pDlg)
{
	if (pDlg)
	{
		pDlg->DestroyWindow();
		delete pDlg;
	}
}

void CPanelDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CPanelDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnMouseMove(nFlags, point);
}

void CPanelDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if (SB_THUMBTRACK == nSBCode)
		if (CPowerDlg* pMainDlg = CPowerDlg::GetMainDlg())
			pMainDlg->SetTransparent(nPos);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CPanelDlg::SetSlider()
{
	bSlider = TRUE;
}
