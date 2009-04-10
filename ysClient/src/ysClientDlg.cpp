// ysClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ysClient.h"
#include "ysClientDlg.h"

#include <WinSock2.h>
#include <fstream>
#include <ysdef.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int VIEW_FLAG_OUT = 0;
const int VIEW_FLAG_IN = 1;

const int input_test_count = 3;
char* input_test[input_test_count] = { YSDICT_IN, YSDICT_IN, YSDICT_IN2 };

// CysClientDlg �Ի���

CysClientDlg::CysClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CysClientDlg::IDD, pParent), m_hSocket(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CysClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CysClientDlg, CDialog)
	ON_WM_PAINT()
    ON_BN_CLICKED(IDC_TEST, OnPrepareRequest)
    ON_BN_CLICKED(ID_SEND, OnSend)
    ON_BN_CLICKED(ID_EXIT, OnExit)
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CysClientDlg ��Ϣ�������

BOOL CysClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CysClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

void CysClientDlg::OnPrepareRequest()
{
    PrepareRequest();
}

void CysClientDlg::OnExit()
{
    if (m_hSocket)
        closesocket(m_hSocket);

    EndDialog(0);
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CysClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CysClientDlg::PrepareRequest()
{
    void* var_array = NULL;
    while (1)
    {
        var_array = YSVarArrayNew(0);
        for (int i = 0; i < input_test_count; ++i) {
            void* var_string = NULL;
            var_string = YSVarStringSave(input_test[i],strlen(input_test[i]));

            YSVarArrayAdd(var_array, var_string);
        }
        
        UpdateView(var_array, VIEW_FLAG_IN);

        break;
    }
    
    YSVarFree(var_array);
}

void CysClientDlg::OnSend()
{
    NewSend();
    //OldSend();
    return;

}

BOOL CysClientDlg::GenerateHeadStruct( void* hs )
{
    BYTE buff[] =
    {
        0x01, // VerM
        0x00, // VerS
        0x00, // ReqType
        0x53, 0x45, 0x52, 0x56, 0x48, 0x41, 0x53, 0x48, // PkgType
        0x01, // PkgSum
        0x01, // PkgNum
        0x00, 0x00, 0x00, 0xda, // DataSum
        0x00, 0x00, 0x00, 0xda, // DataLen

        /* data */
        0x69, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x03, 0x65,
        0x00, 0x00, 0x00, 0x18, 0x00, 0x0a, 0x5f, 0x5f,
        0x44, 0x49, 0x43, 0x54, 0x5f, 0x49, 0x4e, 0x32,
        0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01,
        0x08, 0x00, 0x00, 0x00, 0x29, 0x00, 0x0a, 0x5f,
        0x5f, 0x44, 0x49, 0x43, 0x54, 0x5f, 0x49, 0x4e,
        0x32, 0x37, 0x35, 0x30, 0x33, 0x3a, 0x2d, 0x31,
        0x32, 0x30, 0x38, 0x38, 0x39, 0x39, 0x33, 0x36,
        0x30, 0x2d, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
        0x30, 0x31, 0x65, 0x00, 0x00, 0x00, 0x1f, 0x00,
        0x11, 0x5f, 0x5f, 0x44, 0x49, 0x43, 0x54, 0x5f,
        0x53, 0x43, 0x41, 0x4c, 0x4c, 0x5f, 0x4e, 0x41,
        0x4d, 0x45, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00,
        0x00, 0x01, 0x08, 0x00, 0x00, 0x00, 0x26, 0x00,
        0x11, 0x5f, 0x5f, 0x44, 0x49, 0x43, 0x54, 0x5f,
        0x53, 0x43, 0x41, 0x4c, 0x4c, 0x5f, 0x4e, 0x41,
        0x4d, 0x45, 0x4d, 0x79, 0x44, 0x65, 0x6d, 0x6f,
        0x44, 0x61, 0x74, 0x65, 0x54, 0x69, 0x6d, 0x65,
        0x32, 0x65, 0x00, 0x00, 0x00, 0x17, 0x00, 0x09,
        0x5f, 0x5f, 0x44, 0x49, 0x43, 0x54, 0x5f, 0x49,
        0x4e, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
        0x01, 0x08, 0x00, 0x00, 0x00, 0x28, 0x00, 0x09,
        0x5f, 0x5f, 0x44, 0x49, 0x43, 0x54, 0x5f, 0x49,
        0x4e, 0x37, 0x35, 0x30, 0x33, 0x3a, 0x2d, 0x31,
        0x32, 0x30, 0x38, 0x38, 0x39, 0x39, 0x33, 0x36,
        0x30, 0x2d, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
        0x30, 0x31
    };

    YSPkgDataToStruct(hs,YSPKG_HEADSTRUCT_ST_SIZE \
        ,buff,sizeof(buff));

    void *SendPkg;
    void* Hash;
    void* Str;

    tYSPkgHeadStruct* pHs = (tYSPkgHeadStruct*)(hs);
    if ( NULL==(SendPkg=YSVarBinSave(pHs->Data,pHs->DataLen)) )
    if ( NULL==(SendPkg=YSVarBinSave(buff,sizeof(buff))) )
    {
        MessageBox(_T("Failed at YSVarBinSave"));
        return FALSE;
    }

    Str = YSVarStringNew2(10240);
    char *a = (char *)YSVarBinGet(SendPkg);
 

    if ( 0>(YSVarHashUnPack(&Hash,  SendPkg, 0)) ) {
        MessageBox(_T("���hash����"));
        return FALSE;
    }
    YSVarHashShow(Hash, 0, Str);
    std::ofstream req_file("req.xml");
    req_file.write((char*)YSVarStringGet(Str), YSVarStringGetLen(Str));
    req_file.close();

    YSVarFree(Hash);
    YSVarFree(Str);

    return TRUE;
}

void CysClientDlg::OldSend(  )
{
    tYSPkgHeadStruct hs;
    void* Pkg = NULL;
    void* Hash;
    int time_out = 1;
    if (FALSE == GenerateHeadStruct(&hs)) {
        return ;
    }

    //     if (0 > send(m_hSocket, buff, sizeof(buff), 0)) {
    //         MessageBox(_T("����ʧ��"));
    //         return;
    //     }
    if (FALSE == YSPkgTcpWrite(m_hSocket, time_out, &hs)) {
        MessageBox(_T("��������ʧ��"));
        return ;
    }

    // �հ�
    Pkg = YSVarBinNew();
    if (FALSE == YSPkgTcpRead(m_hSocket, time_out, Pkg, &hs)) {
        MessageBox(_T("��������ʧ��"));
        return ;
    }

    // ���
    if (0 > YSVarHashUnPack(&Hash, Pkg, YSPKG_HEADSTRUCT_MEM_HEADLEN(&hs))) {
        MessageBox(_T("UnPack failed!."));
        return ;
    }


    void* Str;
    Str = YSVarStringNew2(10240);
    YSVarHashShow(Hash, 0, Str);

    std::ofstream ofile("test.xml");
    ofile.write((char*)YSVarStringGet(Str), YSVarStringGetLen(Str));
    ofile.close();

    YSVarBinClear(Pkg);
    YSVarHashFree(Hash);
}

void CysClientDlg::NewSend()
{
    const char* ip = "192.168.0.105";
    int port = 9000;
    int time_out = 5;

    void* SendBus = NULL;
    void* RecvBus = NULL;

    
    char V[128];
    while (1) {
        if ( NULL==(SendBus = YSUserBusNew(0)) ){
            break;
        }

        sprintf(V,"MyDemoDateTime1");
        YSUserBusAddString(SendBus,YSDICT_SERVNAME,V,strlen(V));
        USES_CONVERSION;
        for (size_t i = 0; i < m_pEditIn.GetCount(); ++i) {
            CString strUserInput;
            m_pEditIn[i]->GetWindowText(strUserInput);
            char *p = T2A(strUserInput.GetString());
            YSUserBusAddString(SendBus, input_test[i], p, strlen(p));

//             
//             arr = YSUserBusGetArray(RecvBus,input_test[i]);
//             for ( i=0;i<YSVarArrayGetLen(arr);i++ )
//             {
// 
//                 str = YSVarArrayGet(arr,i);
//                 p = YSVarStringGet(str);
//                 p = A2T(P);
//             }
            
        }
        // sprintf(V,"%d:%d-%08d",getpid(),(INT32)pthread_self(),Idx);
        //YSUserBusAddString(SendBus,YSDICT_IN,V,strlen(V));
        //YSUserBusAddString(SendBus,YSDICT_IN,V,strlen(V));
        //YSUserBusAddString(SendBus,YSDICT_IN2,V,strlen(V));

        if (FALSE == YSServiceClientCallSock(ip, 9000, time_out, SendBus, &RecvBus)) {
            MessageBox(_T("ServiceClientCall failed!"));
            break;
        }

        void* dict_out = YSUserBusGetArray(RecvBus, YSDICT_OUT);
        void* dict_out2 = YSUserBusGetArray(RecvBus, YSDICT_OUT2);
        
        UpdateView(dict_out, VIEW_FLAG_OUT);
        break;
    }

    OutputBusToFile(SendBus);
    OutputBusToFile(RecvBus);

    YSUserBusFree(SendBus);
    YSUserBusFree(RecvBus);

}

void CysClientDlg::OutputBusToFile( void* bus )
{
    void* str = NULL;
    while (1)
    {
        str = YSVarStringNew2(10240);
        YSUserBusShow(bus, 0, str);
        std::ofstream ofile("test.xml", std::ios_base::app);
        ofile << "\n<================ />\n";
        ofile.write((char*)YSVarStringGet(str), YSVarStringGetLen(str));

        break;
    }

    YSVarFree(str);
}


void CysClientDlg::UpdateView(void* var_array, int flag)
{
    CWnd grp_in, grp_out;
    grp_in.Attach(this->GetDlgItem(IDC_GRP_IN)->m_hWnd);
    grp_out.Attach(this->GetDlgItem(IDC_GRP_OUT)->m_hWnd);
    
    if (flag == VIEW_FLAG_IN)
        UpdateViewDetail(var_array, this->GetDlgItem(IDC_GRP_IN)->m_hWnd, m_pStaticIn, m_pEditIn);
    else
        UpdateViewDetail(var_array, this->GetDlgItem(IDC_GRP_OUT)->m_hWnd, m_pStaticOut, m_pEditOut);


    grp_in.Detach();
    grp_out.Detach();
}

void CysClientDlg::UpdateViewDetail( void* var_array, HWND hGroup, StaticAutoPtrArray& arrStatic, EditAutoPtrArray& arrEdit )
{
    int len = YSVarArrayGetLen(var_array);

    // ����֮ǰ�����Ŀؼ�����
    if (!arrStatic.IsEmpty()) {
        arrStatic.RemoveAll();
    }
    if (!arrEdit.IsEmpty()) {
        arrEdit.RemoveAll();
    }    

    for (int i = 0; i < len; ++i) {
        StaticPtr pStatic(new CStatic);
        EditPtr pEdit(new CEdit);
        arrStatic.InsertAt(arrStatic.GetCount(), pStatic);
        arrEdit.InsertAt(arrEdit.GetCount(), pEdit);
    }

    CRect rcDialog, rcGroup, rcCtrl;

    int default_width = 80;
    int default_height = 20;
    int ctrl_to_parent_left = 10;
    int ctrl_to_parent_top = 5;

    ::GetWindowRect(m_hWnd, rcDialog);
    ::GetWindowRect(hGroup, rcGroup);

    rcCtrl.left = rcGroup.left - rcDialog.left + ctrl_to_parent_left;
    rcCtrl.right = rcCtrl.left + default_width;
    rcCtrl.top = rcGroup.top - rcDialog.top + ctrl_to_parent_top;
    rcCtrl.bottom = rcCtrl.top + default_height;

    // ::ScreenToClient(m_hWnd, rcCtrl);
    USES_CONVERSION;
    CString label_text;
    label_text = A2T((char*)YSVarArrayGet(var_array, 0));

    arrStatic[0]->Create(label_text, WS_CHILD | WS_VISIBLE, rcCtrl, this);

    rcCtrl.left = rcCtrl.right + ctrl_to_parent_left;
    rcCtrl.right = rcCtrl.left + default_width;
    rcCtrl.top = rcGroup.top - rcDialog.top + ctrl_to_parent_top;
    rcCtrl.bottom = rcCtrl.top + default_height;

    // ::ScreenToClient(m_hWnd, rcCtrl);
    arrEdit[0]->Create(WS_CHILD | WS_VISIBLE | WS_BORDER, rcCtrl, this, WM_USER + 100);


    for (int i = 1; i < len; ++i)
    {
        /* top and bottom doesn't't need modify */
        rcCtrl.top = rcCtrl.bottom + ctrl_to_parent_top;
        rcCtrl.bottom = rcCtrl.top + default_height;

        /* create static */
        rcCtrl.left = rcGroup.left - rcDialog.left + ctrl_to_parent_left;
        rcCtrl.right = rcCtrl.left + default_width;
        label_text = (char*)YSVarArrayGet(var_array, i);
        arrStatic[i]->Create(label_text, WS_CHILD | WS_VISIBLE, rcCtrl, this);

        /* create edit box */
        rcCtrl.left = rcCtrl.right + ctrl_to_parent_left;
        rcCtrl.right = rcCtrl.left + default_width;
        arrEdit[i]->Create(WS_CHILD | WS_VISIBLE | WS_BORDER, rcCtrl, this, WM_USER + 100);
    }
}
