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
UINT g_iChannelNum = 0;
PairSet g_psApp;

 const std::string app_config_name = "app.config.XML";
 const std::string monitor_pro_id_tmp = "MonitorProcessID.tmp";

//在系统刚开始运行时初始化系统环境
//1、检测配置文件，读取配置
//2、启动进程
//3、设置日志文件目录
BOOL InitSysEnv()
{
	bool ret = true;

	int icount = 0;
	LogWrapper::Info("InitSysEnv().........");

	char pathBuf[512] ="";
	GetCurrentDirectory(512,pathBuf);
	std::string strAppConfigFile = pathBuf ;
	strAppConfigFile +="\\";
	strAppConfigFile +=app_config_name;
	std::string strProIdFile = pathBuf ;
	strProIdFile +="\\";
	strProIdFile += monitor_pro_id_tmp;


	//strAppConfigFile = "d:\\app.config.XML";
	//读取app文件配置
	CSysConfig sysConfig(strAppConfigFile);
	std::string startType = sysConfig.GetStartType();
	std::string gateWay = sysConfig.GetGateWay();
	g_psApp = sysConfig.GetChannels();

	//读取pid配置
	CPIDConfig pidConfig(strProIdFile);
	std::string gwPid = pidConfig.GetGateWayPID();
	PairSet psPid = pidConfig.GetChannelsPID();

	CProcessManage pm;
	DWORD dwPid;

	if (startType == "auto")
	{

		//对gateway启动测试
		{
			dwPid = (DWORD)atol(gwPid.c_str());
			dwPid = pm.IsProgramRunning(dwPid);
			if(dwPid == 0)
			{
				dwPid = pm.StartProgram(gateWay);
				if (dwPid == 0)
				{
					//ret &= false;
					LogWrapper::Error("创建gateway进程失败,app：%s",gateWay.c_str());
				}
				else
				{//记录创建的进程
					pidConfig.SetGateWayPID(dwPid);
					LogWrapper::Debug("创建gateway进程成功,app：%s ,pid：%d",gateWay.c_str(),dwPid);
					//休眠3's,等待gateway启动
					Sleep(3000);
				}
			}
			else
			{
				LogWrapper::Debug("存在gateway原进程,app：%s ,pid：%d",gateWay.c_str(),dwPid);

			}
		}

		//if (ret)
		{//如果连gateway都没启动，说明配置错误

			//对app启动测试
			for(std::vector<Pair>::size_type i=0;i<g_psApp.size();i++)
			{
				std::string sPid = pidConfig.GetChannelPID(g_psApp[i].first);
				dwPid = (DWORD)atol(sPid.c_str());
				dwPid = pm.IsProgramRunning(dwPid);
				if (dwPid == 0)
				{//程序未启动
					std::string prog = g_psApp[i].second + " ";
					prog += g_psApp[i].first;
					dwPid = pm.StartProgram(prog);
					if (dwPid == 0)
					{
						//ret &= false;
						LogWrapper::Error("创建app进程失败,app：%s",prog.c_str());
						//std::cerr<<"创建进程失败"<<std::endl;
					}
					else
					{//记录创建的进程
						icount ++;
						pidConfig.SetChannelPID(g_psApp[i].first,dwPid);
						LogWrapper::Debug("创建app进程成功,app：%s ,pid：%d",prog.c_str(),dwPid);

					}
				}
				else
					icount++;
			}
			LogWrapper::Debug("存在app进程数量：%d",icount);

		}
	}


	//if (icount == 0)
	//{//没有启动一个app，说明配置错误
	//	ret = false;
	//}

	g_iChannelNum = g_psApp.size();

	return ret;
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

//
//
//BOOL CSysInfoDisplay::PutLine(ErrorLevel eLevel,LPCSTR pszOutPut)
//{//调用CFileOutputDisplay::PutLine()
//	DWORD dwID;
//	//CDialog* pMainDlg=(CDialog*)CWnd::FromHandle (glo_hMainWnd) ;
//	CSysInfoList *pList ;
//	switch (eLevel)
//	{
//		//显示在运行日志栏上
//	case ErrorLevel::Message:
//	case ErrorLevel::Success:
//	case ErrorLevel::GeneralWarn:
//	case ErrorLevel::FatalWarn:
//	case ErrorLevel::GeneralError:
//	case ErrorLevel::FatalError:
//		dwID=IDC_LIST_SYS_ERR_INFO;
//		//绑定写错误日志
//		//glo_cAppErrLog.PutLine (COutputDisplay::GeneralError,szTemp);
//		break;
//	}
//	pList=(CSysInfoList *)glo_pMainDlg->GetDlgItem(dwID);
//	pList->DisplayMsg ((int)eLevel,pszOutPut);
//	//return CFileOutputDisplay::PutLine (eLevel,pszOutPut);
//};
//
//BOOL CSysInfoDisplay::PutLineEx(ErrorLevel eLevel,LPCSTR pszOutPut,...)
//{
//	char szTemp[4096];
//	va_list marker;
//	va_start(marker, pszOutPut );
//	
//	int ret=vsprintf(szTemp,pszOutPut,marker);
//	va_end(marker);
//
//	//调用本类的PutLine()
//	return PutLine(eLevel,szTemp);
//}

