#include <iostream>

#include "Session.h"
#include "ysdef.h"
#include "AppConfig.h"

Session::Session(const AppConfigPtr& app_cfg_ptr, const SessionSockCallBackType& _call_back)
: m_appConfigPtr(app_cfg_ptr), m_func(_call_back)
{
	try {
		Init();
	} catch (string& msg) {
		std::cout << msg << std::endl;
	}
}
Session::~Session()
{
    for (BusIterator it = vec_in_bus.begin(); it != vec_in_bus.end(); ++it)
	{
        YSVarFree(*it);
        *it = NULL;
    }

	for (BusIterator it = vec_out_bus.begin(); it != vec_out_bus.end(); ++it)
	{
		YSVarFree(*it);
		*it = NULL;
	}
}

void Session::add_in_bus( void* in_bus )
{
    vec_in_bus.push_back(in_bus);
}

void Session::add_out_bus( void* out_bus )
{
	vec_out_bus.push_back(out_bus);
}

std::list<Glib::ustring> Session::get_service_list()
{
	StringList service_list;
	for (ServiceMap::iterator it = m_serviceMap.begin(); it != m_serviceMap.end(); ++it)
		service_list.push_back(it->first);

	return service_list;
}

void Session::Init()
{
	void* out_bus = NULL;
	void* in_bus = YSUserBusNew(0);
	if (NULL == in_bus)
		throw string("YSUserBusNew() failed while InitServiceList()");
	string strService = m_appConfigPtr->ReadOne(CfgServiceList("GetServiceListAppName"));
	add_in_bus(in_bus);
	YSUserBusAddString(in_bus, YSDICT_SERVNAME, strService.c_str(), strService.length());

	m_func(in_bus, &out_bus);

	void* appBin = YSUserBusGet(out_bus, m_appConfigPtr->ReadOne(CfgServiceList("Output")).c_str());
	if (!appBin)
		throw string("YSUserBusGet() failed while retrieve appVarBin");
	void* appHash= YSMPHashFromVarBin(appBin, 0);
	if (!appHash)
		throw string("HashFromVarBin() failed while retrieve appHash");

	int hash_base = YSVarHashGetBase(appHash);
	for (int i = 0; i < hash_base; ++i) {
		void* hash_link = YSVarHashGetLinkByIdx(appHash, i);
		int link_len = YSVarLinkGetLen(hash_link);
		for (int j = 0; j < link_len; ++j) {
			void* link_obj = YSVarLinkGet(hash_link, j);
			string str = m_appConfigPtr->ReadOne(CfgServiceList("ServiceInfo/name"));
			void* var_name = YSVarStructGetByKey(link_obj, str.c_str(), str.length());
			str = m_appConfigPtr->ReadOne(CfgServiceList("ServiceInfo/input"));
			void* var_input_array = YSVarStructGetByKey(link_obj, str.c_str(), str.length());
			str = m_appConfigPtr->ReadOne(CfgServiceList("ServiceInfo/output"));
			void* var_output_array = YSVarStructGetByKey(link_obj, str.c_str(), str.length());

			StringArray inputArr;
			StringArray outputArr;

			string name = (char*)YSVarStringGet(var_name);
			YsArrayToStringArray(var_input_array, inputArr);
			YsArrayToStringArray(var_output_array, outputArr);

			m_serviceMap.insert(std::make_pair(name, ServiceInfo(name, inputArr, outputArr)));
		}
	}
}

void Session::YsArrayToStringArray( void* var_arr, StringArray& str_arr )
{
	int arr_len = YSVarArrayGetLen(var_arr);
	for (int i = 0; i < arr_len; ++i) {
		
		str_arr.push_back((char*)YSVarStringGet(
			YSVarArrayGet(var_arr, i)));
	}
}

StringArray Session::get_input_args( string service_name )
{
	StringList input_args;
	ServiceMap::iterator it = m_serviceMap.find(service_name);
	if (it == m_serviceMap.end())
		throw string("Service not found while get_input_args()! Service name: ") +
			service_name;

	return it->second.input;
}

StringArray Session::get_output_args( string service_name )
{
	StringList output_args;
	ServiceMap::iterator it = m_serviceMap.find(service_name);
	if (it == m_serviceMap.end())
		throw string("Service not found while get_output_args()! Service name: ") +
			service_name;

	return it->second.output;
}
