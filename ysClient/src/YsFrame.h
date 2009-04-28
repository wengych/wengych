/*
 * YsFrame.h
 *
 *  Created on: Apr 22, 2009
 *      Author: wengych
 */

#include "common.h"

#ifndef YSFRAME_H_
#define YSFRAME_H_

class YsFrame: public Gtk::Frame
{
public:
    YsFrame() :
        Gtk::Frame()
    {
        Init();
    }
    explicit YsFrame(const Glib::ustring& label) :
        Gtk::Frame(label)
    {
        Init();
    }
    virtual ~YsFrame()
    {
    }

    void Init();
    void add_item(Gtk::Label*, Gtk::Widget*);
	int get_item_count();
	string get_item_label_text(int idx);
	string get_item_widget_data(int idx);
    void clear();

protected:
    LabelPtrArray m_labels;
    WidgetPtrArray m_widgets;

    Gtk::VBox m_vBox;
    HBoxPtrArray m_hBoxArr;
};

#endif /* YSFRAME_H_ */
