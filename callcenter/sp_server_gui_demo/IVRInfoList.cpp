// IVRInfoList.cpp : 实现文件
//

#include "stdafx.h"
#include "IVRInfoList.h"
#include "stdafx.h"
#include "RuiTongIVRGUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CIVRInfoList

IMPLEMENT_DYNAMIC(CIVRInfoList, CListCtrl)

CIVRInfoList::CIVRInfoList()
{

}

CIVRInfoList::~CIVRInfoList()
{
}


BEGIN_MESSAGE_MAP(CIVRInfoList, CListCtrl)
END_MESSAGE_MAP()


void CIVRInfoList::PreSubclassWindow() 
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

void CIVRInfoList::InitListCtrlCols( )
{
	//
	DWORD dwStyle = GetExtendedStyle(); //获取当前扩展样式
	dwStyle |= LVS_EX_FULLROWSELECT; //选中某行使整行高亮（report风格时）
	dwStyle |= LVS_EX_GRIDLINES; //网格线（report风格时）
	//dwStyle |= LVS_EX_CHECKBOXES; //item前生成checkbox控件
	SetExtendedStyle(dwStyle); //设置扩展风格

	//

	CRect rect;
	GetClientRect(&rect);
	int nColInterval = rect.Width()/100;

	InsertColumn(0, _T("通道号"), LVCFMT_LEFT, nColInterval*10);
	InsertColumn(1, _T("通道类型"), LVCFMT_LEFT, nColInterval*15);
	InsertColumn(2, _T("主叫号码"), LVCFMT_LEFT, nColInterval*20);
	//InsertColumn(3, _T("通道状态"), LVCFMT_LEFT, nColInterval*15);
	InsertColumn(3, _T("通道状态"), LVCFMT_LEFT, rect.Width()-45*nColInterval);
}

void CIVRInfoList::InitImageList(void)
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

void CIVRInfoList::InitChannel(int lineNum)
{
	// 使用 lvitem 插入数据
	LVITEM lvi;
	CString strItem;
	char szMsg[20] = "";

	lvi.mask =  LVIF_IMAGE | LVIF_TEXT;
	strItem.Format(szMsg);

	for (int i = 0;i<lineNum;i++)
	{
		lvi.iItem = i;
		lvi.iSubItem = 0;
		itoa( i, szMsg, 10 ) ; 
		lvi.pszText = szMsg;//(LPTSTR)(LPCTSTR)(strItem);
		InsertItem(&lvi);

		//设置第一项
		//strItem.Format(_T("%s"), CTime::GetCurrentTime().Format(_T("%Y/%m/%d %H:%M:%S")));
		memset(szMsg,0,sizeof(szMsg));
		lvi.iSubItem =1;
		lvi.pszText =szMsg ;
		SetItem(&lvi);

		memset(szMsg,0,sizeof(szMsg));
		lvi.iSubItem =2;
		lvi.pszText = szMsg;
		SetItem(&lvi);


		strcpy(szMsg,"空闲");
		lvi.iSubItem =3;
		lvi.pszText = szMsg;
		SetItem(&lvi);

		CSize size(-10,40);		
		Scroll(size);
	}
}

void  CIVRInfoList::SetItemStat(int line,PLINESTRUCT pLine)
{
	LVITEM lvi;
	CString strItem;
	char szMsg[512] = "";

	lvi.mask =  LVIF_IMAGE | LVIF_TEXT;
	strItem = szMsg;

	//通道id ，不用修改
		//lvi.iItem = line;
		//lvi.iSubItem = 0;
		//itoa( line, szMsg, 10 ) ; 
		//lvi.pszText = szMsg;//(LPTSTR)(LPCTSTR)(strItem);
		//InsertItem(&lvi);

	//通道类型，暂不设置
		//设置第一项
		//strItem.Format(_T("%s"), CTime::GetCurrentTime().Format(_T("%Y/%m/%d %H:%M:%S")));
		memset(szMsg,0,sizeof(szMsg));
		lvi.iSubItem =1;
		lvi.pszText =szMsg ;
		SetItem(&lvi);

		//呼叫号码
		memset(szMsg,0,sizeof(szMsg));
		if (pLine->szPhone != "NULL")
		{
			strcpy(szMsg,pLine->szPhone.c_str());
		}
		lvi.iSubItem =2;
		lvi.pszText = szMsg;
		SetItem(&lvi);

		//通道信息
		strcpy(szMsg,pLine->szChannelStat.c_str());
		lvi.iSubItem =3;
		lvi.pszText = szMsg;
		SetItem(&lvi);
}

void  CIVRInfoList::SetItemStat(int line,const std::string& phone,const std::string& channelStat)
{
	LVITEM lvi;
	CString strItem;
	char szMsg[512] = "";

	lvi.mask =  LVIF_IMAGE | LVIF_TEXT;
	strItem = szMsg;

	//通道id ，不用修改
	lvi.iItem = line;
	lvi.iSubItem = 0;
	itoa( line, szMsg, 10 ) ; 
	lvi.pszText = szMsg;//(LPTSTR)(LPCTSTR)(strItem);
	SetItem(&lvi);

	//通道类型，暂不设置
	//设置第一项
	//strItem.Format(_T("%s"), CTime::GetCurrentTime().Format(_T("%Y/%m/%d %H:%M:%S")));
	memset(szMsg,0,sizeof(szMsg));
	lvi.iSubItem =1;
	lvi.pszText =szMsg ;
	SetItem(&lvi);

	//呼叫号码
	memset(szMsg,0,sizeof(szMsg));
	if (phone != "NULL")
	{
		strcpy(szMsg,phone.c_str());
	}
	lvi.iSubItem =2;
	lvi.pszText = szMsg;
	SetItem(&lvi);

	//通道信息
	strcpy(szMsg,channelStat.c_str());
	lvi.iSubItem =3;
	lvi.pszText = szMsg;
	SetItem(&lvi);
	Update(line);
}


