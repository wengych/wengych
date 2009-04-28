#ifndef YS_SESSION_H_
#define YS_SESSION_H_

#include "common.h"

class AppConfig;

class Session
{
protected:
	struct ServiceInfo {
		ServiceInfo(const string& _name, const StringArray& _input, const StringArray& _output)
			: name(_name), input(_input), output(_output)
		{}
		ServiceInfo(const ServiceInfo& rhs)
			: name(rhs.name), input(rhs.input), output(rhs.output)
		{}
		string name;
		StringArray input;
		StringArray output;
	};
	typedef std::map<string, ServiceInfo> ServiceMap;
	typedef boost::shared_ptr<AppConfig> AppConfigPtr;

public:
    Session(const AppConfigPtr& , const SessionSockCallBackType&);
    ~Session();

    void add_in_bus(void*);
	void add_out_bus(void*);
	StringList get_service_list();
	StringArray get_input_args(string service_name);
	StringArray get_output_args(string service_name);
	bool valid_input_args(string arg_name, string arg_value);
	void YsArrayToStringArray( void* var_arr, StringArray& str_arr);

protected:
	void Init();

    BusVector vec_in_bus;
	BusVector vec_out_bus;
    void* main_bus;
	AppConfigPtr m_appConfigPtr;
	SessionSockCallBackType m_func;
	ServiceMap m_serviceMap;
};

#endif // YS_SESSION_H_
