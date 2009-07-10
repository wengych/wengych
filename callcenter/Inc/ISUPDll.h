#ifndef __ISUP_DLL__
#define __ISUP_DLL__

//////////////////////////////////////////////////////////
//��ȡͨ��״̬
//ʹ�� DJISUP_GetChnState( ����, ͨ���� ) ��ȡ
//////////////////////////////////////////////////////////
//����״̬
#define ISUP_CH_FREE			1
//DLL�ȴ�Ӧ�ò�ͬ���ͷ���Դ
#define ISUP_CH_WAIT_RELEASE	2
//��������״̬
#define ISUP_CH_LOCAL_BLOCK		3
//Զ������״̬
#define ISUP_CH_REMOTE_BLOCK	4
//���غ�Զ������״̬
#define ISUP_CH_LOCAL_AND_REMOTE_BLOCK 5
//������̬(���粻ͨ��ԭ����)
#define ISUP_CH_UNAVIABLE		6
//������,�ȴ�����Ӧ��
#define ISUP_CALLER_WAIT_ANM	7
//����Ӧ��,ȥ����ͨ
#define ISUP_CALLER_CONNECT		8
//���е���,����ȫ��ַ
#define ISUP_CALLEE_RECV_IAM	9
//ժ��,������ͨ
#define ISUP_CALLEE_CONNECT		10
//������ͣ
#define ISUP_CH_LOCAL_SUSPEND	11
//Զ����ͣ
#define ISUP_CH_REMOTE_SUSPEND	12
//�յ�������Ϣ���ѽ�������
#define ISUP_CH_CON_CONNECT		13
//�յ�������Ϣ���ڴ���ֶ���Ϣ
#define ISUP_CH_CON_NOTCON		14

/***** �������غ������̵�״ָ̬ʾ *****/
// IAM��Ϣ������ʾ
#define	CALLEE_IAM_REACHED		0xf0
// SAM ��Ϣ������ʾ
#define CALLEE_SAM_REACHED		0xf1
/***** END *****/

//////////////////////////////////////////////////////////
//ͨ����������
//ʹ�� DJISUP_SetChnState( ����, ͨ����, Action ) ����
//////////////////////////////////////////////////////////
//APP ����ͨ��״̬Ϊ OxO2 ʱ��ͬ���ͷ�ͨ����Դ
#define	ISUP_CH_SET_FREE		1
//����ͨ��
#define	ISUP_CH_SET_BLOCK		2
//�������
#define	ISUP_CH_SET_UNBLOCK		3
//����������������������ͱ������źţ���·��ͨ��������Ӧ���ź�
#define	ISUP_CALLEE_SET_ACM		4
//����ժ���ź�
#define	ISUP_CALLEE_SET_ANM		5
//����������������������ͱ������źţ���·��ͨ����Ӧ���ź�
#define	ISUP_CALLEE_SET_CON		6
//����·�ͷ��ź�
#define	ISUP_CH_SET_REL			7
//Ⱥ����
#define	ISUP_CH_SET_CGB			8
//Ⱥ�������
#define	ISUP_CH_SET_CGU			9
//������ַ
#define ISUP_CALLER_SET_SAM		10
//��ͣ
#define ISUP_CH_SET_SUS			11
//�ָ�
#define ISUP_CH_SET_RES			12

//����ͨ��֤ʵ
#define ISUP_CH_SET_BLA			0x81
//�������֤ʵ
#define ISUP_CH_SET_UBA			0x82
//��·��ԭ
#define ISUP_CH_SET_RSC			0x83
//��Ϣ����
#define ISUP_CH_SET_INR			0x84
//��Ϣ
#define ISUP_CH_SET_INF			0x85
//Ⱥ����֤ʵ
#define ISUP_CH_SET_CGBA		0x92
//Ⱥ�������֤ʵ
#define ISUP_CH_SET_CGUA		0x94
//Ⱥ��ԭ
#define ISUP_CH_SET_GRS			0x95
//Ⱥ��ԭ֤ʵ
#define ISUP_CH_SET_GRA			0x96
//Ⱥ��Ѷ
#define ISUP_CH_SET_CQM			0x97
//Ⱥ��Ѷ��Ӧ
#define ISUP_CH_SET_CQR			0x98
//�ͷ����
#define ISUP_CH_SET_RLC			0x99
//����
#define ISUP_CH_SET_CFN			0x9a
//���н�չ
#define ISUP_CALLEE_SET_CPG		0xa2

//////////////////////////////////////////////////////////

enum CAUSE_VALUE
{
	RSN_UNALLOCATED_NUMBER = 0x01,		//�պ�
	RSN_NORMAL_CALL_CLEARING = 0x10,	//�����ĺ������
	RSN_USER_BUSY = 0x11,				//�û�æ
	RSN_NO_USER_RESPONDING = 0x12,		//���û���Ӧ����ʱû���յ�ACM
	RSN_USER_ALERTING_NO_ANSWER = 0x13, //������Ӧ�𣬳�ʱδժ��
	RSN_CALL_REJECTED = 0x15,			//���оܾ�
	RSN_INCOMPLETE_NUMBER = 0x1c,		//�������ĺ���
	RSN_NORMAL_NO_SET = 0x1f,			//������δ�涨
	RSN_NO_CIRCUIT_CHANNELAVAILABLE = 0x22, //�޿��õĵ�·
	RSN_REQUESTEDCIRCUIT_CHANNEL_NOTAVAILABLE = 0x2c, //����ĵ�·������
	RSN_RECOVERY_ON_TIME_EXPIRY = 0x66,	//��ʱ����ʱ�ָ�

	RSN_LOCAL_RLC = 0x20,				//�����ͷŵ�·
	RSN_RECEIVE_RSC = 0x21,				//��·��ԭ
};

//////////////////////////////////////////////////////////
//������״ֵ̬�б�
//��DJISUP_GetCalloutState�ķ���ֵ������ֵ����(&)���㣬����֪��ǰ����״̬
//////////////////////////////////////////////////////////
//ͬ��
#define CALLOUT_DUAL_SEIZURE		0x01
//�յ���·����
#define CALLOUT_REV_BLO				0x02
//�յ���·��ԭ
#define CALLOUT_REV_RSC				0x04
//�յ���ַȫ
#define CALLOUT_REV_ACM				0x08
//�յ����н�չ
#define CALLOUT_REV_CPG				0x10
//�յ����������Ϣ
#define CALLOUT_REV_UNREASONABLE	0X80

//////////////////////////////////////////////////////////
//ȡCPG���¼���Ϣ
//DJISUP_GetEventInfo���������¼���Ϣ
//////////////////////////////////////////////////////////
enum EVENT_INFO
{
	EI_NO_VALUE = 0x00,						//δ�н��
	EI_ALERTING = 0x01,						//֪ͨ
	EI_PROGRESS = 0x02,						//����
	EI_INBINFO_OR_APAVA = 0x03,				//������Ϣ��һ���ʺ���ʽ�ֿɻ��
	EI_BUSY_CALLTRANSFER = 0x04,			//��æ����ǰת
	EI_NOANSWER_CALLTRANSFER = 0x05,		//��Ӧ�����ǰת
	EI_UNCONDITIONAL_CALLTRANSFER = 0x06,	//����������ǰת
};


//////////////////////////////////////////////////////////
//�Ʒ�ָʾ�룬�京��ȡ���ڼƷѵĽ�����
//DJISUP_GetChargeIndicator����������ֵ
//DJISUP_SetChnState������nState��ISUP_CALLEE_SET_ACMʱ��Param1��ȡ������ֵ
//////////////////////////////////////////////////////////
enum CHARGE_INDICATOR
{
	CI_NO_INDICATION = 0x00,		//��ָʾ
	CI_NO_CHARGE	 = 0x01,		//���Ʒ�
	CI_CHARGE		 = 0x02,		//�Ʒ�
	CI_SPARE		 = 0x03,		//����
};


//////////////////////////////////////////////////////////
//ȡ�ķ���Ϣ�еĸķ�ָʾ�룺Ĭ��ֵΪ0x04
//DJISUP_GetRedirectionInfIndicator����������Ϣ
//ARIPR: all redirection information presentation restricted
//RNPR: redirection number presentation restricted
//////////////////////////////////////////////////////////
enum REDIRECTION_INDICATOR
{
	RI_NO_REDIRECTION				= 0x00,		//�޸ķ�
	RI_CALL_REROUTED				= 0x01,		//�������±�·
	RI_CALL_REROUTED_ARIPR_INF		= 0x02,		//�������±�·�����иķ���Ϣ��ʾ����
	RI_CALL_DIVERTED				= 0x03,		//����ת��
	RI_CALL_DIVERTED_ARIPR_INF		= 0x04,		//����ת�ƣ����иķ���Ϣ��ʾ����
	RI_CALL_REROUTED_RNPR_NUM		= 0x05,		//�������±�·���ķ�������ʾ����
	RI_CALL_DIVERTION_RNPR_NUM		= 0x06,		//����ת�ƣ��ķ�������ʾ����
};

//////////////////////////////////////////////////////////
//ȡ�ķ���Ϣ�еĸķ�ԭ��Ĭ��ֵΪ0x00
//DJISUP_GetRedirectionInfReason����������Ϣ
//////////////////////////////////////////////////////////
enum REDIRECTION_REASON
{
	RI_UNKNOW_UNAVAILABLE	= 0x00,		//��֪/���ɻ��
	RI_USER_BUSY			= 0x01,		//�û�æ
	RI_NO_REPLY				= 0x02,		//��Ӧ��
	RI_UNCONDITIONAL		= 0x03,		//������
	RI_DEFLECTION_ALERTING	= 0x04,		//֪ͨʱƫת
	RI_DEFLECTION_RESPONSE	= 0x05,		//ƫת������Ӧ
	RI_UNREACHABLE			= 0x06,		//�ƶ��û����ɴﵽ
};


//���������в���
//DJISUP_SetCallingParam�������
//////////////////////////////////////////////////////////
typedef struct _CALLING_PARTY_PARAM
{
	BYTE bNatureOfAddressIndicator;
		//��ַ����ָʾ��
		//0x00������
		//0x01���û�����
		//0x02����֪
		//0x03�����ڣ���Ч������
		//0x04�����ʺ���
	
	BYTE bScreeningIndicator;  //����
		//����ָʾ��
		//0x00������
		//0x01���û��ṩ����֤��ͨ��
		//0x02������
		//0x03�������ṩ

	BYTE bAddressPresentationRestrictedIndicator;  
		//��ַ��ʾ����ָʾ��
		//0x00����ʾ����
		//0x01����ʾ����
		//0x02����ַ��������
		//0x03������

	BYTE bNumberingPlanIndicator;
		//����ƻ�ָʾ��
		//0x00������
		//0x01��ISDN���绰������ƻ���E.164��
		//0x02������
		//0x03�����ݺ���ƻ���X.121��
		//0x04���û��籨����ƻ�
		//0x05���������ڹ���Ӧ��
		//0x06���������ڹ���Ӧ��
		//0x07������

	BYTE bNumberIncompleteIndicator;
		//�����û����벻ȫָʾ��
		//0x00����ȫ
		//0x01������ȫ

	BYTE bCallingPartyCategory;
		//�����û����
		//0x00�����δ֪
		//0x01������Ա������
		//...
		//0x0A����ͨ�����û�
		//0x0B�����������û�
		//0x0C�����ݺ���
		//0x0D�����Ժ���
		//0x0E������
		//0x0F�����ã�Ͷ�ң��绰
		//0x09��������ָ�������û���һ�����ڻ���Ա
}CALLING_PARTY_PARAM, *LPCALLING_PARTY_PARAM;

#define DEFUALT_SET		0xFF

//////////////////////////////////////////////////////////
//����ǰ�����ָʾ��
//DJISUP_SetForwardCallIndicatorsParam�������
//////////////////////////////////////////////////////////
typedef struct _FORWARD_CALL_INDICATORS_PARAM
{
	BYTE bNationalInternationalCallIndicator;
		//����/���ʺ���ָʾ��
		//0x00��������Ϊһ�����ں��д���
		//0x01��������Ϊһ�����ʺ��д���
	BYTE bEndToEndMethodIndicator;
		//�˵��˷���ָʾ��
		//0x00���˵��˷������ɻ�ã����ɻ�������·ת�ӷ�����
		//0x01�����ݣ�pass along�������ɻ��
		//0x02��SCCP�����ɻ��
		//0x03�����ݼ�SCCP�����ɻ��
	BYTE bInterworkingIndicator; 
		//��ָͨʾ��
		//0x00������������ͨ
		//0x01����������ͨ
	BYTE bEndToEndInformationIndicator;
		//�˵�����Ϣָʾ��
		//0x00���޶˵�����Ϣ������
		//0x01���˵�����Ϣ������
	BYTE bISDNUserPartIndicator;
		//ISDN�û�����ָʾ��
		//0x00����ȫ��Ӧ��ISDN�û�����
		//0x01��ȫ��Ӧ��ISDN�û�����
	BYTE bISDNUserPartPreferenceIndicator;
		//ISDN�û���������ָʾ��
		//0x00��ISDN�û�����ȫ������
		//0x01����ȫ����ҪISDN�û�����
		//0x02��ȫ����ҪISDN�û�����
		//0x03������
	BYTE bISDNAccessIndicator;
		//ISDN����ָʾ��
		//0x00��ʼ���˽����ISDN
		//0x01��ʼ���˽���ISDN
	BYTE bSCCPMethodIndicator;
		//SCCP����ָʾ��
		//0x00����ָʾ
		//0x01���޽��������ɻ��
		//0x02�����������ɻ��
		//0x03���޽�����������������ɻ��
}FORWARD_CALL_INDICATORS_PARAM, *LPFORWARD_CALL_INDICATORS_PARAM;

//////////////////////////////////////////////////////////
//���øķ���Ϣ
//DJISUP_SetRedirectionInf�������
//////////////////////////////////////////////////////////
typedef struct _REDIRECTION_INFORMATION_PARAM
{
	BYTE bRedirectingIndicator;
		//�ķ�ָʾ�룺Ĭ��Ϊ0x04
		//000���޸ķ�
		//001���������±�·
		//010���������±�·�����иķ���Ϣ��ʾ����
		//011������ת��
		//100������ת�ƣ����иķ���Ϣ��ʾ����
		//101���������±�·���ķ�������ʾ����
		//110������ת�ƣ��ķ�������ʾ����
		//111������
	BYTE bOriginalRedirectionReason;
		//ԭ���ĸķ�ԭ��Ĭ��Ϊ0x00
		//0000����֪/���ɻ��
		//0001���û�æ
		//0010����Ӧ��
		//0011��������
		//0100-1111������
	BYTE bRedirectionCounter;
		//�ķ���������Ĭ��Ϊ0x05
	BYTE bRedirectingReason;
		//ԭ���ĸķ�ԭ��Ĭ��Ϊ0x00
		//0000����֪/���ɻ��
		//0001���û�æ
		//0010����Ӧ��
		//0011��������
		//0100��֪ͨʱƫת
		//0101��ƫת������Ӧ
		//0110���ƶ��û����ɴﵽ
		//0111-1111������
}REDIRECTION_INFORMATION_PARAM, *LPREDIRECTION_INFORMATION_PARAM;

////////////////////////////////////////////////////////////
//���ú��н�չ��Ϣ
//DJISUP_SetEventInfParam �������
//////////////////////////////////////////////////////////
typedef struct _EVENT_INFORMATION_PARAM
{
	BYTE bEventIndicator;
	//�¼�ָʾ��
	//0000000������
	//0000001��֪ͨ
	//0000010������
	//0000011��������Ϣ��һ��������ʽ�ֿɻ��
	//0000100����æ����ǰת
	//0000101����Ӧ�����ǰת
	//0000110������������ǰת
	BYTE bReserved : 1;
}EVENT_INFORMATION_PARAM, *LPEVENT_INFORMATION_PARAM;

////////////////////////////////////////////////////////////
//���к�����Ϣ
//DJISUP_SetCalledNumPartyParam ���
////////////////////////////////////////////////////////////
typedef struct _CALLED_PARTY_NUMBER_PARAM
{
	BYTE bNatureOfAddressIndicator;
		//��ַ����ָʾ��
		//000000������
		//000001���û�����
		//000010����֪
		//000011�����ڣ���Ч������
		//000100�����ʺ���
	BYTE bOddEvenIndicator;
		//��/żָʾ��
		//0��ż������ַ����
		//1����������ַ����
	BYTE bReserved;
	BYTE bNumberingPlanIndicator;
		//����ƻ�ָʾ��
		//000������
		//001��ISDN���绰������ƻ���E.164��
		//010������
		//011�����ݺ���ƻ���X.121��
		//100���û��籨����ƻ�
		//101���������ڹ���Ӧ��
		//110���������ڹ���Ӧ��
		//111������
	BYTE InternalNetworkNumberIndicator;
		//�ڲ��������ָʾ��
		//0����·���ڲ������������
		//1����·���ڲ�������벻����Ĭ��ֵ��
	BYTE bAddressSignal[17];
}CALLED_PARTY_NUMBER_PARAM, *LPCALLED_PARTY_NUMBER_PARAM;


////////////////////////ISDN�û����ֲ���///////////////////
//����ISDN�û����ֲ���
//DJISUP_SetParam(�м̺ţ�ͨ���ţ�������ʶ�� ���������ָ��)
//ȡ�Ѿ��յ���ISDN�û����ֲ���
//DJISUP_GetParam(�м̺ţ�ͨ���ţ�������ʶ�� ���������ָ��)
///////////////////////////////////////////////////////////
typedef enum _ISUP_PARAM
{
	ISUP_PARAM_AT	= 0x03,				//���봫��ACCESS TRANSPORT
	ISUP_PARAM_UTU	= 0x20,				//�û����û�
}ISUP_PARAM;

#define AT_LEN		100
//���봫�Ͳ�������
typedef struct _PARAM_ACCESSTRANSPORT
{
	BYTE		bLen;	
	BYTE		bInfoUnit[AT_LEN];		//��Ϣ��Ԫ
}PARAM_ACCESSTRANSPORT;

#define UTU_LEN		100
//�û�-�û���Ϣ��������
typedef struct _PARAM_USERTOUSERINFOR
{
	BYTE bLen;
	BYTE bUserToUserInformation[UTU_LEN];	//�û�-�û���Ϣ
}PARAM_USERTOUSERINFOR;

///////////////////////////////////////////////////////////

#define EXIST_REDIRECTION_NUM	0x0001
#define EXIST_REDIRECTION_INF	0x0001

///////////////////////////////////////////////////////////

#ifdef	__cplusplus
extern "C" {
#endif

int		WINAPI DJISUP_InitSystem();
void	WINAPI DJISUP_ExitSystem();
int		WINAPI DJISUP_GetChnState(BYTE nPCM, BYTE nCHN);
void	WINAPI DJISUP_SetChnState(BYTE nPCM, BYTE nCHN, BYTE nState, int Param1 = 0, int Param2 = 0, int Param3 = 0, int Param4 = 0);
void	WINAPI DJISUP_SetChnState_ForVB(BYTE nPCM, BYTE nCHN, BYTE nState, void *Param1 = NULL, int Param2 = 0, int Param3 = 0, int Param4 = 0);
void	WINAPI DJISUP_GetCallerNum(BYTE nPCM, BYTE nCHN, char * strCallerId);
void	WINAPI DJISUP_GetCalleeNum(BYTE nPCM, BYTE nCHN, char * strCalleeId);
int		WINAPI DJISUP_GetOraCalleeNum(BYTE nPCM, BYTE nCHN, char * strOraCalleeId);
void	WINAPI DJISUP_GetEvent();
bool	WINAPI DJISUP_GetEventA(BYTE nLinkId);
int		WINAPI DJISUP_GetEventRawFrame(BYTE * pData);   //pData ��SIO��ʼ
int		WINAPI DJISUP_SetOraCalleeNumber(int nPCM, int nCHN, char * szOraCalleeNumber = "" );
int		WINAPI DJISUP_Callout(int nPCM, int nCHN, char * szCalleeNumber, char * szCallerNumber = "", bool bCalleeSignalTerminal = false, bool bCallerSignalTerminal = false);
int		WINAPI DJISUP_GetCalloutChn(BYTE nPCM);
bool	WINAPI DJISUP_GetCalloutChnNew( BYTE* mo, BYTE* dt );//Add for dual seizure
int		WINAPI DJISUP_GetSpNo( char *sDPC );
bool	WINAPI DJISUP_GetCalloutChnMSP( BYTE nSp_No, BYTE* mo, BYTE* dt );
int		WINAPI DJISUP_GetReleaseReason(int nPCM, int nCHN);
int		WINAPI DJISUP_GetCalloutState(int nPCM, int nCHN);
int		WINAPI DJISUP_GetEventInfo(int nPCM, int nCHN);

int		WINAPI DJISUP_GetRawFrame(int nLinkId, BYTE * pData);
int		WINAPI DJISUP_GetRawFrameFromMTC(BYTE nPCM, BYTE nCHN, BYTE * pData); //pData ����Ϣ���Ϳ�ʼ
int		WINAPI DJISUP_GetNonIsupRawFrame(BYTE * pData);
int		WINAPI DJISUP_GetSccpRawFrame(BYTE * pData);
bool	WINAPI DJISUP_SendRawFrame(BYTE nPCM, BYTE nCHN, BYTE * pData, int nLen);
bool	WINAPI DJISUP_SendSccpRawFrame(BYTE * pData, int nLen);
bool	WINAPI DJISUP_SendSS7RawFrame(BYTE * pData, int nLen);

int		WINAPI DJISUP_SetParam(BYTE nPCM, BYTE nCHN, ISUP_PARAM ParamID, void * pParam);
int		WINAPI DJISUP_GetParam(BYTE nPCM, BYTE nCHN, ISUP_PARAM ParamID, void * pParam);

void	WINAPI DJISUP_SetRedirectionNum(BYTE nPCM, BYTE nCHN, char* pRedirectionNum);

int		WINAPI DJISUP_SetCallingParam(BYTE nPCM, BYTE nCHN, CALLING_PARTY_PARAM *pSetCallingParm);

//�����м̵�ͬ��״̬�����ߺ�����Ӧ���У��ڵ�ʹ�÷Ƕ���Dϵ�а忨ʱʹ��,��������в���ʹ�ô˺�����
int		WINAPI DJISUP_SetPcmSyncState(BYTE nPCM, bool bSync);

int		WINAPI DJISUP_SetForwardCallIndicatorsParam(BYTE nPCM, BYTE nCHN, FORWARD_CALL_INDICATORS_PARAM *pSetForwardCallIndicatorsParam);
int		WINAPI DJISUP_GetRecvCauseValue(int nPCM, int nCHN);
int		WINAPI DJISUP_GetChargeIndicator(int nPCM, int nCHN);

int		WINAPI DJISUP_GetRedirectingNum(BYTE nPCM, BYTE nCHN, char * strRedirectingId);
int		WINAPI DJISUP_SetRedirectingNum(BYTE nPCM, BYTE nCHN, char* pRedirectingNum);

int		WINAPI DJISUP_GetRedirectionInfIndicator(BYTE nPCM, BYTE nCHN );
int		WINAPI DJISUP_GetRedirectionInfReason(BYTE nPCM, BYTE nCHN );
int		WINAPI DJISUP_SetRedirectionInf(BYTE nPCM, BYTE nCHN, REDIRECTION_INFORMATION_PARAM *pSetRedirectionInfParam );

int		WINAPI DJISUP_SetEventInfParam(BYTE nPCM, BYTE nCHN, LPEVENT_INFORMATION_PARAM pSetEventInfParam); 
int		WINAPI DJISUP_SetCalledPartyNumberParam(BYTE nPCM, BYTE nCHN, LPCALLED_PARTY_NUMBER_PARAM pParam);



//DWORD *DJISUP_GetMsgCount(BYTE nPCM, BYTE nCHN);

#ifdef	__cplusplus
}
#endif

#endif
