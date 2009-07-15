#include "Session.h"
#include <ysdef.h>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <ostream>

static unsigned long trace_no = 0;
extern std::ostream& logger;

StringArray GetFileNameListByToken(std::string str)
{
    StringArray ret ;
    typedef boost::tokenizer< boost::char_separator<char> > tokenizer;
    typedef tokenizer::iterator token_iter;
    boost::char_separator<char> sep(",");

    tokenizer token(str, sep);
    for (token_iter it = token.begin(); it != token.end(); ++it)
        ret.push_back(*it);

    return ret;
}

Session::Session(const SessionSockCallBackType& call_back) : m_func(call_back)
{
}

void Session::DoCommand(std::string cmd, std::string channel_id, std::string caller_id, std::string host_id, std::string user_input)
{
	void* in_bus = YSUserBusNew(0);
	void* out_bus;

	in_bus_arr.push_front(in_bus);

	std::string service_name = "YSTbsProxyMain";
	YSUserBusAddString(in_bus, YSDICT_SERVNAME, service_name.c_str(), service_name.length());
	YSUserBusAddString(in_bus, "__YSPAY_CHANNEL__", "TBS", strlen("TBS"));

	std::string term_id = "bank";
	term_id = term_id + boost::lexical_cast<std::string>(channel_id);
	YSUserBusAddString(in_bus, "__YSPAY_TERMID__", term_id.c_str(), term_id.length());
	std::string str_trace_no = boost::lexical_cast<std::string>(trace_no);
	YSUserBusAddString(in_bus, "__YSPAY_TRACENO__", str_trace_no.c_str(), str_trace_no.length());
	YSUserBusAddString(in_bus, "__YSPAY_TBS_SRCPHONE__", caller_id.c_str(), caller_id.length());
	YSUserBusAddString(in_bus, "__YSPAY_TBS_DESTPHONE__", host_id.c_str(), host_id.length());
	YSUserBusAddString(in_bus, YSPAY_TBS_COMMAND, cmd.c_str(), cmd.length());
	if (!user_input.empty())
		YSUserBusAddString(in_bus, "__DICT_IN", user_input.c_str(), user_input.length());

	m_func(in_bus, &out_bus);
	logger << "Service call finish. Command is: " << cmd;
	if (!user_input.empty())
		logger << "  User input is: " << user_input;
	logger << "\n";

	out_bus_arr.push_front(out_bus);
}

const std::string Session::GetLastCommand()
{
	void* bus_obj = YSUserBusGet(*(out_bus_arr.begin()), YSPAY_TBS_COMMAND);
	if (!bus_obj)
		return "";
	return (char*)YSVarStringGet(bus_obj);
}

StringArray Session::GetMenu()
{
	void* bus_obj = YSUserBusGet(*(out_bus_arr.begin()), YSPAY_TBS_MENU);
	if (!bus_obj)
		return StringArray();

	void* arr = YSVarStructGetByKey(bus_obj, "STR", strlen("STR"));
	if (!arr)
		return StringArray();

	StringArray strArr;
	int len = YSVarArrayGetLen(arr);
	for (int i = 0; i < len; ++i)
	{
		void* varStr = YSVarArrayGet(arr, i);
		char* str = (char*)YSVarStringGet(varStr);
        if (strncmp(str, "FILE:", strlen("FILE:")))
            strArr.push_back(std::string(str+strlen("FILE:")));
        else
		    strArr.push_back(std::string(str));
	}

	return strArr;
}

int Session::GetFlag()
{
	void* bus_obj = YSUserBusGet(*(out_bus_arr.begin()), YSPAY_TBS_MENU);
	if (!bus_obj)
		return -1;

	void* flag = YSVarStructGetByKey(bus_obj, "FLAG", strlen("FLAG"));
	if (!flag)
		return -1;

	int ret = 0;
	YSVarInt32Get(flag, &ret);
	return ret;
}

InputRangeSet Session::GetInputRange()
{
    input_range_set.clear();
	void* obj = NULL;
	int idx = 0;
	while (NULL != (obj = YSUserBusArrayGet(*(out_bus_arr.begin()), YSPAY_TBS_INPUT_RANGE, idx)))
    {
		int cur = 0;
		YSVarInt32Get(obj, &cur);
		
        input_range_set.insert(cur);
	}

	return input_range_set;
}