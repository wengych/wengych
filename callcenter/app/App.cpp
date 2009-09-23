#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <ostream>
#include <fstream>
#include <process.h>

#include "App.h"
#include "../dj_driver/InterphonePool.h"

std::string response_queue_name = "response_queue_";
std::string request_queue_name = "request_queue_";
std::string monitor_shared_memory_name = "monitor_shared_memory";
std::string monitor_lock_shared_memory_name = "monitor_lock_shared_memory";
std::string exe_file_name = "瑞通ivr系统";

const int windows_message_type = 0x0400+1001;

extern std::ostream& logger;

App::App(char* channel_id) :
request_queue(boost::interprocess::open_only, (request_queue_name + channel_id).c_str()),
response_queue(boost::interprocess::open_only, (response_queue_name + channel_id).c_str()),
ring_in(false),
time_out(0)
{
	logger << "request queue: " << request_queue_name << channel_id << std::endl;
	logger << "response queue: " << response_queue_name << channel_id << std::endl;

    this->channel_id = channel_id;
}

void App::WriteSharedMemory(std::string str)
{
    using namespace boost::interprocess;
    try {

        named_mutex mutex(open_only, monitor_lock_shared_memory_name.c_str());

        HWND hwnd = FindWindow(NULL, exe_file_name.c_str());
        if (!hwnd)
            return ;

        std::stringstream ss;
        ss  << "app:"
            << channel_id
            << ":"
            << (caller_id.empty() ? "NULL" : caller_id)
            << ":"
            << str
            << "\n";
        {
            scoped_lock<named_mutex> lock (mutex);
            shared_memory_object shared_memory(open_only, monitor_shared_memory_name.c_str(), read_write);
            mapped_region region(shared_memory, read_write);
            char *mem = static_cast<char*>(region.get_address());

            strcat(mem, ss.str().c_str());
        }
        PostMessage(hwnd, windows_message_type, NULL, NULL);
    } catch (interprocess_exception& err) {
        logger << "open shared_memory_object or named_mutex failed:" << err.what() << std::endl;
        return ;
    }

    return ;
}

bool App::InitChannel()
{
    WriteSharedMemory("Init.");
	Request req("INIT");
	logger << req.str() << '\n';
	SendRequest(Request("INIT"));
	Response resp = RecvResponse();

	logger << "init channel" << std::endl;
	return true;
}

bool App::RingIn()
{
    WriteSharedMemory("等待用户呼入.");
    caller_id = "";
	logger << "wait ring in.\n";
	SendRequest(Request("WAIT_RING"));
	Response resp = RecvResponse();
	if (resp.state == "WAIT_RING" &&
		resp.argument_map["ring_in"] == "true")
	{
		logger << "ring in" << std::endl;
        ring_in = true;
		return true;
	}
	return false;
}

void App::OffHook()
{
    WriteSharedMemory("摘机");
	SendRequest(Request("OFF_HOOK"));

	Response resp = RecvResponse();
    if (resp.state == "USER_HANG_UP") {
        ring_in = false;
		HangUp();
    }
	else if (resp.state != "OFF_HOOK")
		throw std::string ("OffHook failed.");
}

void App::Interphone()
{
    WriteSharedMemory("转内线");


    InterphonePool pool;
    int interphone_id = pool.GetRandomAvailableChannel();
 
    Request req("INTERPHONE");
    req.argument_map["interphone_id"] = boost::lexical_cast<std::string>(interphone_id);

    SendRequest(req);

    Response resp = RecvResponse();

    if (resp.state == "USER_HANG_UP")
    {
        ring_in = false;

        pool.ModifyChannel(interphone_id, true);
        return ;
    }
    else if (resp.argument_map["hang_up"] == "inter_phone")
    {
        ring_in = false;

        pool.ModifyChannel(interphone_id, true);
        return ;
    }
}

void App::HangUp()
{
    WriteSharedMemory("挂机");
	SendRequest(Request("USER_HANG_UP"));

	Response resp = RecvResponse();
    if (resp.state == "USER_HANG_UP") {
        ring_in = false;
		return ;
    }
	else
    {
		throw std::string ("Hang Up.");
    }
}

// return true if play end
// return false if play is interrupt
bool App::PlayFile( const std::string& file_names, const std::string& menu_msg, bool block )
{
    if (!ring_in)
        return false;

    WriteSharedMemory(menu_msg.c_str());
	Request req("PLAY_FILE");
	req.argument_map["file_list"] = file_names;
	req.argument_map["is_start"] = "false";
	req.argument_map["block"] = block ? "true" : "false";
	SendRequest(req);

	Response resp = RecvResponse();
    if (resp.state == "USER_HANG_UP") {
		ring_in = false;
        return false;
    }

	Response::ArgMap::iterator it = resp.argument_map.find("dtmf_hit");
	if (it != resp.argument_map.end() &&
		it->second ==  "true") {
		StopPlay();
			return false;
	}

    return true;
}

void App::StopPlay()
{
    WriteSharedMemory("停止播放语音文件.");
	SendRequest(Request("STOP_PLAY"));
	Response resp = RecvResponse();

	return ;
}

std::string App::WaitUserInput( std::set<int> input_type, int en )
{
    first_user_input_time = boost::posix_time::second_clock::universal_time() +
        boost::posix_time::seconds(time_out2);
    // boost::posix_time::time_duration dur = boost::posix_time::seconds(time_out2);
    // first_user_input_time += dur;
    std::string menu_string = "*";
	if (!ring_in)
		return "";
    std::string wait_user_input = "等待用户输入";
    encode = en;

    WriteSharedMemory(wait_user_input);
    if (input_type.size() == 0)
        return "";
    else if (input_type.size() == 1)
    {
        int _type = *input_type.begin();
        switch(_type)
        {
        case _InputTypeNone:
            return WaitNone();
        case _InputTypeString:
            return WaitString();
        case _InputTypeMenu:
            return WaitMenu();
        default:
            if (_type > 1)
                return WaitStringWithLen(_type);
        }
    }
    else if (input_type.size() == 2)
    {
        if (input_type.find(_InputTypeNone) != input_type.end())
		{
            return WaitNone();
		}
        if (input_type.find(_InputTypeMenu) != input_type.end() &&
            input_type.find(_InputTypeString) != input_type.end())
		{
            return WaitMenuString(menu_string);
		}
        else if (input_type.find(_InputTypeMenu) != input_type.end())
		{
            std::set<int>::iterator it = input_type.begin();
            while (it != input_type.end() && *it <= 1)
                ++it;
            return WaitMenuStringWithLen(menu_string, *it);
        }
        else if (input_type.find(_InputTypeString) != input_type.end())
		{
            std::set<int>::iterator it = input_type.begin();
            while (it != input_type.end() && *it <= 1)
                ++it;
            return WaitStringStringWithLen(*it);
        }
		else
		{
			int len = *(input_type.begin());
			std::set<int>::iterator it = input_type.begin();
			++it;
			while (it != input_type.end())
			{
				if (len > *it)
					len = *it;
				++it;
			}

			return WaitStringWithLen(len);
		}
    }
    else if (input_type.size() == 3)
    {
        if (input_type.find(_InputTypeNone) != input_type.end())
            return WaitNone();

        std::set<int>::iterator it = input_type.begin();
        while (it != input_type.end() && *it <= 1)
            ++it;
        return WaitMenuStringStringWithLen(menu_string, *it);
    }

    return "";
}

std::string App::GetHostId()
{
	return "0000";
}

std::string App::GetCallerId()
{
	SendRequest(Request("GET_CALLER_ID"));

	Response resp = RecvResponse();
	if (resp.state == "USER_HANG_UP")
		return resp.state;
	if (resp.state != "GET_CALLER_ID")
		throw std::string ("GetCallerId.");

	logger << "caller_id: " << resp.argument_map["caller_id"] << '\n';

    caller_id = resp.argument_map["caller_id"];
    if (caller_id.empty())
        caller_id = "0000";
	return caller_id;
}

void App::Reset()
{
	caller_id = "";
}

void App::SendRequest( Request& req = Request(""))
{
    if (time_out == 0)
    {
        request_queue.send(req.str().c_str(), req.str().length(), 0);
        return ;
    }

    boost::posix_time::time_duration duration(0, 0, time_out);
    request_queue.timed_send(req.str().c_str(), req.str().length(), 0, 
        boost::posix_time::ptime(boost::gregorian::date(), duration));
}

Response App::RecvResponse()
{
    using namespace boost::posix_time;
	std::size_t recvd_size;
	unsigned int priority;
    ptime recv_time_out(second_clock::universal_time());
    ptime user_input_time_out(second_clock::universal_time());
    time_duration five_sec(seconds(5));

    recv_time_out += five_sec;
    user_input_time_out += time_duration(seconds(time_out));

    // 每秒更新一次心跳文件
    // 判断是否超时
    while (!response_queue.timed_receive(buffer, BUFFER_SIZE, recvd_size, priority, recv_time_out))
    {
        UpdateActiveFile();
        recv_time_out += five_sec;

        // member var time_out will be set more than 0 by WaitUserInput
        // when the WaitUserInput method finished, time_out will set back to 0
        if (time_out > 0 &&
            recv_time_out > user_input_time_out)
            // return Response();
            return Response("TIME_OUT");
        else if (time_out2 > 0 &&
            recv_time_out > first_user_input_time)
            return Response("TIME_OUT");
    }

	Response resp(buffer, recvd_size);

	if (resp.state == "EXIT")
    {
        logger << "Receive EXIT from monitor.\n";
        logger << "will shut up this channel[" << channel_id << "].\n";
        SendRequest();

        exit(0);
	}

	logger << "app:resp:" << resp.state << std::endl;
	return resp;
}

bool App::CheckCmd(const std::string& cmd)
{
	if (cmd == "END") 
    {
		return false;
	}
	else if (cmd == "PICKUP")
    {
		this->OffHook();
		return false;
	}
    else if (cmd == "PROC")
    {
		return false;
    }

	return true;
}

bool App::IsRingIn()
{
    return ring_in;
}

std::string App::GetUserInput(std::string& user_input)
{
    std::string pre_string = "用户输入：";
    if (encode == 0)
        return pre_string + user_input;

    for (size_t i = 0; i < user_input.length(); ++i)
        pre_string += '*';

    return pre_string;
}

std::string App::WaitNone()
{
    return "";
}

std::string App::WaitMenu()
{
    std::string ret ;
    SendRequest(Request("WAIT_DTMF"));
    Response resp = RecvResponse();
    if (resp.state == "USER_HANG_UP") {
        ring_in = false;
        return "";
    }
    if (resp.state == "TIME_OUT") {
        return "TIME_OUT";
    }


    Request::ArgMap::iterator it = resp.argument_map.find("user_input");
    if (it == resp.argument_map.end())
        throw std::string ("WaitUserInput: no user_input.");
    ret = it->second;

    WriteSharedMemory(GetUserInput(ret)/*user_input + ret*/);
    return ret;
}

std::string App::WaitString()
{
    std::string ret;
    for (;;)
    {
        SendRequest(Request("WAIT_DTMF"));
        Response resp = RecvResponse();
        if (resp.state == "USER_HANG_UP") {
            ring_in = false;
            return "";
        }
        if (resp.state == "TIME_OUT") {
            return "TIME_OUT";
        }

        Request::ArgMap::iterator it = resp.argument_map.find("user_input");
        if (it == resp.argument_map.end())
            throw std::string ("WaitUserInput: no user_input.");

        if (it->second == "#")
            break;

        if (it->second == "*")
            ret += ".";
        else
            ret += it->second;

        WriteSharedMemory(GetUserInput(ret));
    }

    return ret;
}

std::string App::WaitStringWithLen(int len)
{
    std::string ret;
    for (int i = 0; i < len; ++i)
    {

        SendRequest(Request("WAIT_DTMF"));
        Response resp = RecvResponse();
        if (resp.state == "USER_HANG_UP") {
            ring_in = false;
            return "";
        }
        if (resp.state == "TIME_OUT") {
            return "TIME_OUT";
        }

        Request::ArgMap::iterator it = resp.argument_map.find("user_input");
        if (it == resp.argument_map.end())
            throw std::string ("WaitUserInput: no user_input.");

        if (it->second == "*")
            ret += ".";
        else
            ret += it->second;

        WriteSharedMemory(GetUserInput(ret));
    }

    return ret;
}

std::string App::WaitMenuString( std::string menu_string )
{
    std::string ret = WaitMenu();
	if (ret.length() != 1)
		return ret;
    std::string::iterator it = std::find(menu_string.begin(), menu_string.end(), *ret.begin());
    if (it != menu_string.end())
        return ret;

	if ("#" != ret)
		ret += WaitString();

    WriteSharedMemory(GetUserInput(ret));
    return ret;
}

std::string App::WaitMenuStringWithLen( std::string menu_string, int len )
{
    std::string ret = WaitMenu();
    if (ret.length() != 1)
        return ret;
    std::string::iterator it = std::find(menu_string.begin(), menu_string.end(), *ret.begin());
    if (it != menu_string.end())
        return ret;

	ret += WaitStringWithLen(len);

    WriteSharedMemory(GetUserInput(ret));
    return ret;
}

std::string App::WaitStringStringWithLen( int len )
{
    std::string ret;
    for (int i = 0; i < len; ++i)
    {

        SendRequest(Request("WAIT_DTMF"));
        Response resp = RecvResponse();
        if (resp.state == "USER_HANG_UP") {
            ring_in = false;
            return "";
        }
        if (resp.state == "TIME_OUT") {
            return "TIME_OUT";
        }

        Request::ArgMap::iterator it = resp.argument_map.find("user_input");
        if (it == resp.argument_map.end())
            throw std::string ("WaitUserInput: no user_input.");

        if (it->second == "#")
            break;

        if (it->second == "*")
            ret += ".";
        else
            ret += it->second;
    }

    WriteSharedMemory(GetUserInput(ret));
    return ret;
}

std::string App::WaitMenuStringStringWithLen( std::string menu_string, int len )
{
    std::string ret = WaitMenu();
    if (ret.length() != 1)
        return ret;
    std::string::iterator it = std::find(menu_string.begin(), menu_string.end(), *ret.begin());
    if (it != menu_string.end())
        return ret;

    ret += WaitStringStringWithLen(len);

    WriteSharedMemory(GetUserInput(ret));
    return ret;
}

void App::InitActiveFileLock()
{
    std::string lock_name = std::string("_app_") + channel_id + "_lock";
    boost::interprocess::named_mutex::remove(lock_name.c_str());
}

void App::UpdateActiveFile()
{
    std::string file_name = std::string("_app_") + channel_id;
    std::string lock_name = file_name + "_lock";
    std::ofstream out_file;
    time_t tm_t;
    using namespace boost::interprocess;

    named_mutex mutex(open_or_create, lock_name.c_str());
    scoped_lock<named_mutex> sc_lock(mutex);
    out_file.open(file_name.c_str(), std::ios_base::out | std::ios_base::trunc);

    out_file << getpid() << ":";
    out_file << time(&tm_t);
}

void App::SetTimeOut(int to, int to2)
{
    time_out = to;
    time_out2 = to2;
}
