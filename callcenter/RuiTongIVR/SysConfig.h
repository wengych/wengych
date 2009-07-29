

#ifndef __SYS_CONFIG_
#define __SYS_CONFIG_

#pragma  once

#include <map>

#include "TinyXmlHelper.hpp"
using namespace helper;


using  namespace helper;

class CSysConfig
{
private:
	xml xDoc;
	bool isLoaded;
public:
	CSysConfig(std::string strFile);
public:
	std::string GetGateWay();
	std::string GetStartType();

	PairSet GetChannels();
};

//////////////////////////////////////////////////////////////////////////

class CPIDConfig
{
private:
	xml xDoc;
	bool isLoaded;
public:
    CPIDConfig(std::string strFile);
    CPIDConfig(){isLoaded = false;};
public:
    void SetConfigFile(std::string strFile);
    std::string GetGateWayPID();

	PairSet GetChannelsPID();
	std::string GetChannelPID(std::string channel);
	void SetGateWayPID(DWORD pid);
    void SetChannelPID(std::string channel,DWORD pid);
    void SetGateWayPID(std::string pid);
    void SetChannelPID(std::string channel,std::string pid);
};




#endif