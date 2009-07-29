// RuiTongIVRGUI.h : main header file for the RuiTongIVRGUI application
//

#if !defined(AFX_RuiTongIVRGUI_H__7844F50E_E313_4C9F_BEA1_B85C9C98CA0C__INCLUDED_)
#define AFX_RuiTongIVRGUI_H__7844F50E_E313_4C9F_BEA1_B85C9C98CA0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRuiTongIVRGUIApp:
// See RuiTongIVRGUI.cpp for the implementation of this class
//

class CRuiTongIVRGUIApp : public CWinApp
{
public:
	CRuiTongIVRGUIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRuiTongIVRGUIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRuiTongIVRGUIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RuiTongIVRGUI_H__7844F50E_E313_4C9F_BEA1_B85C9C98CA0C__INCLUDED_)
