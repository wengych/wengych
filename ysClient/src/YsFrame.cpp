/*
 * YsFrame.cpp
 *
 *  Created on: Apr 22, 2009
 *      Author: wengych
 */

#include "YsFrame.h"

void YsFrame::Init()
{
    /*
    m_labels.push_back(LabelPtr(new Gtk::Label("test label")));
    m_widgets.push_back(WidgetPtr(new Gtk::Entry()));

    HBoxPtr pHBox(new Gtk::HBox());
    m_hBoxArr.push_back(pHBox);
    m_vBox.pack_start(*pHBox, Gtk::PACK_SHRINK);
    */

    add(m_vBox);
    m_vBox.set_size_request(300,300);
}

void YsFrame::add_item(Gtk::Label *label, Gtk::Widget *widget)
{
    m_labels.push_back(LabelPtr(label));
    m_widgets.push_back(WidgetPtr(widget));

    HBoxPtr pHBox(new Gtk::HBox());
    pHBox->pack_start(*label, Gtk::PACK_SHRINK, 5);
    pHBox->pack_start(*widget, Gtk::PACK_SHRINK, 5);
    m_hBoxArr.push_back(pHBox);
    m_vBox.pack_start(*pHBox, Gtk::PACK_SHRINK, 5);
}

void YsFrame::clear()
{
    m_hBoxArr.clear();

}
