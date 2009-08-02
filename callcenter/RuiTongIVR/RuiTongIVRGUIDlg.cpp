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

const std::string app_config_name = "app.config.XML";

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

//初始化系统环境
// bool InitSysEnv();

// 启动指定进程
bool StartProcess(ProcessInfo& process_info)
{
    process_info.process_id = CProcessManage::StartProgram( process_info.file_name + " " + process_info.args );
    if (!process_info.process_id)
    {
        process_info.is_active = false;
        LogWrapper::Error("创建进程失败, file name: %s",process_info.file_name.c_str());
        return false;
    }
    process_info.is_active = true;
    LogWrapper::Debug("创建进程成功, file name: %s ,pid: %d", process_info.file_name.c_str(), process_info.process_id);
    return true;
}

// 初始化过程中启动指定进程
bool InitProcess(ProcessInfo& process_info)
{
    bool is_process_running = false;
    CActiveFile activeFile(process_info.check_file);
    if (activeFile.GetPInfo( process_info.process_id, process_info.last_active_time, process_info.check_file_lock ))
    {
        //说明启动过
        is_process_running = CProcessManage::IsProgramRunning(  process_info.process_id, process_info.process_name);
        CTime getTime( process_info.last_active_time);
        LogWrapper::Debug("从文件中%s读取到进程id:%d ,最后更新时间 %04d%02d%02d %02d:%02d:%02d,运行状态:%s",
            process_info.check_file.c_str(),process_info.process_id,
            getTime.GetYear(),getTime.GetMonth(),getTime.GetDay(),getTime.GetHour(),getTime.GetMinute(),getTime.GetSecond(),
            is_process_running?"running":"not running");
    }

    if (is_process_running)
    {
        // 该进程已经启动
        process_info.is_active = true;
        LogWrapper::Debug("进程存在, file name: %s , pid: %d", process_info.file_name.c_str(), process_info.process_id);
    }
    else if (process_info.auto_start)
    {
        // 需要自动启动进程
        StartProcess(process_info);
        Sleep(2000);
    }
    else
    {
        // 无须自动启动进程且进程并不存在
        process_info.is_active = false;
        process_info.process_id = 0;
        LogWrapper::Debug("process进程非自动启动, file name: %s ", process_info.file_name.c_str());
    }

    return true;
}

//在系统刚开始运行时初始化系统环境
//1、检测配置文件，读取配置
//2、启动进程
//3、设置日志文件目录
bool CRuiTongIVRGUIDlg::InitSysEnv()
{
    bool ret = true;
    bool bAutoStart = false;
    int icount = 0;
    const std::string driver_map_key = "driver";
    const std::string driver_active_file = "_driver";
    const std::string app_active_file = "_app_";

    LogWrapper::Info("InitSysEnv().........");

    char pathBuf[512] ="";
    GetCurrentDirectory(512,pathBuf);
    std::string strPathBuf = pathBuf;
    std::string strAppConfigFile = strPathBuf + "\\"+ app_config_name;

    CSysConfig sysConfig(strAppConfigFile);
    std::string startType = sysConfig.GetStartType();
    channel_config = sysConfig.GetChannels();

    if (startType == "auto")
        // 是否自动启动进程
        bAutoStart  =true;

    driver_process = ProcessInfo(DRIVER, sysConfig.GetGateWay(), "", driver_active_file, bAutoStart);
    InitProcess(driver_process);

    for (helper::PairSet::iterator it = channel_config.begin();
        it != channel_config.end(); ++it)
    {
        ProcessInfo app_process(APP,       // process type
            it->second,                     // process execute file name
            it->first,                      // process command line argument
            app_active_file + it->first,    // active check file name
            bAutoStart);                    // is the process need start automatic
        if (driver_process.is_active)
            InitProcess(app_process);
        app_processes.push_back(app_process);
    }
    return true;
}

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
	{//如果存在或者查找有问题，必须退出本进程
		::PostQuitMessage(0);
		bSysInitOk = false;
	}

	if (bSysInitOk)
	{		
		glo_pMainDlg = this;

		if(!InitSysEnv())
		{
            //初始化系统
			::PostQuitMessage(0);
		}

		// //发送监控信息
		// CMessage::SendStartMonitMsg();

		// 设置窗口属性
		SetProp(m_hWnd,g_szTitle,(HANDLE)1);

		SetTimer(1, 1000, NULL);

		CTime tmNow = CTime::GetCurrentTime();
		CString szNow;
		szNow.Format("%02d%02d %02d:%02d:%02d",
			tmNow.GetMonth(),tmNow.GetDay(),
			tmNow.GetHour(),tmNow.GetMinute(),tmNow.GetSecond());
		DWORD dwID = IDC_EDIT_SYS_START_TIME;
		CEdit* pEdit = (CEdit*)GetDlgItem(dwID);
		pEdit->SetWindowText(szNow.GetString());

        InitChannelGroupControls(channel_ctrls_arr_arr, channel_config);
        AddCtrlsToGroup(IDC_GROUP_CHANNEL, channel_ctrls_arr_arr);

		UpdateStartDriverBtn();

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
            OnMsgAppWriteData();
		}
		break;
    case WM_COMMAND://响应button的按键信息
        {
            UINT msgerId = LOWORD(wParam ); 
            if (msgerId <= IDC_BTN_CHANNEL + app_processes.size() && msgerId >= IDC_BTN_CHANNEL)
            {
                OnButtonChannelClick(msgerId - IDC_BTN_CHANNEL);
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
    static int ActiveCheckCount = 0;
    CTime tmNow = CTime::GetCurrentTime();
    CString szNow;
    szNow.Format("%02d%02d %02d:%02d:%02d",
        tmNow.GetMonth(),tmNow.GetDay(),
        tmNow.GetHour(),tmNow.GetMinute(),tmNow.GetSecond());

    GetDlgItem(IDC_EDIT_SYS_CUR_TIME)->SetWindowText(szNow.GetString());

    ActiveCheckCount++;
    if ( ActiveCheckCount > 30 )
    {
        ActiveCheckCount = 0;
        ActiveCheck();
    }

    CDialog::OnTimer(nIDEvent);
}

bool CheckProcess(ProcessInfo& process_info) 
{
    CTime tmNow = CTime::GetCurrentTime();
    CActiveFile activeFile(process_info.check_file);
    activeFile.GetPInfo( process_info.process_id, process_info.last_active_time, process_info.check_file_lock );

    if (!process_info.is_active)
    {
        // TODO:
        // 是否删除已存在的进程
        // return ;
    }

//    if ((tmNow - process_info.last_active_time) > 60 /*this->time_out*/)
    // TODO:
    // Get time_out from app_config.xml
//    {
        // 说明超时,进程已经死了，或者进程已经退出
//         GLog("进程已经死掉或者已经退出，超时未更新数据：[%s] ",process_info.file_name.c_str());
//         CProcessManage::ExitProgram(process_info.process_id,process_info.process_name);
//         LogWrapper::Debug("将关闭进程id:[%d],app:[%s], failed",process_info.process_id, process_info.file_name.c_str());

        /*
         * CheckProcess does not terminate the process.
         * Do terminate out of this method.
         * By the return value of this method.
         */
    if ((tmNow - process_info.last_active_time) > 60 /*this->time_out*/ ||
        !CProcessManage::IsProgramRunning(process_info.process_id, process_info.process_name))
    {
        process_info.is_active = false;
        return false;
    }
//    }

    if (process_info.is_active == false)
        process_info.is_active = true;
    return true;
}

void CRuiTongIVRGUIDlg::ActiveCheck()
{
    // driver_process.is_active = CheckProcess(driver_process);
    if (!CheckProcess(driver_process))
    {
        CProcessManage::ExitProgram(driver_process.process_id, driver_process.process_name);
        boost::interprocess::named_mutex::remove(driver_process.check_file_lock.c_str());
    }

    for (ProcessInfoArray::iterator it = app_processes.begin();
        it != app_processes.end(); ++it)
    {
        if (!CheckProcess(*it))
        {
            CProcessManage::ExitProgram(it->process_id, it->process_name);
            boost::interprocess::named_mutex::remove(it->check_file_lock.c_str());
        }
    }

    UpdateStartDriverBtn();
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

    // 循环画首行剩下控件
    for (; it != group_ctrls_arr->end(); ++it)
    {
        rcCtrl.left = rcCtrl.right + ctrl_to_ctrl;
        rcCtrl.right = rcCtrl.left + it->width;
        it->ctrl->SetWindowPos(NULL, rcCtrl.left, rcCtrl.top, it->width, it->height, swp_style);
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

        // 循环画剩下控件
        for (; it != group_ctrls_arr->end(); ++it)
        {
            rcCtrl.left = rcCtrl.right + ctrl_to_ctrl;
            rcCtrl.right = rcCtrl.left + it->width;
            it->ctrl->SetWindowPos(NULL, rcCtrl.left, rcCtrl.top, it->width, it->height, swp_style);
        }

    }
}

void CRuiTongIVRGUIDlg::InitChannelGroupControls(ArrayOfGroupControlsArray& arr_arr, const PairSet& psApp)
{
    char pathBuf[MAX_PATH] = "";
    GetCurrentDirectory(MAX_PATH, pathBuf);
    std::string strPathBuf = pathBuf;
    std::string strAppConfigFile = strPathBuf + "\\" + app_config_name;
    CChannelViewConfig cvConfig(strAppConfigFile);
    std::pair<int,int> channel_id_view = cvConfig.GetChannelIDView();
    std::pair<int,int> channel_state_view = cvConfig.GetChannelStateView();
    std::pair<int,int> channel_ctrl_btn_view = cvConfig.GetChannelCtrlBtnView();

    CRect zero_rect(0,0,0,0);
    int wnd_style = WS_CHILD | WS_BORDER | WS_MINIMIZEBOX | WS_EX_CLIENTEDGE;
    for (UINT i = 0; i <psApp.size() ; ++i)
    {
        GroupControlsArray arr;
        GroupControl grp_ctrl;

        CStatic* channel_id = new CStatic();
        channel_id->Create(psApp[i].first.c_str(), wnd_style ,zero_rect, this);
        grp_ctrl.ctrl = channel_id;
        grp_ctrl.height = channel_id_view.second;
        grp_ctrl.width = channel_id_view.first;

        arr.push_back(grp_ctrl);

        // TODO
        // add a new edit box for caller id

        // for display channel status.
        CEdit* channel_status = new CEdit();
        channel_status->Create(wnd_style, zero_rect, this, IDC_EDIT_CHANNEL_STATUS + i);
        channel_status->SetWindowText(_T(""));
        grp_ctrl.ctrl = channel_status;
        grp_ctrl.height = channel_state_view.second;
        grp_ctrl.width = channel_state_view.first;
        arr.push_back(grp_ctrl);

        // to set the channel start or stop.
        CButton* channel_btn = new CButton();
        if( app_processes.at(i).is_active )
        {
            channel_btn->Create(_T("关闭"), wnd_style, zero_rect, this, IDC_BTN_CHANNEL + i);
        }
        else
        {
            channel_btn->Create(_T("开启"), wnd_style, zero_rect, this, IDC_BTN_CHANNEL + i);
        }

        grp_ctrl.ctrl = channel_btn;
        grp_ctrl.height = channel_ctrl_btn_view.second;
        grp_ctrl.width = channel_ctrl_btn_view.first;
        arr.push_back(grp_ctrl);

        arr_arr.push_back(arr);
    }
}

void CRuiTongIVRGUIDlg::OnButtonChannelClick(int idx)
{
    ProcessInfo& process_info = app_processes.at(idx);

    if (!CheckProcess(process_info))
    {
        OnButtonChannelStart(idx);
    }
    else
    {
        //进程已经启动
        OnButtonChannelStop(idx);
    }
}

void CRuiTongIVRGUIDlg::OnButtonChannelStart(int idx)
{
    ProcessInfo& process_info = app_processes.at(idx);

    if (CheckProcess(process_info))
    {
        MessageBox("进程已存在");
        channel_ctrls_arr_arr.at(idx).at(CHANNEL_BUTTON_ID_TO_INDEX).ctrl->SetWindowText(_T("关闭"));
        return ;
    }

    StartProcess(process_info);
    // process_info.process_id = CProcessManage::StartProgram(process_info.file_name);
    if (!process_info.process_id)
    {
        GLog("创建app进程失败,app：%s",process_info.file_name.c_str());
        return ;
    }

    GLog("创建app进程成功,app：%s ,pid：%d", process_info.file_name.c_str(), process_info.process_id);
    channel_ctrls_arr_arr.at(idx).at(CHANNEL_BUTTON_ID_TO_INDEX).ctrl->SetWindowText(_T("关闭"));
}

void CRuiTongIVRGUIDlg::OnButtonChannelStop(int idx)
{
    ProcessInfo& process_info = app_processes.at(idx);
    if (!CheckProcess(process_info))
    {
        MessageBox("进程不存在");
        channel_ctrls_arr_arr.at(idx).at(CHANNEL_BUTTON_ID_TO_INDEX).ctrl->SetWindowText("开启");
        return ;
    }

    GLog("发送停止监控信息到app：[%d],pid[%d] ", idx, process_info.process_id);
    std::string queueName = MSG_QUEUE_TAG;
    queueName += process_info.args;
    CMessage::SendExitMsg(queueName);

    channel_ctrls_arr_arr.at(idx).at(CHANNEL_BUTTON_ID_TO_INDEX).ctrl->SetWindowText("开启");
}

void CRuiTongIVRGUIDlg::OnBnClickedBtnStartDriver()
{
    if (driver_process.is_active)
    {
        if (IDCANCEL == MessageBox(_T("是否关闭驱动程序及应用程序?"), NULL, MB_OKCANCEL))
            return ;

        if (!CheckProcess(driver_process))
        {
            MessageBox("驱动进程不存在");
        }
        else
        {
            CloseAll();
        }
    }
    else
    {
        if (CheckProcess(driver_process))
        {
            MessageBox("进程已经存在");
        }
        else if (!StartProcess(driver_process))
        {
            MessageBox(_T("启动设备驱动程序失败."));
            return ;
        }
    }
   UpdateStartDriverBtn();
}

void CRuiTongIVRGUIDlg::UpdateStartDriverBtn()
{
    if (!driver_process.is_active) 
    {
        // for (ArrayOfGroupControlsArray::iterator arr = channel_ctrls_arr_arr.begin();
        //     arr != channel_ctrls_arr_arr.end() ; ++arr)
        for (size_t i = 0; i < app_processes.size(); ++i)
        {
            channel_ctrls_arr_arr.at(i).at(CHANNEL_BUTTON_ID_TO_INDEX).ctrl->EnableWindow(FALSE);
            channel_ctrls_arr_arr.at(i).at(CHANNEL_BUTTON_ID_TO_INDEX).ctrl->SetWindowText("开启");
        }

        GetDlgItem(IDC_BTN_START_DRIVER)->SetWindowText("开启设备驱动");
     }
    else
    {
        for (ArrayOfGroupControlsArray::iterator arr = channel_ctrls_arr_arr.begin();
            arr != channel_ctrls_arr_arr.end() ; ++arr)
        {
            arr->at(CHANNEL_BUTTON_ID_TO_INDEX).ctrl->EnableWindow(TRUE);
        }
        GetDlgItem(IDC_BTN_START_DRIVER)->SetWindowText("关闭设备驱动");
    }
}

void CRuiTongIVRGUIDlg::CloseAll()
{
    for (ProcessInfoArray::iterator it = app_processes.begin();
        it != app_processes.end();
        ++it)
    {
        CProcessManage::ExitProgram(it->process_id, it->process_name);
        it->is_active = false;
        boost::interprocess::named_mutex::remove(it->check_file_lock.c_str());
    }

    CProcessManage::ExitProgram(driver_process.process_id, driver_process.process_name);
    driver_process.is_active = false;
    boost::interprocess::named_mutex::remove(driver_process.check_file_lock.c_str());
}

void CRuiTongIVRGUIDlg::OnMsgAppWriteData()
{
    //读取映射内存数据
    std::vector<std::string > strVector;
    std::string channelid;
    std::string phone;
    std::string stat;
    if (channel_ctrls_arr_arr.empty() )
    {
        return;
    }
    if(!m_memMsg.Read(strVector))
        return ;

    for(size_t i = 0; i < strVector.size(); )
    {
        channelid = strVector[i+1];
        phone = strVector[i+2];
        stat = strVector[i+3];
        // m_listSysRunInfo.SetItemStat(atoi(id.c_str()),phone,stat);
        // arrayId = channel_array_map[channelid];

        int array_index = 0;
        for (;
            array_index < app_processes.size();
            ++array_index)
        {
            if (app_processes.at(array_index).args == channelid)
                break;
        }

        channel_ctrls_arr_arr[array_index][CHANNEL_EDIT_ID_TO_INDEX].ctrl->SetWindowText(stat.c_str());

        i += 4;
    }
}
