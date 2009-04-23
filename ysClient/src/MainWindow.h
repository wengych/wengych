/*
 * MainWindow.h
 *
 *  Created on: Apr 21, 2009
 *      Author: wengych
 */

#include <gtkmm/dialog.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/textview.h>
#include <gtkmm/listviewtext.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/box.h>

#include <iostream>

#include "YsFrame.h"

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

class MainWindow: public Gtk::Dialog
{
public:
    MainWindow();
    virtual ~MainWindow();

    void on_service_list_raw_activated(const Gtk::TreeModel::Path&, Gtk::TreeViewColumn*);
    void on_send_button_clicked();

    int get_activated_row_in_service_list();

protected:
    YsFrame m_inputFrame;
    YsFrame m_outputFrame;
    Gtk::ListViewText m_serviceList;

    Gtk::Button m_btnSendRequest;

    Gtk::VBox m_vBox;
    Gtk::HBox m_hBox1;
    Gtk::HButtonBox m_hBox2;
};

#endif /* MAINWINDOW_H_ */
