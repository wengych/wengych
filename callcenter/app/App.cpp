#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <ostream>

#include "App.h"

std::string response_queue_name = "response_queue_";
std::string request_queue_name = "request_queue_";

extern std::ostream& logger;

App::App(char* channel_id) :
request_queue(boost::interprocess::open_only, (request_queue_name + channel_id).c_str()),
response_queue(boost::interprocess::open_only, (response_queue_name + channel_id).c_str()),
ring_in(false)
{
	logger << "request queue: " << request_queue_name << channel_id << std::endl;
	logger << "response queue: " << response_queue_name << channel_id << std::endl;

}

bool App::InitChannel()
{
	Request req("INIT");
	logger << req.str() << '\n';
	SendRequest(Request("INIT"));
	Response resp = RecvResponse();

	logger << "init channel" << std::endl;
	return true;
}

bool App::RingIn()
{
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
	SendRequest(Request("USER_HANG_UP"));

	Response resp = RecvResponse();
    if (resp.state == "USER_HANG_UP") {
        ring_in = false;
		return ;
    }
	else
		throw std::string ("Hang Up.");
}

void App::PlayFile( const std::string& file_names, bool block )
{
    if (!ring_in)
        return ;

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
	SendRequest(Request("STOP_PLAY"));
	Response resp = RecvResponse();

	return ;
}

std::string App::WaitUserInput( std::set<int> input_type )
{
    std::string menu_string = "*";
	if (!ring_in)
		return "";

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

	return resp.argument_map["caller_id"];
}

void App::Reset()
{
	;
}

void App::SendRequest( Request& req )
{
	request_queue.send(req.str().c_str(), req.str().length(), 0);
}

Response App::RecvResponse()
{
	std::size_t recvd_size;
	unsigned int priority;
	response_queue.receive(buffer, BUFFER_SIZE, recvd_size, priority);
	Response resp(buffer, recvd_size);
	while (resp.state == "SET_MONITOR") {
		// hwnd = boost::lexical_cast<HWND>(resp.argument_map["HANDLE"]);
		hwnd = ::FindWindow(NULL, resp.argument_map["window_name"].c_str());
		if (hwnd)
			monitor = true;
		else
			monitor = false;

		response_queue.receive(buffer, BUFFER_SIZE, recvd_size, priority);
		resp = Response(buffer, recvd_size);
	}
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
    SendRequest(Request("WAIT_DTMF"));
    Response resp = RecvResponse();
    if (resp.state == "USER_HANG_UP") {
        ring_in = false;
        return "";
    }

    Request::ArgMap::iterator it = resp.argument_map.find("user_input");
    if (it == resp.argument_map.end())
        throw std::string ("WaitUserInput: no user_input.");
    return it->second;
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

    return ret;
}

std::string App::WaitMenuStringWithLen( std::string menu_string, int len )
{
    std::string ret = WaitMenu();
    std::string::iterator it = std::find(menu_string.begin(), menu_string.end(), *ret.begin());
    if (it != menu_string.end())
        return ret;

	ret += WaitStringWithLen(len);

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
    return ret;
}

std::string App::WaitMenuStringStringWithLen( std::string menu_string, int len )
{
    std::string ret = WaitMenu();
    std::string::iterator it = std::find(menu_string.begin(), menu_string.end(), *ret.begin());
    if (it != menu_string.end())
        return ret;

    ret += WaitStringStringWithLen(len);

    return ret;
}
