
#include "stdafx.h"
#include "SysConfig.h"
#include <tinyxml.h>
#include <xpath_static.h>

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

// void SetServerInfo(TiXmlElement* elem, std::string& ip, std::string& port, std::string& time_out, std::string& app_name)
void SetChannelConfig(TiXmlElement* elem, ChannelConfig& cfg)
{
    std::string text = elem->FirstChild()->Value();
    std::string key = elem->Value();
    if (key == "ip")
        cfg.ip = text;
    else if (key == "port")
        cfg.port = text;
    else if (key == "time_out")
        cfg.time_out = text;
    else if (key == "app")
        cfg.app_name = text;
    else
        throw std::string("illegal xml config file in server info.");
}

ChannelConfigArray CSysConfig::GetChannels()
{
    std::string xPath = "/configuration/device/channels";
    ChannelConfigArray cc_array;
    if (!isLoaded)
        return cc_array;

    TiXmlNode* node = TinyXPath::XNp_xpath_node(xDoc.xmlRoot_, xPath.c_str());
    if (!node)
        return cc_array;

    for (TiXmlElement* channel_node = node->FirstChildElement();
         channel_node != NULL;
         channel_node = channel_node->NextSiblingElement())
    {
        try
        {
            ChannelConfig channel_cfg;
            channel_cfg.id = channel_node->Attribute("id");
            if (channel_cfg.id.empty())
                throw std::string("attribute id not found");

            TiXmlElement* tmp = channel_node->FirstChildElement();
            if (NULL == tmp)
                continue;
            do
            {
                SetChannelConfig(tmp, channel_cfg);

            } while(NULL != (tmp = tmp->NextSiblingElement()));


            cc_array.push_back(channel_cfg);
        }
        catch (const std::string& err)
        {
            return ChannelConfigArray();
        }
        
    }

    return cc_array;
//    std::string xPath = "/configuration/device/channels";
//    PairSet ps;
//    if (isLoaded)
//    {
//        ps = xDoc.GetKeyAndTextOfChilds(xPath,"id");
//    }
//    return   ps;
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
