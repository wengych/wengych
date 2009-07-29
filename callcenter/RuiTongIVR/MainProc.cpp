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

std::string g_gateWay;
helper::PairSet g_psApp;
ProcessInfoMap g_piMap;


 const std::string app_config_name = "app.config.XML";
 const std::string monitor_pro_id_tmp = "MonitorProcessID.tmp";

//在系统刚开始运行时初始化系统环境
//1、检测配置文件，读取配置
//2、启动进程
//3、设置日志文件目录
BOOL InitSysEnv()
{
	bool ret = true;
    bool bAutoStart = false;
	int icount = 0;
    const std::string mapKey = "driver";
    const std::string gwFile = "driver";


	LogWrapper::Info("InitSysEnv().........");

	char pathBuf[512] ="";
	GetCurrentDirectory(512,pathBuf);
    std::string strPathBuf = pathBuf;
	std::string strAppConfigFile = strPathBuf + "\\"+ app_config_name;
	//std::string strProIdFile = strPathBuf + "\\"+ monitor_pro_id_tmp;

	CSysConfig sysConfig(strAppConfigFile);
	std::string startType = sysConfig.GetStartType();
    g_gateWay = sysConfig.GetGateWay();
	g_psApp = sysConfig.GetChannels();

	//读取pid配置
	//g_pidConfig.SetConfigFile(strProIdFile);
	//g_gwPid = g_pidConfig.GetGateWayPID();
	//g_psChannelPid = g_pidConfig.GetChannelsPID();*/

	CProcessManage pm;
	DWORD dwPid;
    string strPid;

	if (startType == "auto")
    {//是否自动启动进程
        bAutoStart  =true;
    }

		//对gateway启动测试
		{

            PROCESS_INFO process_info;
            memset(&process_info,0x00,sizeof(PROCESS_INFO));
            process_info._app_file = g_gateWay;
            process_info._process_name= g_gateWay.substr(g_gateWay.find_last_of("\\")+1);
            process_info._app_type = AppType::DRIVER;
			process_info._check_file = strPathBuf+"\\"+"_driver";
			process_info._last_active_time = CTime::GetCurrentTime();
			process_info._last_check_time = CTime::GetCurrentTime();
			process_info._app_name  = process_info._app_file;
			process_info._time_out_count = 0;

            dwPid = pm.IsProgramRunning( g_gwPid);
			if(dwPid == 0)
			{
                if (bAutoStart)
                {//没启动则启动
                    dwPid = pm.StartProgram(g_gateWay);
                    process_info._process_id = dwPid;

                    if (dwPid == 0)
                    {
                        process_info._is_active = false;
                        process_info._start_type = StartType::FIRST_STOP;//启动失败，要求手工启动,系统不去主动启动
                        LogWrapper::Error("创建gateway进程失败,app：%s",g_gateWay.c_str());
                    }
                    else
                    {//记录创建的进程
                        g_pidConfig.SetGateWayPID(dwPid);
                        char szPid[64] = "";
                        sprintf(szPid,"%d",dwPid);
                        g_gwPid = szPid;

                        process_info._is_active = true;
                        process_info._start_type = StartType::FIRST_START;

                        LogWrapper::Debug("创建gateway进程成功,app：%s ,pid：%d",g_gateWay.c_str(),dwPid);
                        //休眠3's,等待gateway启动
                        Sleep(3000);
                    }
                }
                else
                {//如果非自动读取
					LogWrapper::Debug("gateway进程非自动启动,app：%s ",g_gateWay.c_str());
                    process_info._process_id = dwPid;
                    process_info._is_active = false;
                    process_info._start_type = StartType::FIRST_STOP;
                }
			}
			else
			{
				process_info._process_id = dwPid;
				process_info._is_active = true;
                process_info._start_type = StartType::FIRST_START;
				LogWrapper::Debug("存在gateway原进程,app：%s ,pid：%d",g_gateWay.c_str(),dwPid);
			}
			//插入对应
			g_piMap.insert(make_pair(mapKey,process_info));
		}

		//if (ret)
		{//如果连gateway都没启动，说明配置错误

			//对app启动测试
			for(std::vector<Pair>::size_type i=0;i<g_psApp.size();i++)
			{
				PROCESS_INFO process_info;
				process_info._app_file = g_psApp[i].second;
				process_info._process_name = g_psApp[i].second.substr(g_psApp[i].second.find_last_of("\\")+1);
                process_info._app_type = AppType::APP;
				process_info._last_active_time = CTime::GetCurrentTime();
				process_info._last_check_time = CTime::GetCurrentTime();
				process_info._time_out_count = 0;

				std::string sPid = g_pidConfig.GetChannelPID(g_psApp[i].first);
				
				dwPid = pm.IsProgramRunning(sPid);
				if (dwPid == 0)
				{//程序未启动
					std::string prog = g_psApp[i].second + " ";
					prog += g_psApp[i].first;
                    process_info._check_file = strPathBuf+ "\\" +"_app_"+g_psApp[i].first;
                    process_info._app_name = process_info._app_file +" "+ g_psApp[i].first;

                    if (bAutoStart)
                    {
 					    dwPid = pm.StartProgram(prog);
    					
					    process_info._process_id = dwPid;

					    if (dwPid == 0)
					    {
						    process_info._is_active = false;
                            process_info._start_type = StartType::FIRST_STOP;
        				    LogWrapper::Error("创建app进程失败,app：%s",prog.c_str());
						    //std::cerr<<"创建进程失败"<<std::endl;
					    }
					    else
					    {//记录创建的进程
						    icount ++;
						    g_pidConfig.SetChannelPID(g_psApp[i].first,dwPid);
                            for(std::vector<Pair>::size_type j=0;j<g_psApp.size();j++)
                            {
                                if (g_psChannelPid[j].first ==g_psApp[i].first )
                                {//更新pid
                                    char szPid[64] = "";
                                    sprintf(szPid,"%d",dwPid);
                                    g_psChannelPid[j].second = szPid;
                                    break;
                                }
                            }
						    process_info._is_active = true;
                            process_info._start_type = StartType::FIRST_START;
						    LogWrapper::Debug("创建app进程成功,app：%s ,pid：%d",prog.c_str(),dwPid);
					    }
                   }
                    else
                    {//如果不是自动启动
                        process_info._process_id = dwPid;
                        process_info._is_active = false;
                        process_info._start_type = StartType::FIRST_STOP;
                   }
				}
				else
				{
					process_info._process_id = dwPid;
					process_info._is_active = true;
                    process_info._start_type = StartType::FIRST_START;
					icount++;
				}
                g_piMap.insert(std::make_pair(g_psApp[i].first,process_info));

			}
			LogWrapper::Debug("存在app进程数量：%d",icount);

		}
	return ret;
}
//
////启动程序
//int StartProgram(std::string& pid,std::string strProgram)
//{
//    bool ret = false;
//   DWORD dwPid = CProcessManage::IsProgramRunning(pid);
//    if (dwPid == 0)
//    {//程序未启动
//
//        dwPid = CProcessManage::StartProgram(prog);
//        if (dwPid == 0)
//        {
//            //ret = true;
//            LogWrapper::Error("创建app进程失败,app：%s",prog.c_str());
//            //std::cerr<<"创建进程失败"<<std::endl;
//        }
//        else
//        {//记录创建的进程
//            ret = true;
//            g_pidConfig.SetChannelPID(g_psApp[i].first,dwPid);
//            //for(std::vector<Pair>::size_type j=0;j<g_psApp.size();j++)
//            //{
//            //    if (g_psChannelPid[j].first ==g_psApp[i].first )
//            //    {//更新pid
//            //        char szPid[64] = "";
//            //        sprintf(szPid,"%d",dwPid);
//            //        g_psChannelPid[j].second = szPid;
//            //        break;
//            //    }
//            //}
//            LogWrapper::Debug("创建app进程成功,app：%s ,pid：%d",prog.c_str(),dwPid);
//        }
//    }
//}


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

