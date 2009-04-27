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

Glib::ustring AppConfig::ReadOne(const Glib::ustring& config_name)
{
    xmlpp::NodeSet node_set = m_configRoot->find(config_name);
    xmlpp::Element *elem = dynamic_cast<xmlpp::Element *>(*node_set.begin());
    if (NULL == elem)
        throw Glib::ustring("Not a content node while retrieve a node by config_name.");
    if (!elem->has_child_text())
        throw Glib::ustring("No child text in element.");

    return elem->get_child_text()->get_content();
}
