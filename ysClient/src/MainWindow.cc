/*
 * MainWindow.cpp
 *
 *  Created on: Apr 21, 2009
 *      Author: wengych
 */

#include "MainWindow.h"

#include <ysdef.h>
#include <boost/lexical_cast.hpp>
#include <memory>

#ifdef __OS_WIN__
#pragma comment(lib,"wsock32.lib")
#include <windows.h>
#endif

#include "AppConfig.h"
#include "Session.h"
#include "YsFrame.h"

MainWindow::MainWindow() :
    m_inputFramePtr(), m_outputFramePtr(), m_serviceList(),
    m_btnSendRequest(), m_vBox(false, 5), m_hBox1(false, 5)
{
	m_appConfigPtr.reset(new AppConfig());
	m_inputFramePtr.reset(new YsFrame());
	m_outputFramePtr.reset(new YsFrame);

    InitServerInfo();
	m_sessionPtr.reset(new Session(m_appConfigPtr, sigc::mem_fun(this, &MainWindow::ServiceCallSock)));
	if (!m_sessionPtr)
		throw string("Init session failed!");

    this->set_title(m_appConfigPtr->ReadOne(CfgMainWindow("title")));
    this->set_border_width(30);

	m_btnSendRequest.set_label(m_appConfigPtr->ReadOne(CfgMainWindow("SendRequest")));

    m_inputFramePtr->set_label(m_appConfigPtr->ReadOne(CfgMainWindow("InputFrame/label")));
    m_outputFramePtr->set_label(m_appConfigPtr->ReadOne(CfgMainWindow("OutputFrame/label")));
    m_hBox1.pack_start(*m_inputFramePtr, Gtk::PACK_SHRINK);
    m_hBox1.pack_start(*m_outputFramePtr, Gtk::PACK_SHRINK);

    InitServiceList();
    m_hBox1.pack_start(m_treeScrollWnd, Gtk::PACK_SHRINK);

    //// ================
    m_btnSendRequest.signal_clicked().connect(sigc::mem_fun(*this,
            &MainWindow::on_send_button_clicked));
    m_hBox2.pack_start(m_btnSendRequest);

    //// ================
    m_vBox.pack_start(m_hBox1);
    m_vBox.pack_start(m_hBox2);

    this->get_vbox()->pack_start(m_vBox);

    show_all();
    std::cout << "show_all()" << std::endl;
}

void MainWindow::on_service_list_select_change()
{
    std::cout << "on_service_list_select_change()" << std::endl;
	try {
		m_inputFramePtr->clear();
		m_outputFramePtr->clear();

		Gtk::TreeIter treeIt = m_refTreeSelection->get_selected();
		if ( 0 == m_refTreeSelection->count_selected_rows() )
			return ;
		Gtk::TreeNodeChildren treeNodeChild = m_refTreeStore->children();
		Gtk::TreeModel::Path path = m_refTreeStore->get_path(treeIt);
		// string index = m_refTreeStore->get_string(treeIt);
		// Gtk::TreeRow row = treeNodeChild[boost::lexical_cast<int>(index)];
		Gtk::TreeRow row = treeNodeChild[*(path.begin())];
		string service_name = row[m_columns.item];
		UpdateInputFrame(m_sessionPtr->get_input_args(service_name));

		m_btnSendRequest.set_sensitive();
	} catch (string& msg) {
		Gtk::MessageDialog infoDlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
		infoDlg.run();
	}
}

void MainWindow::output_var_to_xml_file( void* var, const string& sep = "========" )
{
    void* str = NULL;
    while (1)
    {
        str = YSVarStringNew2(10240);
        YSVarShow(var, 0, str);
        std::ofstream ofile("test.xml", std::ios_base::app);
        ofile << "\n<" << sep << "/>\n";
        ofile.write((char*)YSVarStringGet(str), YSVarStringGetLen(str));
		ofile.close();

        break;
    }

    YSVarFree(str);
}

void MainWindow::on_send_button_clicked()
{
    void* send_bus = NULL;
    void* recv_bus = NULL;
    void* recv_key_array = NULL;

    try {
        if ( NULL==(send_bus = YSUserBusNew(0)) )
            throw string("SendBus is NULL.");

		Gtk::TreeIter treeIt = m_refTreeSelection->get_selected();
		Gtk::TreeModel::Path path = m_refTreeStore->get_path(treeIt);
		Gtk::TreeNodeChildren treeNodeChild = m_refTreeStore->children();
		Gtk::TreeRow row = treeNodeChild[*(path.begin())];
		string service_name = row[m_columns.item];

        YSUserBusAddString(send_bus, YSDICT_SERVNAME, service_name.c_str(), service_name.length());
		int count = m_inputFramePtr->get_item_count();
		for (int i = 0; i < count; ++i)
		{
			string label = m_inputFramePtr->get_item_label_text(i);
			string widget = m_inputFramePtr->get_item_widget_data(i);
			if (widget.length() > 0)
				YSUserBusAddString(send_bus, label.c_str(), widget.c_str(), widget.length());
		}

        // 输出SendBus到文件
        this->output_var_to_xml_file(send_bus, "Send bus");
		ServiceCallSock(send_bus, &recv_bus);
        // 输出RecvBus到文件
        this->output_var_to_xml_file(recv_bus, "Recv bus");

        if (!recv_bus)
            throw string("Error occurred when recv data, create recvBus failed!");

        UpdateOutputFrame(m_sessionPtr->get_output_args(service_name), recv_bus);
    } catch (string& msg) {
        Gtk::MessageDialog infoDlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
        infoDlg.run();
    }

    YSUserBusFree(send_bus);
    YSUserBusFree(recv_bus);
    YSVarArrayFree(recv_key_array);
}

MainWindow::~MainWindow()
{
}

void MainWindow::InitServiceList()
{
	try {
		m_serviceList.set_size_request(150, 100);

		// TreeStore
		m_refTreeStore = Gtk::TreeStore::create(m_columns);

		m_serviceList.set_model(m_refTreeStore);
		m_serviceList.set_rules_hint();

		int cols_count = m_serviceList.append_column(
			m_appConfigPtr->ReadOne(CfgMainWindow("ServiceListColumnName")),
			m_columns.item);
		Gtk::TreeViewColumn* pCol = m_serviceList.get_column(cols_count - 1);
		if (pCol) {
			Gtk::CellRenderer* pRenderer = pCol->get_first_cell_renderer();
#ifdef GLIBMM_PROPERTIES_ENABLED
			pRenderer->property_xalign().set_value(0.0);
#else
			pRenderer->set_property("xalign", 0.0);
#endif
			pCol->set_clickable();
		}

		// TreeSelection
		m_refTreeSelection = m_serviceList.get_selection();
		m_refTreeSelection->set_mode(Gtk::SELECTION_SINGLE);
		m_refTreeSelection->signal_changed().connect(
			sigc::mem_fun(*this, &MainWindow::on_service_list_select_change));
		
		std::list<string> service_list = m_sessionPtr->get_service_list();
		for (std::list<string>::iterator it = service_list.begin(); it != service_list.end(); ++it) {
			Gtk::TreeRow row = *(m_refTreeStore->append());
			string tmp = *it;
			row.set_value(m_columns.item, tmp);
            Session::ServiceInfo& serviceInfo = m_sessionPtr->get_service_info(*it);
			Gtk::TreeRow childRow = *(m_refTreeStore->append(row.children()));
            childRow.set_value(m_columns.item, serviceInfo.version);
			childRow = *(m_refTreeStore->append(row.children()));
			childRow.set_value(m_columns.item, serviceInfo.application_name);
			childRow = *(m_refTreeStore->append(row.children()));
			childRow.set_value(m_columns.item, serviceInfo.function_name);
			childRow = *(m_refTreeStore->append(row.children()));
			childRow.set_value(m_columns.item, serviceInfo.library_name);
			childRow = *(m_refTreeStore->append(row.children()));
			childRow.set_value(m_columns.item, serviceInfo.dictory_ver);
		}
		m_serviceList.expand_all();

		m_treeScrollWnd.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
		m_treeScrollWnd.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
		m_treeScrollWnd.add(m_serviceList);
    } catch (string& msg) {
        Gtk::MessageDialog infoDlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
        infoDlg.run();
        throw string("InitServiceList failed.");
    }
}

void MainWindow::InitServerInfo()
{
    string ip = m_appConfigPtr->ReadOne(CfgServerInfo("ip"));
    string port = m_appConfigPtr->ReadOne(CfgServerInfo("port"));
    string time_out = m_appConfigPtr->ReadOne(CfgServerInfo("time_out"));

    memset(m_ip, 0, sizeof(ip));
    strcpy(m_ip, ip.c_str());
    m_port = boost::lexical_cast<short>(port);
    m_time_out = boost::lexical_cast<int>(time_out);
}

void MainWindow::YsArrayToStringArray( void* var_arr, StringArray& str_arr)
{
    int arr_len = YSVarArrayGetLen(var_arr);
    for (int i = 0; i < arr_len; ++i) {
        str_arr.push_back((char*)YSVarStringGet(
            YSVarArrayGet(var_arr, i)));
    }
}

void MainWindow::ServiceCallSock( void* p_in_bus, void** pp_out_bus)
{
	if (FALSE == YSServiceClientCallSock(m_ip, m_port, m_time_out, p_in_bus, pp_out_bus)) {
#ifdef __OS_WIN__
		int err = GetLastError();
		throw string(boost::lexical_cast<string>(err));
#elif
		throw string("ServiceClientCall failed!");
#endif // __OS_WIN__
	}
}

void MainWindow::UpdateOutputFrame( StringArray &output_args, void* recv_bus )
{
	for (StringArray::iterator it = output_args.begin(); it != output_args.end(); ++it)
	{
		void* arr = YSUserBusGetArray(recv_bus, it->c_str());
		if (!arr)
			throw string("Get Array from recv_bus failed! Array key: ") + *it;

		int arr_len = YSVarArrayGetLen(arr);
		for (int j = 0; j < arr_len; ++j) {
			Gtk::Widget* widget = NULL;
			void* var = YSVarArrayGet(arr, j);
			if (!var)
				throw string("Get var from Array failed! Array key: ") + *it + string(" Index of array: ") + boost::lexical_cast<string>(j);
			string text; // ((char*)YSVarStringGet(var));
			switch (YSVarGetType(var)) {
				case VARTYPE_MEM_VT_STRING:
					{
						text = (char*)YSVarStringGet(var);
						Gtk::Entry* entry = new Gtk::Entry();
						entry->set_text(text);
						entry->set_editable(false);
						widget = entry;
						break;
					}
				case VARTYPE_MEM_VT_BIN:
					{
						void* tmp_hash = YSMPHashFromVarBin(var, 0);
						void* tmp_str = YSVarStringNew();

						output_var_to_xml_file(var, "bin");
						output_var_to_xml_file(tmp_hash, "hash");

						YSVarHashShow(tmp_hash, 0, tmp_str);
						char* tmp = (char*)YSVarStringGet(tmp_str);
						if (tmp != NULL)
							text = tmp;

						Gtk::Entry* entry = new Gtk::Entry();
						Gtk::TreeView* tree = new Gtk::TreeView;
						entry->set_text(text);
						entry->set_editable(false);
						widget = entry;
						break;
					}
				default:
					break;
			}
			m_outputFramePtr->add_item(new Gtk::Label(*it), widget);
		}
	}

	m_outputFramePtr->show_all_children();
}

void MainWindow::UpdateInputFrame( StringArray &input_args )
{
	for (StringArray::iterator it = input_args.begin(); it != input_args.end(); ++it)
		m_inputFramePtr->add_item(new Gtk::Label(*it), new Gtk::Entry());

	m_inputFramePtr->show_all_children();
}
