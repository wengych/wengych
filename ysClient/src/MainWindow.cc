/*
 * MainWindow.cpp
 *
 *  Created on: Apr 21, 2009
 *      Author: wengych
 */

#include "MainWindow.h"

#include <ysdef.h>
#include <boost/lexical_cast.hpp>

#ifdef __OS_WIN__
#pragma comment(lib,"wsock32.lib")
#include <windows.h>
#endif

MainWindow::MainWindow() :
    m_inputFrame(), m_outputFrame(), m_serviceList(1),
    m_btnSendRequest("Send"), m_vBox(false, 5), m_hBox1(false, 5),
    m_sessionPtr(new Session())
{
    InitServerInfo();

    this->set_title(m_appConfig.ReadOne("/config/MainWindow/title"));
    this->set_border_width(30);

    m_inputFrame.set_label(m_appConfig.ReadOne("/config/MainWindow/InputFrame/label"));
    m_outputFrame.set_label(m_appConfig.ReadOne("/config/MainWindow/OutputFrame/label"));
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

void MainWindow::on_service_list_raw_activated(const Gtk::TreeModel::Path&, Gtk::TreeViewColumn*)
{
    std::cout << "on_service_list_raw_activated()" << std::endl;
    std::cout << "service list selection: " << get_activated_row_in_service_list() << std::endl;

    switch (get_activated_row_in_service_list()) {
    case 0:
        m_inputFrame.clear();
        m_inputFrame.add_item(new Gtk::Label("__DICT_IN"), new Gtk::Entry());
        m_inputFrame.add_item(new Gtk::Label("__DICT_IN2"), new Gtk::Entry());

        break;
    case 1:
        m_inputFrame.clear();
        m_inputFrame.add_item(new Gtk::Label("__DICT_IN"), new Gtk::Entry());
        break;
    default :
        break;
    }
    m_inputFrame.show_all_children();
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

        char strServName[] = "MyDemoDateTime1";
        char strDictIn[] = "dict_in1";
        YSUserBusAddString(send_bus, YSDICT_SERVNAME, strServName, strlen(strServName));
        YSUserBusAddString(send_bus, YSDICT_IN, strDictIn, strlen(strDictIn));

        /* ========================
         * TODO: loop read all input from widgets in input frame.
        for (size_t i = 0; i < m_pEditIn.GetCount(); ++i) {
            CString strUserInput;
            m_pEditIn[i]->GetWindowText(strUserInput);
            char *p = T2A(strUserInput.GetString());
            YSUserBusAddString(SendBus, input_test[i], p, strlen(p));
        }
        */
        // 输出SendBus到文件
        this->output_var_to_xml_file(send_bus);

        if (FALSE == YSServiceClientCallSock(m_ip, m_port, m_time_out, send_bus, &recv_bus)) {
#ifdef __OS_WIN__
            int err = GetLastError();
            throw string(boost::lexical_cast<string>(err));
#elif
            throw string("ServiceClientCall failed!");
#endif // __OS_WIN__
        }

        // 输出RecvBus到文件
        this->output_var_to_xml_file(recv_bus);

        if (!recv_bus)
            throw string("Error occurred when recv data, create recvBus failed!");

        recv_key_array = YSVarArrayNew(0);

        void* strDictOut = YSVarStringSave(YSDICT_OUT, strlen(YSDICT_OUT));
        void* strDictOut2 = YSVarStringSave(YSDICT_OUT2, strlen(YSDICT_OUT2));

        YSVarArrayAdd(recv_key_array, strDictOut);
        YSVarArrayAdd(recv_key_array, strDictOut2);

        // TODO: re-write update method
        // UpdateView(recv_key_array, VIEW_FLAG_OUT, RecvBus);
    } catch (string& msg) {
        Gtk::MessageDialog infoDlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
        infoDlg.run();
    }

    YSUserBusFree(send_bus);
    YSUserBusFree(recv_bus);
    YSVarArrayFree(recv_key_array);
}

int MainWindow::get_activated_row_in_service_list()
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
        void* out_bus = NULL;
        void* in_bus = YSUserBusNew(0);
        if (NULL == in_bus)
            throw string("YSUserBusNew() failed while InitServiceList()");
        string strService = m_appConfig.ReadOne("/config/ServiceList/GetServiceListAppName");
        m_sessionPtr->in_bus_add(in_bus);
        YSUserBusAddString(in_bus, YSDICT_SERVNAME, strService.c_str(), strService.length());

        this->output_var_to_xml_file(in_bus);

        if (FALSE == YSServiceClientCallSock(m_ip, m_port, m_time_out, in_bus, &out_bus)) {
#ifdef __OS_WIN__
            int err = GetLastError();
            throw string(boost::lexical_cast<string>(err));
#elif
            throw string("ServiceClientCall failed!");
#endif // __OS_WIN__
        }

        // 输出RecvBus到文件
        this->output_var_to_xml_file(out_bus);
        void* appBin = YSUserBusGet(out_bus, m_appConfig.ReadOne("/config/ServiceList/Output").c_str());
        if (!appBin)
            throw string("YSUserBusGet() failed while retrieve appVarBin");
        void* appHash= YSMPHashFromVarBin(appBin);
        if (!appHash)
            throw string("HashFromVarBin() failed while retrieve appHash");

        output_var_to_xml_file(appHash);

        int hash_base = YSVarHashGetBase(appHash);
        for (int i = 0; i < hash_base; ++i) {
            void* hash_link = YSVarHashGetLinkByIdx(appHash, i);
            int link_len = YSVarLinkGetLen(hash_link);
            for (int j = 0; j < link_len; ++j) {
                void* link_obj = YSVarLinkGet(hash_link, j);
                string str = m_appConfig.ReadOne("/config/ServiceList/ServiceInfo/name");
                void* var_name = YSVarStructGetByKey(link_obj, str.c_str(), str.length());
                str = m_appConfig.ReadOne("/config/ServiceList/ServiceInfo/input");
                void* var_input_array = YSVarStructGetByKey(link_obj, str.c_str(), str.length());
                str = m_appConfig.ReadOne("/config/ServiceList/ServiceInfo/output");
                void* var_output_array = YSVarStructGetByKey(link_obj, str.c_str(), str.length());

                // m_serviceList.append_text((char*)YSVarStringGet(var_name));
                string name = (char*)YSVarStringGet(var_name);
                StringArray inputArr;//  = (char*)YSVarStringGet(var_input);
                StringArray outputArr;//  = (char*)YSVarStringGet(var_output);

                YsArrayToStringArray(var_input_array, inputArr);
                YsArrayToStringArray(var_output_array, outputArr);


                m_serviceMap.insert(std::make_pair(name, ServiceInfo(name, inputArr, outputArr)));
            }
        }

        // TODO: dynamic generate items in service list.
        m_serviceList.set_size_request(100, 100);
        m_serviceList.set_column_title(0, m_appConfig.ReadOne("/config/MainWindow/ServiceListColumnName"));

        for (ServiceMap::iterator it = m_serviceMap.begin(); it != m_serviceMap.end(); ++it) {
            m_serviceList.append_text(it->first);
        }

        // m_serviceList.add_events(Gdk::EventMask::ALL_EVENTS_MASK);
        m_serviceList.signal_row_activated().connect(sigc::mem_fun(*this,
            &MainWindow::on_service_list_raw_activated));
    } catch (string& msg) {
        Gtk::MessageDialog infoDlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
        infoDlg.run();
        throw string("InitServiceList failed.");
    }
}

void MainWindow::InitServerInfo()
{
    string ip = m_appConfig.ReadOne("/config/ServerInfo/ip");
    string port = m_appConfig.ReadOne("/config/ServerInfo/port");
    string time_out = m_appConfig.ReadOne("/config/ServerInfo/time_out");

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