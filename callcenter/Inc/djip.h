/************************************************************************

        (c) COPYRIGHT 2000-2008 by Oriental Communicaton System, Inc.
                          All rights reserved.

This software is confidential and proprietary to Oriental Communicaton 
System, Inc.  No part of this software may be reproduced,stored, 
transmitted, disclosed or used in any form or by any means other 
than as expressly provided by the written license agreement between 
Oriental Communicaton System and its licensee.

FileName:       
Author:          
Version:         
Date:             
Description:   
Others:
History:
1.	Date:   
Author:        
Modification:
                                                     
************************************************************************/
#ifndef	__DJ_IP_H__
#define	__DJ_IP_H__

#include <windows.h>

#define    DJ_OK                          0
#define    GET_INT_INFO_ERROR             -1     /*��ȡ��ʼ����Ϣ����*/
#define    SYS_CHECK_READY_ERROR          -2     /*���DSp�Ƿ�Ready����*/
#define    VAD_LEVEL_ERROR                -3     /*��ȡVAD Level����*/
#define    DTMF_ON_TIME_ERROR             -4      /*��ȡDTMF������ʱ�����*/
#define    DTMF_OFF_TIME_ERROR            -5      /*��ȡDTMF�½���ʱ�����*/
#define    PACKET_LOSS_RECOVERY_ERROR     -6      /*��ȡ���ݰ���ʧ�ָ�ʱʹ�õ�֡�ĸ�������*/
#define    CODER_TYPE_ERROR               -7      /*��ȡ�������ʹ���*/
#define    FRAME_SIZE_ERROR               -8      /*��ȡ���ʱ������*/
#define    CHANNEL_ERROR                  -9      /*ͨ���Ŵ���*/
#define    NOT_VALID_DATA                 -10     /*�Ƿ�����*/
#define    NEW_CHANNEL_ERROR              -11     /*����ȫ��ͨ����������*/
#define    CHANNEL_INIT_ERROR             -12     /*ͨ����ʼ������*/
#define    INIT_SOCKET_ERROR              -13     /*��ʼ��Socket����*/
#define    CREATE_SOCKET_ERROR            -14     /*����Socket����*/
#define    SOCKET_BIND_ERROR              -15     /*��Socket����*/
#define    SET_SEND_BUFFER_ERROR          -16     /*���÷���Scoket Buffer����*/
#define    SET_IP_HDRINCL_ERROR           -17     /*�����Լ���IPͷ����*/
#define    CLOSE_SOCKET_ERROR             -18     /*�ر�Socket����*/
#define    CREATE_THREAD_ERROR            -20     /*�����̴߳���*/
#define    PARAMETER_ERROR                -21     /*��������*/
#define    CAN_NOT_WRITE                  -22     /*����д*/
#define    SYS_INIT_ERROR                 -23     /*��ʼ��ʧ��*/
#define    NO_SYS_INIT_ERROR              -24     /*û�г�ʼ���͵��ú���*/
#define    BUFFER_SIZE_ERROR              -25
#define    CLOSE_CHANNEL_ERROR            -26
#define    D081A4P_LOAD_DEV_ERROR         -27
#define    VOICE_BUFFER_NULL              -30

// ����DJIP.INI�Ľṹ
typedef struct 
{
	int		iDetailInfo;

	WORD	wVAD_CNG_Enable;
	short	shVAD_Level;
	
	WORD	wDTMF_TransMode;
	WORD	wDTMF_On_Time;
	WORD	wDTMF_Off_Time;

	WORD	wEC_Enable;

	WORD	wPLR_OptNum;
	WORD	wPLR_MaxNum;

	WORD	wCoder;
	WORD	wFrameSize;

	WORD	wPort_Call;
	WORD	wPort_RTP;
	short    wSendVolumeSize;
	short    wRecvVolumeSize;

} TYPE_DJIP_INI_PARAMETER;

// ����ϵͳ�����Ľṹ
typedef struct 
{
	int		iTotalNum;
} TYPE_DJIP_SYS_PARAMETER;

//int iTotalIPNum; 
	
#ifdef __cplusplus
extern "C" {
#endif

// ------------------
int		WINAPI	DJIP_SetRtpFlag(unsigned short wRtpFlag);
int		WINAPI	DJIP_Sys_Init(void);   /*ϵͳ��ʼ��*/
int		WINAPI	DJIP_Sys_Release(void);
void	WINAPI	DJIP_Sys_GetIniInfo ( TYPE_DJIP_INI_PARAMETER *pIniInfo );
void	WINAPI	DJIP_Sys_GetSysInfo ( TYPE_DJIP_SYS_PARAMETER *pSysInfo );

int		WINAPI	DJIP_Ch_GetTimeSlot ( int iChID );
int		WINAPI	DJIP_Ch_ConnectFromTS ( int iChID, int iTS );
int		WINAPI	DJIP_Ch_DisconnectTS ( int iChID );

//int		WINAPI  DJIP_GetVocFromDsp(int channel,char* buffer);
int		WINAPI  DJIP_GetVocFromDsp(int channel,char* buffer,int BufferLen);
int		WINAPI  DJIP_GetVocFromDspEx(int channel,char* buffer,int BufferLen);
int		WINAPI  DJIP_PutVocToDsp(int channel,char* buffer);
int		WINAPI  DJIP_PutSilenceToDsp(int channel);
int		WINAPI  DJIP_IsSilenceBuf(char*);

short   WINAPI  DJIP_RtpDecoder( unsigned short CID, char *pBuffer, unsigned short BufferLen );
short   WINAPI  DJIP_JitterBufferDispatcher( unsigned short CID );

int     WINAPI  DJIP_Channel_Init(int Channel);
int     WINAPI  DJIP_OpenChannel(int CID);
int     WINAPI  DJIP_CloseChannel(int CID);
int     WINAPI DJIP_OpenChannelEx(int CID,
							 unsigned long LocalIP,
							 unsigned long RemoteIP,
							 unsigned short LocalPort,
							 unsigned short RemotePort);
int     WINAPI DJIP_CloseChannelEx(int CID);

int 	WINAPI  DJIP_SetChannelCoderType(short Channel,int CodeType,short SingleOrDouble);
int	    WINAPI  DJIP_GetChannelCodeType ( short Channel,unsigned short RecvAndSendFlag );

int     WINAPI  DJIP_SetChannelEC(int CID,unsigned short ECValue);
int     WINAPI  DJIP_GetChannelEC(int CID);         /*��ȡEC�Ƿ�ʹ��*/

int     WINAPI  DJIP_SetChannelJitterSize(int CID,unsigned char JitterBufferSize);
int     WINAPI  DJIP_GetChannelJitterSize(int CID);  /*��ȡJitter buffer�Ĵ�С*/

int     WINAPI  DJIP_SetChannelVadAndCng( int CID, unsigned char VadAndCngEnable );
int     WINAPI  DJIP_GetChannelVadAndCng(int CID);  /*��ȡVAD�Ƿ�ʹ��*/

int     WINAPI  DJIP_SetChannelVadLevel( int CID, short VadLevel );
int     WINAPI  DJIP_GetChannelVadLevel(int CID);   /*��ȡͨ����VAD����*/

int     WINAPI DJIP_SetChannelSendVolume( int CID, short VolumeLevel );
int     WINAPI DJIP_SetChannelRecvVolume( int CID, short VolumeLevel );
int     WINAPI DJIP_GetChannelSendVolume( int CID );
int     WINAPI DJIP_GetChannelRecvVolume( int CID );
int     WINAPI DJIP_GetWriteFlag(int channel);     /*��ȡд��־*/
unsigned long WINAPI DJIP_GetRecvOctets(int CID);
unsigned long WINAPI DJIP_GetRecvPacket(int CID);
unsigned long WINAPI DJIP_GetLostPacket(int CID);
WORD WINAPI DJIP_GetStartTimeSlot(int CID);

//

//
#ifdef __cplusplus
}
#endif

#endif

