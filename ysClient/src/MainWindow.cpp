/*
 * MainWindow.cpp
 *
 *  Created on: Apr 21, 2009
 *      Author: wengych
 */

#include "MainWindow.h"
// #include <ysdef.h>

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

void MainWindow::on_send_button_clicked()
{
    std::cout << "on_send_button_clicked" << std::endl;
    std::cout << "service list selection: " << get_activated_row_in_service_list() << std::endl;

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
