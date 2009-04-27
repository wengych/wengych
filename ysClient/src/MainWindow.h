/*
 * MainWindow.h
 *
 *  Created on: Apr 21, 2009
 *      Author: wengych
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <gtkmm.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "YsFrame.h"
#include "AppConfig.h"
#include "Session.h"


typedef Glib::ustring string;
typedef boost::shared_ptr<Session> SessionPtr;
typedef std::vector<string> StringArray;

struct ServiceInfo {
    ServiceInfo(const string& _name, const StringArray& _input, const StringArray& _output)
        : name(_name), input(_input), output(_output)
    {}
    ServiceInfo(const ServiceInfo& rhs)
        : name(rhs.name), input(rhs.input), output(rhs.output)
    {}
    string name;
    StringArray input;
    StringArray output;
};
typedef std::map<string, ServiceInfo> ServiceMap;

class MainWindow: public Gtk::Dialog
{
public:
    MainWindow();
    virtual ~MainWindow();

    void on_service_list_raw_activated(const Gtk::TreeModel::Path&, Gtk::TreeViewColumn*);
    void on_send_button_clicked();
    int get_activated_row_in_service_list();
    void output_var_to_xml_file( void* bus );
    void InitServiceList();
    void InitServerInfo();
    void YsArrayToStringArray(void* , StringArray& );

protected:
    YsFrame m_inputFrame;
    YsFrame m_outputFrame;
    Gtk::ListViewText m_serviceList;

    Gtk::Button m_btnSendRequest;

    Gtk::VBox m_vBox;
    Gtk::HBox m_hBox1;
    Gtk::HButtonBox m_hBox2;

    SessionPtr m_sessionPtr;
    AppConfig m_appConfig;

    char m_ip[16];
    short m_port;
    int m_time_out;

    ServiceMap m_serviceMap;
};

#endif /* MAINWINDOW_H_ */
