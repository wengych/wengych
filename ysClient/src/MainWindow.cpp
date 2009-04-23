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
    m_inputFrame("input"), m_outputFrame("output"), m_serviceList(1),
    m_btnSendRequest("Send"), m_vBox(false, 5), m_hBox1(false, 5)
{
    using namespace std;
    this->set_title("ysClient");
    this->set_border_width(30);

    m_hBox1.pack_start(m_inputFrame, Gtk::PACK_SHRINK);

    m_hBox1.pack_start(m_outputFrame, Gtk::PACK_SHRINK);

    m_serviceList.set_size_request(100, 100);
    m_serviceList.set_column_title(0, "Service List");
    m_serviceList.append_text("First column");
    m_serviceList.append_text("Second column");

    // m_serviceList.add_events(Gdk::EventMask::ALL_EVENTS_MASK);
    m_serviceList.signal_row_activated().connect(sigc::mem_fun(*this,
            &MainWindow::on_service_list_raw_activated));
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

    std::cout << "service list selection: " << get_activated_row_in_service_list() << std::endl;
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

void MainWindow::output_bus_to_xml_file( void* bus )
{
    void* str = NULL;
    while (1)
    {
        str = YSVarStringNew2(10240);
        YSUserBusShow(bus, 0, str);
        std::ofstream ofile("test.xml", std::ios_base::app);
        ofile << "\n<================ />\n";
        ofile.write((char*)YSVarStringGet(str), YSVarStringGetLen(str));

        break;
    }

    YSVarFree(str);
}

void MainWindow::on_send_button_clicked()
{

    const char* ip = "192.168.0.105";
    int port = 9000;
    int time_out = 5;

    void* SendBus = NULL;
    void* RecvBus = NULL;
    void* recv_key_array = NULL;

    try {
        if ( NULL==(SendBus = YSUserBusNew(0)) )
            throw string("SendBus is NULL.");

        char strServName[] = "MyDemoDateTime1";
        char strDictIn[] = "dict_in1";
        YSUserBusAddString(SendBus, YSDICT_SERVNAME, strServName, strlen(strServName));
        YSUserBusAddString(SendBus, YSDICT_IN, strDictIn, strlen(strDictIn));

        /* ========================
         * TODO:
         * loop read all input from widgets in input frame.
        for (size_t i = 0; i < m_pEditIn.GetCount(); ++i) {
            CString strUserInput;
            m_pEditIn[i]->GetWindowText(strUserInput);
            char *p = T2A(strUserInput.GetString());
            YSUserBusAddString(SendBus, input_test[i], p, strlen(p));
        }
        */
        // 输出SendBus到文件
        this->output_bus_to_xml_file(SendBus);

        if (FALSE == YSServiceClientCallSock(ip, port, time_out, SendBus, &RecvBus)) {
#ifdef __OS_WIN__
            int err = GetLastError();
            throw string(boost::lexical_cast<string>(err));
#elif
            throw string("ServiceClientCall failed!");
#endif // __OS_WIN__
        }

        // 输出RecvBus到文件
        this->output_bus_to_xml_file(RecvBus);

        if (!RecvBus)
            throw string("Error occurred when recv data, create recvBus failed!");

        recv_key_array = YSVarArrayNew(0);

        void* strDictOut = YSVarStringSave(YSDICT_OUT, strlen(YSDICT_OUT));
        void* strDictOut2 = YSVarStringSave(YSDICT_OUT2, strlen(YSDICT_OUT2));

        YSVarArrayAdd(recv_key_array, strDictOut);
        YSVarArrayAdd(recv_key_array, strDictOut2);

        // TODO:UpdateView(recv_key_array, VIEW_FLAG_OUT, RecvBus);
    } catch (string& msg) {
        Gtk::MessageDialog infoDlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
        infoDlg.run();
    }

    YSUserBusFree(SendBus);
    YSUserBusFree(RecvBus);
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
