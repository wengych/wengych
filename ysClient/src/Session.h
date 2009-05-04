#ifndef YS_SESSION_H_
#define YS_SESSION_H_

#include "common.h"

class AppConfig;

class Session
{
public:
	struct ServiceInfo {
		ServiceInfo(const string& _name, const StringArray& _input, const StringArray& _output,
                const string& ver, const string& app, const string& fun, const string& lib, const string& dic_ver)
			: name(_name), input(_input), output(_output),
            version(ver), application_name(app), function_name(fun), library_name(lib), dictory_ver(dic_ver)
		{}
		ServiceInfo(const ServiceInfo& rhs)
			: name(rhs.name), input(rhs.input), output(rhs.output),
			version(rhs.version), application_name(rhs.application_name), function_name(rhs.function_name),
			library_name(rhs.library_name), dictory_ver(rhs.dictory_ver)
		{}
		string name;
		StringArray input;
		StringArray output;

		string version;
		string application_name;
		string function_name;
		string library_name;
		string dictory_ver;
	};
	typedef std::map<string, ServiceInfo> ServiceMap;
	typedef boost::shared_ptr<AppConfig> AppConfigPtr;

public:
    Session(const AppConfigPtr& , const SessionSockCallBackType&);
    ~Session();

    void add_in_bus(void*);
	void add_out_bus(void*);
	StringList get_service_list();
    ServiceInfo& get_service_info(const string&);
	StringArray get_input_args(const string& service_name);
	StringArray get_output_args(const string& service_name);
	bool valid_input_args(string arg_name, string arg_value);
	void YsArrayToStringArray( void* var_arr, StringArray& str_arr);

protected:
	void Init();
	string GetStringFromStruct(void*, const string&);

    BusVector vec_in_bus;
	BusVector vec_out_bus;
    void* main_bus;
	AppConfigPtr m_appConfigPtr;
	SessionSockCallBackType m_func;
	ServiceMap m_serviceMap;
};

#endif // YS_SESSION_H_
