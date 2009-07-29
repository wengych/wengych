#if !defined(AFX_SYSINFOLIST_H__3B337CE5_F9AF_4114_982D_7E52307AE13F__INCLUDED_)
#define AFX_SYSINFOLIST_H__3B337CE5_F9AF_4114_982D_7E52307AE13F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SysInfoList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSysInfoList window

class CSysInfoList : public CListCtrl
{
// Construction
public:
	CSysInfoList(){};

// Attributes
public:
	CImageList m_cImageListSmall;


public:
	//调用此函数显示信息
	void DisplayMsg(int eLevel,LPCTSTR szDisplay);

protected:
	//初始化列表头
	void InitListCtrlCols( );
	//初始化图象列表
	void InitImageList(void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysInfoList)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSysInfoList(){};

	// Generated message map functions
protected:
	//{{AFX_MSG(CSysInfoList)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSINFOLIST_H__3B337CE5_F9AF_4114_982D_7E52307AE13F__INCLUDED_)
