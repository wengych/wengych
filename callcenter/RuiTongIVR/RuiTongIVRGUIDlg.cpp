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
	ON_BN_CLICKED(IDC_BUTTON_SYS_RUN, OnButtonSysRun)
	ON_BN_CLICKED(IDC_BUTTON_SYS_PAUSE, OnButtonSysPause)
	ON_BN_CLICKED(IDC_BUTTON_SYS_STOP, OnButtonSysStop)
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
	{//如果存在或者查找有问题，必须退出本进程
		::PostQuitMessage(0);
		bSysInitOk = false;
	}

	if (bSysInitOk)
	{		
		glo_pMainDlg = this;

		if(!InitSysEnv())
		{//初始化系统
			::PostQuitMessage(0);
		}

		////发送监控信息
		//CMessage::SendStartMonitMsg();

		//设置窗口属性
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
		GLog("系统启动！");
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
	case WM_APP_WRITE_DATA://响应自定义的消息
		{
			//读取映射内存数据
            std::vector<std::string > strVector;
			std::string channelid;
			std::string phone;
			std::string stat;
            int arrayId;
            if (channel_ctrls_arr_arr.empty() )
            {
                break;
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
                    
                    //int arrArrId = CHANNEL_CTR_ID_TO_INDEX(IDC_EDIT_CHANNEL_STATUS);
                    channel_ctrls_arr_arr[arrayId][CHANNEL_EDIT_ID_TO_INDEX].ctrl->SetWindowText(stat.c_str());
                    
					i +=4;
				}
			}
		}
		break;
    case WM_COMMAND://响应button的按键信息
        {
            UINT msgerId = LOWORD(wParam ); 
            if (msgerId <= IDC_BTN_CHANNEL + g_psApp.size() && msgerId >= IDC_BTN_CHANNEL)
            {//说明是button产生的消息
                //::MessageBox(NULL,"button click","",0);
                OnButtonChannelClick(msgerId);
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
	//如果按下escape键，最小化系统到托盘
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

void CRuiTongIVRGUIDlg::OnButtonSysRun() 
{
}

void CRuiTongIVRGUIDlg::OnButtonSysPause() 
{
	//if(glo_storeData.GetServerStatus()->GetParentThreadStatus() == CServerStatus::Running)
	//{
	//	glo_storeData.GetServerStatus()->SetPause();
	//	glo_myDisplay.PutLine(CSysInfoDisplay::Message,"系统暂停运行");
	//	GetDlgItem(IDC_BUTTON_SYS_PAUSE)->SetWindowText("系统恢复");
	//}
	//else if(glo_storeData.GetServerStatus()->GetParentThreadStatus() == CServerStatus::Pause)
	//{
	//	glo_storeData.GetServerStatus()->SetResume();
	//	glo_myDisplay.PutLine(CSysInfoDisplay::Message,"系统恢复运行");
	//	GetDlgItem(IDC_BUTTON_SYS_PAUSE)->SetWindowText("系统暂停");
	//}
	//else
	//	glo_myDisplay.PutLine(CSysInfoDisplay::Message,"状态不正确，不能暂停或恢复");
}

void CRuiTongIVRGUIDlg::OnButtonSysStop() 
{

	DWORD dwID = IDC_EDIT_LINE_NO;
	CEdit* pEdit = (CEdit*)GetDlgItem(dwID);
	CString szText;
	pEdit->GetWindowText(szText);
	char szNum[128] ="";
	sprintf(szNum,"%s",szText.Trim());
	
	for (int j = 0;j<strlen(szNum);j++)
	{
		if (isdigit(szNum[j]) == 0)
		{
			GLog(log4cplus::ERROR_LOG_LEVEL,"输入的线路号[%s]错误，请重新输入",szText);
			return;
		}
	}

	if(szText.Trim().GetLength() ==0 )
	{
		GLog(log4cplus::ERROR_LOG_LEVEL,"输入的线路号[%s]错误，请重新输入",szText);
		return;
	}


	bool isRight = false;
	for(UINT i = 0;i <g_psApp.size();i++)
	{
		if(atoi(szText) == atoi(g_psApp[i].first.c_str()))
		{
			isRight = true;
			break;
		}
	}

	if (isRight)
	{
		GLog("发送停止监控信息到app：[%s] ",szText);
		std::string queueName = MSG_QUEUE_TAG;
		queueName += szText.GetString();
		//CMessage msg;
        CMessage::SendExitMsg(queueName);
	}
	else
	{
		GLog(log4cplus::ERROR_LOG_LEVEL,"输入的线路号[%s]错误，请重新输入",szText);
	}
}

void CRuiTongIVRGUIDlg::OnButtonSysQuit() 
{

		if(IDYES == AfxMessageBox("是否要退出？",MB_YESNO))
		{
			::RemoveProp(m_hWnd,g_szTitle);
			QuitSystem();
			CDialog::OnOK();
		}

}

void CRuiTongIVRGUIDlg::OnTimer(UINT nIDEvent) 
{
    //三分钟超时
    CTimeSpan ts(0,0,3,0);
    CTimeSpan tsCheck(0,0,1,0);
	CTime tmNow = CTime::GetCurrentTime();
	CString szNow;
	szNow.Format("%02d%02d %02d:%02d:%02d",
		tmNow.GetMonth(),tmNow.GetDay(),
		tmNow.GetHour(),tmNow.GetMinute(),tmNow.GetSecond());
	DWORD dwID = IDC_EDIT_SYS_CUR_TIME;
	CEdit* pEdit = (CEdit*)GetDlgItem(dwID);
	pEdit->SetWindowText(szNow.GetString());

    //读取心跳文件
    std::map<std::string,PROCESS_INFO>::iterator   piIterator=g_piMap.begin();   
    for(;piIterator!=g_piMap.end();++piIterator)   
    {
         PROCESS_INFO pi = piIterator->second;
        
         DWORD dwId;
         CActiveFile activeFile((piIterator->second)._check_file);
         activeFile.GetPInfo(dwId,piIterator->second._last_active_time );

        if (piIterator->second._is_active ==true &&
            (tmNow - piIterator->second._last_check_time ) >tsCheck)
        {
			LogWrapper::Debug("tmNow:%02d%02d%02d",tmNow.GetHour(),tmNow.GetMinute(),tmNow.GetSecond());
			LogWrapper::Debug("_last_check_time:%02d%02d%02d",piIterator->second._last_check_time.GetHour(),piIterator->second._last_active_time.GetMinute(),piIterator->second._last_active_time.GetSecond());
			piIterator->second._last_check_time = tmNow;
            if (piIterator->second._is_active == true)
            {//说明进程存活
                if (piIterator->first != "driver")
                {//是app
                    GLog("发送激活信息到app：[%s] ",piIterator->first.c_str());
                    std::string queueName = MSG_QUEUE_TAG  + piIterator->first;
                    //CMessage msg;
                    CMessage::SendActiveMsg(queueName);
                }
            }       
        }

        if (piIterator->second._is_active ==true &&
            (tmNow - piIterator->second._last_active_time ) >ts)
        {//说明超时,说明进程已经死了
			GLog("进程或许已经死掉，超时未返回数据：[%s] ",piIterator->second._app_name.c_str());
            if (piIterator->second._is_active == true)
            {//说明进程存活
               //  if (piIterator->first == "driver")
                {//就必须杀死进程
                    HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,TRUE, piIterator->second._process_id);   
                    if(hProcess!=NULL)   
                    {   
                        TerminateProcess(hProcess,0);   
                        CloseHandle(hProcess);
                    }
                    else
                    {
                        GLog("打开进程错误");
                    }
                }
                /*
                else
                {//是app
                    GLog("发送停止监控信息到app：[%s] ",piIterator->first.c_str());
                    std::string queueName = MSG_QUEUE_TAG  + piIterator->first;
                    //CMessage msg;
                    CMessage::SendExitMsg(queueName);

                    int arrayId = channel_array_map[piIterator->first];
                    channel_ctrls_arr_arr[arrayId][CHANNEL_BUTTON_ID_TO_INDEX].ctrl->SetWindowText("启动");
                }
                */

                piIterator->second._process_id = 0;
                piIterator->second._is_active = false;
                piIterator->second._start_type = StartType::MONITOR_STOP;
				piIterator->second._last_stop_time =tmNow;

            }            
        }

        if (piIterator->second._is_active == false 
			&& piIterator->second._start_type == StartType::MONITOR_STOP
			&& (tmNow-piIterator->second._last_stop_time) >tsCheck)
        {//如果是死掉了，就必须启动，并且如果超过一段时间后启动
			GLog("定时启动进程");
            DWORD dwPid = CProcessManage::StartProgram(piIterator->second._app_name);
            if (dwPid >0)
            {
                piIterator->second._process_id = dwPid;
                piIterator->second._is_active = true;
                piIterator->second._start_type = StartType::MONITOR_START;
				piIterator->second._last_active_time = tmNow;
				piIterator->second._last_check_time = tmNow;
            }
            else
            {
                GLog("定时启动进程失败");
            }
        }
    }

	CDialog::OnTimer(nIDEvent);
}


void CRuiTongIVRGUIDlg::OnBnClickedButtonRestartMonitor()
{
}

// 向group中逐行添加控件
// 输入参数中的group_ctrls_arr为保存控件指针及控件高度宽度的二维数组
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

    // 画第一行
    ArrayOfGroupControlsArray::iterator group_ctrls_arr = group_ctrls_arr_arr.begin();
    GroupControlsArray::iterator it = group_ctrls_arr->begin();

    rcCtrl.left = rcGroup.left - rcDialog.left + ctrl_to_parent_left;
    rcCtrl.right = rcCtrl.left + it->width;
    rcCtrl.top = rcGroup.top - rcDialog.top + ctrl_to_parent_top;
    rcCtrl.bottom = rcCtrl.top + it->height;
    // 首行首列控件
    it->ctrl->SetWindowPos(NULL, rcCtrl.left, rcCtrl.top, it->width, it->height, swp_style);
    //it->ctrl->UpdateWindow();

    // 循环画首行剩下控件
    for (; it != group_ctrls_arr->end(); ++it)
    {
        rcCtrl.left = rcCtrl.right + ctrl_to_ctrl;
        rcCtrl.right = rcCtrl.left + it->width;
        it->ctrl->SetWindowPos(NULL, rcCtrl.left, rcCtrl.top, it->width, it->height, swp_style);
        //it->ctrl->UpdateWindow();
    }


    // 循环按行画控件
    for (; group_ctrls_arr != group_ctrls_arr_arr.end(); ++group_ctrls_arr)
    {
        it = group_ctrls_arr->begin();
        rcCtrl.left = rcGroup.left - rcDialog.left + ctrl_to_parent_left;
        rcCtrl.right = rcCtrl.left + it->width;
        rcCtrl.top = rcCtrl.bottom + ctrl_to_ctrl;
        rcCtrl.bottom = rcCtrl.top + it->height;
        // 本行首列控件
        it->ctrl->SetWindowPos(NULL, rcCtrl.left, rcCtrl.top, it->width, it->height, swp_style);
        //it->ctrl->UpdateWindow();

        // 循环画剩下控件
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
                channel_btn->Create(_T("关闭"), wnd_style, zero_rect, this, IDC_BTN_CHANNEL + i);
            }
            else
            {
                channel_btn->Create(_T("开启"), wnd_style, zero_rect, this, IDC_BTN_CHANNEL + i);
            }
//         }

        grp_ctrl.ctrl = channel_btn;
        grp_ctrl.height = 21;
        grp_ctrl.width = 60;
        arr.push_back(grp_ctrl);

        arr_arr.push_back(arr);
        
        //增加channel_id与vector 数组id 之间的关系
        channel_array_map.insert(make_pair(psApp[i].first,i));
        //增加button id与channel_id之间匹配
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
            GLog("创建app进程失败,app：%s",process_info._app_name.c_str());
        }
        else
        {//记录创建的进程
            process_info._process_id = dwPid;
            process_info._is_active = true;
            process_info._start_type = StartType::MANUAL_START;

            bCreakOk  = true;
            GLog("创建app进程成功,app：%s ,pid：%d",process_info._app_name.c_str(),dwPid);
        }
        if (bCreakOk)
        {
            int arrayId = channel_array_map[button_channel_map[butID]];
            channel_ctrls_arr_arr[arrayId][CHANNEL_BUTTON_ID_TO_INDEX].ctrl->SetWindowText("停止");
        }
    }
    else
    {//进程已经启动
        GLog("发送停止监控信息到app：[%s] ",button_channel_map[butID].c_str());
        std::string queueName = MSG_QUEUE_TAG;
        queueName += button_channel_map[butID];
        CMessage::SendExitMsg(queueName);

        //置空
        process_info._process_id = 0;
        process_info._is_active = false;
        process_info._start_type = StartType::MANUAL_STOP;

        int arrayId = channel_array_map[button_channel_map[butID]];
        channel_ctrls_arr_arr[arrayId][CHANNEL_BUTTON_ID_TO_INDEX].ctrl->SetWindowText("启动");
    }

}

void CRuiTongIVRGUIDlg::OnBnClickedBtnStartDriver()
{
    // TODO: 在此添加控件通知处理程序代码
    if (g_piMap["driver"]._is_active) {
        if (MB_OK != MessageBox(_T("是否关闭驱动程序及应用程序?"), NULL, MB_OKCANCEL))
            return ;
        CloseAll();
        GetDlgItem(IDC_BTN_START_DRIVER)->SetWindowText("启动设备驱动");
    }
    else
    {
        if (!StartDriver()) {
            MessageBox(_T("启动设备驱动程序失败."));
            return ;
        }
        GetDlgItem(IDC_BTN_START_DRIVER)->SetWindowText("关闭设备驱动");
    }
}

void CRuiTongIVRGUIDlg::CloseAll()
{
    for (ProcessInfoMap::iterator it = g_piMap.begin(); it != g_piMap.end(); ++it)
    {
        HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, it->second._process_id);
        TerminateProcess(hProcess, 0);
        it->second._is_active = false;
        CloseHandle(hProcess);
    }
}

bool CRuiTongIVRGUIDlg::StartDriver()
{
    ProcessInfoMap::iterator it = g_piMap.find("driver");
    if (it == g_piMap.end())
        return false;
    if (0 == 
       (it->second._process_id ==
        CProcessManage::StartProgram(it->second._app_name)))
        return false;

    return true;
}
