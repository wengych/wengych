#ifndef _YS_CLIENT_COMMON_H_
#define _YS_CLIENT_COMMON_H_

#include <vector>
#include <list>
#include <map>
#include <boost/function.hpp>
#include <gtkmm.h>
#include <glibmm.h>
#include <iostream>
#include <fstream>
#include <boost/shared_ptr.hpp>

typedef Glib::ustring string;
typedef std::vector<void*> BusVector;
typedef BusVector::iterator BusIterator;
typedef boost::function<void(void* /*bus_in*/, void** /*bus_out*/)> SessionSockCallBackType;
typedef std::vector<string> StringArray;
typedef std::list<string> StringList;

#endif // _YS_CLIENT_COMMON_H_