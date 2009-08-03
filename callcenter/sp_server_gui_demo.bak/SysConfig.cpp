
#include "stdafx.h"
#include "SysConfig.h"

CSysConfig::CSysConfig(std::string strFile)
{
	isLoaded = false;
	if (strFile.length() >0)
	{
		isLoaded = xDoc.LoadFile(strFile);
	}
}

std::string CSysConfig::GetStartType()
{
	std::string retVal;
	std::string xPath = "/configuration/device/start";

	if (isLoaded)
	{
		retVal = xDoc.GetNodeValue(xPath);	
	}

	return retVal;
}

std::string CSysConfig::GetGateWay()
{
	std::string retVal;
	std::string xPath = "/configuration/device/gateway";

	if (isLoaded)
	{
		retVal = xDoc.GetNodeValue(xPath);	
	}
	
	return retVal;
}

PairSet CSysConfig::GetChannels()
{
		std::string xPath = "/configuration/device/channels";
		PairSet ps;
		if (isLoaded)
		{
			ps = xDoc.GetKeyAndTextOfChilds(xPath,"id");
		}
		return   ps;
}



//////////////////////////////////////////////////////////////////////////

CPIDConfig::CPIDConfig(std::string strFile)
{
	isLoaded = false;
	if (strFile.length() >0)
	{
		isLoaded = xDoc.LoadFile(strFile);
	}
}

std::string CPIDConfig::GetGateWayPID()
{
	std::string retVal;
	std::string xPath = "/configuration/device/gateway";
	if (isLoaded)
	{
		retVal = xDoc.GetNodeValue(xPath);	
	}
	return retVal;
}

PairSet CPIDConfig::GetChannelsPID()
{
	std::string xPath = "/configuration/device/channels";
	PairSet ps;
	if (isLoaded)
	{
		ps = xDoc.GetKeyAndTextOfChilds(xPath,"id");
	}
	return   ps;
}

std::string CPIDConfig::GetChannelPID(std::string channel)
{
	char xPath[512] = "";
	sprintf(xPath ,"/configuration/device/channels/channel[@id='%s']",channel.c_str());

	std::string val;
	if (isLoaded)
	{
		val = xDoc.GetValue(xPath);
	}
	return   val;
}


void CPIDConfig::SetGateWayPID(DWORD pid)
{
	std::string xPath = "/configuration/device/gateway";
	
	if (isLoaded)
	{
		char szPid[64] = "";
		sprintf(szPid,"%d",pid);

		xDoc.SetNode(xPath.c_str(),szPid);
		xDoc.SaveFile();
	}
}

void CPIDConfig::SetChannelPID(string channel,DWORD pid)
{
	char xPath[512] = "";
	sprintf(xPath ,"/configuration/device/channels/channel[@id='%s']",channel.c_str());

	if (isLoaded)
	{
		char szPid[64] = "";
		sprintf(szPid,"%d",pid);

		xDoc.SetNode(xPath,szPid);
		xDoc.SaveFile();
	}
}