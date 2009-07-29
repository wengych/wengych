#ifndef __MAIN_PROC_H_
#define __MAIN_PROC_H_


#define ID_TIMER WM_USER+100

#include "SysConfig.h"

// 定义全局变量
//对话框窗口指针
extern CDialog *glo_pMainDlg; 
extern HANDLE  g_hMutex;
extern CString g_szTitle;
extern UINT g_iChannelNum;
extern PairSet g_psApp;

//初始化系统环境
BOOL InitSysEnv();

//查找正在运行的程序，是否启动
int GlobalOpenUniqueProcess();
//退出系统，进行清理工作
void QuitSystem();

#endif