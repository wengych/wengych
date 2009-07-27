// RuiTongIVRGUIDlg.h : header file
//

#if !defined(AFX_CUBATCHPAYFRONTDLG_H__F4C63221_CF83_426E_ADB7_9DFE8DBC69AB__INCLUDED_)
#define AFX_CUBATCHPAYFRONTDLG_H__F4C63221_CF83_426E_ADB7_9DFE8DBC69AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRuiTongIVRGUIDlg dialog
#include "SysInfoList.h"
#include "IVRInfoList.h"
#include "Message.h"

#ifndef WM_APP_WRITE_DATA 
#define WM_APP_WRITE_DATA  (0x0400+1001)
#endif

#define IDC_EDIT_CHANNEL_STATUS (WM_USER + 1400)
#define IDC_BTN_CHANNEL (WM_USER + 1500)

struct GroupControl {
    CWnd* ctrl;
    int width;
    int height;

    GroupControl() : ctrl(NULL), width(0), height(0) {}
    GroupControl(const GroupControl& rhs) : ctrl(rhs.ctrl), width(rhs.width), height(rhs.height) {}
};

typedef std::vector<GroupControl> GroupControlsArray;
typedef std::vector<GroupControlsArray> ArrayOfGroupControlsArray;

class CRuiTongIVRGUIDlg : public CDialog
{
// Construction
public:
	CRuiTongIVRGUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRuiTongIVRGUIDlg)
	enum { IDD = IDD_RuiTongIVRGUI_DIALOG };
	//CEdit	m_txtLinking;
	CEdit	m_txtState;
	CIVRInfoList	m_listSysRunInfo;
	CSysInfoList	m_listSysErrInfo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRuiTongIVRGUIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT CRuiTongIVRGUIDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	//}}AFX_VIRTUAL

// Implementation
protected:
    void AddCtrlsToGroup(int group_id, ArrayOfGroupControlsArray&);
    void InitChannelGroupControls(ArrayOfGroupControlsArray&);
	HICON m_hIcon;

private:
	CMemMsg m_memMsg;

public:
	// Generated message map functions
	//{{AFX_MSG(CRuiTongIVRGUIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSysRun();
	afx_msg void OnButtonSysPause();
	afx_msg void OnButtonSysStop();
	afx_msg void OnButtonSysQuit();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButtonRestartMonitor();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUBATCHPAYFRONTDLG_H__F4C63221_CF83_426E_ADB7_9DFE8DBC69AB__INCLUDED_)
