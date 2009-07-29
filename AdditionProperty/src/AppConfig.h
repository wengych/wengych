#ifndef YS_APP_CONFIG_H_
#define YS_APP_CONFIG_H_

#include "common.h"
#include <libxml++/libxml++.h>

struct CfgServerInfo : public string
{
    CfgServerInfo(const string& cfg_name);
};

struct CfgMainWindow : public string
{
    CfgMainWindow(const string& cfg_name);
};

struct CfgTradeList : public string
{
    CfgTradeList(const string& cfg_name);
};

class AppConfig
{
public:
    AppConfig();
    ~AppConfig();
    void
    Init();
    string
    ReadOne(const string& config_name);
protected:
    xmlpp::Node* m_configRoot;
    xmlpp::DomParser xml_parser;
};

#endif // YS_APP_CONFIG_H_
