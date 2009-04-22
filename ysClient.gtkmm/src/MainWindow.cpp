/*
 * MainWindow.cpp
 *
 *  Created on: Apr 21, 2009
 *      Author: wengych
 */

#include "MainWindow.h"
#include <ysdef.h>

MainWindow::MainWindow() :
    m_inputFrame("输入"), m_outputFrame("输出"), m_serviceList(1),
            m_btnSendRequest("发送请求"), m_vBox(false, 5), m_hBox1(false, 5)
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

    m_serviceList.add_events();
    m_serviceList.signal_columns_changed().connect(sigc::mem_fun(*this,
            &MainWindow::on_columns_changed));
    m_hBox1.pack_start(m_serviceList, Gtk::PACK_SHRINK);

    //// ================
    m_hBox2.pack_start(m_btnSendRequest);

    //// ================
    m_vBox.pack_start(m_hBox1);
    m_vBox.pack_start(m_hBox2);

    this->get_vbox()->pack_start(m_vBox);

    show_all();
    std::cout << "show_all()" << std::endl;
}

bool MainWindow::on_service_list_press(GdkEventButton* event)
{
    std::cout << "on_service_list_press" << std::endl;

    return true;
}

void MainWindow::on_columns_changed()
{
    std::cout << "on_columns_changed()" << std::endl;

    m_inputFrame.add_item(new Gtk::Label("__DICT_IN"), new Gtk::Entry());
    m_inputFrame.add_item(new Gtk::Label("__DICT_IN2"), new Gtk::Entry());
}
MainWindow::~MainWindow()
{
}
