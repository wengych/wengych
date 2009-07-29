// SysInfoList.cpp : implementation file
//

#include "stdafx.h"
#include "RuiTongIVRGUI.h"
#include "SysInfoList.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSysInfoList


BEGIN_MESSAGE_MAP(CSysInfoList, CListCtrl)
	//{{AFX_MSG_MAP(CSysInfoList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysInfoList message handlers

void CSysInfoList::PreSubclassWindow() 
{
	CListCtrl::PreSubclassWindow();

	//设置控件的特性
	DWORD dwStyle = GetWindowLong(GetSafeHwnd(),GWL_STYLE);
	dwStyle=(dwStyle& ~LVS_TYPEMASK)|WS_CHILD | LVS_REPORT;//|LVS_NOCOLUMNHEADER;
	SetWindowLong(GetSafeHwnd(),GWL_STYLE,dwStyle);

	InitListCtrlCols();
	InitImageList();

	DeleteAllItems();
	
}

void CSysInfoList::InitListCtrlCols( )
{
	DWORD dwStyle = GetExtendedStyle(); //获取当前扩展样式
	dwStyle |= LVS_EX_FULLROWSELECT; //选中某行使整行高亮（report风格时）
	dwStyle |= LVS_EX_GRIDLINES; //网格线（report风格时）
	//dwStyle |= LVS_EX_CHECKBOXES; //item前生成checkbox控件
	SetExtendedStyle(dwStyle); //设置扩展风格

	//插入三列：0：信息类型，1：产生时间，2：信息内容
	CRect rect;
	GetClientRect(&rect);
	int nColInterval = rect.Width()/100;

		InsertColumn(0, _T("消息类型"), LVCFMT_LEFT, nColInterval*15);
		InsertColumn(1, _T("时间"), LVCFMT_LEFT, nColInterval*26);
		InsertColumn(2, _T("消息内容"), LVCFMT_LEFT, rect.Width()-41*nColInterval);
}

void CSysInfoList::InitImageList(void)
{
	//设置listctrl 的图标
	// Create 256 color image lists
	HIMAGELIST 	hList = ImageList_Create(16, 16, ILC_COLOR8 | ILC_MASK, 8, 1);
	m_cImageListSmall.Attach(hList);
	// Load the large icons
	CBitmap cBmp;
	cBmp.LoadBitmap(IDB_BMP_MSG_STATUS);
	m_cImageListSmall.Add(&cBmp, RGB(255,0, 255));
	cBmp.DeleteObject();
	SetImageList(&m_cImageListSmall, LVSIL_SMALL);
}

void CSysInfoList::DisplayMsg(int eLevel,LPCTSTR szDisplay)
{
	// 使用 lvitem 插入数据
	LVITEM lvi;
	CString strItem;
	char szMsgType[512];
//	COutputDisplay::GetErrorLevelString ((COutputDisplay::ErrorLevel)eLevel,szMsgType);
	std::string s = LogWrapper::GetLevel((log4cplus::LogLevel)eLevel);
	strcpy(szMsgType,s.c_str());
	int iItemCount=GetItemCount();
	if(iItemCount>1000) DeleteAllItems();
	//int iLevel=eLevel;
	//插入的一项
	//strcpy(szMsgType,szLevel);
	lvi.mask =  LVIF_IMAGE | LVIF_TEXT;
	
	lvi.iItem = iItemCount;
	lvi.iSubItem = 0;
	lvi.pszText = szMsgType;//(LPTSTR)(LPCTSTR)(strItem);
	lvi.iImage = eLevel;
	InsertItem(&lvi);
	
	//设置第一项
	strItem.Format(_T("%s"), CTime::GetCurrentTime().Format(_T("%Y/%m/%d %H:%M:%S")));
	lvi.iSubItem =1;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
	SetItem(&lvi);
	
	//设置第一项
	lvi.iSubItem =2;
	lvi.pszText = (LPTSTR)szDisplay;
	SetItem(&lvi);
	CSize size(-10,40);		
	Scroll(size);

}
