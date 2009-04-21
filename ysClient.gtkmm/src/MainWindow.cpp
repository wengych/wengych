/*
 * MainWindow.cpp
 *
 *  Created on: Apr 21, 2009
 *      Author: wengych
 */

#include "MainWindow.h"
#include <ysdef.h>

MainWindow::MainWindow() :
    m_inputFrame("输入"), m_outputFrame("输出"), m_vBox(false, 5)
{
    /*
    using namespace std;
    get_vbox()->pack_start(m_vBox);
    cout << "get_vbox." << endl;
    m_vBox.set_border_width(5);
    cout << "m_vBox.set_border_width()" << endl;
    m_vBox.pack_start(m_inputFrame);
    cout << "m_vBox.pack_start(m_inputFrame)" << endl;
    m_vBox.pack_start(m_outputFrame, Gtk::PACK_SHRINK);
    cout << "m_vBox.pack_start(m_outputFrame, Gtk::PACK_SHRINK)" << endl;

    show_all();
    */
}

MainWindow::~MainWindow()
{
    // TODO Auto-generated destructor stub
}
