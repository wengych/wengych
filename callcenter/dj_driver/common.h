#ifndef __COMMON_H__
#define __COMMON_H__

#include <ostream>
#include <string>
#include <sstream>
#include <map>

struct DJDrv
{
	DJDrv();
	~DJDrv();
};

struct DJCard
{
	DJCard();
	~DJCard();
};

enum CHANNEL_STATE {
	CH_INIT,
	CH_WAIT_RING,
	CH_DETECT_RING,
	CH_RECEIVE_ID,
	CH_WELCOME,
	CH_DOJOB,
	CH_OFFHOOK,
};

typedef std::map<std::string, CHANNEL_STATE> ChannelStateStringMap;
extern ChannelStateStringMap _channelStateStringMap;
void InitChannelStateStringMap();
CHANNEL_STATE StringToState(const std::string&);
const std::string& StateToString(CHANNEL_STATE);


extern std::ostream& logger;

char ConvertDtmf(int ch);

#endif // __COMMON_H__
