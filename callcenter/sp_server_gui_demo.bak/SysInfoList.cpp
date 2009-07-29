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

	//���ÿؼ�������
	DWORD dwStyle = GetWindowLong(GetSafeHwnd(),GWL_STYLE);
	dwStyle=(dwStyle& ~LVS_TYPEMASK)|WS_CHILD | LVS_REPORT;//|LVS_NOCOLUMNHEADER;
	SetWindowLong(GetSafeHwnd(),GWL_STYLE,dwStyle);

	InitListCtrlCols();
	InitImageList();

	DeleteAllItems();
	
}

void CSysInfoList::InitListCtrlCols( )
{
	DWORD dwStyle = GetExtendedStyle(); //��ȡ��ǰ��չ��ʽ
	dwStyle |= LVS_EX_FULLROWSELECT; //ѡ��ĳ��ʹ���и�����report���ʱ��
	dwStyle |= LVS_EX_GRIDLINES; //�����ߣ�report���ʱ��
	//dwStyle |= LVS_EX_CHECKBOXES; //itemǰ����checkbox�ؼ�
	SetExtendedStyle(dwStyle); //������չ���

	//�������У�0����Ϣ���ͣ�1������ʱ�䣬2����Ϣ����
	CRect rect;
	GetClientRect(&rect);
	int nColInterval = rect.Width()/100;

		InsertColumn(0, _T("��Ϣ����"), LVCFMT_LEFT, nColInterval*15);
		InsertColumn(1, _T("ʱ��"), LVCFMT_LEFT, nColInterval*26);
		InsertColumn(2, _T("��Ϣ����"), LVCFMT_LEFT, rect.Width()-41*nColInterval);
}

void CSysInfoList::InitImageList(void)
{
	//����listctrl ��ͼ��
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
	// ʹ�� lvitem ��������
	LVITEM lvi;
	CString strItem;
	char szMsgType[512];
//	COutputDisplay::GetErrorLevelString ((COutputDisplay::ErrorLevel)eLevel,szMsgType);
	std::string s = LogWrapper::GetLevel((log4cplus::LogLevel)eLevel);
	strcpy(szMsgType,s.c_str());
	int iItemCount=GetItemCount();
	if(iItemCount>1000) DeleteAllItems();
	//int iLevel=eLevel;
	//�����һ��
	//strcpy(szMsgType,szLevel);
	lvi.mask =  LVIF_IMAGE | LVIF_TEXT;
	
	lvi.iItem = iItemCount;
	lvi.iSubItem = 0;
	lvi.pszText = szMsgType;//(LPTSTR)(LPCTSTR)(strItem);
	lvi.iImage = eLevel;
	InsertItem(&lvi);
	
	//���õ�һ��
	strItem.Format(_T("%s"), CTime::GetCurrentTime().Format(_T("%Y/%m/%d %H:%M:%S")));
	lvi.iSubItem =1;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
	SetItem(&lvi);
	
	//���õ�һ��
	lvi.iSubItem =2;
	lvi.pszText = (LPTSTR)szDisplay;
	SetItem(&lvi);
	CSize size(-10,40);		
	Scroll(size);

}
