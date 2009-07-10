#ifndef __ISUP_DLL__EX__
#define __ISUP_DLL__EX__

#define MAX_DATALEN 255
enum ISUP_MSG_TYPE_EX
{
	IM_BACKWARD_CALL_INDICATORS_EX,// 3.5 �������ָʾ��
	IM_EVENT_INFORMATION_EX,// 3.21 �¼���Ϣ���ر��ֶΣ�
	IM_FACILITY_INDICATOR_EX,// 3.22 ����ָʾ�루�ر��ֶΣ�
	IM_INFORMATION_INDICATORS_EX,// 3.28 ��Ϣָʾ��
	IM_INFORMATION_REQUEST_INDICATORS_EX,// 3.29 ��Ϣ����ָʾ��
	IM_NATURE_OF_CONNECTION_INDICATORS_EX,// 3.35 ��������ָʾ��
	IM_FORWARD_CALL_INDICATORS_EX,// 3.23 ǰ�����ָʾ��
	IM_CALLING_PARTY_CATEGORY_EX,// 3.11 �����û����
	IM_TRANSMISSION_MEDIUM_REQUIREMENT_EX,// 3.54 ����ý��Ҫ��
	IM_SUSPEND_RESUME_INDICATORS_EX,// 3.52 ��ͣ/�ָ�ָʾ��
	IM_CIRCUIT_GROUP_SUPERVISION_MESSAGE_TYPE_EX,// 3.13 ��·Ⱥ������Ϣָʾ��
	IM_RANGE_AND_STATUS_EX,// 3.43 ��Χ��״̬
	IM_CIRCUIT_STATE_INDICATOR_EX,// 3.14 ��·״ָ̬ʾ��
	IM_CAUSE_INDICATORS_EX,// 3.12 ԭ��ָʾ��
	IM_CALLED_PARTY_NUMBER_EX,// 3.9 �����û����루ֻ������ʼ��ַ��Ϣ��
	IM_SUBSEQUENT_NUMBER_EX,// 3.51 ��������
	IM_USER_TO_USER_INFORMATION_EX,// 3.61 �û����û���Ϣ
	IM_CALLING_PARTY_NUMBER_EX,// 3.10 �����û�����
	IM_REDIRECTION_NUMBER_EX,// 3.46 �ķ����루�౻�к��룩
	IM_CALL_HISTORY_INFORMATION_EX,// 3.7 ������ʷ
	IM_PROPAGATION_DELAY_COUNTER_EX,// 3.42 ����ʱ�ӣ����룩
	IM_OPTIONAL_BACKWARD_CALL_INDICATORS_EX,// 3.37 ��ѡ�������ָʾ��
	IM_OPTIONAL_FORWARD_CALL_INDICATORS_EX,// 3.38 ��ѡǰ�����ָʾ��
	IM_ORA_CALLEE_PARTY_NUMBER_EX,// 3.39 ԭ���к���
	IM_ACCESS_TRANSPORT_EX,// ���봫��
	IM_MESSAGE_COMPATIBILITY_INFORMATION_EX,// 3.33 ��Ϣ��������Ϣ
	IM_PARAM_COMPATIBILITY_INFORMATION_EX,// 3.41 ������������Ϣ
	IM_REDIRECTING_NUMBER_EX,// 3.44 �ķ�����
	IM_REDIRECTION_INFORMATION_EX, //3.45 �ķ���Ϣ
	IM_USER_SERVICE_INFORMATION_EX,	// �û�ҵ����Ϣ

	// �ڲ�ת����ʶ�������Ϻ���
	_IM_CALLING_PARTY_EX,
	_IM_FORWARD_CALL_INDICATORS_EX,
	_IM_REDIRECTION_INFORMATION_EX,
	_IM_EVENT_INFORMATION_EX,
	_IM_CALLED_PARTY_NUMBER_EX,
	
};

// 3.5 �������ָʾ��
typedef struct _BACKWARD_CALL_INDICATORS_PARAM_EX
{
	BYTE bChargeIndicator ;
		//�Ʒ�ָʾ��
		//00����ָʾ
		//01�����Ʒ�
		//10���Ʒ�
		//11������
	BYTE bCalledStatusIndicator ;
		//�����û�״ָ̬ʾ��
		//00����ָʾ
		//01���û�����
		//10������ʱ����
		//11������
	BYTE bCalledCategoryIndicator ;
		//�����û����ָʾ��
		//00����ָʾ
		//01����ͨ�û�
		//10��Ͷ�ҵ绰
		//11������
	BYTE bEndToEndMethodIndicator ;
		//�˵��˷���ָʾ��
		//00���޶˵��˷���������
		//01�����ݷ���������
		//10��SCCP����������
		//11�����ݺ�SCCP����������
	BYTE bInterworkingIndicator ;
		//��ָͨʾ��
		//0������������ͨ
		//1��������ͨ
	BYTE bEndToEndInformationIndicator ;
		//�˵�����Ϣָʾ��
		//0���޶˵�����Ϣ������
		//1���˵�����Ϣ������
	BYTE bISDNUserPartIndicator ;
		//ISDN�û�����ָʾ��
		//0���ն˽����ISDN
		//1���ն˽���ISDN
	BYTE bHoldingIndicator ;
		//����ָʾ��
		//0������δ����
		//1����������
	BYTE bISDNAccessIndicator ;
		//ISDN����ָʾ��
		//0���ն˽����ISDN
		//0���ն˽���ISDN
	BYTE bEchoControlDeviceIndicator ;
		//������������ָʾ��
		//0�������������������δ����
		//1�����������������������
	BYTE bSCCPMethodIndicator ;
		//SCCP����ָʾ��
		//00����ָʾ
		//01���޽�������������
		//10����������������
		//11���޽����������������������
}BACKWARD_CALL_INDICATORS_PARAM_EX, *LPBACKWARD_CALL_INDICATORS_PARAM_EX;

// 3.21 �¼���Ϣ���ر��ֶΣ�
typedef struct _EVENT_INFORMATION_PARAM_EX
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
	BYTE bReserved ;
}EVENT_INFORMATION_PARAM_EX, *LPEVENT_INFORMATION_PARAM_EX;

// 3.18 ��ָͨʾ��

// 3.22 ����ָʾ�루�ر��ֶΣ�
typedef struct _FACILITY_INDICATOR_PARAM_EX
{
	BYTE bFacilityIndicator;
}FACILITY_INDICATOR_PARAM_EX, *LPFACILITY_INDICATOR_PARAM_EX;

// 3.28 ��Ϣָʾ��
typedef struct _INFORMATION_INDICATORS_PARAM_EX
{
	BYTE bCallingPartyAddressResponseIndicator ;
		//�����û���ַ��Ӧָʾ��
		//00�������û���ַ������
		//01�������û���ַ���ɻ��
		//10������
		//11�������û���ַ����
	BYTE bHoldProvidedIndicator ;
		//�����ṩָʾ��
		//0�����ֲ��ṩ
		//1�������ṩ
	BYTE bReserved1 ;
	BYTE bCallingPartyCategoryResponseIndicator ;
		//�����û������Ӧָʾ��
		//0�������û���𲻰���
		//1�������û�������
	BYTE bChargeInformationResponseIndicator ;
		//�Ʒ���Ϣָʾ��
		//0���Ʒ���Ϣ������
		//1���Ʒ���Ϣ����
	BYTE bSolicitedInformationIndicator ;
		//������Ϣָʾ��
		//0������
		//1��δ����
	BYTE bReserved2;
}INFORMATION_INDICATORS_PARAM_EX, *LPINFORMATION_INDICATORS_PARAM_EX;

// 3.29 ��Ϣ����ָʾ��
typedef struct _INFORMATION_REQUEST_INDICATORS_PARAM_EX
{
	BYTE bCallingPartyAddressRequestIndicator ;
	BYTE bHoldingIndicator ;
	BYTE bReserved1 ;
	BYTE bCallingPartyCategoryRequestIndicator ;
	BYTE bChargeInformationRequestIndicator ;
	BYTE bReserved2 ;
	BYTE bMaliciousCallIdentificationRequestIndicator ;
	BYTE bReserved3;
}INFORMATION_REQUEST_INDICATORS_PARAM_EX, *LPINFORMATION_REQUEST_INDICATORS_PARAM_EX;

// 3.35 ��������ָʾ��
typedef struct _NATURE_OF_CONNECTION_INDICATORS_PARAM_EX
{
	BYTE bSatelliteIndicator ;
		//����ָʾ��
		//00�������������ǵ�·
		//01����������һ�����ǵ�·
		//10�����������������ǵ�·
		//01������
	BYTE bContinuityCheckIndicator ;
		//��ͨ����ָʾ��
		//00������Ҫ��ͨ����
		//01����������·����Ҫ��ͨ����
		//10����ǰ���·��������ͨ����
		//11������
	BYTE bEchoControlDeviceIndicator ;
		//������������ָʾ��
		//0��ȥ���������������������
		//1��ȥ�������������������

	BYTE bReserved ;
}NATURE_OF_CONNECTION_INDICATORS_PARAM_EX, *LPNATURE_OF_CONNECTION_INDICATORS_PARAM_EX;

// 3.23 ǰ�����ָʾ��
typedef struct _FORWARD_CALL_INDICATORS_PARAM_EX
{
	BYTE bNationalInternationalCallIndicator ;
		//����/���ʺ���ָʾ��
		//0��������Ϊһ�����ں��д���
		//1��������Ϊһ�����ʺ��д���
	BYTE bEndToEndMethodIndicator ;
		//�˵��˷���ָʾ��
		//00���˵��˷������ɻ�ã����ɻ�������·ת�ӷ�����
		//01�����ݣ�pass along�������ɻ��
		//10��SCCP�����ɻ��
		//11�����ݼ�SCCP�����ɻ��
	BYTE bInterworkingIndicator ; 
		//��ָͨʾ��
		//0������������ͨ
		//1����������ͨ
	BYTE bEndToEndInformationIndicator ;
		//�˵�����Ϣָʾ��
		//0���޶˵�����Ϣ������
		//1���˵�����Ϣ������
	BYTE bISDNUserPartIndicator ;
		//ISDN�û�����ָʾ��
		//0����ȫ��Ӧ��ISDN�û�����
		//1��ȫ��Ӧ��ISDN�û�����
	BYTE bISDNUserPartPreferenceIndicator ;
		//ISDN�û���������ָʾ��
		//00��ISDN�û�����ȫ������
		//01����ȫ����ҪISDN�û�����
		//10��ȫ����ҪISDN�û�����
		//11������
	BYTE bISDNAccessIndicator ;
		//ISDN����ָʾ��
		//0��ʼ���˽����ISDN
		//1��ʼ���˽���ISDN
	BYTE bSCCPMethodIndicator ;
		//SCCP����ָʾ��
		//00����ָʾ
		//01���޽��������ɻ��
		//10�����������ɻ��
		//11���޽�����������������ɻ��
	//BYTE bReserved1 ;
	//BYTE bReserved2 ;
}FORWARD_CALL_INDICATORS_PARAM_EX, *LPFORWARD_CALL_INDICATORS_PARAM_EX;

// 3.11 �����û����
typedef struct _CALLING_PARTY_CATEGORY_PARAM_EX
{
	BYTE bCallingPartyCategory;
		//�����û����
		//00000000�����δ֪
		//00000001������Ա������
		//...
		//00001010����ͨ�����û�
		//00001011�����������û�
		//00001100�����ݺ���
		//00001101�����Ժ���
		//00001110������
		//00001111�����ã�Ͷ�ң��绰
		//00001001��������ָ�������û���һ�����ڻ���Ա
}CALLING_PARTY_CATEGORY_PARAM_EX, *LPCALLING_PARTY_CATEGORY_PARAM_EX;

// 3.54 ����ý��Ҫ��
typedef struct _TRANSMISSION_MEDIUM_REQUIREMENT_PARAM_EX
{
	BYTE bTransmissionMediumRequirement;
}TRANSMISSION_MEDIUM_REQUIREMENT_PARAM_EX, *LPTRANSMISSION_MEDIUM_REQUIREMENT_PARAM_EX;

// 3.52 ��ͣ/�ָ�ָʾ��
typedef struct _SUSPEND_RESUME_INDICATORS_PARAM_EX
{
	BYTE bSuspendResumeIndicator ;
		// 0��ISDN�û�����
		// 1�����緢��
	BYTE bReserved ;
}SUSPEND_RESUME_INDICATORS_PARAM_EX, *LPSUSPEND_RESUME_INDICATORS_PARAM_EX;

// 3.13 ��·Ⱥ������Ϣָʾ��
typedef struct _CIRCUIT_GROUP_SUPERVISION_MESSAGE_TYPE_PARAM_EX
{
	BYTE bCircuitGroupSupervisionMessageTypeIndicator ;
	//����ָʾ��
	//00������ά��
	//01������Ӳ������
	//10������
	//11������
	BYTE bReserved ;	
}CIRCUIT_GROUP_SUPERVISION_MESSAGE_TYPE_PARAM_EX, *LPCIRCUIT_GROUP_SUPERVISION_MESSAGE_TYPE_PARAM_EX;

// 3.43 ��Χ��״̬
typedef struct _RANGE_AND_STATUS_PARAM_EX
{
	BYTE bRange;
	BYTE bStatus[32];
}RANGE_AND_STATUS_PARAM_EX, *LPRANGE_AND_STATUS_PARAM_EX;

// 3.14 ��·״ָ̬ʾ��
typedef struct _CIRCUIT_STATE_INDICATOR_PARAM_EX
{
	BYTE bCircuitState[32];
}CIRCUIT_STATE_INDICATOR_PARAM_EX, *LPCIRCUIT_STATE_INDICATOR_PARAM_EX;

// 3.12 ԭ��ָʾ��
typedef struct _CAUSE_INDICATORS_PARAM_EX
{ 
	BYTE bLocation ; 
		//λ��
		//0 0 0 0		user (U)
		//0 0 0 1		private network serving the local user (LPN)
		//0 0 1 0		public network serving the local user (LN)
		//0 0 1 1		transit network (TN)
		//0 1 0 0		public network serving the remote user (RLN)
		//0 1 0 1		private network serving the remote user (RPN)
		//0 1 1 1		international network (INTL)
		//1 0 1 0		network beyond interworking point (BI)
		//1 1 0 0		reserved for national use
		//1 1 0 1		reserved for national use
		//1 1 1 0		reserved for national use
		//1 1 1 1		reserved for national use
	BYTE bReserved ;
	BYTE bCodingStandard ;		
		//�����׼
		//0 0		ITU-T standardized coding, as described below
		//0 1		ISO/IEC standard (see Note)
		//1 0		national standard (see Note)
		//1 1		standard specific to identified location (see Note)
	BYTE bExtensionIndicator1 ;	
		//����
		//0		octet continues through the next octet (e.g. octet 1 to 1a)
		//1		last octet

	BYTE bRecommendation ;		//ԭ��ֵ
	BYTE bExtensionIndicator2 ;	//����
	BYTE bDiagnosis[10];
}CAUSE_INDICATORS_PARAM_EX, *LPCAUSE_INDICATORS_PARAM_EX;

// 3.9 �����û����루ֻ������ʼ��ַ��Ϣ��
typedef struct _CALLED_PARTY_NUMBER_PARAM_EX
{
	BYTE bNatureOfAddressIndicator ;
		//��ַ����ָʾ��
		//000000������
		//000001���û�����
		//000010����֪
		//000011�����ڣ���Ч������
		//000100�����ʺ���
	BYTE bOddEvenIndicator ;
		//��/żָʾ��
		//0��ż������ַ����
		//1����������ַ����
	BYTE bReserved ;
	BYTE bNumberingPlanIndicator ;
		//����ƻ�ָʾ��
		//000������
		//001��ISDN���绰������ƻ���E.164��
		//010������
		//011�����ݺ���ƻ���X.121��
		//100���û��籨����ƻ�
		//101���������ڹ���Ӧ��
		//110���������ڹ���Ӧ��
		//111������
	BYTE InternalNetworkNumberIndicator ;
		//�ڲ��������ָʾ��
		//0����·���ڲ������������
		//1����·���ڲ�������벻����
	BYTE bAddressSignal[17];
}CALLED_PARTY_NUMBER_PARAM_EX, *LPCALLED_PARTY_NUMBER_PARAM_EX;

// 3.51 ��������
typedef struct _SUBSEQUENT_NUMBER_PARAM_EX
{
	BYTE bReserved ;
	BYTE bOddEvenIndicator ;
	BYTE bAddressSignal[7];
}SUBSEQUENT_NUMBER_PARAM_EX, *LPSUBSEQUENT_NUMBER_PARAM_EX;

// 3.61 �û����û���Ϣ
typedef struct _USER_TO_USER_INFORMATION_PARAM_EX
{
	BYTE bUserToUserInformation[ MAX_DATALEN - 18 ];//129];
}USER_TO_USER_INFORMATION_PARAM_EX, *LPUSER_TO_USER_INFORMATION_PARAM_EX;

// 3.10 �����û�����
typedef struct _CALLING_PARTY_NUMBER_PARAM_EX
{
	BYTE bNatureOfAddressIndicator ;
		//��ַ����ָʾ��
		//000000������
		//000001���û�����
		//000010����֪
		//000011�����ڣ���Ч������
		//000100�����ʺ���
	BYTE bOddEvenIndicator ;
		//��/żָʾ��
		//0��ż������ַ����
		//1����������ַ����
	BYTE bScreeningIndicator ;  //����
		//����ָʾ��
		//00������
		//01���û��ṩ����֤��ͨ��
		//10������
		//11�������ṩ
	BYTE bAddressPresentationRestrictedIndicator ;  
		//��ַ��ʾ����ָʾ��
		//00����ʾ����
		//01����ʾ����
		//10����ַ��������
		//11������
	BYTE bNumberingPlanIndicator ;
		//����ƻ�ָʾ��
		//000������
		//001��ISDN���绰������ƻ���E.164��
		//010������
		//011�����ݺ���ƻ���X.121��
		//100���û��籨����ƻ�
		//101���������ڹ���Ӧ��
		//110���������ڹ���Ӧ��
		//111������
	BYTE bNumberIncompleteIndicator ;
		//�����û����벻ȫָʾ��
		//0����ȫ
		//1������ȫ
	BYTE bAddressSignal[17];
}CALLING_PARTY_NUMBER_PARAM_EX, *LPCALLING_PARTY_NUMBER_PARAM_EX;

// 3.46 �ķ����루�౻�к��룩
typedef struct _REDIRECTION_NUMBER_PARAM_EX
{
	BYTE bNatureOfAddressIndicator ;
		//��ַ����ָʾ��
		//000000������
		//000001���û�����
		//000010����֪
		//000011�����ڣ���Ч������
		//000100�����ʺ���
	BYTE bOddEvenIndicator ;
		//��/żָʾ��
		//0��ż������ַ����
		//1����������ַ����
	BYTE bReserved ;
	BYTE bNumberingPlanIndicator ;
		//����ƻ�ָʾ��
		//000������
		//001��ISDN���绰������ƻ���E.164��
		//010������
		//011�����ݺ���ƻ���X.121��
		//100���û��籨����ƻ�
		//101���������ڹ���Ӧ��
		//110���������ڹ���Ӧ��
		//111������
	BYTE InternalNetworkNumberIndicator ;
		//�ڲ��������ָʾ��
		//0����·���ڲ������������
		//1����·���ڲ�������벻����
	BYTE bAddressSignal[17];
}REDIRECTION_NUMBER_PARAM_EX, *LPREDIRECTION_NUMBER_PARAM_EX;

// 3.7 ������ʷ
typedef struct _CALL_HISTORY_INFORMATION_PARAM_EX
{
	BYTE bPropagationValue[2];
}CALL_HISTORY_INFORMATION_PARAM_EX, *LPCALL_HISTORY_INFORMATION_PARAM_EX;


// 3.42 ����ʱ�ӣ����룩
typedef struct _PROPAGATION_DELAY_COUNTER_PARAM_EX
{
	BYTE bPropagationValue[2];
}PROPAGATION_DELAY_COUNTER_PARAM_EX, *LPPROPAGATION_DELAY_COUNTER_PARAM_EX;

// 3.37 ��ѡ�������ָʾ��
typedef struct _OPTIONAL_BACKWARD_CALL_INDICATORS_PARAM_EX
{
	BYTE bInBandInformationIndicator ;			//������Ϣָʾ��
		//0����ָʾ
		//1��������Ϣ��һ���ʺϵ���ʽ�ֿɻ��
	BYTE bCallTransferPossibleIndicator ;		//����ת�ƿ��ܷ���ָʾ��
		//0����ָʾ
		//1������ת�ƿ��ܷ���
	BYTE bSimpleSegmentationIndicator ;		//�򵥷ֶ�ָʾ��
		//0���޶�����Ϣ��Ҫ�ͳ�
		//1��������Ϣ����һ���ֶ���Ϣ���ͳ�
	BYTE bMLPPUserIndicator ;					//MLPP�û�ָʾ��
		//0����ָʾ
		//1��MLPP�û�
	BYTE bReserved  ;							//����
}OPTIONAL_BACKWARD_CALL_INDICATORS_PARAM_EX, *LPOPTIONAL_BACKWARD_CALL_INDICATORS_PARAM_EX;

// 3.38 ��ѡǰ�����ָʾ��
typedef struct _OPTIONAL_FORWARD_CALL_INDICATORS_PARAM_EX
{
	BYTE bCUGCallIndicator ;					//��CUG������ָʾ��
		//00����CUG����
		//01������
		//10��CUG���У�ȥ����������
		//11��CUG���У�ȥ������������
	BYTE bSimpleSegmentationIndicator ;		//�򵥷ֶ�ָʾ��
		//0���޶�����Ϣ��Ҫ�ͳ�
		//1��������Ϣ����һ���ֶ���Ϣ���ͳ�
	BYTE bReserved ;							//����		
		//����
	BYTE bJointingUserIdentifyIndicator ;		//�������û�ʶ������ָʾ��
		//0��δ����
		//1������
}OPTIONAL_FORWARD_CALL_INDICATORS_PARAM_EX, *LPOPTIONAL_FORWARD_CALL_INDICATORS_PARAM_EX;

// 3.39 ԭ���к���
typedef struct _ORA_CALLEE_PARTY_NUMBER_PARAM_EX
{ 
	BYTE bNatureOfAddressIndicator ;
		//��ַ����ָʾ��
		//000000������
		//000001���û�����
		//000010����֪
		//000011�����ڣ���Ч������
		//000100�����ʺ���
	BYTE bOddEvenIndicator ;
		//��/żָʾ��
		//0��ż������ַ����
		//1����������ַ����
	BYTE bReserved1 ;  //����
	BYTE bAddressPresentationRestrictedIndicator ;  
		//��ַ��ʾ����ָʾ��
		//00����ʾ����
		//01����ʾ����
		//10����ַ��������
		//11������
	BYTE bNumberingPlanIndicator ;
		//����ƻ�ָʾ��
		//000������
		//001��ISDN���绰������ƻ���E.164��
		//010������
		//011�����ݺ���ƻ���X.121��
		//100���û��籨����ƻ�
		//101���������ڹ���Ӧ��
		//110���������ڹ���Ӧ��
		//111������
	BYTE bReserved2 ;  //����
	BYTE bAddressSignal[17];
}ORA_CALLEE_PARTY_NUMBER_PARAM_EX, *LPORA_CALLEE_PARTY_NUMBER_PARAM_EX;

// ���봫��
typedef struct _ACCESS_TRANSPORT_PARAM_EX
{
	BYTE bInfoUnit[ MAX_DATALEN - 18 ];//129];
}ACCESS_TRANSPORT_PARAM_EX, *LPACCESS_TRANSPORT_PARAM_EX;

// 3.33 ��Ϣ��������Ϣ
typedef struct _MESSAGE_COMPATIBILITY_INFORMATION_PARAM_EX
{ 
	BYTE bMiddleSwitchingExchaneEandemIndicator ;	//���м佻���ֻ��ָʾ��
		//0:���˵��
		//1:�ն˽ڵ�˵��
	BYTE bReleaseCallIndicator ;					//�ͷź���ָʾ��
		//0:���ͷź���
		//1:�ͷź���
	BYTE bSendAnnounceIndicator ;					//����ָ֪ͨʾ��
		//0:����֪ͨ
		//1:����֪ͨ
	BYTE bObsoleteMessageIndicator ;				//������Ϣָʾ��
		//0:��������Ϣ
		//1:������Ϣ
	BYTE bPassPossibleIndicator ;					//��ͨ����������ָʾ��
		//0:�ͷź���
		//1:������Ϣ
	BYTE bReserved ;								//����
	BYTE bExtendIndicator ;						//����
		//0:��һ����λ�����
		//1:���İ�λ��
	struct _MORE_DIRECTIVE_INDICATOR
	{
		BYTE bMoreDirectiveIndicatior  ;					//�����ָ��ָʾ��
		BYTE bExtendIndicator ;							//����
	}	m_bMoreDirectiveIndicator[30];					
}MESSAGE_COMPATIBILITY_INFORMATION_PARAM_EX, *LPMESSAGE_COMPATIBILITY_INFORMATION_PARAM_EX;

// 3.41 ������������Ϣ
typedef struct _PARAM_COMPATIBILITY_INFORMATION_PARAM_EX
{
	BYTE bDateBuf[ MAX_DATALEN - 18 ];
}PARAM_COMPATIBILITY_INFORMATION_PARAM_EX, *LPPARAM_COMPATIBILITY_INFORMATION_PARAM_EX;

// 3.44 �ķ�����
typedef struct _REDIRECTING_NUMBER_PARAM_EX
{
	BYTE bNatureOfAddressIndicator ;
		//��ַ����ָʾ��
		//000000������
		//000001���û�����
		//000010����֪
		//000011�����ڣ���Ч������
		//000100�����ʺ���
	BYTE bOddEvenIndicator ;
		//��/żָʾ��
		//0��ż������ַ����
		//1����������ַ����
	BYTE bReserved1 ;  //����
	BYTE bAddressPresentationRestrictedIndicator ;  
		//��ַ��ʾ����ָʾ��
		//00����ʾ����
		//01����ʾ����
		//10����ַ��������
		//11������
	BYTE bNumberingPlanIndicator ;
		//����ƻ�ָʾ��
		//000������
		//001��ISDN���绰������ƻ���E.164��
		//010������
		//011�����ݺ���ƻ���X.121��
		//100���û��籨����ƻ�
		//101���������ڹ���Ӧ��
		//110���������ڹ���Ӧ��
		//111������
	BYTE bReserved2 ;  //����
	BYTE bAddressSignal[17];
}REDIRECTING_NUMBER_PARAM_EX, *LPREDIRECTING_NUMBER_PARAM_EX;

//3.45 �ķ���Ϣ 
typedef struct _REDIRECTION_INFORMATION_PARAM_EX
{
	BYTE bRedirectingIndicator ;
		//�ķ�ָʾ��
		//000���޸ķ�
		//001���������±�·
		//010���������±�·�����иķ���Ϣ��ʾ����
		//011������ת��
		//100������ת�ƣ����иķ���Ϣ��ʾ����
		//101���������±�·���ķ�������ʾ����
		//110������ת�ƣ��ķ�������ʾ����
		//111������
	BYTE bReserved1 ;  //����
	BYTE bOriginalRedirectionReason ;
		//ԭ���ĸķ�ԭ��
		//0000����֪/���ɻ��
		//0001���û�æ
		//0010����Ӧ��
		//0011��������
		//0100-1111������
	BYTE bRedirectionCounter ;
	BYTE bReserved2 ;  //����
	BYTE bRedirectingReason ;
		//ԭ���ĸķ�ԭ��
		//0000����֪/���ɻ��
		//0001���û�æ
		//0010����Ӧ��
		//0011��������
		//0100��֪ͨʱƫת
		//0101��ƫת������Ӧ
		//0110���ƶ��û����ɴﵽ
		//0111-1111������
}REDIRECTION_INFORMATION_PARAM_EX, *LPREDIRECTION_INFORMATION_PARAM_EX;

// �û�ҵ����Ϣ
typedef struct _USER_SERVICE_INFORMATION_PARAM_EX
{
	BYTE bInformationTransferCapability;// 5
		//��Ϣ��������
		//00000:����
		//01000:�����޵�������Ϣ
		//10000:3.1KHZ��Ƶ
		//10001:�����ź�����¼��֪ͨ�Ĳ�����������Ϣ
		//11000:��Ƶ
	BYTE bCodingStandard;// 2
		//00:ITU-T
	BYTE bExt1;// 1

	BYTE bInformationTransferRate;// 5
		//��Ϣ��������
		//10000:64KBit/s
		//10001:2*64KBit/s
		
	BYTE bTransferMode; // 2
		//���ݷ�ʽ
		//00:��·��ʽ
		//11:���鷽ʽ

	BYTE bExt2 ;// 1;
}USER_SERVICE_INFORMATION_PARAM_EX, *LPUSER_SERVICE_INFORMATION_PARAM_EX;


#ifdef	__cplusplus
extern "C" {
#endif

int DJISUP_SetISUPParam(BYTE nPCM, BYTE nCHN, ISUP_MSG_TYPE_EX MsgType, void *pParam);
int DJISUP_GetISUPParam(BYTE nPCM, BYTE nCHN, ISUP_MSG_TYPE_EX MsgType, void *pParam);

#ifdef	__cplusplus
}
#endif

#endif