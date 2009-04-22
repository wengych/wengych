/*
 * MainWindow.h
 *
 *  Created on: Apr 21, 2009
 *      Author: wengych
 */

#include <gtkmm/dialog.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/textview.h>
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

protected:
    YsFrame m_inputFrame;
    YsFrame m_outputFrame;

    Gtk::VBox m_vBox;
    Gtk::HBox m_hBox;
};

#endif /* MAINWINDOW_H_ */
