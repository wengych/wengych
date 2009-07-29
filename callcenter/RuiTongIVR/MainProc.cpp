#include "stdafx.h"
#include "RuiTongIVRGUI.h"
#include "MainProc.h"
#include <direct.h>
#include "Message.h"
#include "ProcessManage.h"
#include "SysInfoList.h"

//CSysInfoDisplay glo_myDisplay(MY_SERVER_NAME,LOG_FILE);
//CSocketGlobalDataStorage glo_storeData(MY_SERVER_NAME,MainProcCallback,&glo_myDisplay);//�����ļ��������
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

//��ϵͳ�տ�ʼ����ʱ��ʼ��ϵͳ����
//1����������ļ�����ȡ����
//2����������
//3��������־�ļ�Ŀ¼
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

	//��ȡpid����
	//g_pidConfig.SetConfigFile(strProIdFile);
	//g_gwPid = g_pidConfig.GetGateWayPID();
	//g_psChannelPid = g_pidConfig.GetChannelsPID();*/

	CProcessManage pm;
	DWORD dwPid;
    string strPid;

	if (startType == "auto")
    {//�Ƿ��Զ���������
        bAutoStart  =true;
    }

		//��gateway��������
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
                {//û����������
                    dwPid = pm.StartProgram(g_gateWay);
                    process_info._process_id = dwPid;

                    if (dwPid == 0)
                    {
                        process_info._is_active = false;
                        process_info._start_type = StartType::FIRST_STOP;//����ʧ�ܣ�Ҫ���ֹ�����,ϵͳ��ȥ��������
                        LogWrapper::Error("����gateway����ʧ��,app��%s",g_gateWay.c_str());
                    }
                    else
                    {//��¼�����Ľ���
                        g_pidConfig.SetGateWayPID(dwPid);
                        char szPid[64] = "";
                        sprintf(szPid,"%d",dwPid);
                        g_gwPid = szPid;

                        process_info._is_active = true;
                        process_info._start_type = StartType::FIRST_START;

                        LogWrapper::Debug("����gateway���̳ɹ�,app��%s ,pid��%d",g_gateWay.c_str(),dwPid);
                        //����3's,�ȴ�gateway����
                        Sleep(3000);
                    }
                }
                else
                {//������Զ���ȡ
					LogWrapper::Debug("gateway���̷��Զ�����,app��%s ",g_gateWay.c_str());
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
				LogWrapper::Debug("����gatewayԭ����,app��%s ,pid��%d",g_gateWay.c_str(),dwPid);
			}
			//�����Ӧ
			g_piMap.insert(make_pair(mapKey,process_info));
		}

		//if (ret)
		{//�����gateway��û������˵�����ô���

			//��app��������
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
				{//����δ����
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
        				    LogWrapper::Error("����app����ʧ��,app��%s",prog.c_str());
						    //std::cerr<<"��������ʧ��"<<std::endl;
					    }
					    else
					    {//��¼�����Ľ���
						    icount ++;
						    g_pidConfig.SetChannelPID(g_psApp[i].first,dwPid);
                            for(std::vector<Pair>::size_type j=0;j<g_psApp.size();j++)
                            {
                                if (g_psChannelPid[j].first ==g_psApp[i].first )
                                {//����pid
                                    char szPid[64] = "";
                                    sprintf(szPid,"%d",dwPid);
                                    g_psChannelPid[j].second = szPid;
                                    break;
                                }
                            }
						    process_info._is_active = true;
                            process_info._start_type = StartType::FIRST_START;
						    LogWrapper::Debug("����app���̳ɹ�,app��%s ,pid��%d",prog.c_str(),dwPid);
					    }
                   }
                    else
                    {//��������Զ�����
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
			LogWrapper::Debug("����app����������%d",icount);

		}
	return ret;
}
//
////��������
//int StartProgram(std::string& pid,std::string strProgram)
//{
//    bool ret = false;
//   DWORD dwPid = CProcessManage::IsProgramRunning(pid);
//    if (dwPid == 0)
//    {//����δ����
//
//        dwPid = CProcessManage::StartProgram(prog);
//        if (dwPid == 0)
//        {
//            //ret = true;
//            LogWrapper::Error("����app����ʧ��,app��%s",prog.c_str());
//            //std::cerr<<"��������ʧ��"<<std::endl;
//        }
//        else
//        {//��¼�����Ľ���
//            ret = true;
//            g_pidConfig.SetChannelPID(g_psApp[i].first,dwPid);
//            //for(std::vector<Pair>::size_type j=0;j<g_psApp.size();j++)
//            //{
//            //    if (g_psChannelPid[j].first ==g_psApp[i].first )
//            //    {//����pid
//            //        char szPid[64] = "";
//            //        sprintf(szPid,"%d",dwPid);
//            //        g_psChannelPid[j].second = szPid;
//            //        break;
//            //    }
//            //}
//            LogWrapper::Debug("����app���̳ɹ�,app��%s ,pid��%d",prog.c_str(),dwPid);
//        }
//    }
//}


int GlobalOpenUniqueProcess()
{
	g_hMutex=::CreateMutex(NULL,TRUE,g_szTitle);   
	if   (g_hMutex!=NULL)   
	{   
		if   (GetLastError()==ERROR_ALREADY_EXISTS)   
		{  //��ʾ�Ѿ�����
			HWND hWndPrev=::GetWindow(::GetDesktopWindow(),GW_CHILD);    

			while(::IsWindow(hWndPrev))
			{
				//�жϴ����Ƿ�������Ԥ�����õı�ǣ����У���������Ѱ�ҵĴ��ڣ����������
				if(::GetProp(hWndPrev,g_szTitle))    
				{
					//�������������С������ָ����С��
					if (::IsIconic(hWndPrev))      
						::ShowWindow(hWndPrev,SW_RESTORE);
					//��Ӧ�ó���������ڼ��
					::SetForegroundWindow(hWndPrev);

					::ReleaseMutex(g_hMutex);
					::CloseHandle(g_hMutex);

					return 1;                      //�˳�ʵ����
				}
				//����Ѱ����һ�����ڡ�
				hWndPrev = ::GetWindow(hWndPrev,GW_HWNDNEXT); 
			}
			::MessageBox(NULL,"����һ�����ʵ�������У����Ҳ������������ڣ����ֹ�ɱ��ԭ���̡�","",MB_OK);
			LogWrapper::Error("����һ�����ʵ�������У����Ҳ������������ڣ����ֹ�ɱ��ԭ���̡�");
		} 
		else
		{//�����ڣ����봴��
			return 0;
		}
	}
	else
	{
		::MessageBox(NULL,"ϵͳ��ʼ���ź�ʧ�ܣ�����ϵͳ��","",MB_OK);
		LogWrapper::Error("ϵͳ��ʼ���ź�ʧ�ܣ�����ϵͳ��");
	}

	return -1;
}



void QuitSystem()
{
	//���������̷�����ͣ�����Ϣ
//	CMessage::SendStopMonitMsg();
	LogWrapper::Error("ϵͳ�˳��У�");

	//�ͷ��ź�
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

