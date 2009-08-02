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
#include "MainProc.h"

#include "TinyXmlHelper.hpp"
// using namespace helper;

#include <map>

#ifndef WM_APP_WRITE_DATA 
#define WM_APP_WRITE_DATA  (0x0400+1001)
#endif

#define IDC_EDIT_CHANNEL_STATUS (WM_USER + 1400)
#define IDC_BTN_CHANNEL (WM_USER + 1500)

//œ»–¥À¿
#define CHANNEL_EDIT_ID_TO_INDEX 1
#define CHANNEL_BUTTON_ID_TO_INDEX 2


// #define  CHANNEL_CTR_ID_TO_INDEX(control_id,arr_index)\
//     switch (control_id)\
//     {\
//     case IDC_EDIT_CHANNEL_STATUS:\
//         arr_index = 1;\
//         break;\
//     case IDC_BTN_CHANNEL:\
//         arr_index = 2;\
//     	break;\
//   }

struct GroupControl {
    CWnd* ctrl;
    int width;
    int height;

    GroupControl() : ctrl(NULL), width(0), height(0) {}
    GroupControl(const GroupControl& rhs) : ctrl(rhs.ctrl), width(rhs.width), height(rhs.height) {}
};

typedef std::vector<GroupControl> GroupControlsArray;
typedef std::vector<GroupControlsArray> ArrayOfGroupControlsArray;

typedef std::map<std::string ,int> ChannelArrayMap;
typedef std::map<UINT, std::string> ButtonChannelMap;

typedef std::vector<ProcessInfo> ProcessInfoArray;

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
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	//}}AFX_VIRTUAL

// Implementation
protected:
    void AddCtrlsToGroup(int group_id, ArrayOfGroupControlsArray&);
    void InitChannelGroupControls(ArrayOfGroupControlsArray&, const helper::PairSet& );

    void OnButtonChannelClick(int);
    void OnButtonChannelStop(int);
    void OnButtonChannelStart(int);

    void CloseAll();
    bool StartDriver();
    void ActiveCheck();

    
    void UpdateStartDriverBtn();
    bool InitSysEnv();

    HICON m_hIcon;
    ArrayOfGroupControlsArray channel_ctrls_arr_arr;
    ChannelArrayMap channel_array_map;

private:
	CMemMsg m_memMsg;
    ProcessInfoArray app_processes;
    ProcessInfo driver_process;
    helper::PairSet channel_config;

public:
	// Generated message map functions
	//{{AFX_MSG(CRuiTongIVRGUIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSysQuit();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButtonRestartMonitor();
    afx_msg void OnBnClickedBtnStartDriver();
    void OnMsgAppWriteData();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUBATCHPAYFRONTDLG_H__F4C63221_CF83_426E_ADB7_9DFE8DBC69AB__INCLUDED_)
