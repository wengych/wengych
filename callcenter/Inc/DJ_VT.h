#ifndef __DJVT_H__
#define __DJVT_H__


#include "windows.h"
#include "stdio.h"

#define MAX_CHANNEL_NUM           1024 

#define DJVT_VTDISABLE             0x00
#define DJVT_VTENABLE              0x01


typedef struct {
	WORD	wCardNum;						//�߼��忨��
	WORD	wCardType;						//�忨����
	WORD	wVTSourceNum;					//������Դ��
} VT_SYS_INFO,*PVT_SYS_INFO;

//��ɫ����ʼ������
int  WINAPI DJVT_InitVtCard(void);
void WINAPI DJVT_ReleaseVtCard(void);
void WINAPI DJVT_GetSysInfo(PVT_SYS_INFO pTmpVSIN);

int	WINAPI DJVT_ConnectFromTS(int iVTID,int iTS);
int	WINAPI DJVT_DisconnectTS(int iVTID);
int	WINAPI DJVT_GetTimeSlot(int iVTID);
int	WINAPI DJVT_GetStreamNum();
int	WINAPI DJVT_SetScale(int iVTID,int iValue);
int	WINAPI DJVT_SetScaleEx(int iVTID,int iValue);
int	WINAPI DJVT_GetScale(int iVTID);


//�����Ӻ�����Ϊ��֧�ֻ���������Դ
int WINAPI DJEC_SetCardRes(int iECRes);       //���û���������Դ��
int WINAPI DJEC_ConnectFromTS(int iECID,int iTS);  
int	WINAPI DJEC_DisconnectTS(int iECID);
int WINAPI DJEC_GetTimeSlot(int iECID);
int WINAPI DJEC_ConnectReferenceTS(int iECID,int iTS);
int	WINAPI DJEC_DisConnectReferenceTS(int iECID);

#endif
