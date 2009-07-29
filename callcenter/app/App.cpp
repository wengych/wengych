#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <ostream>
#include <fstream>
#include <process.h>

#include "App.h"

std::string response_queue_name = "response_queue_";
std::string request_queue_name = "request_queue_";
std::string shared_memory_name = "monitor_shared_memory";
std::string lock_shared_memory_name = "monitor_lock_shared_memory";
std::string exe_file_name = "瑞通ivr系统";

const int windows_message_type = 0x0400+1001;

extern std::ostream& logger;

App::App(char* channel_id) :
request_queue(boost::interprocess::open_only, (request_queue_name + channel_id).c_str()),
response_queue(boost::interprocess::open_only, (response_queue_name + channel_id).c_str()),
ring_in(false)
{
	logger << "request queue: " << request_queue_name << channel_id << std::endl;
	logger << "response queue: " << response_queue_name << channel_id << std::endl;

    this->channel_id = channel_id;
}

void App::WriteSharedMemory(std::string str)
{
    using namespace boost::interprocess;
    try {

        named_mutex mutex(open_only, lock_shared_memory_name.c_str());

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
            shared_memory_object shared_memory(open_only, shared_memory_name.c_str(), read_write);
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
		throw std::string ("Hang Up.");
}

void App::PlayFile( const std::string& file_names, const std::string& menu_msg, bool block )
{
    if (!ring_in)
        return ;

    WriteSharedMemory(menu_msg.c_str());
	Request req("PLAY_FILE");
	req.argument_map["file_list"] = file_names;
	req.argument_map["is_start"] = "false";
	req.argument_map["block"] = block ? "true" : "false";
	SendRequest(req);

	Response resp = RecvResponse();
    if (resp.state == "USER_HANG_UP") {
		ring_in = false;
        return ;
    }

	Response::ArgMap::iterator it = resp.argument_map.find("dtmf_hit");
	if (it != resp.argument_map.end() &&
		it->second ==  "true") {
		// StopPlay();
			return ;
	}
}

void App::StopPlay()
{
    WriteSharedMemory("停止播放语音文件.");
	SendRequest(Request("STOP_PLAY"));
	Response resp = RecvResponse();

	return ;
}

std::string App::WaitUserInput( std::set<int> input_type, int time_out )
{
    std::string menu_string = "*";
	if (!ring_in)
		return "";
    std::string wait_user_input = "等待用户输入";

    this->time_out = time_out;

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
	return "";
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
	return resp.argument_map["caller_id"];
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
	std::size_t recvd_size;
	unsigned int priority;
	response_queue.receive(buffer, BUFFER_SIZE, recvd_size, priority);
	Response resp(buffer, recvd_size);

    while (resp.state == "ACTIVE_CHECK") {
        logger << "Receive ACTIVE CHECK.\n";
        UpdateActiveFile();
        response_queue.receive(buffer, BUFFER_SIZE, recvd_size, priority);
        resp = Response(buffer, recvd_size);
    }

	if (resp.state == "EXIT") {
		// hwnd = boost::lexical_cast<HWND>(resp.argument_map["HANDLE"]);
        logger << "Receive EXIT from monitor.\n";
        logger << "will shut up this channel[" << channel_id << "].\n";
        SendRequest();
        // system("pause");

        exit(0);
	}

    UpdateActiveFile();
	logger << "app:resp:" << resp.state << std::endl;
	return resp;
}

bool App::CheckCmd(const std::string& cmd)
{
	if (cmd == "END") {
		return false;
	}
	else if (cmd == "PICKUP") {
		OffHook();
		return false;
	}
	else if (cmd == "PROC")
		return false;

	return true;
}

bool App::IsRingIn()
{
    return ring_in;
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

    Request::ArgMap::iterator it = resp.argument_map.find("user_input");
    if (it == resp.argument_map.end())
        throw std::string ("WaitUserInput: no user_input.");
    ret = it->second;

    std::string user_input = "用户输入：";
    WriteSharedMemory(user_input + ret);
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

        Request::ArgMap::iterator it = resp.argument_map.find("user_input");
        if (it == resp.argument_map.end())
            throw std::string ("WaitUserInput: no user_input.");

        if (it->second == "#")
            break;

        if (it->second == "*")
            ret += ".";
        else
            ret += it->second;

        std::string user_input = "用户输入：";
        WriteSharedMemory(user_input + ret);
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

        Request::ArgMap::iterator it = resp.argument_map.find("user_input");
        if (it == resp.argument_map.end())
            throw std::string ("WaitUserInput: no user_input.");

        if (it->second == "*")
            ret += ".";
        else
            ret += it->second;

        std::string user_input = "用户输入：";
        WriteSharedMemory(user_input + ret);
    }

    return ret;
}

std::string App::WaitMenuString( std::string menu_string )
{
    std::string ret = WaitMenu();
	if (ret.empty())
		return ret;
    std::string::iterator it = std::find(menu_string.begin(), menu_string.end(), *ret.begin());
    if (it != menu_string.end())
        return ret;

	if ("#" != ret)
		ret += WaitString();

    std::string user_input = "用户输入：";
    WriteSharedMemory(user_input + ret);
    return ret;
}

std::string App::WaitMenuStringWithLen( std::string menu_string, int len )
{
    std::string ret = WaitMenu();
    std::string::iterator it = std::find(menu_string.begin(), menu_string.end(), *ret.begin());
    if (it != menu_string.end())
        return ret;

	ret += WaitStringWithLen(len);

    std::string user_input = "用户输入：";
    WriteSharedMemory(user_input + ret);
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

    std::string user_input = "用户输入：";
    WriteSharedMemory(user_input + ret);
    return ret;
}

std::string App::WaitMenuStringStringWithLen( std::string menu_string, int len )
{
    std::string ret = WaitMenu();
    std::string::iterator it = std::find(menu_string.begin(), menu_string.end(), *ret.begin());
    if (it != menu_string.end())
        return ret;

    ret += WaitStringStringWithLen(len);

    std::string user_input = "用户输入：";
    WriteSharedMemory(user_input + ret);
    return ret;
}

void App::UpdateActiveFile()
{
    std::string file_name = std::string("_app_") + channel_id;
    std::ofstream out_file;
    out_file.open(file_name.c_str(), std::ios_base::out | std::ios_base::trunc);

    time_t tm_t;
    out_file << getpid() << ":";

    out_file << time(&tm_t);
}
