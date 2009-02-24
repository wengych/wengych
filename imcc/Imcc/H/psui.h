#if !defined(PSUI_H_INCLUDE_)
#define PSUI_H_INCLUDE_

#ifndef	PSRESID_H_INCLUDE
	#include "psresid.h"
	//#ifndef	PS_STDAFX_H
	//#include "imccappid.h"
#endif

#ifndef PSDOCDEF_H_INCLUDE	// prevent duplicated definition

typedef	DWORD	psID;
typedef DWORD	psOffset;
#define	psNullID	(psID)(0)
#define psNullOffset (psOffset)(-1)

#define PS_VIEWMODE_BYAPP		0x00
#define PS_VIEWMODE_ACTUALSIZE	0x01
#define PS_VIEWMODE_FITPAGE		0x02
#define PS_VIEWMODE_FITWIDTH	0x03
#define PS_VIEWMODE_FITVISIBLE	0x04
#define PS_VIEWMODE_ZOOM25		0x05
#define PS_VIEWMODE_ZOOM50		0x06
#define PS_VIEWMODE_ZOOM75		0x07
#define PS_VIEWMODE_ZOOM125		0x08
#define PS_VIEWMODE_ZOOM150		0x09
#define PS_VIEWMODE_ZOOM200		0x0a	
#define PS_VIEWMODE_ZOOM300		0x0b
#define PS_VIEWMODE_ZOOM400		0x0c
#define PS_VIEWMODE_ZOOM500		0x0d
#define PS_VIEWMODE_ZOOM800		0x0e
#define PS_VIEWMODE_ZOOMPERCENT	0x0f

#define PS_VIEWMODE_FULLSCREEN	0x80

#define	 ZOOM_ASPERCENT		PS_VIEWMODE_ZOOMPERCENT
#define	 ZOOM_ACTUALSIZE	PS_VIEWMODE_ACTUALSIZE
#define	 ZOOM_FITVISIBLE	PS_VIEWMODE_FITVISIBLE
#define	 ZOOM_FITPAGE		PS_VIEWMODE_FITPAGE
#define	 ZOOM_FITWIDTH		PS_VIEWMODE_FITWIDTH

#define	 ZOOM_FACTOR_BASE	100

typedef struct tagpsZoomInfo
{
	UINT	nZoomType;
	int		nPercent;
}psZoomInfo;

enum E_DOCTYPE
{
	TYPE_PS_DOC    = 0,
	TYPE_PS_PPTDOC = 1,
	TYPE_PS_WORDDOC = 2,
	TYPE_PS_EXCELDOC = 3,
	TYPE_PS_NOANIMPPTDOC = 3,
};

typedef	int		psCoord;

typedef struct tagpsSize
{
	psCoord	cx;
	psCoord	cy;
}psSize;

typedef struct tagpsPoint
{
	psCoord	x;
	psCoord	y;
}psPoint;

typedef struct tagpsPointRatio
{
	double x;
	double y;
}psPointRatio;

typedef struct tagpsRect
{
	psCoord	left;
	psCoord	top;
	psCoord	right;
	psCoord	bottom;
}psRect;


#endif

class IPsDoc;

class IPsPage
{
public:
	virtual psID	GetPageID() = 0;
	virtual int		GetPageNo() = 0;

	virtual IPsDoc * GetIDoc() = 0;
};

class IPsDoc
{
public:
	virtual WORD	GetDocType() = 0;	// PPT document, it returns TYPE_PS_PPTDOC or TYPE_PS_NOANIMPPTDOC. Otherwise, TYPE_PS_DOC
	virtual psID	GetDocID() = 0;		// Document ID
	virtual LPSTR	GetDocTitle() = 0;	// Document title
	
	virtual BOOL	IsDocDirty() = 0;   // Is document changed after last save?
	virtual BOOL	Save() = 0;			// Save the document
	virtual BOOL	SaveAs(LPCSTR lpszFile) = 0;			// Save the document

	virtual int		GetPageNum() = 0;	// Number of pages of the documents

	virtual	psID	GetCurrentPageID() = 0; // The current page of this document
	virtual	int		GetCurrentPageNo() = 0; // The current page of this document
	virtual	int		GetPageNoByID(psID PageID) = 0;
	virtual	psID	GetPageIDByNo(int n) = 0;

	virtual void *  SetCurrentPageByID(psID PageID, BOOL update_remote) = 0;
	virtual void *  SetCurrentPageByNo(int n, BOOL update_remote) = 0;

	virtual	IPsPage *GetIPageByID(psID PageID) = 0;
	virtual	IPsPage *GetIPageByNo(int n) = 0;
	
	virtual	BOOL	GetPageTitleByNo(int n, LPSTR lpszTitle, int nCharSize) = 0;  // nCharSize should be large enough, for example 256
	virtual	BOOL	GetPageTitleByNo(int n, LPWSTR lpszTitle, int nCharSize) = 0; // nCharSize should be large enough, for example 256

	virtual	BOOL	IsCreator() = 0; //Is the document created from this computer?
};


class IPsUIEventCallback
{
public:
	/*
		注意 IPsUIEventCallback与IPsUIMgr进入死循环。比如说，你通过IPsUIMgr上发出一个要求换页
		的请求。你会同步收到on_page_change_after()。如果你的程序在on_page_change_after里面
		更新UI的状态（你肯定会那么做的，比如说文档的页列表，你要显示当前页面），你的程序在
		响应UI变化时（比如页列表的current item changes)，你可能又会调用IPsUIMgr去试图change 当前页。
		这样就进入死循环了。你的程序应该避免这种情况。
	*/
	
	// 换当前页
	virtual	void on_page_change_before(IPsPage *pPage) = 0; // this one is not used
	virtual	void on_page_change_after(IPsPage *pPage) = 0;
	
	// 换当前文档
	virtual	void on_doc_change_before(IPsDoc *pDoc) = 0;  // this one is not used
	virtual	void on_doc_change_after(IPsDoc *pDoc) = 0;

	// 用户的权限发送了变化。这个通常导致UI上的变化，比如有些button要disable。
	// Please call HasChangePagePrivilege() etc functions to determine privilege.
	// Don't decompose NewPrivilege directly
	virtual void on_privilege_change(DWORD OldPrivilege, DWORD NewPrivilege) = 0;

	// Presenter has changed, you need to update UI status with checking privilege
	// Please call HasChangePagePrivilege() etc functions to determine privilege.
	virtual void on_presenter_change(IMCC_Node_ID FromWhom, IMCC_Node_ID ToWhom) = 0;


	// Attendees receive command from presenter to enter/exit fullscreen
	// If the presenter click fullscreen button, on_enter_fullscreen still will be triggered.
	virtual void on_enter_fullscreen(HWND hFullscreenWnd) = 0;
	virtual void on_exit_fullscreen() = 0;

	// When the attendee receives command from the presenter to change zoom
	// Sees the definitions of ZOOM_xxx in this H file
	// nPercent is used when ZoomType is ZOOM_ASPERCENT
	// pDoc: The zoom info is applied to which document.
	//
	// Yo usually don't need to process this callback.
	virtual	void on_zoom_change(IPsDoc *pDoc, UINT ZoomType, int nPercent) = 0;

	// A new page is added
	virtual void on_add_page(IPsPage *pPage) = 0;		
	virtual void on_add_page_after(IPsPage *pPage) = 0;		
	// A new page deleted (only for whiteboard)
	virtual void on_delete_page(IPsPage *pPage) = 0;	

	// A new document is generated, and it becomes the current document.
	virtual	void on_add_document(IPsDoc *pDoc, BOOL from_remote) = 0;

	// A document is closed
	virtual	void on_close_document(psID doc_id) = 0;

	// All documents have been closed (Usually sent when the last document is closed)
	virtual void on_nomore_documents() = 0;

	// When you call pIComEventHandler->OnWindowMessage(NULL, WM_COMMAND, CMR_IDM_VIEW_PREVIOUS
	// to change to next step, you really have no idea what will happen.
	// If it causes changing to next animation step, you receive on_next_animationstep(),
	// otherwise, it must be on_next_page(). If you don't get neither callbacks,
	// Means it just does change anything.

	virtual void on_next_animationstep() = 0;
	virtual void on_previous_animationstep() = 0;

	virtual void on_next_page() = 0;
	virtual void on_previous_page() = 0;
	
	// If the page is bigger than the view area, whenever presenter scrolls the page
	// each attendee(include host) automatically follows. You can reject that by return FALSE.
	virtual	BOOL please_accept_pagescroll(psID Doc, psID Page, psCoord x, psCoord y) = 0;
	// If the presenter changes zoom mode, each attendee(include host) will get this callback. 
	// Return FALSE not to change zoom mode for individual attendee (include host).
	virtual	BOOL please_accept_zoomchange(psID Doc, UINT ZoomType, int nPercent) = 0;
	// Whenever the presenter enter or exit fullscreen mode, attendee should 
	// automatically enter/exit fullscreen. However, you can reject fullscreen change 
	// by return FALSE for individual attendee (include host).
	virtual	BOOL please_accept_fullscreen(BOOL bFullscreen) = 0;
};

class IPsUIMgr
{
public:
	virtual	void set_ui_event_callback(IPsUIEventCallback *ui_event_callback) = 0;
	virtual	void no_default_ui() = 0;	

	virtual	BOOL HasChangePagePrivilege() = 0;	//这个用户是否有翻页的权限
	virtual	BOOL HasChangeViewPrivilege() = 0; //这个用户是否有设置放大比率的权限
	virtual	BOOL IsHostSyncAll() = 0;	//主持人翻页是否影响全部
	virtual	BOOL HasSaveDocPrivilege() = 0; //这个用户是否有权限保存文档
	virtual	BOOL HasAnnotationPrivilege() = 0; //这个用户是否有annotation的权限
	virtual	BOOL HasOpenDocPrivilege() = 0; //这个人是否有打开文档的权限
	virtual	BOOL HasAnnotationNewPagePrivilege() = 0; //这个人是否创建一个空白页来做评注（就是白板）。只在white board session里面才有用

	virtual BOOL IsWhiteboardSession() = 0; //当前是文档共享，还是白板

	virtual	int	 GetDocCount() = 0;		//当前有多少个文档
	virtual	int	 GetCurrentDocNo() = 0;	// The current document No.
	virtual psID GetCurrentDocID() = 0; // the current document ID
	virtual	int	 GetDocNoByID(psID DocID) = 0;	// Get the document No. by doc ID
	virtual psID GetDocIDByNo(int n) = 0;		// Get the document ID by doc No.
	virtual	void CloseDocByID(psID DocID) = 0;  // Close the current document
	
	virtual IPsDoc *GetIDocByID(psID DocID) =0;
	virtual IPsDoc *GetIDocByNo(int n) = 0;

	virtual	void *SetCurrentDocByID(psID DocID, BOOL update_remote) = 0;
	virtual	void *SetCurrentDocByNo(int n, BOOL update_remote) = 0;

	virtual	BOOL LoadPresentation(LPCSTR lpszFile, WPARAM Flag) = 0; // Load a document

	virtual	void GetDrawingFormat(int &nPenWidth, COLORREF &crPenColor, COLORREF &crFillColor) = 0;
	virtual	void ChangeDrawingFormat(int nPenWidth, COLORREF crPenColor, COLORREF crFillColor) = 0;

	virtual	void GetHilightColor(COLORREF &crHilightColor) = 0;
	virtual	void SetHilightColor(COLORREF crHilightColor) = 0;

	virtual	void LeaveAnnotationMode() = 0;
	virtual	void SetZoomPercent(int nPercent) = 0;
	virtual	void GetZoomPercent(int &nPercent) = 0;
	
	// The following APIs may fail. You need to check the return value.

	// Get the presenter's zoom mode (not local).
	virtual	BOOL GetPresenterZoomMode(UINT &ZoomType, int &nPercent) = 0;
	// Get the current page and current document in presenter side
	virtual	BOOL GetPresenterCurrentPage(psID &DocID, psID &PageID) = 0;
	// Check whether presenter is in fullscreen
	virtual	BOOL GetPresenterFullScreenStatus() = 0;
	// Be careful to use this API. If you call this API from presenter side, it will
	// sync all attendees. If you call this API from an attendee. It basically sync 
	// itself to the attendee. 
	virtual	BOOL SyncDisplay() = 0;
};

extern "C"
{
	BOOL	WINAPI	InstallDriver(int *bRebootNeeded);
	BOOL	WINAPI	UninstallDriver(int *bRebootNeeded);
}

/* Implementation guide

  1. presentation or whiteboard component interface
	 pIComEventHandler (in classcommgr.cpp, you have this interface after loading presentation module)

  2. Get IPsUIMgr interface
	 COMPONENT_INFO *pComInfo = pIComEventHandler->GetComponentInfo();
	 MufAssert(pComInfo);
	 iPsUIMrg = (IPsUIMgr *)pComInfo->dwReserved;
	 MufAssert(iPsUIMrg);
	 
	 // Then you need to immediately set the callback interface
	 iPsUIMrg->set_ui_event_callback(Your callback interace);

	 // Then immediately call 
	 iPsUIMrg->no_default_ui() to override the default UI.


  3. UI command
	(1) Open document
		iPsUIMrg->LoadPresentation(FileName, AnimationSupport); // Support animation by set AnimationSupport = 1
		// Never call this API in whiteboard session.

	(2) Save document
		BOOL b;
		pIComEventHandler->OnWindowMessage(NULL, WM_COMMAND, CMR_IDM_SAVE, 0, b);

	(3) Close a document
		// You should show a confirm message for the user to confirm to close the document.

		// You should keep DocID in IPsUIEventCallback:on_add_document callback
		iPsUIMrg->CloseDocByID(psID DocID);

	(4) Enter/exit full screen
		BOOL b;
		pIComEventHandler->OnWindowMessage(NULL, WM_COMMAND, CMR_IDM_VIEW_FULLSCREEN, 0, b);
	
	(5) Change layout:
		 CmdID is the following value
		CMR_IDM_VIEW_ACTUALSIZE
		CMR_IDM_VIEW_FITPAGE
		CMR_IDM_VIEW_FITWIDTH
		CMR_IDM_ZOOM_25
		CMR_IDM_ZOOM_33
		CMR_IDM_ZOOM_50
		CMR_IDM_ZOOM_66
		CMR_IDM_ZOOM_75
		CMR_IDM_ZOOM_100
		CMR_IDM_ZOOM_120
		CMR_IDM_ZOOM_150
		CMR_IDM_ZOOM_175
		CMR_IDM_ZOOM_200
		CMR_IDM_ZOOM_250
		CMR_IDM_ZOOM_300
		CMR_IDM_ZOOM_400
		CMR_IDM_ZOOM_500
		CMR_IDM_ZOOM_600
		CMR_IDM_ZOOM_800

		BOOL b;
		pIComEventHandler->OnWindowMessage(NULL, WM_COMMAND, CmdID, 0, b);

	(6) Print the document
		BOOL b;
		pIComEventHandler->OnWindowMessage(NULL, WM_COMMAND, CMR_IDM_PRINTDOC, 0, b);
	
	(7) New page, delete page, copy the current page in Whiteboard session
		
		CmdID is the following value
		PS_IDM_PAGE_NEW
		PS_IDM_PAGE_DELETE
		PS_IDM_PAGE_COPY

		BOOL b;
		pIComEventHandler->OnWindowMessage(NULL, WM_COMMAND, CmdID, 0, b);
		
		// Never call these commands in presentation mode

	(8) Annotation mode 
		CmdID is the following value:
		CMR_IDM_VIEW_LASER			// Laser point mode
		PS_IDM_MARK_CHECKMARK		// Draw check mark (勾)
		PS_IDM_MARK_XCHECKMARK		// Draw X check mark (叉)
		PS_IDM_MARK_RIGHTPOINTER	// Draw right arrow (右箭头)
		PS_IDM_MARK_LEFTPOINTER
		PS_IDM_MARK_UPPOINTER
		PS_IDM_MARK_DOWNPOINTER
		PS_IDM_DRAWING_FREEHAND			// free pen
		PS_IDM_DRAWING_RECTANGLE		// draw rectangle with a pen without filling inside
		PS_IDM_DRAWING_FILLRECTANGLE	// draw a rectangle frame with a pen, fill inside with a ink
		PS_IDM_DRAWING_ROUNDRECTANGLE	// draw round rectangle with a pen without filling inside
		PS_IDM_DRAWING_FILLROUNDRECTANGLE // draw a round rectangle frame with a pen, fill inside with a ink
		PS_IDM_DRAWING_ELLIPSE			// draw ellipse with a pen without filling inside	
		PS_IDM_DRAWING_FILLELLIPSE		// draw ellipse frame with a pen, fill inside with a ink
		PS_IDM_DRAWING_LINE				// draw a line with a pen
		PS_IDM_DRAWING_LINEARROW		// draw a line with one arrow
		PS_IDM_DRAWING_LINEDOUBLEARROW	// draw a line with arrow in each side
		PS_IDM_TEXT						// Text annotation
		PS_IDM_SELECT_SELECT			// In object selection mode
		PS_IDM_SELECT_ERASER			// In object erase mode
		PS_IDM_HIGHLIGHT				// Hilight pen
		PS_IDM_SELECT_ERASERALL			// Erase all annotation objects on the page
		PS_IDM_SELECT_ERASERMYALL		// Erase all my annotation objects on the page
		PS_IDM_SELECT_ERASEROTHERS		// Erase all other users' annotation objects on the page

		BOOL b;
		pIComEventHandler->OnWindowMessage(NULL, WM_COMMAND, CmdID, 0, b);
	
	(9) Previous Step (Without annimation, it is actually PreviousPage)
		BOOL b;
		pIComEventHandler->OnWindowMessage(NULL, WM_COMMAND, CMR_IDM_VIEW_PREVIOUS, 0, b);
		
	(10)Next Step (Without annimation, it is actually NextPage)
		BOOL b;
		pIComEventHandler->OnWindowMessage(NULL, WM_COMMAND, CMR_IDM_VIEW_NEXT, 0, b);
		
  4. Change current document
	 // update_remote should be set to TRUE if you want other attendees to follow
	 // DocID is the document ID of the new current document
	 iPsUIMrg->SetCurrentDocByID(psID DocID, BOOL update_remote);

  5. Change current page (Each doc has its current page)
	 // update_remote should be set to TRUE if you want other attendees to follow
	 // PageID is the page ID of the new current page
	 IPsDoc->SetCurrentPageByID(psID PageID, BOOL update_remote);
  
  6.  Change drawing color
	 // If crPenColor is set to RGB(255,255,255), then no pen is used
	 // If crFillColor is set to RGB(255,255,255), then the internal of the object is not filled
	 iPsUIMrg->ChangeDrawingFormat(int nPenWidth, COLORREF crPenColor, COLORREF crFillColor);

  7.  Change hilight pen color
	 iPsUIMrg->SetHilightColor(COLORREF crHilightColor);

*/


#endif PSUI_H_INCLUDE_



	
	