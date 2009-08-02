
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
void CPIDConfig::SetConfigFile(std::string strFile)
{
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

void CPIDConfig::SetGateWayPID(std::string pid)
{
    std::string xPath = "/configuration/device/gateway";

    if (isLoaded)
    {
        xDoc.SetNode(xPath,pid);
        xDoc.SaveFile();
    }
}

void CPIDConfig::SetChannelPID(std::string channel,DWORD pid)
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

void CPIDConfig::SetChannelPID(std::string channel,std::string pid)
{
    char xPath[512] = "";
    sprintf(xPath ,"/configuration/device/channels/channel[@id='%s']",channel.c_str());

    if (isLoaded)
    {
        char szPid[64] = "";
        sprintf(szPid,"%d",pid);

        xDoc.SetNode(xPath,pid.c_str());
        xDoc.SaveFile();
    }
}

//////////////////////////////////////////////////////////////////////////

CChannelViewConfig::CChannelViewConfig(std::string strFile)
{
    isLoaded = false;
    if (strFile.length() >0)
    {
        isLoaded = xDoc.LoadFile(strFile);
    }
}
void CChannelViewConfig::SetConfigFile(std::string strFile)
{
    if (strFile.length() >0)
    {
        isLoaded = xDoc.LoadFile(strFile);
    }
}
std::pair<int ,int> CChannelViewConfig::GetChannelCtrlView(std::string xpath)
{
    std::string width = xpath + "/@width";
    std::string heigtht = xpath +"/@height";

    std::pair<int ,int> p;
    if (isLoaded)
    {
//         Pair p1 = xDoc.GetAttrValue(width);
//         Pair p2 = xDoc.GetAttrValue(heigtht);
        p.first = atoi(xDoc.GetAttrValue(width).c_str());
        p.second = atoi(xDoc.GetAttrValue(heigtht).c_str());
    }
    return p;
}
std::pair<int ,int> CChannelViewConfig::GetChannelIDView()
{
    std::string xpath = "/configuration/device/channel_view/channel_id";
    return  GetChannelCtrlView(xpath);
}

std::pair<int ,int> CChannelViewConfig::GetChannelStateView()
{
    std::string xpath = "/configuration/device/channel_view/channel_state";
    return  GetChannelCtrlView(xpath);
}

std::pair<int ,int> CChannelViewConfig::GetChannelCtrlBtnView()
{
    std::string xpath = "/configuration/device/channel_view/channel_ctl_btn";
    return  GetChannelCtrlView(xpath);
}
