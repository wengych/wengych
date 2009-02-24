#if !defined(SHARINGUI_H_INCLUDE_)
#define SHARINGUI_H_INCLUDE_

#ifndef	SH_STDAFX_H
#include "sharingresid.h"
#endif

#define		SHARING_SETTINGS_BITRATE			0x01
#define		SHARING_SETTINGS_COLORDEPTH			0x02
#define		SHARING_SETTINGS_FRAMERATE			0x04

class ISharingUIEventCallback
{
public:
	
	virtual	void on_start_sharing_before() = 0; // Presenter starts sharing before sharing core is loaded
	virtual	void on_start_sharing_after() = 0;  // Presenter starts sharing after sharing code is loaded
	virtual	void on_end_sharing() = 0;			// Presenter stops sharing
	
	// Annotation evens in presenter side
	virtual	void on_start_annotation(HWND hCanvasWnd) = 0; // enter annotation mode
	virtual	void on_end_annotation() = 0; // leave annotation mode

	// Get sharing menu handle when the user clicks "sharing" button
	// please return an valid menu handle, and fill phWnd to an valid window handle to receive command
	virtual	HMENU on_get_menu(HWND *phWnd) = 0; 
	virtual	void  on_menu_cmd(UINT uCmd) = 0;

	// The menu has to be as:
	// Í£Ö¹¹²Ïí		SHARING_IDM_STOPSHARING
	// ¹²ÏíÇÐ»»
	// |---ÎÄµµ¹²Ïí SHARING_IDM_SWITCHTO_DOCSHARING
	// |---°×°å¹²Ïí	SHARING_IDM_SWITCHTO_WHITEBOARD
	// 

	// You are responsible to switch to doc sharing and whiteboard mode
	virtual void on_switchto_docsharing() = 0;	// Please switch to document sharing
	virtual void on_switchto_whiteboard() = 0;	// Please switch to whiteboard


	// Attendees receive command from presenter to enter/exit fullscreen
	// If the viewer's screen is bigger than that of the presenter, we don't show a true fullscreen window
	virtual void on_enter_fullscreen(HWND hFullscreenWnd, BOOL bTrueFullScreen) = 0;
	virtual void on_exit_fullscreen() = 0;

	virtual	BOOL on_confirm_end_sharing() = 0; // If you want to sharing stopped, please return TRUE

	// An attendee is requesting annotation. If you process this function, please return FALSE
	virtual BOOL on_request_annot_privilege(IMCC_Node_ID UserID) = 0;

	virtual	BOOL on_give_annotation() = 0; // return FALSE if you process it
	virtual	BOOL on_lose_annotation() = 0; // return FALSE if you process it

	// An attendee is requesting remote control. If you process this function, please return FALSE
	virtual BOOL on_request_control_privilege(IMCC_Node_ID UserID) = 0;

	virtual	BOOL on_give_control() = 0;	// return FALSE if you process it
	virtual	BOOL on_lose_control() = 0; // return FALSE if you process it

};

class ISharingUIMgr
{
public:
	virtual	void set_ui_event_callback(ISharingUIEventCallback *ui_event_callback) = 0;
	virtual	void set_oem_mode(DWORD OEMID) = 0;	// GNet OEMID = 1
	
	virtual	BOOL IsSharing() = 0; //Check whether sharing has already started

	virtual	BOOL ShareDesktop() = 0;  // Share the desktop
	virtual	BOOL ShareApp(HWND hWnd) = 0; // Share an application with a window handle
	virtual	BOOL ShareApp(DWORD dwProcessId) = 0; // Share an application with a process id

	virtual	void StopSharing() = 0;	 // Stop sharing
	virtual void PauseSharing() = 0; // 
	virtual	void ContinueSharing() = 0;

	virtual	void StartAnnoation() = 0;
	virtual void LeaveAnnotation() = 0;

	virtual void RequestAnnotPrivilege() = 0;

	virtual	void AssignAnnotationPrivilege(IMCC_Node_ID UserID) = 0;
	virtual void RevokeAnnotationPrivilege(IMCC_Node_ID UserID) = 0;

	virtual void RequestControlPrivilege() = 0;
	virtual void ReleaseControlPrivilege() = 0;

	virtual	void AssignControlPrivilege(IMCC_Node_ID UserID) = 0;
	virtual void RevokeControlPrivilege(IMCC_Node_ID UserID) = 0;

	virtual	void CancelDrawingMode() = 0;

	virtual void UseOemUI() = 0;

	virtual	void GetDrawingFormat(int &nPenWidth, COLORREF &crPenColor, COLORREF &crFillColor) = 0;	
	virtual	void ChangeDrawingFormat(int nPenWidth, COLORREF crPenColor, COLORREF crFillColor) = 0;

	virtual	void GetHilightColor(COLORREF &crHilightColor) = 0;
	virtual	void SetHilightColor(COLORREF crHilightColor) = 0;

	// Right now, nColorDepth is not used
	// uFlag should be set to SHARING_SETTINGS_BITRATE|SHARING_SETTINGS_FRAMERATE
	virtual	void ChangeSharingSettings(UINT uBitrate, int nColorDepth, int nFrameRate, UINT uFlag) = 0;
};

typedef BOOL	(WINAPI	 *InstallDriver_API)(int *Reserved);
typedef BOOL	(WINAPI	 *UninstallDriver_API)(int *Reserved);


/* Implementation guide

  1. sharing component interface
	 pIComEventHandler (in classcommgr.cpp, you have this interface after loading sharing module)

  2. Get ISharingUIMgr interface
	 COMPONENT_INFO *pComInfo = pIComEventHandler->GetComponentInfo();
	 MufAssert(pComInfo);
	 iSharingUIMrg = (ISharingUIMgr *)pComInfo->dwReserved;
	 MufAssert(iSharingUIMrg);
	 
	 // Then you need to immediately set the callback interface
	 iSharingUIMrg->set_ui_event_callback(Your callback interace);

	 // Then immediately call 
	 iSharingUIMrg->set_oem_mode(1) to declare GNET oem mode


  3. Start/Stop desktop sharing
	(1) Start desktop sharing
		iSharingUIMrg->ShareDesktop();

	(2) Stop sharing
		iSharingUIMrg->StopSharing();

  4. Annotation
	(1) Enter annotation mode
		iSharingUIMrg->StartAnnoation();

	(2) Leave annotation
		iSharingUIMrg->LeaveAnnoation();
	
	(3) Permit an attendee to annotate
		iSharingUIMrg->AssignAnnotationPrivilege(UserID);

	(4) Revoke annotation privilege from an attendee
		iSharingUIMrg->RevokeAnnotationPrivilege(UserID);
	
	(5) Attendee requests annotation privilege
		iSharingUIMrg->RequestAnnotPrivilege();
		The presenter will receive a callback on_request_annot_privilege(). 
		If you want to process the request by your self, please return FALSE.

    (6) Annotation mode
		First of all, you should not call this API before on_start_annotation() gets called
		
		The following annotation mode are supported
		SHARING_IDM_MARK_CHECKMARK		// Draw check mark (¹´)
		SHARING_IDM_MARK_XCHECKMARK		// Draw X check mark (²æ)
		SHARING_IDM_MARK_RIGHTPOINTER	// Draw right arrow (ÓÒ¼ýÍ·)
		SHARING_IDM_MARK_LEFTPOINTER
		SHARING_IDM_MARK_UPPOINTER
		SHARING_IDM_MARK_DOWNPOINTER
		SHARING_IDM_DRAWING_FREEHAND		// free pen
		SHARING_IDM_DRAWING_RECTANGLE		// draw rectangle with a pen without filling inside
		SHARING_IDM_DRAWING_FILLRECTANGLE	// draw a rectangle frame with a pen, fill inside with a ink
		SHARING_IDM_DRAWING_ROUNDRECTANGLE	// draw round rectangle with a pen without filling inside
		SHARING_IDM_DRAWING_FILLROUNDRECTANGLE // draw a round rectangle frame with a pen, fill inside with a ink
		SHARING_IDM_DRAWING_ELLIPSE			// draw ellipse with a pen without filling inside	
		SHARING_IDM_DRAWING_FILLELLIPSE		// draw ellipse frame with a pen, fill inside with a ink
		SHARING_IDM_DRAWING_LINE			// draw a line with a pen
		SHARING_IDM_DRAWING_LINEARROW		// draw a line with one arrow
		SHARING_IDM_DRAWING_LINEDOUBLEARROW	// draw a line with arrow in each side
		SHARING_IDM_TEXT					// Text annotation
		SHARING_IDM_HIGHLIGHT				// Hilight pen
		SHARING_IDM_SELECT_SELECT			// Select an annotation
		SHARING_IDM_SELECT_ERASER			// Delete an selected annotation
		SHARING_IDM_SELECT_ERASERALL		// Delete all annotations
		SHARING_IDM_SELECT_ERASERMYALL		// Delete my annotations
		SHARING_IDM_SELECT_ERASEROTHERS		// Delete others' annotations

		BOOL b;
		pIComEventHandler->OnWindowMessage(NULL, WM_COMMAND, CmdID, 0, b);

	 (7) Create your own annotation Toolbar
		(a) In on_start_annotation() cal back, you create your toolbar. You should create 
			a parent window for the toolbar to receive command message. And the parent
			window should be the child window of hCanvasWnd.
		(b) Then you can set annotation mode as described in section (6)
		(c) Hide or destroy your toolbar in on_end_annotation()

  5. Install/Uninstall sharing driver
	(1) Install
		Get "InstallDriver" function from cenwsharing.dll by GetProcAddress(hDLL, "InstallDriver");
		typedef BOOL	(WINAPI	 *InstallDriver_API)(int *Reserved);
		InstallDriver_API fn = (InstallDriver_API)GetProcAddress(hDLL, "InstallDriver"); 
		if (fn)
			fn(&nReserved);

		// *** NOT IMPLEMENTED
    (2) Uninstall
		Get "UninstallDriver" function from cenwsharing.dll by GetProcAddress(hDLL, "UninstallDriver");
		typedef BOOL	(WINAPI	 *UninstallDriver_API)(int *Reserved);
		UninstallDriver_API fn = (UninstallDriver_API)GetProcAddress(hDLL, "UninstallDriver"); 
		if (fn)
			fn(&nReserved);


*/


#endif SHARINGUI_H_INCLUDE_



	
	