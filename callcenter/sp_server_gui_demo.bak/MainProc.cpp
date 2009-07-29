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
UINT g_iChannelNum = 0;
PairSet g_psApp;

 const std::string app_config_name = "app.config.XML";
 const std::string monitor_pro_id_tmp = "MonitorProcessID.tmp";

//��ϵͳ�տ�ʼ����ʱ��ʼ��ϵͳ����
//1����������ļ�����ȡ����
//2����������
//3��������־�ļ�Ŀ¼
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
	//��ȡapp�ļ�����
	CSysConfig sysConfig(strAppConfigFile);
	std::string startType = sysConfig.GetStartType();
	std::string gateWay = sysConfig.GetGateWay();
	g_psApp = sysConfig.GetChannels();

	//��ȡpid����
	CPIDConfig pidConfig(strProIdFile);
	std::string gwPid = pidConfig.GetGateWayPID();
	PairSet psPid = pidConfig.GetChannelsPID();

	CProcessManage pm;
	DWORD dwPid;

	if (startType == "auto")
	{

		//��gateway��������
		{
			dwPid = (DWORD)atol(gwPid.c_str());
			dwPid = pm.IsProgramRunning(dwPid);
			if(dwPid == 0)
			{
				dwPid = pm.StartProgram(gateWay);
				if (dwPid == 0)
				{
					//ret &= false;
					LogWrapper::Error("����gateway����ʧ��,app��%s",gateWay.c_str());
				}
				else
				{//��¼�����Ľ���
					pidConfig.SetGateWayPID(dwPid);
					LogWrapper::Debug("����gateway���̳ɹ�,app��%s ,pid��%d",gateWay.c_str(),dwPid);
					//����3's,�ȴ�gateway����
					Sleep(3000);
				}
			}
			else
			{
				LogWrapper::Debug("����gatewayԭ����,app��%s ,pid��%d",gateWay.c_str(),dwPid);

			}
		}

		//if (ret)
		{//�����gateway��û������˵�����ô���

			//��app��������
			for(std::vector<Pair>::size_type i=0;i<g_psApp.size();i++)
			{
				std::string sPid = pidConfig.GetChannelPID(g_psApp[i].first);
				dwPid = (DWORD)atol(sPid.c_str());
				dwPid = pm.IsProgramRunning(dwPid);
				if (dwPid == 0)
				{//����δ����
					std::string prog = g_psApp[i].second + " ";
					prog += g_psApp[i].first;
					dwPid = pm.StartProgram(prog);
					if (dwPid == 0)
					{
						//ret &= false;
						LogWrapper::Error("����app����ʧ��,app��%s",prog.c_str());
						//std::cerr<<"��������ʧ��"<<std::endl;
					}
					else
					{//��¼�����Ľ���
						icount ++;
						pidConfig.SetChannelPID(g_psApp[i].first,dwPid);
						LogWrapper::Debug("����app���̳ɹ�,app��%s ,pid��%d",prog.c_str(),dwPid);

					}
				}
				else
					icount++;
			}
			LogWrapper::Debug("����app����������%d",icount);

		}
	}


	//if (icount == 0)
	//{//û������һ��app��˵�����ô���
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

//
//
//BOOL CSysInfoDisplay::PutLine(ErrorLevel eLevel,LPCSTR pszOutPut)
//{//����CFileOutputDisplay::PutLine()
//	DWORD dwID;
//	//CDialog* pMainDlg=(CDialog*)CWnd::FromHandle (glo_hMainWnd) ;
//	CSysInfoList *pList ;
//	switch (eLevel)
//	{
//		//��ʾ��������־����
//	case ErrorLevel::Message:
//	case ErrorLevel::Success:
//	case ErrorLevel::GeneralWarn:
//	case ErrorLevel::FatalWarn:
//	case ErrorLevel::GeneralError:
//	case ErrorLevel::FatalError:
//		dwID=IDC_LIST_SYS_ERR_INFO;
//		//��д������־
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
//	//���ñ����PutLine()
//	return PutLine(eLevel,szTemp);
//}

