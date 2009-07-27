#ifndef __DJD08HELPER_
#define __DJD08HELPER_

#include <string>

/*
����Ƕ���d08����������������
*/


enum CHANNEL_STATE 
{
	CH_FREE,
	CH_RECEIVEID,
	CH_WAITSECONDRING,
	CH_WELCOME,
	CH_ACCOUNT,
	CH_ACCOUNT1,
	CH_PASSWORD,
	CH_PASSWORD1,
	CH_SELECT,
	CH_SELECT1,
	CH_PLAYRESULT,
	CH_RECORDFILE,
	CH_PLAYRECORD,
	CH_OFFHOOK,
	CH_WAITUSERONHOOK,
};


typedef struct _tagLINESTRUCT
{
	//int nType;
	//int State;
	//char CallerID[32];
	////˫����Ƶ�ź�
	//char Dtmf[32];
	//int nTimeElapse;
	std::string szType;
	int iChannel;
	std::string szPhone;
	std::string szChannelStat;
}LINESTRUCT,*PLINESTRUCT;


class ChannelStatHelper
{
public:

public:
	static std::string   GetChannelState(CHANNEL_STATE stat);


};



#endif
