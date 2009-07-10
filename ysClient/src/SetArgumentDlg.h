/*
 * SetArgumentDlg.h
 *
 *  Created on: July 8, 2009
 *      Author: wengych
 */

#ifndef SETARGUMENTDLG_H_
#define SETARGUMENTDLG_H_

#include "common.h"

class SetArgumentDlg : public Gtk::Dialog
{
public:
	SetArgumentDlg(Gtk::Window& parent, ParentDlgCallBackType parent_call_back, StringArray strArr);
	~SetArgumentDlg();
	void on_btn_click(string);

private:
	typedef std::vector<Gtk::Button*> ButtonPtrArr;
	ButtonPtrArr m_btnPtrArr;

	ParentDlgCallBackType m_parentCallBack;
	Gtk::VBox m_box;
};

#endif

