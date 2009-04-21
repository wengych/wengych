/*
 * MainWindow.h
 *
 *  Created on: Apr 21, 2009
 *      Author: wengych
 */

#include <gtkmm/dialog.h>
#include <gtkmm/label.h>
#include <gtkmm/frame.h>
#include <gtkmm/box.h>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>

#include <iostream>

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

class MainWindow: public Gtk::Dialog
{
public:
    MainWindow();
    virtual ~MainWindow();

protected:
    typedef boost::shared_ptr<Gtk::Label> LabelPtr;
    typedef boost::shared_array<Gtk::Label> LabelArray;

    typedef boost::shared_ptr<Gtk::Widget> WidgetPtr;
    typedef boost::shared_array<Gtk::Widget> WidgetArray;

    LabelArray m_inputLabels;
    LabelArray m_outputLabels;

    WidgetArray m_inputWidgets;
    WidgetArray m_outputWidgets;

    Gtk::Frame m_inputFrame;
    Gtk::Frame m_outputFrame;

    Gtk::VBox m_vBox;
};

#endif /* MAINWINDOW_H_ */
