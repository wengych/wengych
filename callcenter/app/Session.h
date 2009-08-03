#ifndef __SESSION_H__
#define __SESSION_H__

#include <boost/function.hpp>
#include <string>
#include <list>
#include <vector>
#include <set>

#define YSPAY_TBS_COMMAND "__YSPAY_TBS_COMMAND__"
#define YSPAY_TBS_MENU "__YSPAY_TBS_MENU__"
#define YSPAY_TBS_INPUT_RANGE "__YSPAY_TBS_INPUT_RANGE__"
#define YSPAY_TBS_MENUMSG "__YSPAY_TBS_MENUMSG__"

typedef boost::function<void(void* /*bus_in*/, void** /*bus_out*/)> SessionSockCallBackType;
typedef std::list<void*> BusArray;
typedef std::vector<std::string> StringArray;
typedef std::set<int> InputRangeSet;

class Session {
public:
	Session(const SessionSockCallBackType&);
	void DoCommand(std::string cmd, std::string channel_id, std::string caller_id, std::string host_id, std::string user_input);
	const std::string GetLastCommand();
	StringArray GetMenu();
    char* GetMenuMsg();
	int GetFlag();
    int GetTimeOut();
    int GetTimeOut2();
    int GetEncode();
	InputRangeSet GetInputRange();

private:
	SessionSockCallBackType m_func;
	BusArray in_bus_arr;
	BusArray out_bus_arr;
    InputRangeSet input_range_set;
};

#endif
