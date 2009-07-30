#ifndef __MAIN_PROC_H_
#define __MAIN_PROC_H_


#define ID_TIMER WM_USER+100

#include "SysConfig.h"


enum AppType{
    DRIVER = 0,
    APP =1,
};

enum StartType{
     FIRST_START =0,//刚开始就启动，需要守护
     FIRST_STOP,//刚开始没有启动,不启动，需要手工启动
     MANUAL_START  ,//手工启动,如果是是MANUAL_STOP了，就不启动
     MANUAL_STOP,
     MONITOR_START,//需要守护
     MONITOR_STOP,//需要重启
};
//进程信息
typedef struct _tagProcessInfo
{
    AppType _app_type;//是driver还是app
    std::string _process_name;//文件名称，不带路径
    DWORD _process_id;//进程id
    std::string _app_name;//app文件名，带路径，参数
    std::string _app_file;//app文件（带路径和文件名）
    std::string _check_file;//要定时检查的文件，通过这个来确定进程是否存活
    CTime _last_active_time;//指定进程上次活动时间
	CTime _last_check_time;//最近发送检查线路的时间
	CTime _last_stop_time;//最近关闭进程的时间
    bool _is_active;//进程是否活动
    StartType _start_type;
    int _time_out_count;//进程统计次数
}PROCESS_INFO,*PPROCESS_INFO;

//map的 first：对driver来说是"driver"，对app来说，是通道id;
// <driver|channel_id : process_info>
typedef std::map<std::string ,PROCESS_INFO> ProcessInfoMap;

// 定义全局变量
//对话框窗口指针
extern CDialog *glo_pMainDlg; 
extern HANDLE  g_hMutex;
extern CString g_szTitle;

extern std::string g_gateWay;
extern PairSet g_psApp;
extern ProcessInfoMap g_piMap;

//初始化系统环境
BOOL InitSysEnv();

//查找正在运行的程序，是否启动
int GlobalOpenUniqueProcess();
//退出系统，进行清理工作
void QuitSystem();

#endif