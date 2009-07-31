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

// ������Ϣ
// ProcessInfo::is_active is set to false default.
// But will be set to true if StartProcess success.
struct ProcessInfo
{
    AppType _app_type;              // ��driver����app
    std::string process_name;       // �ļ����ƣ�����·��
    DWORD process_id;               // ����id
    std::string file_name;          // ��ִ���ļ���,��·��
    std::string args;               // ������������
    std::string check_file;         // Ҫ��ʱ�����ļ���ͨ�������ȷ�������Ƿ���
    std::string check_file_lock;    // �����ļ�����
    CTime last_active_time;         // ָ�������ϴλʱ��
	CTime _last_stop_time;          // ����رս��̵�ʱ��
    bool is_active;                 // �����Ƿ�
    int time_out_count;             // ����ͳ�ƴ���
    bool auto_start;                // �����Ƿ��Զ�����

    ProcessInfo();
    ProcessInfo(const ProcessInfo&);
    ProcessInfo(AppType /*app_type*/,
        const std::string& /*execute file name*/,
        const std::string& /*command line arguments*/,
        const std::string& /*active file name*/,
        bool);

    ProcessInfo& operator=(const ProcessInfo&);

    // std::string _app_name;   // app�ļ�������·��������
    // StartType _start_type;
    // CTime last_check_time;     // ������ͼ����·��ʱ��
};
typedef ProcessInfo* PPROCESS_INFO;

// ����ȫ�ֱ���
//�Ի��򴰿�ָ��
extern CDialog *glo_pMainDlg;
extern HANDLE  g_hMutex;
extern CString g_szTitle;

// extern std::string g_gateWay;
// extern PairSet g_psApp;
// extern ProcessInfoMap g_piMap;

//�����������еĳ����Ƿ�����
int GlobalOpenUniqueProcess();
//�˳�ϵͳ������������
void QuitSystem();

#endif