#ifndef	_FSK_MIX_H_
#define	_FSK_MIX_H_

#include "windows.h"

#define FSK_CH_TYPE_160	1
#define FSK_CH_TYPE_E1	2

#ifdef __cplusplus
extern "C" {
#endif


int WINAPI DJFsk_InitForFsk(int Mode);
void WINAPI DJFsk_ResetFskBuffer ( int trunkID ,int Mode);
int WINAPI DJFsk_CheckSendFSKEnd ( int vocID ,int Mode);
int WINAPI DJFsk_SendFSK(int trunkID,BYTE* pInfo,WORD wSize,int Mode);
int WINAPI DJFsk_GetFSK(int trunkID,BYTE* pInfo,int Mode);
void WINAPI DJFsk_StopSend(int trunkID,int Mode);
void WINAPI DJFsk_Release();
int WINAPI DJFsk_SendFSKA(int trunkID,BYTE* pInfo,WORD wSize,int Mode,int MarkNum);

//add by yezm, 2004/11/29
int WINAPI DJFsk_SendFSKBit(int trunkID, BYTE* pInfo, WORD wSize, int Mode);
//end add.

//D161Aģ�⿨����ģ��飬ģ����������նˣ����պͷ��Ͷ��ŵ�API����
//2003/12/31,yezhimin add.
int WINAPI DJSM_Init(int iStartCh, int iEndCh, int Mode, char *strNum);
int WINAPI DJSM_SendSM(int ChannelNo, char *ReceiveID, int MailNum, char *strMsg);
int WINAPI DJSM_GetSM(char *SenderID, int *MailNum, char *strMsg, char *strTime);
void WINAPI DJSM_Release();
int WINAPI DJSM_GetChannelState(int ChannelNo, int *state, int *smdirection, int *ErrorCode, char *strErr);
bool WINAPI DJSM_CheckSM();

//���ϣ���2003/12/31,  yezhimin add.

// add next fuction in 2005.10.26
int WINAPI DJFsk_SendFSK_ThenReset(int trunkID,BYTE* pInfo,WORD wSize,int Mode);

#ifdef __cplusplus
}
#endif

#endif