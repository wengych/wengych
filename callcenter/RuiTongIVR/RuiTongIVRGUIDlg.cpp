// RuiTongIVRGUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RuiTongIVRGUI.h"
#include "RuiTongIVRGUIDlg.h"
#include "MainProc.h"
#include "Message.h"
#include "ProcessManage.h"
#include <vector>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRuiTongIVRGUIDlg dialog

CRuiTongIVRGUIDlg::CRuiTongIVRGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRuiTongIVRGUIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRuiTongIVRGUIDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRuiTongIVRGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRuiTongIVRGUIDlg)
	//DDX_Control(pDX, IDC_EDIT_CLIENT_NUM, m_txtLinking);
	DDX_Control(pDX, IDC_EDIT_SYS_STATE, m_txtState);
	// DDX_Control(pDX, IDC_LIST_SYS_RUN_INFO, m_listSysRunInfo);
	DDX_Control(pDX, IDC_LIST_SYS_ERR_INFO, m_listSysErrInfo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRuiTongIVRGUIDlg, CDialog)
	//{{AFX_MSG_MAP(CRuiTongIVRGUIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SYS_QUIT, OnButtonSysQuit)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_RESTART_MONITOR, &CRuiTongIVRGUIDlg::OnBnClickedButtonRestartMonitor)
    ON_BN_CLICKED(IDC_BTN_START_DRIVER, &CRuiTongIVRGUIDlg::OnBnClickedBtnStartDriver)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRuiTongIVRGUIDlg message handlers

BOOL CRuiTongIVRGUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
		pSysMenu->EnableMenuItem (6,MF_BYPOSITION|MF_GRAYED);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	bool bSysInitOk = true;

	if(GlobalOpenUniqueProcess() != 0)
	{//������ڻ��߲��������⣬�����˳�������
		::PostQuitMessage(0);
		bSysInitOk = false;
	}

	if (bSysInitOk)
	{		
		glo_pMainDlg = this;

		if(!InitSysEnv())
		{//��ʼ��ϵͳ
			::PostQuitMessage(0);
		}

		////���ͼ����Ϣ
		//CMessage::SendStartMonitMsg();

		//���ô�������
		SetProp(m_hWnd,g_szTitle,(HANDLE)1);

		// m_listSysRunInfo.InitChannel(g_iChannelNum);
		//m_listSysRunInfo.InitChannel(8);

		SetTimer(1,1000,NULL);


		CTime tmNow = CTime::GetCurrentTime();
		CString szNow;
		szNow.Format("%02d%02d %02d:%02d:%02d",
			tmNow.GetMonth(),tmNow.GetDay(),
			tmNow.GetHour(),tmNow.GetMinute(),tmNow.GetSecond());
		DWORD dwID = IDC_EDIT_SYS_START_TIME;
		CEdit* pEdit = (CEdit*)GetDlgItem(dwID);
		pEdit->SetWindowText(szNow.GetString());

        InitChannelGroupControls(channel_ctrls_arr_arr,channel_array_map,g_psApp,g_piMap);
        AddCtrlsToGroup(IDC_GROUP_CHANNEL, channel_ctrls_arr_arr);

		if (g_piMap["driver"]._is_active)
		{
			GetDlgItem(IDC_BTN_START_DRIVER)->SetWindowText("�ر��豸����");
		}
		else
		{
			GetDlgItem(IDC_BTN_START_DRIVER)->SetWindowText("�����豸����");
		}

		GLog("ϵͳ������");
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRuiTongIVRGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRuiTongIVRGUIDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.

HCURSOR CRuiTongIVRGUIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//cul
LRESULT CRuiTongIVRGUIDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_APP_WRITE_DATA://��Ӧ�Զ������Ϣ
		{
            OnMsgAppWriteData();
		}
		break;
    case WM_COMMAND://��Ӧbutton�İ�����Ϣ
        {
            UINT msgerId = LOWORD(wParam ); 
            if (msgerId <= IDC_BTN_CHANNEL + g_psApp.size() && msgerId >= IDC_BTN_CHANNEL)
            {
				//˵����button��������Ϣ
                //::MessageBox(NULL,"button click","",0);
                OnButtonChannelClick(msgerId);
            }
			else if (msgerId == IDC_BTN_START_DRIVER)
			{
				OnBnClickedBtnStartDriver();
			}
        }
        break;
	default:
		break;
	}
	return CWnd::WindowProc(message, wParam, lParam);

}


BOOL CRuiTongIVRGUIDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	//�������escape������С��ϵͳ������
	UINT nID = LOWORD(wParam);
	int nCode = HIWORD(wParam);
	HWND hWndCtrl = (HWND)lParam;
	
	if(nID==2&&nCode==0&&hWndCtrl==NULL)
	{
//		MinimizeSysToTray();
		return TRUE;
	}
	
	return CDialog::OnCommand(wParam, lParam);
}


void CRuiTongIVRGUIDlg::OnButtonSysQuit() 
{
    if(IDYES == AfxMessageBox("�Ƿ�Ҫ�˳���",MB_YESNO))
    {
        ::RemoveProp(m_hWnd,g_szTitle);
        QuitSystem();
        CDialog::OnOK();
    }
}

void CRuiTongIVRGUIDlg::OnTimer(UINT nIDEvent) 
{
    //�رպ�10s������
    CTimeSpan ts(0,0,0,10);
    //1���ӷ�һ����������
    CTimeSpan tsCheck(0,0,0,30);
    //��ʱʱ�����
    const int time_out_count = 4;
    CTime tmNow = CTime::GetCurrentTime();
    CString szNow;
    szNow.Format("%02d%02d %02d:%02d:%02d",
        tmNow.GetMonth(),tmNow.GetDay(),
        tmNow.GetHour(),tmNow.GetMinute(),tmNow.GetSecond());
    DWORD dwID = IDC_EDIT_SYS_CUR_TIME;
    CEdit* pEdit = (CEdit*)GetDlgItem(dwID);
    pEdit->SetWindowText(szNow.GetString());

    //��ȡ�����ļ�
    std::map<std::string,PROCESS_INFO>::iterator   piIterator=g_piMap.begin();   
    for(;piIterator!=g_piMap.end();++piIterator)   
    {
        PROCESS_INFO& pi = piIterator->second;        

        if (pi._is_active ==true &&
            (tmNow - pi._last_check_time ) >tsCheck)
        {
            //˵�����̴��
            if (piIterator->first != "driver")
            {
                //��app
                GLog("���ͼ�����Ϣ��app��[%s] ",piIterator->first.c_str());
                std::string queueName = MSG_QUEUE_TAG  + piIterator->first;
                //CMessage msg;
                CMessage::SendActiveMsg(queueName);
            }

            DWORD dwId;
            CActiveFile activeFile(pi._check_file);
            activeFile.GetPInfo(dwId,pi._last_active_time );

            pi._last_check_time = tmNow;

            if ( pi._time_out_count ++ >time_out_count)
            {
                //˵����ʱ,�����Ѿ����ˣ����߽����Ѿ��˳�
                GLog("�����Ѿ����������Ѿ��˳�����ʱδ�������ݣ�[%s] ",pi._app_name.c_str());
                CProcessManage::ExitProgram(pi._process_id);

                pi._process_id = 0;
                pi._is_active = false;
                pi._start_type = MONITOR_STOP;
                pi._last_stop_time =tmNow;
                pi._time_out_count = 0;
            }
        }


        if (pi._start_type == MONITOR_STOP
            && (tmNow-pi._last_stop_time) >ts)
        {//����������ˣ��ͱ��������������������һ��ʱ�������
            GLog("��ʱ��������");
            pi._process_id  = CProcessManage::StartProgram(pi._app_name);
            if ( pi._process_id  >0)
            {
                pi._is_active = true;
                pi._start_type = MONITOR_START;
                pi._last_active_time = tmNow;
                pi._time_out_count = 0;
            }
            else
            {
                GLog("��ʱ��������ʧ��");
            }
        }
    }

    CDialog::OnTimer(nIDEvent);
}


void CRuiTongIVRGUIDlg::OnBnClickedButtonRestartMonitor()
{
}

// ��group��������ӿؼ�
// ��������е�group_ctrls_arrΪ����ؼ�ָ�뼰�ؼ��߶ȿ�ȵĶ�ά����
void CRuiTongIVRGUIDlg::AddCtrlsToGroup(int group_id, ArrayOfGroupControlsArray& group_ctrls_arr_arr)
{
    if (group_ctrls_arr_arr.empty() || group_ctrls_arr_arr.begin()->empty())
        return ;

    int swp_style = SWP_NOZORDER | SWP_SHOWWINDOW;

    CWnd* group = GetDlgItem(group_id/*IDC_GROUP_CHANNEL*/);
    // int default_width = 100;
    // int default_height = 20;
    int ctrl_to_parent_left = 10;
    int ctrl_to_parent_top = 5;
    int ctrl_to_ctrl = 5;

    CRect rcDialog, rcGroup, rcCtrl;
    this->GetWindowRect(rcDialog);
    group->GetWindowRect(rcGroup);

    // ����һ��
    ArrayOfGroupControlsArray::iterator group_ctrls_arr = group_ctrls_arr_arr.begin();
    GroupControlsArray::iterator it = group_ctrls_arr->begin();

    rcCtrl.left = rcGroup.left - rcDialog.left + ctrl_to_parent_left;
    rcCtrl.right = rcCtrl.left + it->width;
    rcCtrl.top = rcGroup.top - rcDialog.top + ctrl_to_parent_top;
    rcCtrl.bottom = rcCtrl.top + it->height;
    // �������пؼ�
    it->ctrl->SetWindowPos(NULL, rcCtrl.left, rcCtrl.top, it->width, it->height, swp_style);
    //it->ctrl->UpdateWindow();

    // ѭ��������ʣ�¿ؼ�
    for (; it != group_ctrls_arr->end(); ++it)
    {
        rcCtrl.left = rcCtrl.right + ctrl_to_ctrl;
        rcCtrl.right = rcCtrl.left + it->width;
        it->ctrl->SetWindowPos(NULL, rcCtrl.left, rcCtrl.top, it->width, it->height, swp_style);
        //it->ctrl->UpdateWindow();
    }


    // ѭ�����л��ؼ�
    for (; group_ctrls_arr != group_ctrls_arr_arr.end(); ++group_ctrls_arr)
    {
        it = group_ctrls_arr->begin();
        rcCtrl.left = rcGroup.left - rcDialog.left + ctrl_to_parent_left;
        rcCtrl.right = rcCtrl.left + it->width;
        rcCtrl.top = rcCtrl.bottom + ctrl_to_ctrl;
        rcCtrl.bottom = rcCtrl.top + it->height;
        // �������пؼ�
        it->ctrl->SetWindowPos(NULL, rcCtrl.left, rcCtrl.top, it->width, it->height, swp_style);
        //it->ctrl->UpdateWindow();

        // ѭ����ʣ�¿ؼ�
        for (; it != group_ctrls_arr->end(); ++it)
        {
            rcCtrl.left = rcCtrl.right + ctrl_to_ctrl;
            rcCtrl.right = rcCtrl.left + it->width;
            it->ctrl->SetWindowPos(NULL, rcCtrl.left, rcCtrl.top, it->width, it->height, swp_style);
            //it->ctrl->UpdateWindow();
        }

    }
}

void CRuiTongIVRGUIDlg::InitChannelGroupControls(ArrayOfGroupControlsArray& arr_arr,ChannelArrayMap& channel_array_map,const PairSet& psApp ,ProcessInfoMap& piMap)
{
    std::string view_path = "/configuration/view";
    CRect zero_rect(0,0,0,0);
    int wnd_style = WS_CHILD | WS_BORDER | WS_MINIMIZEBOX | WS_EX_CLIENTEDGE;
    for (UINT i = 0; i <psApp.size() ; ++i)
    {
        GroupControlsArray arr;
        GroupControl grp_ctrl;

        CStatic* channel_id = new CStatic();
        channel_id->Create(_T(psApp[i].first.c_str()), wnd_style ,zero_rect, this);
        grp_ctrl.ctrl = channel_id;
        grp_ctrl.height = 21;
        grp_ctrl.width = 20;

        arr.push_back(grp_ctrl);

        // TODO
        // add a new edit box for caller id

        // for display channel status.
        CEdit* channel_status = new CEdit();
        channel_status->Create(wnd_style, zero_rect, this, IDC_EDIT_CHANNEL_STATUS + i);
        channel_status->SetWindowText(_T(""));
        grp_ctrl.ctrl = channel_status;
        grp_ctrl.height = 21;
        grp_ctrl.width = 300;
        arr.push_back(grp_ctrl);

        // to set the channel start or stop.
        CButton* channel_btn = new CButton();
//         map<std::string,PROCESS_INFO>::iterator it = piMap.find(psApp[i].first);
//         if (it != piMap.end())
//         {
//            if (it->second._is_active)
            if( piMap[psApp[i].first]._is_active)
            {
                channel_btn->Create(_T("�ر�"), wnd_style, zero_rect, this, IDC_BTN_CHANNEL + i);
            }
            else
            {
                channel_btn->Create(_T("����"), wnd_style, zero_rect, this, IDC_BTN_CHANNEL + i);
            }
//         }

        grp_ctrl.ctrl = channel_btn;
        grp_ctrl.height = 21;
        grp_ctrl.width = 60;
        arr.push_back(grp_ctrl);

        arr_arr.push_back(arr);
        
        //����channel_id��vector ����id ֮��Ĺ�ϵ
        channel_array_map.insert(make_pair(psApp[i].first,i));
        //����button id��channel_id֮��ƥ��
        button_channel_map.insert(make_pair( IDC_BTN_CHANNEL + i,psApp[i].first));
    }
}

void CRuiTongIVRGUIDlg::OnButtonChannelClick(UINT butID)
{
    bool bCreakOk = false;
    std::string channelId ;
    // PROCESS_INFO process_info;
    PROCESS_INFO& process_info = g_piMap[button_channel_map[butID]];
    DWORD dwPid = CProcessManage::IsProgramRunning(process_info._process_id, "app.exe");

    if (dwPid == 0)
    {
        dwPid = CProcessManage::StartProgram(process_info._app_name);
        if (dwPid == 0)
        {
            GLog("����app����ʧ��,app��%s",process_info._app_name.c_str());
        }
        else
        {//��¼�����Ľ���
            process_info._process_id = dwPid;
            process_info._is_active = true;
            process_info._start_type = MANUAL_START;
            process_info._last_active_time = CTime::GetCurrentTime();

            bCreakOk  = true;
            GLog("����app���̳ɹ�,app��%s ,pid��%d",process_info._app_name.c_str(),dwPid);
        }

        if (bCreakOk)
        {
            int arrayId = channel_array_map[button_channel_map[butID]];
            channel_ctrls_arr_arr[arrayId][CHANNEL_BUTTON_ID_TO_INDEX].ctrl->SetWindowText("ֹͣ");
        }
    }
    else
    {//�����Ѿ�����
        GLog("����ֹͣ�����Ϣ��app��[%s] ",button_channel_map[butID].c_str());
        std::string queueName = MSG_QUEUE_TAG;
        queueName += button_channel_map[butID];
        CMessage::SendExitMsg(queueName);

        //�ÿ�
        process_info._process_id = 0;
        process_info._is_active = false;
        process_info._start_type = MANUAL_STOP;
        process_info._last_stop_time = CTime::GetCurrentTime();

        int arrayId = channel_array_map[button_channel_map[butID]];
        channel_ctrls_arr_arr[arrayId][CHANNEL_BUTTON_ID_TO_INDEX].ctrl->SetWindowText("����");
    }

}

void CRuiTongIVRGUIDlg::OnBnClickedBtnStartDriver()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    if (g_piMap["driver"]._is_active) {
        if (IDCANCEL == MessageBox(_T("�Ƿ�ر���������Ӧ�ó���?"), NULL, MB_OKCANCEL))
            return ;
        CloseAll();
        GetDlgItem(IDC_BTN_START_DRIVER)->SetWindowText("�����豸����");
    }
    else
    {
        if (!StartDriver()) {
            MessageBox(_T("�����豸��������ʧ��."));
            return ;
        }
        GetDlgItem(IDC_BTN_START_DRIVER)->SetWindowText("�ر��豸����");
    }
}

void CRuiTongIVRGUIDlg::CloseAll()
{
    for (ProcessInfoMap::iterator it = g_piMap.begin(); it != g_piMap.end(); ++it)
    {
        CProcessManage::ExitProgram(it->second._process_id);
        it->second._process_id = 0;
        it->second._is_active = false;
        it->second._start_type = MANUAL_STOP;
        it->second._last_stop_time = CTime::GetCurrentTime();
    }
}

bool CRuiTongIVRGUIDlg::StartDriver()
{
    ProcessInfoMap::iterator it = g_piMap.find("driver");
    if (it == g_piMap.end())
        return false;
    if (0 == 
        (it->second._process_id =
        CProcessManage::StartProgram(it->second._app_name)))
        return false;

    it->second._is_active = true;
    it->second._start_type = MANUAL_START;
    it->second._last_active_time = CTime::GetCurrentTime();

    return true;
}

void CRuiTongIVRGUIDlg::OnMsgAppWriteData()
{
    //��ȡӳ���ڴ�����
    std::vector<std::string > strVector;
    std::string channelid;
    std::string phone;
    std::string stat;
    int arrayId;
    if (channel_ctrls_arr_arr.empty() )
    {
        return;
    }
    if(m_memMsg.Read(strVector))
    {
        for(std::vector<std::string >::size_type i = 0; i<strVector.size();)
        {
            channelid = strVector[i+1];
            phone = strVector[i+2];
            stat = strVector[i+3];
            // m_listSysRunInfo.SetItemStat(atoi(id.c_str()),phone,stat);
            arrayId = channel_array_map[channelid];

            int array_index;
            CHANNEL_CTR_ID_TO_INDEX(IDC_EDIT_CHANNEL_STATUS,array_index);
            channel_ctrls_arr_arr[arrayId][array_index].ctrl->SetWindowText(stat.c_str());

            i +=4;
        }
    }
}
