/*
 * MainWindow.h
 *
 *  Created on: Apr 21, 2009
 *      Author: wengych
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "common.h"

class Session;
class AppConfig;
class InfoFrame;

class MainWindow: public Gtk::Dialog
{
protected:
	typedef Glib::ustring string;
	typedef boost::shared_ptr<Session> SessionPtr;
	typedef boost::shared_ptr<AppConfig> AppConfigPtr;
	typedef boost::shared_ptr<InfoFrame> InfoFramePtr;
	typedef std::vector<string> StringArray;
public:
    MainWindow();
    virtual ~MainWindow();
    void on_service_list_select_change();

	void on_send_button_clicked();
	void on_add_argument_clicked();
	void add_argument(string&);
	void UpdateInputFrame( StringArray & );
	void UpdateOutputFrame( StringArray &, void* );
	int get_selected_row_in_service_list();
    void output_var_to_xml_file( void* bus, const string& );
    void InitServiceList();
    void InitServerInfo();
    void YsArrayToStringArray(void* , /*out*/ StringArray& );
	void ServiceCallSock(void*, void**);

protected:
    InfoFramePtr m_infoFramePtr;

	Gtk::ScrolledWindow m_treeScrollWnd;
	Gtk::TreeView m_serviceList;

    Gtk::Button m_btnSendRequest;
	Gtk::Button m_btnAddArgument;

    Gtk::VBox m_vBox;
    Gtk::HBox m_hBox1;
    Gtk::HButtonBox m_hBox2;

	AppConfigPtr m_appConfigPtr;
    SessionPtr m_sessionPtr;

    char m_ip[16];
    short m_port;
    int m_time_out;

	Glib::RefPtr<Gtk::TreeSelection> m_refTreeSelection;
	Glib::RefPtr<Gtk::TreeStore> m_refTreeStore;

	struct ModelColumns : public Gtk::TreeModelColumnRecord
	{
		Gtk::TreeModelColumn<string> item;
		ModelColumns() {
			add(item);
		}
	};

	const ModelColumns m_columns;
};

#endif /* MAINWINDOW_H_ */
