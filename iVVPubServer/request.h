#ifndef SERVER_REQUEST
#define SERVER_REQUEST

struct request_header
{
	char request_len[4];		//������ܳ���=len(��ͷ)+len(����)-4
	char request_type[4];		//����������
	char flow_no[20];			//ϵͳƾ֤��-ϵͳ��ˮ��,�ڵ����ۿ�ƽ̨��Ψһ(�ɽ�����ȳ������)
	char merchant_code[6];		//�̻���,Ψһ��ʶһ���̻�
	char branch_no[4];			//Ӫҵ�������(POS��װ�����)
	char terminal_no[8];		//POS�ն˺�,POS�ն˵�Ψһ��ʶ��
	char pos_flow_no[6];		//POSƾ֤��-POS��ˮ��
	char request_body_len[4];	//������峤��
};

class request
{
private:
	request_header header;
};

#endif // SERVER_REQUEST
