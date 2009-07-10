#ifndef	_NO7DLL_H
#define	_NO7DLL_H

//////////////////////////////////////////////////////////
//ͨ��״̬����
//ʹ�� DJNo7_GetChnState( ����, ͨ���� ) ���
//////////////////////////////////////////////////////////

//����״̬
#define CH_FREE			1
//DLL�ȴ�Ӧ�ò�ͬ���ͷ���Դ
#define CH_WAIT_RELEASE	2
//��������״̬
#define CH_LOCAL_BLOCK	3
//Զ������״̬
#define CH_REMOTE_BLOCK	4
//������̬(���粻ͨ��ԭ����)
#define CH_UNAVIABLE	5

//ȥ����ͨ״̬
#define CALLER_CONNECT  6
//���з��Ͳ����ź�,�ȴ����л����ͷż໤�ź�
#define CALLER_WAIT_RLG 7

//���е���,����ȫ��ַ
#define CALLEE_RECV_IAM 8
//������ͨ״̬
#define CALLEE_CONNECT  9
//�ѷ��͹һ��źţ��ȴ����з��Ͳ����ź�
#define CALLEE_WAIT_CLF 10


//�ڲ�״̬��Ӧ�ó��򲻶Դ�״̬���д���
#define CH_CANOMIT		11

#define CALLER_RECV_CBK	12
#define CALLER_RECV_RAN 13

//���ڱ��п��ƹػ�ʱ�������յ�CCL
#define CALLEE_RECV_CCL 14
//���ڱ��п��ƹػ�ʱ�������յ�RAN
#define CALLEE_RECV_RAN 15

#define CALLER_RECV_ACM 0x91	//�����յ�ACM

// IAM��Ϣ����
#define CALLEE_IAM_REACHED 0xF0
// IAI��Ϣ����
#define CALLEE_IAI_REACHED 0xF1
// SAO��Ϣ����
#define CALLEE_SAO_REACHED 0xF2
// SAM��Ϣ����
#define CALLEE_SAM_REACHED 0xF3
// �ȴ�GSM��Ϣ
#define CALLEE_WAIT_GSM	0xa3

//////////////////////////////////////////////////////////
//ͨ����������
//ʹ�� DJNo7_SetChnState( ����, ͨ����, Action ) ����
//////////////////////////////////////////////////////////
//APP ����ͨ��״̬Ϊ 0x02(CH_WAIT_RELEASE) ʱ��ͬ���ͷ�ͨ����Դ
#define	CH_SET_FREE		1
//����ͨ��
#define	CH_SET_BLOCK	2
//�������
#define	CH_SET_UNBLOCK	3

//����������������������ͱ������źţ���·��ͨ��������Ӧ���ź�
#define	CALLEE_SET_ACM	4
//����ժ���ź�
#define	CALLEE_SET_ANC	6
//����������������������ͱ���æ�ź�
#define	CALLEE_SET_SSB	7
//����������������������ͱ�����æ�ź�
#define	CALLEE_SET_SLB	8
//����������������������ͱ��г�æ�ź�
#define	CALLEE_SET_STB	9
//����������������������Ϳպ��ź�
#define	CALLEE_SET_UNN	10
//�������������ͱ��йһ��ź�
#define	CALLEE_SET_CBK	12
//�������������Ͳ���֤ʵ�ź�
#define	CALLEE_SET_RLG	13
//ȥ�����������Ͳ����ź�
#define	CALLER_SET_CLF	14
//����������������·�������ź�
#define	CALLEE_SET_LOS	15
//�������������ͽ���ܾ��ź�
#define	CALLEE_SET_ACB	16

//��·��ԭ
#define CH_SET_RSC		0x81
//��·Ⱥ��ԭ
#define CH_SET_GRS		0x82
//һ��������Ϣ
#define CALLEE_SET_GRQ	0x83
//�������������ͺ��й����ź�
#define	CALLEE_SET_CFL	0x84
//�������������͵�ַ��ȫ�ź�
#define	CALLEE_SET_ADI	0x85

//����ά����Ⱥ������Ϣ
#define	CH_SET_MGB		101	//0x65
//����ά���Ľ��Ⱥ������Ϣ
#define	CH_SET_MGU		0x87
//Ӳ�����ϵ�Ⱥ������Ϣ
#define	CH_SET_HGB		100	//0x64
//Ӳ�����ϵĽ��Ⱥ������Ϣ
#define	CH_SET_HGU		0x89
//���������Ⱥ������Ϣ
#define	CH_SET_SGB		0x90
//��������Ľ��Ⱥ������Ϣ
#define	CH_SET_SGU		0x91

//////////////////////////////////////////////////////////
//���������û����
//DJNo7_CalloutEx��CallerCategory��������
//////////////////////////////////////////////////////////
//���ڻ���Ա
#define CALLEE_C_00		0x00
#define CALLEE_C_01		0x01
#define CALLEE_C_02		0x02
#define CALLEE_C_03		0x03
#define CALLEE_C_04		0x04
#define CALLEE_C_05		0x05
#define CALLEE_C_06		0x06
#define CALLEE_C_07		0x07
#define CALLEE_C_08		0x08
#define CALLEE_C_09		0x09
//��ͨ�û����ڳ������ʣ������� �������ʣ����оּ�ʹ��
#define CALLEE_C_0A		0x0A
//�����û����ڳ������ʣ������� �������ʣ����У� �У��оּ�ʹ��
#define CALLEE_C_0B		0x0B
//���ݺ���
#define CALLEE_C_0C		0x0C
//���Ժ���
#define CALLEE_C_0D		0x0D
//��ͨ�����		�����У��������ʣ��ּ�ʹ�ã�
#define CALLEE_C_10		0x10
//��ͨ������		�����У��������ʣ��ּ�ʹ�ã�
#define CALLEE_C_11		0x11
//��ͨ���û������������У��������ʣ��ּ�ʹ�ã�
#define CALLEE_C_12		0x12
//��ͨ����ӡ�������������У��������ʣ��ּ�ʹ�ã�
#define CALLEE_C_13		0x13
//���ȡ����		�����У��������ʣ��ּ�ʹ�ã�
#define CALLEE_C_14		0x14
//���ȡ�����		�����У��������ʣ��ּ�ʹ�ã�
#define CALLEE_C_15		0x15
//��ͨ�û������У��оּ�ʹ��
#define CALLEE_C_18		0x18

//////////////////////////////////////////////////////////
//������ַ���ʱ�ʾ��
//DJNo7_CalloutEx��OriCalleeAddrAttr��������
//DJNo7_CalloutEx2��CalleeAddrAttr��OriCalleeAddrAttr��������
//DJNo7_CalloutBEx��CalleeAddrAttr��������
//////////////////////////////////////////////////////////
//�����û�����
#define CALLEE_AT_00		0x00
//����
#define CALLEE_AT_01		0x01
//������Ч����
#define CALLEE_AT_10		0x02
//���ʺ���
#define CALLEE_AT_11		0x03

//////////////////////////////////////////////////////////
//���������û����
//DJNo7_CalloutEx��DJNo7_CalloutBEx��CallerAddrAttr��������
//////////////////////////////////////////////////////////
//�����û�����
#define CALLER_AT_00		0x00
//���ڱ���
#define CALLER_AT_01		0x01
//������Ч����
#define CALLER_AT_10		0x02
//���ʺ���
#define CALLER_AT_11		0x03


//////////////////////////////////////////////////////////
//����״̬
//DJNo7_CheckCalloutResult����
//////////////////////////////////////////////////////////
//δ���ؽ��
#define C_NO_RESULT		0
//���п���
#define C_USER_IDLE		1
//����ժ������ͨ״̬
#define C_USER_OFFHOOK	2
//��ַ��ȫ
#define C_ADDR_LACK		3
//ռ��
#define C_USER_BUSY		4
//�պ�
#define	C_UNALLOC_CODE	5
//����ͬ��
#define	C_CALL_COLLIDE	6
//�Ծ��޻�Ӧ
#define	C_TIME_OUT		7
//����ԭ����в��ɹ�
#define	C_CALL_FAIL		8
//Զ��ͨ������
#define	C_REMOTE_BLOCK	9
//���йһ�
#define C_USER_ONHOOK	10
//����60������Ӧ��
#define C_NO_ANSWER		11

//////////////////////////////////////////////////////////
//�û�������״̬,�ں�����,DJNo7_CheckCalloutResult����C_USER_IDLEʱ
//����DJNo7_CheckCalloutSubResult��������
//////////////////////////////////////////////////////////
#define C_SUB_NOINDICATE_NOINDICATE   0x0   //��ַȫ,�û���æδָʾ
#define C_SUB_CHARGE_NOINDICATE       0x1   //��ַȫ,�Ʒ�,�û���æδָʾ
#define C_SUB_NOCHARGE_NOINDICATE     0x2   //��ַȫ,���,�û���æδָʾ
#define C_SUB_COIN_NOINDICATE         0x3   //��ַȫ,Ͷ��ʽ�绰,�û�æ��δָʾ
#define C_SUB_NOINDICATE_IDLE         0x4   //��ַȫ,�û���
#define C_SUB_CHARGE_IDLE             0x5   //��ַȫ,�Ʒ�,�û���
#define C_SUB_NOCHARGE_IDLE           0x6   //��ַȫ,���,�û���
#define C_SUB_COIN_IDLE               0x7   //��ַȫ,Ͷ��ʽ�绰,�û���

//////////////////////////////////////////////////////////
//����ʧ����״̬,�ں�����,DJNo7_CheckCalloutResult����C_USER_BUSYʱ
//����DJNo7_CheckCalloutSubResult��������
//////////////////////////////////////////////////////////
//�û�æ
#define C_SUB_SSB					0x0001
//�û���æ
#define C_SUB_SLB					0x0002
//�û���æ
#define C_SUB_STB					0x0003
//����ܾ�
#define C_SUB_ACB					0x0004


//////////////////////////////////////////////////////////
//����ʧ����״̬,�ں�����,DJNo7_CheckCalloutResult����C_CALL_FAILʱ
//����DJNo7_CheckCalloutSubResult��������
//////////////////////////////////////////////////////////
//�����豸ӵ��
#define C_SUB_SEC					0x0010
//��·Ⱥӵ��
#define C_SUB_CGC					0x0011
//������ӵ��
#define C_SUB_NNC					0x0012
//��·������
#define C_SUB_LOS					0x0013
//����ר���ź����ź�
#define C_SUB_SST					0x0014
//���ṩ����ͨ��
#define C_SUB_DPN					0x0015
//���й���
#define C_SUB_CFL					0x0016

//////////////////////////////////////////////////////////
//�����ɹ���״̬,�ں�����,DJNo7_CheckCalloutResult����C_USER_OFFHOOKʱ
//����DJNo7_CheckCalloutSubResult��������
//////////////////////////////////////////////////////////
//�Ʒ�δ˵��
#define C_SUB_NOINDICATE			0x0000
//�Ʒ�
#define C_SUB_CHARGE				0x0100
//���Ʒ�
#define C_SUB_UNCHARGE				0x0200

//////////////////////////////////////////////////////////
//�������ɹ���Ϣ���Ͷ���
//ΪDJNo7_SetChnStateA( nPCM, nCHN, CALLEE_SET_ACM, param )��param����
//param must be: (ACM_ADDR_XXXX | ACM_CALLEE_XXXX | ...)
//////////////////////////////////////////////////////////
//��ַȫ
#define ACM_ADDR_COMPLETE	0
//��ַȫ,�Ʒ�
#define ACM_ADDR_CHARGE		1
//��ַȫ,���Ʒ�
#define ACM_ADDR_UNCHARGE	2
//��ַȫ,Ͷ��ʽ�绰
#define ACM_ADDR_COINTEL	3

//�û�æ��״̬δָʾ
#define ACM_CALLEE_UNKNOW	0
//�û���
#define ACM_CALLEE_IDLE		4

//�ź�ͨ����ʾ��
//�κ�ͨ��
#define ACM_ANY_PATH		0
//ȫ����No7�źŷ�ʽͨ��
#define ACM_ALL_NO7_PATH	32

//////////////////////////////////////////////////////////
//������м�����Ϣ���Ͷ���
//ΪDJNo7_SetChnStateA( nPCM, nCHN, CALLEE_SET_ANC, param )��param����
//////////////////////////////////////////////////////////
//Ӧ���ź�,�Ʒ�δ˵��(ANU)
#define CSM_CHARGE_NOINDICATE		0x0		// == TYPE_ANSWER
//Ӧ���ź�,�Ʒ�(ANC)
#define CSM_CHARGE					0x1		// == TYPE_ANSWER_CHARGE
//Ӧ���ź�,���Ʒ�(ANN)
#define CSM_UNCHARGE				0x2		// == TYPE_ANSWER_NOCHARGE

//////////////////////////////////////////////////////////
//��ͨ��״̬��CH_WAIT_RELEASEʱ��������״̬��ԭ������
//DJNo7_GetReleaseCause( nPCM, nCHN)��ȡԭ��ֵ��
//ԭ��ֵ�Ķ�������
//////////////////////////////////////////////////////////
//Ӧ�ó����ʼ���������ͷ�
#define RELEASE_NO_CAUSE			0x00
//�յ�CLF�ź�
#define RELEASE_RECV_CLF			0x01
//�յ�RLG�ź�
#define RELEASE_RECV_RLG			0x02
//���ؽ�����յõ�֤ʵ
#define RELEASE_RECV_UBA			0x03
//Զ�˵�·Ⱥ��ԭ
#define RELEASE_RECV_GRS			0x04
//���ص�·Ⱥ��ԭ�õ�֤ʵ
#define RELEASE_RECV_GRA			0x05
//Զ�˵�·Ⱥ�������
#define RELEASE_REMOTE_GU			0x06


#ifdef	__cplusplus
extern "C" {
#endif

int  WINAPI DJNo7_InitSystem();
void WINAPI DJNo7_ExitSystem();
void WINAPI DJNo7_GetEvent();
bool WINAPI DJNo7_GetEventA(BYTE nLinkId);
int  WINAPI DJNo7_GetEventRawFrame(BYTE *pData);	   //pData ��SIO��ʼ
BYTE WINAPI DJNo7_GetChnState( BYTE mo_num, BYTE dt_num );
void WINAPI DJNo7_SetChnState( BYTE mo_num, BYTE dt_num, BYTE state );
void WINAPI DJNo7_SetChnStateA( BYTE nPCM, BYTE nCHN, BYTE state, BYTE param ) ;
void WINAPI DJNo7_SetChnStateB( BYTE nPCM, BYTE nCHN, BYTE state, unsigned long param ) ;
void WINAPI DJNo7_GetCalleeNum( BYTE mo_num, BYTE dt_num, char* call_id );
void WINAPI DJNo7_GetCallerNum( BYTE mo_num, BYTE dt_num, char* call_id );
void WINAPI DJNo7_GetOriCalleeNum( BYTE mo_num, BYTE dt_num, char* call_id );
//add for ZDH for Power builder
char * WINAPI DJNo7_GetCallerNumA(BYTE nPCM, BYTE nCHN);
char * WINAPI DJNo7_GetCalleeNumA(BYTE nPCM, BYTE nCHN);
char * WINAPI DJNo7_GetOriCalleeNumA(BYTE nPCM, BYTE nCHN);
//add for ZDH for Power builder

int  WINAPI DJNo7_GetSpNo( char *sDPC );	// sDPC��"x.y.z"����ʽ����
bool WINAPI DJNo7_GetCalloutChn( BYTE* mo_num, BYTE* dt_num );
bool WINAPI DJNo7_GetCalloutChnMSP(BYTE nSp_No, BYTE* mo, BYTE* dt );
bool WINAPI DJNo7_Callout( BYTE mo_num, BYTE dt_num, char* callee, char* caller = "" );
bool WINAPI DJNo7_CalloutEx( BYTE nPCM, BYTE nCHN, char* callee, char *caller, BYTE CallerCategory = 0x18, BYTE CallerAddrAttr = 0, bool bTranCall = false, char* OriCallee = "", BYTE OriCalleeAddrAttr = 0);
bool WINAPI DJNo7_CalloutEx2( BYTE nPCM, BYTE nCHN, char* callee, char *caller, BYTE CallerCategory = 0x18, BYTE CalleeAddrAttr = 0, BYTE CallerAddrAttr = 0, bool bTranCall = false, char* OriCallee = "", BYTE OriCalleeAddrAttr = 0);
bool WINAPI DJNo7_CalloutB( BYTE nPCM, BYTE nCHN, char* callee, char *caller );
bool WINAPI DJNo7_CalloutBEx( BYTE nPCM, BYTE nCHN, char* callee, char *caller, BYTE CallerCategory = 0x18, BYTE CalleeAddrAttr = 0, BYTE CallerAddrAttr = 0);
BYTE WINAPI DJNo7_CheckCalloutResult( BYTE mo_num, BYTE dt_num );
DWORD WINAPI DJNo7_CheckCalloutSubResult( BYTE nPCM, BYTE nCHN );
bool WINAPI DJNo7_CalloutA( BYTE mo_num, BYTE dt_num, BYTE* data, int len );
void WINAPI DJNo7_SetCalloutAParam( BYTE nPCM, BYTE nCHN, char* caller);
bool WINAPI DJNo7_CalloutC( BYTE mo_num, BYTE dt_num, char * s_callee);
//�Լ���������,�������������û����,�������Ƶ�,data����SIF�е�H0,H1��������Ϣ����
void WINAPI DJNo7_GetCallInfo( BYTE mo_num, BYTE dt_num, char * info, int len );

int WINAPI DJNo7_GetCallRawFrame(BYTE nPCM, BYTE nCHN, char *RawFrame);
BYTE WINAPI DJNo7_GetACMMessage(BYTE nPCM, BYTE nCHN);

void WINAPI DJNo7_SetSystemMode( DWORD mode , DWORD param=0 );
//�ú�����������ϵͳ�Ĺ���ģʽ���˺���Ӧ��ϵͳ��ʼ����ɺ����
//mode�ĵ�0λΪ1(mode|=1)ʱ,�ڽ��յ�IAM��IAI��,��ʼ�ȴ�SAM,�ڵȴ�param���,�绹δ�յ�SAM,����Ϊ��ַȫ,
//               ������ڱ��е�ַ����δ֪ʱʹ��
//mode�ĵ�1λΪ1(mode|=2)ʱ,����Ա���빦��,�ں���ʱ,���Ի���Ա�����û�������
//               �ڵȴ�ACMʱ���ز�����ʱ�ж�,�򽻻��������ACM�ź�,���������ܻ�SSB,SLB,STB
//               ���յ��û�æ,�û���æ,�û���æ�ź�,ϵͳ������CLF,��DJNo7_CheckCalloutResult��DJNo7_CheckCalloutSubResult
//				 ���Եõ��������
//               ���յ�����һ��ź�CBK,ϵͳ������CLF,���ǽ�ͨ��״̬��ΪCALLER_RECV_CBK,��DJNo7_GetChnState���Բ�׽����״̬
//mode�ĵ�2λΪ1(mode|=4)ʱ, �����뷢��ԭʼ���ݰ�, ϵͳ�������ݰ����κδ���������DJNo7_GetEvent����
//mode�ĵ�3λΪ1(mode|=8)ʱ, ��ģʽ����7���������أ����ڵ�Ƕ����忨����Dialogic�忨��ʱ�������м̵�ͬ����Ϣ��
//				�����ڵ���DJNo7_GetEvent����֮ǰ��DJNo7_SetSystemMode��ϵͳ��ʾÿ���м̵�ͬ��״̬��
//				��DJNo7_SetSystemMode�Ĳ��� mode��ֵ��Ϊ8������param��32λ��ֵ��ÿһλ��ʾ��ӦPCM��ͬ��״̬��
//				֧��32���м�״̬��1Ϊͬ����0Ϊʧ�������磺����һ����Ӧ��ϵͳ����3���м̣����е�0 �м�ʧ���ˣ�
//				��1��2 �м��������������ú�����DJNo7_SetSystemMode(8,0x00000006)��
//mode�ĵ�4λΪ1(mode|=16)ʱ�����ڻ�ȡ�յ��ķ�TUP���ݣ��μ�����DJNo7_GetRawFrameOt��
//mode�ĵ�5λΪ1(mode|=32)ʱ�����п��ƹһ���ʽ

void WINAPI DJNo7_SetCalloutAParam( BYTE nPCM, BYTE nCHN, char* caller);
void WINAPI DJNo7_StartTimer(BYTE nPCM, BYTE nCHN, int nTimerValue);
int WINAPI DJNo7_TimerElapsed(BYTE nPCM, BYTE nCHN);

int WINAPI DJNo7_GetRawFrame(int nLinkId, BYTE * strRawFrame);//strRawFrame����SIO ��SIF 
bool WINAPI DJNo7_SendRawFrame(BYTE nPCM, BYTE nCHN, BYTE* pData, int nLen);//pDataΪSIF�е�H0,H1��������Ϣ����

int WINAPI DJISUP_GetRawFrame(int nLinkId,BYTE * strRawFrame);	//strRawFrame����SIO ��SIF 
bool WINAPI DJISUP_SendRawFrame(BYTE* pData,int nLen);//pData����SIO ��SIF 

bool WINAPI DJNo7_SendSS7RawFrame(BYTE* pData, int nLen);//pData����SIO ��SIF 

int WINAPI DJNo7_GetRawFrameOt(BYTE * strRawFrame);//strRawFrame����SIO ��SIF 
bool WINAPI DJNo7_SendRawFrameOt(BYTE* pData,int nLen);//pData����SIO ��SIF 
int WINAPI DJNo7_GetSccpRawFrame(BYTE * strRawFrame);//strRawFrame����Ϣ���Ϳ�ʼ��������SIO��DPC��OPC & SLS

int WINAPI DJNo7_GetReleaseCause(BYTE nPCM, BYTE nCHN);

BYTE WINAPI DJNo7_GetACMMessage(BYTE nPCM, BYTE nCHN);

#ifdef	__cplusplus
}
#endif

#endif