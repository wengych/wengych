#include <boost/lexical_cast.hpp>
#include <ostream>

#include "App.h"

std::string response_queue_name = "response_queue_";
std::string request_queue_name = "request_queue_";

extern std::ostream& logger;

App::App(char* channel_id) :
request_queue(boost::interprocess::open_only, (request_queue_name + channel_id).c_str()),
response_queue(boost::interprocess::open_only, (response_queue_name + channel_id).c_str())
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
		return true;
	}
	return false;
}

void App::OffHook()
{
	SendRequest(Request("OFF_HOOK"));

	Response resp = RecvResponse();
	if (resp.state == "USER_HANG_UP")
		HangUp();
	else if (resp.state != "OFF_HOOK")
		throw std::string ("OffHook failed.");
}

void App::HangUp()
{
	SendRequest(Request("USER_HANG_UP"));

	Response resp = RecvResponse();
	if (resp.state == "USER_HANG_UP")
		return ;
	else
		throw std::string ("Hang Up.");
}

std::string App::PlayFile( const std::string& file_names, bool block )
{
	Request req("PLAY_FILE");
	req.argument_map["file_list"] = file_names;
	req.argument_map["is_start"] = "false";
	req.argument_map["block"] = boost::lexical_cast<std::string>(block);
	SendRequest(req);

	Response resp = RecvResponse();
	if (resp.state == "USER_HANG_UP")
		return resp.state;
	Response::ArgMap::iterator it = resp.argument_map.find("dtmf_hit");
	if (it != resp.argument_map.end() &&
		it->second ==  "true") {
		StopPlay();
		return resp.argument_map["user_input"];
	}
	else if (resp.argument_map["is_end"] == "true")
		return "";
	else
		throw std::string ("PlayFile Exception.");
}

void App::StopPlay()
{
	SendRequest(Request("STOP_PLAY"));
	Response resp = RecvResponse();

	return ;
}

std::string App::WaitUserInput( int input_type )
{
	switch(input_type)
	{
	case _InputTypeNone:
		return "";
	case _InputTypeMenu:
		{
			SendRequest(Request("WAIT_DTMF"));
			Response resp = RecvResponse();
			if (resp.state == "USER_HANG_UP")
				return resp.state;
			Request::ArgMap::iterator it = resp.argument_map.find("user_input");
			if (it == resp.argument_map.end())
				throw std::string("WaitUserInput: no user_input.");
			return it->second;
		}
	case _InputTypeString:
		{
			Request::ArgMap::iterator it;
			std::string ret;
			for (;;) {
				SendRequest(Request("WAIT_DTMF"));
				Response resp = RecvResponse();
				if (resp.state == "USER_HANG_UP")
					return resp.state;
				it = resp.argument_map.find("user_input");
				if (it == resp.argument_map.end())
					throw std::string("WaitUserInput: no user_input.");
				if (it->second == "#")
					break;

				if (it->second == "*")
					ret += '.';
				else
					ret += it->second;
			}

			return ret;
		}
	case _InputTypeString + _InputTypeMenu :
		{
			Request::ArgMap::iterator it;
			std::string ret;

			SendRequest(Request("WAIT_DTMF"));
			Response resp = RecvResponse();
			if (resp.state == "USER_HANG_UP")
				return resp.state;
			it = resp.argument_map.find("user_input");
			if (it == resp.argument_map.end())
				throw std::string("WaitUserInput: no user_input.");
			if (it->second == "*")
				return "*";
			else 
				ret += it->second;

			for (;;) {
				SendRequest(Request("WAIT_DTMF"));
				Response resp = RecvResponse();
				if (resp.state == "USER_HANG_UP")
					return resp.state;
				it = resp.argument_map.find("user_input");
				if (it == resp.argument_map.end())
					throw std::string("WaitUserInput: no user_input.");
				if (it->second == "#")
					break;

				if (it->second == "*")
					ret += '.';
				else
					ret += it->second;
			}

			return ret;
		}
		default :
			throw std::string ("no such input type");
	}
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
	if (cmd == "END")
		HangUp();
	else if (cmd == "PICKUP") {
		OffHook();
		return false;
	}
	else if (cmd == "PROC")
		return false;

	return true;
}