/*
 * MainWindow.cpp
 *
 *  Created on: Apr 21, 2009
 *      Author: wengych
 */

#include "MainWindow.h"
// #include <ysdef.h>

MainWindow::MainWindow() :
    m_inputFrame("输入"), m_outputFrame("输出"), m_vBox(false, 5), m_hBox(false, 5)
{
    using namespace std;
    this->set_title("ysClient");
    this->set_border_width(30);

    m_hBox.pack_start(m_inputFrame, Gtk::PACK_SHRINK);

    m_inputFrame.add_item(new Gtk::Label("__DICT_IN"), new Gtk::Entry());
    m_inputFrame.add_item(new Gtk::Label("__DICT_IN2"), new Gtk::Entry());

    m_hBox.pack_start(m_outputFrame, Gtk::PACK_SHRINK);

    m_vBox.pack_start(m_hBox);

    this->get_vbox()->pack_start(m_vBox);

    show_all();
}

MainWindow::~MainWindow()
{
    // TODO Auto-generated destructor stub
}
