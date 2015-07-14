; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPowerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Power.h"

ClassCount=3
Class1=CPowerApp
Class2=CPowerDlg

ResourceCount=3
Resource2=IDD_POWER_DIALOG
Resource1=IDR_MAINFRAME
Class3=CPanelDlg
Resource3=IDD_PANEL_DIALOG

[CLS:CPowerApp]
Type=0
HeaderFile=Power.h
ImplementationFile=Power.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CPowerDlg]
Type=0
HeaderFile=PowerDlg.h
ImplementationFile=PowerDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_SLIDER1



[DLG:IDD_POWER_DIALOG]
Type=1
Class=CPowerDlg
ControlCount=0

[DLG:IDD_PANEL_DIALOG]
Type=1
Class=CPanelDlg
ControlCount=1
Control1=IDC_STATIC_TITLE,static,1342308865

[CLS:CPanelDlg]
Type=0
HeaderFile=PanelDlg.h
ImplementationFile=PanelDlg.cpp
BaseClass=CDialog
Filter=W
LastObject=IDC_STATIC_TITLE
VirtualFilter=dWC

