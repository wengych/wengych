#ifndef __DJCONFNEW_H__
#define __DJCONFNEW_H__

#include "djconf.h"


////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_CONF_BOARD_NUM			  4		//ϵͳ�����������忨��(����忨)
#define CONF_CARD_NUM_PER_BOARD		  4     //ÿƬ���鿨�������߼��忨��
#define MAX_CONF_CARD_NUM_NEW	      MAX_CONF_BOARD_NUM*CONF_CARD_NUM_PER_BOARD	//ϵͳ������������߼��忨��
#define MAX_CONF_RES_NUM_PER_CARD     64	//ÿƬ�����߼��忨��Դ��
#define MAX_CONF_GROUP_NUM_PER_CARD   32	//ÿƬ�����߼��忨������������������
#define MAX_CONF_GROUP_NUM_NEW	      512	//ϵͳ������������������
#define MAX_MEMBER_NUM_PER_GROUP_NEW  512   //�����������������Ա��
#define MAX_SPEAKER_NUM_PER_GROUP     63	//������������ӵ�з���Ȩ������Ա��
#define MAX_SPEAKING_NUM_PER_GROUP    6	    //������������ͬʱ˵��������Ա��

//DJConf_SetParam��ParamID�Ķ���
#define DTMF_BATE                 1  //����0ΪDISABLE,����1ΪENABLE,Ĭ��Ϊ1


//DJConf_SetParam��DTMF_BATE��ParamValue�Ķ���
#define DTMF_BATE_DISABLE       0
#define DTMF_BATE_ENABLE        1


typedef enum {
	CONF_NULL,								//����(û��ͨ���������)
	CONF_LISTEN,							//ֻ����˵(����)
	CONF_SPEAKER_NORMAL,					//���ж�̬����Ȩ
	CONF_SPEAKER_ALWAYS,					//���Ǿ��з���Ȩ
	CONF_SPEAKER_ONLY						//ֻ�з���Ȩ(ֻ˵���������ڶԻ������)
}MEMBER_MODE;

typedef struct {
	WORD	wCardNum;						//�߼��忨��
	WORD	wCardType;						//�忨����
	WORD	wGroupNum;						//����������
	WORD    wNewConfFlag;					//�»��鹦�ܱ�־
	WORD	wGroupMaxMember;				//�����������������Ա��
	WORD	wGroupMaxSpeaker;				//��������������з���Ȩ������Ա��
	WORD	wGroupMaxSpeaking;				//������������ͬʱ˵��������Ա��
	WORD	wMaxSilenceTime;				//���Ĭʱ��
	WORD	wJoinedByEnergy;				//��ռʽ���Ա�־
	WORD	wAddress[MAX_CONF_CARD_NUM];
	WORD	wStream[MAX_CONF_CARD_NUM];
} CONF_SYS_INFO_NEW;

typedef struct {
	WORD			wGroupID;				//������ID��
	WORD			wMemberID;				//�������г�ԱID��

	BYTE			cbChnlType;				//ͨ������
	WORD			wChnlNo;				//ͨ����
	WORD			wResNo;                 //������Ӧ�����ʱ϶

	int				eMode;					//ģʽ
	BOOL			bActive;				//��ǰ���ڻ״̬��־

	char			cAtteVal;				//�������
	BYTE			cbNoiseSupp;			//��������
	DWORD			dwVADKeepTime;			//VAD״̬��ʱ��
	BOOL			bVADFlag;				//�Ƿ���˵��״̬
} MEMBER_CTRL;

typedef struct {
	WORD			wGroupID;				//������ID��
	
	WORD			wMaxMemberNum;			//�����������Ա��
	WORD			wMaxSpeakerNum;			//�����ܹ���������Ա��
	WORD			wMaxSpeakingNum;		//����ͬʱ��������Ա��
	WORD			wMinSlienceTime;		//��С��Ĭʱ��
	WORD			wJoinedByEnergy;		//��ռʽ���Ա�־

	WORD			wCardNo;				//��ԴԤ�����߼��忨��
    WORD            wGroupNo;               //�������Ӧ���߼����Ļ������

	WORD			wMemberNum;				//��ǰ�����Ա��
	WORD			wResNum;				//��ǰռ����Դ��
	WORD			wListenNum;				//��ǰ������Ա��
	WORD			wListenNo;              //���鵱ǰ���������ʱ϶
	WORD            wListenSlot;            //���鵱ǰʱ϶����
	WORD			wSpeakerNum;			//��ǰ�����Գ�Ա��
	WORD			wSpeakingNum;			//��ǰ���ڷ��Գ�Ա��
	
	MEMBER_CTRL	MemberCtrl[MAX_MEMBER_NUM_PER_GROUP_NEW];//ָ������Ա����
} GROUP_CTRL;

#ifndef __BUILD_FOR_SYS__

//functions:
#ifdef	__cplusplus
extern "C" {
#endif

//�»����ʼ������
int  WINAPI DJConf_InitConfCardNew(void);
void WINAPI DJConf_ReleaseConfCardNew(void);
void WINAPI DJConf_GetSysInfoNew(CONF_SYS_INFO_NEW *TmpCSIN);

//�»����������
int  WINAPI DJConf_CreateConfGroup(int iMaxMember, int iMaxSpeaker, int iMaxSpeaking, 
								   int iMaxSilenceTime, int iJoinedByEnergy);
int  WINAPI DJConf_CreateConfGroupEx(int iGroupID, int iMaxMember, int iMaxSpeaker, 
								     int iMaxSpeaking, int iMaxSilenceTime, int iJoinedByEnergy);
int WINAPI DJConf_FreeConfGroup(int iGroupID);

int  WINAPI DJConf_JoinConfGroup(int iGroupID, BYTE cbChnlType, WORD wChnlNo, MEMBER_MODE eMode,
								 char chAtte, BYTE cbNoiseSupp, BOOL bCreateGroup);
int  WINAPI DJConf_ExitConfGroup(BYTE cbChnlType, WORD wChnlNo, BOOL bFreeGroupKeep);
int  WINAPI DJConf_ExitConfGroupEx(MEMBER_CTRL* pMemberCtrl, BOOL bFreeGroupKeep);

//�»�����/��Ա��Ϣ
int  WINAPI DJConf_GetGroupInfoNew(int iGroupID, GROUP_CTRL *TmpGroupCtrl);
int  WINAPI DJConf_GetGroupMemberInfo(int iGroupID, int iMemberID, MEMBER_CTRL *TmpMemberCtrl);
long WINAPI DJConf_GetChnlGroupInfoNew(BYTE cbChnlType, WORD wChnlNo);
int  WINAPI DJConf_SetChnlAtte(BYTE cbChnlType, WORD wChnlNo, char chAtte);
int  WINAPI DJConf_SetChnlAtteEx(MEMBER_CTRL* pMemberCtrl, char chAtte);

//add by lanjun for get conf StreamNum 2005.5.18
int WINAPI DJConf_GetStreamNum();
int WINAPI DJConf_SetParam(int ParamID,int ParamValue);//ParamID ���忴ǰ���#define

int WINAPI DJConf_GetAllFreeRes();

#ifdef	__cplusplus
}
#endif

#endif
////////////////////////////////////////////////////////////////////////////////////////////
#endif //#ifndef __DJCONFNEW_H__