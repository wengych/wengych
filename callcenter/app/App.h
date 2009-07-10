#ifndef __APP_H__
#define __APP_H__

#include "../gateway/Request.h"
#include "../gateway/Response.h"
#include <boost/interprocess/ipc/message_queue.hpp>
#include <ostream>
#include <Windows.h>

#define BUFFER_SIZE 1024

enum UserInputType {
	_InputTypeNone = 0,
	_InputTypeMenu,
	_InputTypeString
};

class App {
public:
	App(char* channel_id);
	void SendRequest(Request&);
	Response RecvResponse();
	bool InitChannel();


	bool RingIn();
	void OffHook();
	std::string PlayFile(const std::string& file_name, bool block);
	void StopPlay();
	std::string WaitUserInput(int input_type);
	std::string GetHostId();
	std::string GetCallerId();
	void Reset();
	void HangUp();

	bool CheckCmd(const std::string&);

private:
	boost::interprocess::message_queue request_queue;
	boost::interprocess::message_queue response_queue;
	bool monitor;
	HWND hwnd;
	char buffer[BUFFER_SIZE];
};

extern std::ostream& logger;

#endif
