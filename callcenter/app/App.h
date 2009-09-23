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
    void Interphone();
	bool PlayFile(const std::string& file_name, const std::string& menu_msg, bool block);
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

    void GetFileNames( std::stringstream& file_names, std::string &menu ) 
    {
        // StringArray::iterator it = menu.begin();
        // file_names << "cn\\" << *it;
        typedef boost::tokenizer< boost::char_separator<char> > tokenizer;
        boost::char_separator<char> sep(",");
        tokenizer token = tokenizer(menu, sep);
        tokenizer::iterator it_token = token.begin();
        file_names << "cn\\" << *it_token;
        while (++it_token != token.end())
        {
            file_names << ',' << "cn\\" << *it_token;
        }
    }
    bool DoCmd(std::string& str, std::string& menu_msg, bool flag)
    {
        const std::string file_begin = "FILE:";
        const std::string cmd_begin = "CMD:";
        if (0 == str.compare(0, file_begin.length(), file_begin))
        {
            std::stringstream file_names;         
            GetFileNames(file_names, str.substr(file_begin.length()));
            return PlayFile(file_names.str(), menu_msg, flag);
        }
        else if (0 == str.compare(0, cmd_begin.length(), cmd_begin))
        {
            if (str.substr(cmd_begin.length()) == "INTERPHONE")
                Interphone();

            return true;
        }
    }

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
