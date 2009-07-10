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
	ButtonPtr btn(new Gtk::Button("Del"));
	m_delBtn.push_back(btn);
    m_labels.push_back(LabelPtr(label));
    m_widgets.push_back(WidgetPtr(widget));

    HBoxPtr pHBox(new Gtk::HBox());
	pHBox->pack_start(*btn, Gtk::PACK_SHRINK, 5);
    pHBox->pack_start(*label, Gtk::PACK_SHRINK, 5);
    pHBox->pack_start(*widget, Gtk::PACK_SHRINK, 5);
    m_hBoxArr.push_back(pHBox);
    m_vBox.pack_start(*pHBox, Gtk::PACK_SHRINK, 5);

	btn->signal_clicked().connect(boost::bind(&YsFrame::on_delete_item, this, pHBox.get(), btn.get(), label, widget));
}

void YsFrame::on_delete_item(Gtk::HBox* box, Gtk::Button* btn, Gtk::Label* label, Gtk::Widget* widget)
{
	m_vBox.remove(*box);

	for (HBoxPtrArray::iterator it = m_hBoxArr.begin();
		it != m_hBoxArr.end(); ++it)
	{
		if (it->get() == box)
		{
			m_hBoxArr.erase(it);
			break;
		}
	}


	for (ButtonPtrArray::iterator it = m_delBtn.begin();
		it != m_delBtn.end(); ++it)
	{
		if (it->get() == btn)
		{
			m_delBtn.erase(it);
			break;
		}
	}

	
	for (LabelPtrArray::iterator it = m_labels.begin();
		it != m_labels.end(); ++it)
	{
		if (it->get() == label)
		{
			m_labels.erase(it);
			break;
		}
	}

	for (WidgetPtrArray::iterator it = m_widgets.begin();
		it != m_widgets.end(); ++it)
	{
		if (it->get() == widget)
		{
			m_widgets.erase(it);
			break;
		}
	}


	/*
	m_vBox.remove(m_hBoxArr.find());
	m_hBoxArr.erase(m_hBoxArr.begin() + (index));
	m_labels.erase(m_labels.begin() + (index));
	m_widgets.erase(m_widgets.begin() + (index));
	m_delBtn.erase(m_delBtn.begin() + (index));

	for (size_t i = 0; i < m_delBtn.size(); ++i)
	{
		m_delBtn[i]->signal_clicked().connect(boost::bind(&YsFrame::on_delete_item, this, i));
	}
	*/
}

void YsFrame::clear()
{
	m_delBtn.clear();
	m_labels.clear();
	m_widgets.clear();
    m_hBoxArr.clear();
}

string YsFrame::get_item_label_text( int idx )
{
	return m_labels.at(idx)->get_text();
}

string YsFrame::get_item_widget_data( int idx )
{
	Gtk::Entry *entry = dynamic_cast<Gtk::Entry *>(m_widgets.at(idx).get());
	if (NULL != entry)
		return entry->get_text();
	return "";
}

int YsFrame::get_item_count()
{
	assert( m_labels.size() == m_widgets.size() );
	return m_labels.size();
}