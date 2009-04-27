/*
 * MainWindow.h
 *
 *  Created on: Apr 21, 2009
 *      Author: wengych
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "common.h"
#include "YsFrame.h"
#include "AppConfig.h"
#include "Session.h"

class MainWindow: public Gtk::Dialog
{
protected:
	typedef Glib::ustring string;
	typedef boost::shared_ptr<Session> SessionPtr;
	typedef std::vector<string> StringArray;
public:
    MainWindow();
    virtual ~MainWindow();

    void on_service_list_select_change();
    void on_send_button_clicked();
    int get_selected_row_in_service_list();
    void output_var_to_xml_file( void* bus );
    void InitServiceList();
    void InitServerInfo();
    void YsArrayToStringArray(void* , StringArray& );
	void ServiceCallSock(void*, void**);

protected:
    YsFrame m_inputFrame;
    YsFrame m_outputFrame;
    Gtk::ListViewText m_serviceList;

    Gtk::Button m_btnSendRequest;

    Gtk::VBox m_vBox;
    Gtk::HBox m_hBox1;
    Gtk::HButtonBox m_hBox2;

	AppConfig m_appConfig;
    SessionPtr m_sessionPtr;

    char m_ip[16];
    short m_port;
    int m_time_out;

	Glib::RefPtr<Gtk::TreeSelection> m_refTreeSelection;
};

#endif /* MAINWINDOW_H_ */
