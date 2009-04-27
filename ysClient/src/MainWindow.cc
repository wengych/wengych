/*
 * MainWindow.cpp
 *
 *  Created on: Apr 21, 2009
 *      Author: wengych
 */

#include "MainWindow.h"

#include <ysdef.h>
#include <boost/lexical_cast.hpp>
#include <memory>

#ifdef __OS_WIN__
#pragma comment(lib,"wsock32.lib")
#include <windows.h>
#endif

MainWindow::MainWindow() :
    m_inputFrame(), m_outputFrame(), m_serviceList(1),
    m_btnSendRequest("Send"), m_vBox(false, 5), m_hBox1(false, 5)
{
    InitServerInfo();
	m_sessionPtr.reset(new Session(m_appConfig, sigc::mem_fun(this, &MainWindow::ServiceCallSock)));
	if (!m_sessionPtr)
		throw string("Init session failed!");

    this->set_title(m_appConfig.ReadOne(CfgMainWindow("title")));
    this->set_border_width(30);

    m_inputFrame.set_label(m_appConfig.ReadOne(CfgMainWindow("InputFrame/label")));
    m_outputFrame.set_label(m_appConfig.ReadOne(CfgMainWindow("OutputFrame/label")));
    m_hBox1.pack_start(m_inputFrame, Gtk::PACK_SHRINK);
    m_hBox1.pack_start(m_outputFrame, Gtk::PACK_SHRINK);

    InitServiceList();
    m_hBox1.pack_start(m_serviceList, Gtk::PACK_SHRINK);

    //// ================
    m_btnSendRequest.signal_clicked().connect(sigc::mem_fun(*this,
            &MainWindow::on_send_button_clicked));
    m_hBox2.pack_start(m_btnSendRequest);

    //// ================
    m_vBox.pack_start(m_hBox1);
    m_vBox.pack_start(m_hBox2);

    this->get_vbox()->pack_start(m_vBox);

    show_all();
    std::cout << "show_all()" << std::endl;
}

void MainWindow::on_service_list_select_change()
{
    std::cout << "on_service_list_select_change()" << std::endl;
    std::cout << "service list selection: " << get_selected_row_in_service_list() << std::endl;

	try {
		m_inputFrame.clear();
		m_outputFrame.clear();
		int idx = get_selected_row_in_service_list();
		if (idx < 0) {
			m_btnSendRequest.set_sensitive(false);
			return ;
		}

		string service_name = m_serviceList.get_text(idx);
		StringArray input_args = m_sessionPtr->get_input_args(service_name);
		for (StringArray::iterator it = input_args.begin(); it != input_args.end(); ++it)
			m_inputFrame.add_item(new Gtk::Label(*it), new Gtk::Entry());

		m_inputFrame.show_all_children();
		m_btnSendRequest.set_sensitive();
	} catch (string& msg) {
		Gtk::MessageDialog infoDlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
		infoDlg.run();
	}
}

void MainWindow::output_var_to_xml_file( void* bus )
{
    void* str = NULL;
    while (1)
    {
        str = YSVarStringNew2(10240);
        YSVarShow(bus, 0, str);
        std::ofstream ofile("test.xml", std::ios_base::app);
        ofile << "\n<================ />\n";
        ofile.write((char*)YSVarStringGet(str), YSVarStringGetLen(str));

        break;
    }

    YSVarFree(str);
}

void MainWindow::on_send_button_clicked()
{
    void* send_bus = NULL;
    void* recv_bus = NULL;
    void* recv_key_array = NULL;

    try {
        if ( NULL==(send_bus = YSUserBusNew(0)) )
            throw string("SendBus is NULL.");

		int idx = get_selected_row_in_service_list();
		if (idx < 0)
			throw string("illegal index of service list");
		string service_name = m_serviceList.get_text(idx);

        char strDictIn[] = "dict_in1";
        YSUserBusAddString(send_bus, YSDICT_SERVNAME, service_name.c_str(), service_name.length());
		int count = m_inputFrame.get_item_count();
		for (int i = 0; i < count; ++i)
		{
			string label = m_inputFrame.get_item_label_text(i);
			string widget = m_inputFrame.get_item_widget_data(i);
			YSUserBusAddString(send_bus, label.c_str(), widget.c_str(), widget.length());
		}

        // 输出SendBus到文件
        this->output_var_to_xml_file(send_bus);
		ServiceCallSock(send_bus, &recv_bus);
        // 输出RecvBus到文件
        this->output_var_to_xml_file(recv_bus);

        if (!recv_bus)
            throw string("Error occurred when recv data, create recvBus failed!");

        // TODO: re-write update method
        // UpdateView(recv_key_array, VIEW_FLAG_OUT, RecvBus);
		StringArray output_args = m_sessionPtr->get_output_args(service_name);
		for (StringArray::iterator it = output_args.begin(); it != output_args.end(); ++it)
		{
			void* arr = YSUserBusGetArray(recv_bus, it->c_str());
			if (!arr)
				throw string("Get Array from recv_bus failed! Array key: ") + *it;

			int arr_len = YSVarArrayGetLen(arr);
			for (int j = 0; j < arr_len; ++j) {
				void* var = YSVarArrayGet(arr, j);
				if (!var)
					throw string("Get var from Array failed! Array key: ") + *it + string(" Index of array: ") + boost::lexical_cast<string>(j);
				string text((char*)YSVarStringGet(var));
				Gtk::Entry* entry = new Gtk::Entry();
				entry->set_text(text);
				entry->set_editable(false);
				m_outputFrame.add_item(new Gtk::Label(*it), entry);
			}
		}

		m_outputFrame.show_all_children();
    } catch (string& msg) {
        Gtk::MessageDialog infoDlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
        infoDlg.run();
    }

    YSUserBusFree(send_bus);
    YSUserBusFree(recv_bus);
    YSVarArrayFree(recv_key_array);
}

int MainWindow::get_selected_row_in_service_list()
{
    if (m_serviceList.get_selected().size() == 1)
        return m_serviceList.get_selected().at(0);
    else
        return -1;
}

MainWindow::~MainWindow()
{
}

void MainWindow::InitServiceList()
{
	try {
		m_serviceList.set_size_request(100, 100);
		m_serviceList.set_column_title(0, m_appConfig.ReadOne(CfgMainWindow("ServiceListColumnName")));
		std::list<string> service_list = m_sessionPtr->get_service_list();
		for (std::list<string>::iterator it = service_list.begin(); it != service_list.end(); ++it)
			m_serviceList.append_text(*it);

		m_refTreeSelection = m_serviceList.get_selection();
		m_refTreeSelection->set_mode(Gtk::SELECTION_SINGLE);
		m_refTreeSelection->signal_changed().connect(
			sigc::mem_fun(*this, &MainWindow::on_service_list_select_change));
    } catch (string& msg) {
        Gtk::MessageDialog infoDlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
        infoDlg.run();
        throw string("InitServiceList failed.");
    }
}

void MainWindow::InitServerInfo()
{
    string ip = m_appConfig.ReadOne(CfgServerInfo("ip"));
    string port = m_appConfig.ReadOne(CfgServerInfo("port"));
    string time_out = m_appConfig.ReadOne(CfgServerInfo("time_out"));

    memset(m_ip, 0, sizeof(ip));
    strcpy(m_ip, ip.c_str());
    m_port = boost::lexical_cast<short>(port);
    m_time_out = boost::lexical_cast<int>(time_out);
}

void MainWindow::YsArrayToStringArray( void* var_arr, StringArray& str_arr)
{
    int arr_len = YSVarArrayGetLen(var_arr);
    for (int i = 0; i < arr_len; ++i) {
        str_arr.push_back((char*)YSVarStringGet(
            YSVarArrayGet(var_arr, i)));
    }
}

void MainWindow::ServiceCallSock( void* p_in_bus, void** pp_out_bus)
{
	if (FALSE == YSServiceClientCallSock(m_ip, m_port, m_time_out, p_in_bus, pp_out_bus)) {
#ifdef __OS_WIN__
		int err = GetLastError();
		throw string(boost::lexical_cast<string>(err));
#elif
		throw string("ServiceClientCall failed!");
#endif // __OS_WIN__
	}

}
