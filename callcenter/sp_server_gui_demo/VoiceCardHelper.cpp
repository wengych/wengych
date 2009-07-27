
#include "StdAfx.h"
#include "VoiceCardHelper.h"

std::string ChannelStatHelper::GetChannelState(CHANNEL_STATE stat)
{
	std::string ret;
	switch(stat)
	{
	case CHANNEL_STATE::CH_FREE:
		ret = "����";
		break;
	case CHANNEL_STATE::CH_RECEIVEID:
		ret = "���ܱ���";
		break;
	default:
		ret = "δ֪״̬";
		break;
	}
	return ret;
}