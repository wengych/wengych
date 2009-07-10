#include "SetArgumentDlg.h"

SetArgumentDlg::SetArgumentDlg(Gtk::Window& parent, ParentDlgCallBackType parent_call_back, StringArray strArr)
: Dialog(string(""), parent), m_parentCallBack(parent_call_back), m_box()
{
	for (StringArray::iterator it = strArr.begin(); it != strArr.end(); ++it)
	{
		Gtk::Button* pBtn = new Gtk::Button(*it);
		pBtn->signal_clicked().connect(boost::bind(&SetArgumentDlg::on_btn_click, this, *it));
		m_box.pack_start(*pBtn, Gtk::PACK_SHRINK);
		m_btnPtrArr.push_back(pBtn);
	}
	
	get_vbox()->pack_start(m_box);
	show_all();
}

void SetArgumentDlg::on_btn_click(string str)
{
	m_parentCallBack(str);
}

SetArgumentDlg::~SetArgumentDlg()
{
	for (ButtonPtrArr::iterator it = m_btnPtrArr.begin(); it != m_btnPtrArr.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}
}

