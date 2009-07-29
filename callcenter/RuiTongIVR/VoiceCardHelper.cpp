
#include "StdAfx.h"
#include "VoiceCardHelper.h"

std::string ChannelStatHelper::GetChannelState(CHANNEL_STATE stat)
{
	std::string ret;
	switch(stat)
	{
	case CHANNEL_STATE::CH_FREE:
		ret = "空闲";
		break;
	case CHANNEL_STATE::CH_RECEIVEID:
		ret = "接受被叫";
		break;
	default:
		ret = "未知状态";
		break;
	}
	return ret;
}