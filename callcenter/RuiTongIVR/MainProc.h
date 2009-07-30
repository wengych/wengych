#ifndef __MAIN_PROC_H_
#define __MAIN_PROC_H_


#define ID_TIMER WM_USER+100

#include "SysConfig.h"


enum AppType{
    DRIVER = 0,
    APP =1,
};

enum StartType{
     FIRST_START =0,//�տ�ʼ����������Ҫ�ػ�
     FIRST_STOP,//�տ�ʼû������,����������Ҫ�ֹ�����
     MANUAL_START  ,//�ֹ�����,�������MANUAL_STOP�ˣ��Ͳ�����
     MANUAL_STOP,
     MONITOR_START,//��Ҫ�ػ�
     MONITOR_STOP,//��Ҫ����
};
//������Ϣ
typedef struct _tagProcessInfo
{
    AppType _app_type;//��driver����app
    std::string _process_name;//�ļ����ƣ�����·��
    DWORD _process_id;//����id
    std::string _app_name;//app�ļ�������·��������
    std::string _app_file;//app�ļ�����·�����ļ�����
    std::string _check_file;//Ҫ��ʱ�����ļ���ͨ�������ȷ�������Ƿ���
    CTime _last_active_time;//ָ�������ϴλʱ��
	CTime _last_check_time;//������ͼ����·��ʱ��
	CTime _last_stop_time;//����رս��̵�ʱ��
    bool _is_active;//�����Ƿ�
    StartType _start_type;
    int _time_out_count;//����ͳ�ƴ���
}PROCESS_INFO,*PPROCESS_INFO;

//map�� first����driver��˵��"driver"����app��˵����ͨ��id;
// <driver|channel_id : process_info>
typedef std::map<std::string ,PROCESS_INFO> ProcessInfoMap;

// ����ȫ�ֱ���
//�Ի��򴰿�ָ��
extern CDialog *glo_pMainDlg; 
extern HANDLE  g_hMutex;
extern CString g_szTitle;

extern std::string g_gateWay;
extern PairSet g_psApp;
extern ProcessInfoMap g_piMap;

//��ʼ��ϵͳ����
BOOL InitSysEnv();

//�����������еĳ����Ƿ�����
int GlobalOpenUniqueProcess();
//�˳�ϵͳ������������
void QuitSystem();

#endif