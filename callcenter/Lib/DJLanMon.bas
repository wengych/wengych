Attribute VB_Name = "Module4"
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'DJLanMon.DLL����֧��ͨ������������¼��������
'��D081Aģ����������ĳ·ͨ����¼��ʱ��
'�ýӿڿ����ṩ�û�Զ�̻򱾻�����D081Aģ����������ĳ·ͨ����¼��?
'ͷ�ļ�DJLanMon.h , Lib�ļ�DJLanMon.lib, Dll�ļ�DJLanMon.Dll?
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'�޸�ʱ��: 2003-07-21


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'��ʼ�����������( ServerIp = ������IP��ַ; BuffSize = IP��ַ�ַ�������)
'����ֵ:
'  0  =  �ɹ�,��������������
'  -1 =  ���ɹ���ԭ�򣺻�ȡ��������Сʧ��
'  -2 =  ���ɹ���ԭ�򣺳�ʼ��ʧ��
'  -3 =  ���ɹ���ԭ������������ʧ��
Declare Function DJLM_Svr_Init Lib "DJLanMon.DLL" (ByVal ServerIp As String, ByVal BuffSize As Long) As Long


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'��ʼ�������ͻ���( ServerIp = ������IP��ַ; BuffSize1 = ������IP��ַ�ַ�������; ClientIp = �ͻ���IP��ַ; BuffSize = �ͻ���IP��ַ�ַ�������; )
'����ֵ:
'  0  = �ɹ�
'  -1 = ���ɹ���ԭ�򣺳�ʼ����Դʧ��
'  -2 = ���ɹ���ԭ�򣺳�ʼ������ʧ��
Declare Function DJLM_Clt_Init Lib "DJLanMon.DLL" (ByVal ServerIp As String, ByVal BuffSize1 As Long, ByVal ClientIp As String, ByVal BuffSize As Long) As Long


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'�ر��ͷż��������
Declare Sub DJLM_Svr_Quit Lib "DJLanMon.DLL" ()


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'�ر��ͷż����ͻ���
Declare Sub DJLM_Clt_Quit Lib "DJLanMon.DLL" ()


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'�������򱻼����˷���ĳͨ���ļ�����־������sign��ֵΪ1��ʾ������0��ʾȡ������
'����ֵ:
'   0  = �ɹ�
'   -1 = ���ɹ���ԭ��׼����Դʧ��
'   -2 = ���ɹ���ԭ����Զ�˷�������ʧ��
'   -3 = ���ɹ���ԭ��Ŀǰ��һ��ͨ�����ڼ���
'   -4 = ���ɹ���ԭ����������ʧ��
Declare Function DJLM_Clt_SetMonSign Lib "DJLanMon.DLL" (ByVal Channel As Long, ByVal sign As Long) As Long


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'��ü���ͨ��Channel�Ŀͻ��˸���
'����ֵ:�����ͻ��˸���
Declare Function DJLM_Svr_GetMonInfo_MoniterClientCount Lib "DJLanMon.DLL" (ByVal Channel As Long) As Long


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'��ü���ͨ��Channel�Ŀͻ������к�ΪClientIndex��IP��ַ( ClientIndex ��ȡֵ��Χ[1~16] )
'����ֵ:IP��ַ�ַ���
Declare Function DJLM_Svr_GetMonInfo_MoniterClientIP Lib "DJLanMon.DLL" (ByVal Channel As Long, ByVal ClientIndex As Long) As String


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'��ÿͻ������к�ΪClientIndex�ļ���ͨ��Channel��ʼʱ��( ClientIndex ��ȡֵ��Χ[1~16] )
'����ֵ:������ʼʱ���ַ���
Declare Function DJLM_Svr_GetMonInfo_MonStartTime Lib "DJLanMon.DLL" (ByVal Channel As Long, ByVal ClientIndex As Long) As String


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'��ÿͻ������к�ΪClientIndex�ļ���ͨ��Channel�ĳ���ʱ��( ClientIndex ��ȡֵ��Χ[1~16] )
'����ֵ:��������ʱ�䵥λ(��)
Declare Function DJLM_Svr_GetMonInfo_MonDura Lib "DJLanMon.DLL" (ByVal Channel As Long, ByVal ClientIndex As Long) As Long


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'������к�ΪClientIndex�Ŀͻ����Ƿ����ڼ���ͨ��Channel( ClientIndex ��ȡֵ��Χ[1~16] )
'����ֵ:
'    -1 = ��ǰ��ͨ���޿ͻ��˼���
'    0  = ���к�ΪClientIndex�Ŀͻ���û�м�����ͨ��
'    1  = ���к�ΪClientIndex�Ŀͻ������ڼ�����ͨ��
Declare Function DJLM_Svr_GetMonInfo_IsMonStatus Lib "DJLanMon.DLL" (ByVal Channel As Long, ByVal ClientIndex As Long) As Long






