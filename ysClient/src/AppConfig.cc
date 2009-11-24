#include "AppConfig.h"

AppConfig::AppConfig()
{
    Init();
}

AppConfig::~AppConfig()
{

}

void AppConfig::Init()
{
        xml_parser.parse_file("config.xml");
        m_configRoot = xml_parser.get_document()->get_root_node();
}

string AppConfig::ReadOne(const string& config_name)
{
    xmlpp::NodeSet node_set = m_configRoot->find(config_name);
    xmlpp::Element *elem = dynamic_cast<xmlpp::Element *>(*node_set.begin());
    if (NULL == elem)
        throw string("Not a content node while retrieve a node by config_name.");
    if (!elem->has_child_text())
        throw string("No child text in element.");

    return elem->get_child_text()->get_content();
}

CfgServerInfo::CfgServerInfo( const string& cfg_name ) : string (string("/config/ServerInfo/") + cfg_name)
{

}

CfgMainWindow::CfgMainWindow( const string& cfg_name ) : string (string("/config/MainWindow/") + cfg_name)
{

}

CfgServiceList::CfgServiceList( const string& cfg_name ) : string (string("/config/ServiceList/") + cfg_name)
{

}