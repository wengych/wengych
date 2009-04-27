#ifndef YS_APP_CONFIG_H_
#define YS_APP_CONFIG_H_

#include <glibmm.h>
#include <libxml++/libxml++.h>

class AppConfig
{
public:
    AppConfig();
    ~AppConfig();
    void Init();
    Glib::ustring ReadOne(const Glib::ustring& config_name);
protected:
    xmlpp::Node* m_configRoot;
    xmlpp::DomParser xml_parser;
};

#endif // YS_APP_CONFIG_H_
