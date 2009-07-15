#ifndef __APP_H__
#define __APP_H__

#include "../dj_driver/Request.h"
#include "../dj_driver/Response.h"
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/function.hpp>
#include <ostream>
#include <Windows.h>
#include <set>
#include <map>

#define BUFFER_SIZE 1024

enum UserInputType {
    _InputTypeString = -1,
	_InputTypeNone,
	_InputTypeMenu,
    _InputTypeStringWithLen
};

class App {
public:
	App(char* channel_id);
	void SendRequest(Request&);
	Response RecvResponse();
	bool InitChannel();


	bool RingIn();
	void OffHook();
	void PlayFile(const std::string& file_name, bool block);
	void StopPlay();
    std::string WaitUserInput(std::set<int> input_type);
    std::string WaitNone();
    std::string WaitMenu();
    std::string WaitString();
    std::string WaitStringWithLen(int len);
    std::string WaitMenuString( std::string menu_string );
    std::string WaitMenuStringWithLen( std::string menu_string, int len );
    std::string WaitStringStringWithLen( int len );
    std::string WaitMenuStringStringWithLen( std::string menu_string, int len );

	std::string GetHostId();
	std::string GetCallerId();
	void Reset();
	void HangUp();
    bool IsRingIn();

	bool CheckCmd(const std::string& cmd);

private:
	boost::interprocess::message_queue request_queue;
	boost::interprocess::message_queue response_queue;
	bool monitor;
	HWND hwnd;
	char buffer[BUFFER_SIZE];
    bool ring_in;
    std::map<std::set<int>, boost::function<std::string()> > wait_user_input_function_map;
};

extern std::ostream& logger;

#endif
