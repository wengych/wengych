#ifndef _YS_CLIENT_COMMON_H_
#define _YS_CLIENT_COMMON_H_

#include <vector>
#include <list>
#include <map>
#include <gtkmm.h>
#include <glibmm.h>
#include <iostream>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

typedef Glib::ustring string;
typedef std::vector<void*> BusVector;
typedef BusVector::iterator BusIterator;
typedef boost::function<void(void* /*bus_in*/, void** /*bus_out*/)> SessionSockCallBackType;
typedef std::vector<string> StringArray;
typedef std::list<string> StringList;

typedef boost::shared_ptr<Gtk::Label> LabelPtr;
typedef std::vector<LabelPtr> LabelPtrArray;

typedef boost::shared_ptr<Gtk::Widget> WidgetPtr;
typedef std::vector<WidgetPtr> WidgetPtrArray;

typedef boost::shared_ptr<Gtk::HBox> HBoxPtr;
typedef std::vector<HBoxPtr> HBoxPtrArray;

#endif // _YS_CLIENT_COMMON_H_
