#include "common.h"
#include "../Inc/tc08a32.h"
#include "../Inc/NewSig.h"
#include <iostream>
#include <boost/tokenizer.hpp>

ChannelStateStringMap _channelStateStringMap;

DJDrv::DJDrv()
{
	if (LoadDRV())
		throw std::string ("Load driver error.");
	logger << "LoadDRV!\n";
}

DJDrv::~DJDrv()
{
	FreeDRV();
	logger << "FreeDRV!\n";
}

DJCard::DJCard()
{
	WORD TotalLine = CheckValidCh();
	if (EnableCard(TotalLine, 1024*8) != 0L)
		throw std::string ("Enable Board FAIL.");
	logger << "EnableCard!\n";
}

DJCard::~DJCard()
{
	DisableCard();
	logger << "DisableCard!\n";
}

char ConvertDtmf(int ch)
{
	char c;

	switch(ch)
	{
	case 10:
		c = '0';
		break;
	case 11:
		c = '*';
		break;
	case 12:
		c = '#';
		break;
	case 13:
	case 14:
	case 15:
		c=ch-13+'a';
		break;
	case 0:
		c='d';
		break;
	default:
		c = ch + '0';//change DTMF from number to ASCII
	}
	return c;
}

CHANNEL_STATE StringToState( const std::string& _key )
{
	ChannelStateStringMap::const_iterator it = _channelStateStringMap.find(_key);
	if (it != _channelStateStringMap.end())
		return it->second;

	else throw std::string ("StringToState failed, no such STATE: ") + _key;
}

const std::string& StateToString( CHANNEL_STATE _value )
{
	for (ChannelStateStringMap::iterator it = _channelStateStringMap.begin();
		it != _channelStateStringMap.end();
		++it) {
			if (it->second == _value)
				return it->first;
	}

	throw std::string ("StateToString failed.");
}

void InitChannelStateStringMap()
{
	_channelStateStringMap["CH_INIT"] = CH_INIT;
	_channelStateStringMap["CH_WAIT_RING"] = CH_WAIT_RING;
	_channelStateStringMap["CH_DETECT_RING"] = CH_DETECT_RING;
	_channelStateStringMap["CH_RECEIVE_ID"] = CH_RECEIVE_ID;
	_channelStateStringMap["CH_WELCOME"] = CH_WELCOME;
	_channelStateStringMap["CH_DOJOB"] = CH_DOJOB;
	_channelStateStringMap["CH_OFFHOOK"] = CH_OFFHOOK;
}

