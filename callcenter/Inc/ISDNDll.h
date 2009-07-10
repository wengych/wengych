#ifndef	__ISDNDLL_H__
#define	__ISDNDLL_H__

//////////////////////////////////////////////////////////
//ͨ���ͷ�ԭ����
//ʹ�� DJISDN_GetDsiconnectReason( ����, ͨ���� ) ���
//////////////////////////////////////////////////////////
enum DISCONNECT_REASON
{
	RSN_UNKNOW_REASON = 0X00,		//ԭ��δ֪
	RSN_UNALLOC_NUMBER = 0x01,		//�պ�
	RSN_NORMAL_DISCONNECT = 0X10,	//�����ĺ������ 
	RSN_USER_BUSY = 0X11,			//�û�æ
	RSN_NO_RESPOND = 0X12,			//����Ӧ
	RSN_NO_ANSWER = 0X13,			//���û�Ӧ��
	RSN_REFUSR_CALL = 0X15,			//���оܾ�
	RSN_NUMBER_ERROR = 0X1C,		//���벻ȫ
	RSN_TIMEOUT	= 0X66,				//��ʱ
	RSN_DCHANNEL_DOWN = 0Xfd,		//��·�ж�
	RSN_BCHANNEL_UNAVIABLE = 0X22,  //ͨ��������
	RSN_UNAVIABLE_CIRCULT = 0X2c,	//�޿���ͨ·
	RSN_UNSVIABLE_MSG = 0X5F,		//��Ч����Ϣ 
};

//////////////////////////////////////////////////////////
//ͨ��״̬����
//ʹ�� DJISDN_GetChnState( ����, ͨ���� ) ���
//////////////////////////////////////////////////////////
//����״̬   //
#define CH_FREE					1

//DLL�ȴ�Ӧ�ò�ͬ���ͷ���Դ
#define CH_WAIT_APP_FREE		2

//������̬(���粻ͨ��ԭ����)
#define CH_UNAVIABLE			3

//�ȴ�����֤ʵ
#define CH_WAIT_CONNECT_ACK		4

//��ͨ״̬  
#define CH_CONNECT				5 

//�ѷ��Ͳ����źţ��ȴ��Է������ͷ��ź�  
#define CH_WAIT_RELEASE			6

//�ѷ����ͷ��źţ��ȴ��Է������ͷ�֤ʵ�ź�
#define CH_WAIT_RELEASE_COMPLETE 7

//������ ���е���
#define CALLEE_WAIT_ANSWER		11 

//ȥ���� �Ѻ������ȴ����л�Ӧ
#define CALLER_WAIT_ANSWER		12

//ȥ���� �ѽ��յ�������Ϣ
#define CALLER_RECV_ALERT		21

//ȥ���� �ѽ��յ�����ȷ����Ϣ 
#define CALLER_RECV_SETUP_ACK	22

//ȥ���� �ѽ��յ����й�����Ϣ
#define CALLER_RECV_CALLPROCESS 23

#define CALLER_WAIT_SETUP_ACK	24

//////////////////////////////////////////////////////////
//ͨ����������
//ʹ�� DJISDN_SetChnState( ����, ͨ����, Action ) ����
//////////////////////////////////////////////////////////
//APP ����ͨ��״̬Ϊ OxO2 ʱ��ͬ���ͷ�ͨ����Դ
#define	CH_SET_FREE			1
//����ͨ������
#define CH_SET_CONNECT		2
//���ͨ������
#define CH_SET_DISCONNECT	3
//���з�����������Ϣ
#define CALLEE_SET_ALERTING	4
//����ͨ����������
#define	CH_SET_RESTART		5

//////////////////////////////////////////////////////////
//�������
//////////////////////////////////////////////////////////

//δ���ؽ��  //
#define C_NO_RESULT		 0
//���п���
#define C_USER_IDLE		 1
//����ժ������ͨ״̬
#define C_USER_OFFHOOK	 2
//�ص����ͣ��ȴ�����ȷ�ϱ��к�����
#define C_WAIT_CALL_PROC 3
//���������п��ܽ�������ʹ�� DJISDN_GetChnState ��������ͨ��״̬
#define C_OTHERS 10

//////////////////////////////////////////////////////////
//������� 
//////////////////////////////////////////////////////////
//δ֪  
#define CALLNUM_UNKNOWN			0x00
//���ʺ���
#define CALLNUM_INTERNATIONAL	0x01
//���ں���
#define CALLNUM_DOMESTIC		0x02
//�����ض�����
#define CALLNUM_NETWORK_SPECIFIC	0x03
//�û�����
#define CALLNUM_USER			0x04
//��չ����
#define CALLNUM_RESERVE			0x07


#ifdef	__cplusplus
extern "C" {
#endif

int WINAPI DJISDN_InitSystem();
void WINAPI DJISDN_ExitSystem();
void WINAPI DJISDN_GetEvent();

int WINAPI DJISDN_GetChnState(int nPCM, int nCHN);
int WINAPI DJISDN_GetChnStateA(int nPCM, int nCHN);

int WINAPI DJISDN_SetChnState(int nPCM, int nCHN, int nState, int nParam=0);
void WINAPI DJISDN_GetCallerNumber(int nPCM, int nCHN, char * szNumber);
void WINAPI DJISDN_GetCallerSubAddr(int nPCM, int nCHN, char * szSubAddr);
void WINAPI DJISDN_GetCalleeNumber(int nPCM, int nCHN, char * szNumber);
void WINAPI DJISDN_GetCalleeSubAddr(int nPCM, int nCHN, char * szSubAddr);

bool WINAPI DJISDN_GetCalloutChn( int * nPCM, int * nCHN );

void WINAPI DJISDN_GetChangeNumber(int nPCM, int nCHN, char * szNumber);

int WINAPI DJISDN_Callout(int nPCM, int nCHN, char * szCalleeNumber, char * szCalleeSubAddr="", char * szCallerNumber="", char * szCallerSubAddr="");
int WINAPI DJISDN_CalloutA(int nPCM, int nCHN, char * szCalleeNumber, char * szCalleeSubAddr, char * szCallerNumber, char * szCallerSubAddr, int nCalleeNumType=0x02, int nCallerNumType=0x02);
int WINAPI DJISDN_CalloutB(int nPCM, int nCHN, char * szCalleeNumber, char * szCalleeSubAddr, char * szCallerNumber, char * szCallerSubAddr, int nCalleeNumType=0x02, int nCallerNumType=0x02);
int WINAPI DJISDN_CalloutC(int nPCM, int nCHN, char * szCalleeNumber , bool bSendEnd);

int WINAPI DJISDN_GetCalloutResult(int nPCM, int nCHN);
int WINAPI DJISDN_GetDisconnectReason(int nPCM, int nCHN);
bool WINAPI DJISDN_SendRawData(int nPCM, BYTE * pRawData, int nLen);
//
BYTE * WINAPI DJISDN_GetRawDate(int *pPCM, int *pLen);
int CCB_RawDateGetCallNum(int *pPCM, int *pCHN, char *pCalleeNum, char *pCallerNum);

void WINAPI DJISDN_SetSystemMode( int nMode , int nParam );

int WINAPI DJISDN_GetErrorPacket(int nPCM);
#ifdef	__cplusplus
}
#endif
#endif


// 