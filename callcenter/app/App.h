#ifndef __APP_H__
#define __APP_H__

#include "../dj_driver/Request.h"
#include "../dj_driver/Response.h"
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
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
	void PlayFile(const std::string& file_name, const std::string& menu_msg, bool block);
	void StopPlay();
    void SetTimeOut(int to = 0, int to2 = 0);
    std::string WaitUserInput(std::set<int> input_type, int encode);
    std::string WaitNone();
    std::string WaitMenu();
    std::string WaitString();
    std::string WaitStringWithLen(int len);
    std::string WaitMenuString( std::string menu_string );
    std::string WaitMenuStringWithLen( std::string menu_string, int len );
    std::string WaitStringStringWithLen( int len );
    std::string WaitMenuStringStringWithLen( std::string menu_string, int len );

    void WriteSharedMemory(std::string);

	std::string GetHostId();
	std::string GetCallerId();
	void Reset();
	void HangUp();
    bool IsRingIn();

    bool CheckCmd(const std::string& cmd);
    void InitActiveFileLock();
    void UpdateActiveFile();
    std::string GetUserInput(std::string& user_input);

private:
	boost::interprocess::message_queue request_queue;
	boost::interprocess::message_queue response_queue;
	char buffer[BUFFER_SIZE];
    bool ring_in;
    std::map<std::set<int>, boost::function<std::string()> > wait_user_input_function_map;

    std::string channel_id;
    std::string caller_id;

    int time_out;
    int time_out2;
    int encode;
    boost::posix_time::ptime first_user_input_time;

};

extern std::ostream& logger;

#endif
