#ifndef __MAIN_PROC_H_
#define __MAIN_PROC_H_


#define ID_TIMER WM_USER+100

#include "SysConfig.h"

// ����ȫ�ֱ���
//�Ի��򴰿�ָ��
extern CDialog *glo_pMainDlg; 
extern HANDLE  g_hMutex;
extern CString g_szTitle;
extern UINT g_iChannelNum;
extern PairSet g_psApp;

//��ʼ��ϵͳ����
BOOL InitSysEnv();

//�����������еĳ����Ƿ�����
int GlobalOpenUniqueProcess();
//�˳�ϵͳ������������
void QuitSystem();

#endif