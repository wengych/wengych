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

    bool on_service_list_press(GdkEventButton*);
    void on_columns_changed();

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
