#ifndef SERVER_REQUEST
#define SERVER_REQUEST

struct request_header
{
	char request_len[4];		//请求包总长度=len(包头)+len(包体)-4
	char request_type[4];		//请求类型码
	char flow_no[20];			//系统凭证号-系统流水号,在电子售卡平台中唯一(由接入调度程序产生)
	char merchant_code[6];		//商户号,唯一标识一个商户
	char branch_no[4];			//营业网点号码(POS安装点号码)
	char terminal_no[8];		//POS终端号,POS终端的唯一标识号
	char pos_flow_no[6];		//POS凭证号-POS流水号
	char request_body_len[4];	//请求包体长度
};

class request
{
private:
	request_header header;
};

#endif // SERVER_REQUEST
