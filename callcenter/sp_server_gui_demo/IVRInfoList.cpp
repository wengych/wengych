// IVRInfoList.cpp : ʵ���ļ�
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

	//���ÿؼ�������
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
	DWORD dwStyle = GetExtendedStyle(); //��ȡ��ǰ��չ��ʽ
	dwStyle |= LVS_EX_FULLROWSELECT; //ѡ��ĳ��ʹ���и�����report���ʱ��
	dwStyle |= LVS_EX_GRIDLINES; //�����ߣ�report���ʱ��
	//dwStyle |= LVS_EX_CHECKBOXES; //itemǰ����checkbox�ؼ�
	SetExtendedStyle(dwStyle); //������չ���

	//

	CRect rect;
	GetClientRect(&rect);
	int nColInterval = rect.Width()/100;

	InsertColumn(0, _T("ͨ����"), LVCFMT_LEFT, nColInterval*10);
	InsertColumn(1, _T("ͨ������"), LVCFMT_LEFT, nColInterval*15);
	InsertColumn(2, _T("���к���"), LVCFMT_LEFT, nColInterval*20);
	//InsertColumn(3, _T("ͨ��״̬"), LVCFMT_LEFT, nColInterval*15);
	InsertColumn(3, _T("ͨ��״̬"), LVCFMT_LEFT, rect.Width()-45*nColInterval);
}

void CIVRInfoList::InitImageList(void)
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

void CIVRInfoList::InitChannel(int lineNum)
{
	// ʹ�� lvitem ��������
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

		//���õ�һ��
		//strItem.Format(_T("%s"), CTime::GetCurrentTime().Format(_T("%Y/%m/%d %H:%M:%S")));
		memset(szMsg,0,sizeof(szMsg));
		lvi.iSubItem =1;
		lvi.pszText =szMsg ;
		SetItem(&lvi);

		memset(szMsg,0,sizeof(szMsg));
		lvi.iSubItem =2;
		lvi.pszText = szMsg;
		SetItem(&lvi);


		strcpy(szMsg,"����");
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

	//ͨ��id �������޸�
		//lvi.iItem = line;
		//lvi.iSubItem = 0;
		//itoa( line, szMsg, 10 ) ; 
		//lvi.pszText = szMsg;//(LPTSTR)(LPCTSTR)(strItem);
		//InsertItem(&lvi);

	//ͨ�����ͣ��ݲ�����
		//���õ�һ��
		//strItem.Format(_T("%s"), CTime::GetCurrentTime().Format(_T("%Y/%m/%d %H:%M:%S")));
		memset(szMsg,0,sizeof(szMsg));
		lvi.iSubItem =1;
		lvi.pszText =szMsg ;
		SetItem(&lvi);

		//���к���
		memset(szMsg,0,sizeof(szMsg));
		if (pLine->szPhone != "NULL")
		{
			strcpy(szMsg,pLine->szPhone.c_str());
		}
		lvi.iSubItem =2;
		lvi.pszText = szMsg;
		SetItem(&lvi);

		//ͨ����Ϣ
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

	//ͨ��id �������޸�
	lvi.iItem = line;
	lvi.iSubItem = 0;
	itoa( line, szMsg, 10 ) ; 
	lvi.pszText = szMsg;//(LPTSTR)(LPCTSTR)(strItem);
	SetItem(&lvi);

	//ͨ�����ͣ��ݲ�����
	//���õ�һ��
	//strItem.Format(_T("%s"), CTime::GetCurrentTime().Format(_T("%Y/%m/%d %H:%M:%S")));
	memset(szMsg,0,sizeof(szMsg));
	lvi.iSubItem =1;
	lvi.pszText =szMsg ;
	SetItem(&lvi);

	//���к���
	memset(szMsg,0,sizeof(szMsg));
	if (phone != "NULL")
	{
		strcpy(szMsg,phone.c_str());
	}
	lvi.iSubItem =2;
	lvi.pszText = szMsg;
	SetItem(&lvi);

	//ͨ����Ϣ
	strcpy(szMsg,channelStat.c_str());
	lvi.iSubItem =3;
	lvi.pszText = szMsg;
	SetItem(&lvi);
	Update(line);
}


