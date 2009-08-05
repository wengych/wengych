#include "stdafx.h"
#include "RuiTongIVRGUI.h"
#include "MainProc.h"
#include <direct.h>
#include "Message.h"
#include "ProcessManage.h"
#include "SysInfoList.h"

//CSysInfoDisplay glo_myDisplay(MY_SERVER_NAME,LOG_FILE);
//CSocketGlobalDataStorage glo_storeData(MY_SERVER_NAME,MainProcCallback,&glo_myDisplay);//创建文件输出对象
//CSocketParentThread glo_parentThread(&glo_storeData);

CDialog *glo_pMainDlg=NULL;
HANDLE  g_hMutex = NULL;
CString g_szTitle = "RuiTongIvr.Monitor";

//
//std::string g_gwPid;
//PairSet g_psChannelPid ;
//CPIDConfig g_pidConfig;

// std::string g_gateWay;
// ProcessInfoMap g_piMap;


// const std::string monitor_pro_id_tmp = "MonitorProcessID.tmp";

ProcessInfo::ProcessInfo()
{

}

ProcessInfo::ProcessInfo(const ProcessInfo& rhs) :
    _app_type(rhs._app_type),
    file_name(rhs.file_name),
    channel_id(rhs.channel_id),
    server_ip(rhs.server_ip),
    server_port(rhs.server_port),
    time_out(rhs.time_out),
    is_active(rhs.is_active),
    process_name(rhs.process_name),
    check_file(rhs.check_file),
    check_file_lock(rhs.check_file_lock),
    last_active_time(rhs.last_active_time),
    auto_start(rhs.auto_start),
    process_id(rhs.process_id)
{

}

ProcessInfo::ProcessInfo(AppType app_type, const std::string& exec_file_name, const std::string& cmd_arg, const std::string& active_file_name, bool is_process_auto_start)
{
    _app_type = app_type;
    file_name = exec_file_name;
    channel_id = cmd_arg;
    is_active = false;
    process_name = exec_file_name.substr(exec_file_name.find_last_of("\\") + 1);
    check_file = exec_file_name.substr(0, exec_file_name.find_last_of("\\") + 1) + active_file_name;
    check_file_lock = active_file_name + "_lock";
    last_active_time = CTime::GetCurrentTime();
    time_out_count = 0;
    auto_start = is_process_auto_start;
    process_id = 0;
}

ProcessInfo& ProcessInfo::operator=(const ProcessInfo& rhs)
{
    _app_type = rhs._app_type;
    file_name = rhs.file_name;
    channel_id = rhs.channel_id;
    server_ip = rhs.server_ip;
    server_port = rhs.server_port;
    time_out = rhs.time_out;
    is_active = rhs.is_active;
    process_name = rhs.process_name;
    check_file = rhs.check_file;
    check_file_lock = rhs.check_file_lock;
    last_active_time = rhs.last_active_time;
    time_out_count = time_out_count;
    auto_start = rhs.auto_start;
    process_id = rhs.process_id;

    return *this;
}

void ProcessInfo::AddServerInfo(const std::string& ip, const std::string& port, const std::string& to)
{
    this->server_ip = ip;
    this->server_port = port;
    this->time_out = to;
}

int GlobalOpenUniqueProcess()
{
	g_hMutex=::CreateMutex(NULL,TRUE,g_szTitle);   
	if   (g_hMutex!=NULL)   
	{   
		if   (GetLastError()==ERROR_ALREADY_EXISTS)   
		{  //表示已经存在
			HWND hWndPrev=::GetWindow(::GetDesktopWindow(),GW_CHILD);    

			while(::IsWindow(hWndPrev))
			{
				//判断窗口是否有我们预先设置的标记，如有，则是我们寻找的窗口，并将它激活。
				if(::GetProp(hWndPrev,g_szTitle))    
				{
					//如果主窗口已最小化，则恢复其大小。
					if (::IsIconic(hWndPrev))      
						::ShowWindow(hWndPrev,SW_RESTORE);
					//将应用程序的主窗口激活。
					::SetForegroundWindow(hWndPrev);

					::ReleaseMutex(g_hMutex);
					::CloseHandle(g_hMutex);

					return 1;                      //退出实例。
				}
				//继续寻找下一个窗口。
				hWndPrev = ::GetWindow(hWndPrev,GW_HWNDNEXT); 
			}
			::MessageBox(NULL,"已有一个监控实例在运行，但找不到它的主窗口！请手工杀死原进程。","",MB_OK);
			LogWrapper::Error("已有一个监控实例在运行，但找不到它的主窗口！请手工杀死原进程。");
		} 
		else
		{//不存在，必须创建
			return 0;
		}
	}
	else
	{
		::MessageBox(NULL,"系统初始化信号失败，请检查系统！","",MB_OK);
		LogWrapper::Error("系统初始化信号失败，请检查系统！");
	}

	return -1;
}

void QuitSystem()
{
	//给启动进程发送暂停监控消息
//	CMessage::SendStopMonitMsg();
	LogWrapper::Error("系统退出中！");

	//释放信号
	::ReleaseMutex(g_hMutex);
	::CloseHandle(g_hMutex);

}

void GLog(log4cplus::LogLevel level,const char * pFormat, ...)
{
	va_list args;
	va_start(args, pFormat);
	char buf[1024] = {0};
	vsnprintf(buf, sizeof(buf), pFormat, args);
	va_end(args);


	switch(level)
	{
	case log4cplus::DEBUG_LOG_LEVEL:
		LogWrapper::Debug(buf);
		break;
	case log4cplus::FATAL_LOG_LEVEL:
		LogWrapper::Fatal(buf);
		break;
	case log4cplus::TRACE_LOG_LEVEL:
		LogWrapper::Trace(buf);
		break;
	case log4cplus::ERROR_LOG_LEVEL:
		LogWrapper::Error(buf);
		break;
	case log4cplus::INFO_LOG_LEVEL:
		LogWrapper::Info(buf);
		break;
	case log4cplus::WARN_LOG_LEVEL:
		LogWrapper::Warn(buf);
		break;
	default:
		LogWrapper::Debug(buf);
		break;
	}

	DWORD dwID=IDC_LIST_SYS_ERR_INFO;
	//CDialog* pMainDlg=(CDialog*)CWnd::FromHandle (glo_hMainWnd) ;
	CSysInfoList *pList ;
	pList=(CSysInfoList *)glo_pMainDlg->GetDlgItem(dwID);
	pList->DisplayMsg ((int)level,buf);
}
void GLog(const char * pFormat, ...)
{
	va_list args;
	va_start(args, pFormat);
	char buf[1024] = {0};
	vsnprintf(buf, sizeof(buf), pFormat, args);
	va_end(args);
	LogWrapper::Info(buf);

	DWORD dwID=IDC_LIST_SYS_ERR_INFO;
	//CDialog* pMainDlg=(CDialog*)CWnd::FromHandle (glo_hMainWnd) ;
	CSysInfoList *pList ;
	pList=(CSysInfoList *)glo_pMainDlg->GetDlgItem(dwID);
	pList->DisplayMsg ((int)log4cplus::INFO_LOG_LEVEL,buf);
}

