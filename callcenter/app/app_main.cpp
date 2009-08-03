#include <iostream>
#include <string>
#include <ysdef.h>
#include <signal.h>
#include <boost/lexical_cast.hpp>
#include <boost/interprocess/exceptions.hpp>

#ifdef __OS_WIN__
#pragma comment(lib,"wsock32.lib")
#include <windows.h>
#endif

#include "App.h"
#include "Session.h"
#include "Dict.h"


std::ostream& logger = std::cout;

void ServiceCallSock( void* p_in_bus, void** pp_out_bus)
{
	char* ip = "192.168.0.77";
	short port = 6100;
	int time_out = 10;

	if (FALSE == YSServiceClientCallSock(ip, port, time_out, p_in_bus, pp_out_bus)) {
#ifdef __OS_WIN__
		int err = GetLastError();
		throw std::string(boost::lexical_cast<std::string>(err));
#elif
		throw string("ServiceClientCall failed!");
#endif // __OS_WIN__
	}
}

bool init_socket()
{
	WSADATA wsaData;
	WORD wVersionRequested;
	int err;

	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
		return false;

	return true;
}

void MyMethod( App &app, char** argv ) 
{
    while (app.RingIn())
    {
        try {
            std::string host_id = app.GetHostId();
            std::string caller_id = app.GetCallerId();

            Session sess(ServiceCallSock);
            std::string last_command = "RING";
            std::string user_input = "";
            do {
                logger << "Command: " << last_command << '\n';
                sess.DoCommand(last_command, argv[1], caller_id, host_id, user_input);
                last_command = sess.GetLastCommand();
                if (!app.CheckCmd(last_command))
                {
                    // need input args.
                    StringArray menu = sess.GetMenu();
                    int flag = sess.GetFlag();

                    logger << "menu: ";
                    for (StringArray::iterator it = menu.begin(); it != menu.end(); ++it)
                        logger << *it << std::endl;
                    if (menu.empty())
                        continue;

                    std::stringstream file_names;
                    StringArray::iterator it = menu.begin();
                    // file_names << "cn\\" << *it;
                    typedef boost::tokenizer< boost::char_separator<char> > tokenizer;
                    boost::char_separator<char> sep(",");
                    tokenizer token = tokenizer(*it, sep);
                    tokenizer::iterator it_token = token.begin();
                    file_names << "cn\\" << *it_token;
                    while (++it_token != token.end())
                    {
                        file_names << ',' << "cn\\" << *it_token;
                    }
                    ++it;
                    while (it != menu.end()) {
                        // .pcm files will put in directory [cn] currently.
                        // Replace with specific parameter that receive from service call later.
//                         typedef boost::tokenizer< boost::char_separator<char> > tokenizer;
//                         boost::char_separator<char> sep(",");
//                         tokenizer token(*it, sep);
                        token = tokenizer(*it, sep);
                        for (it_token = token.begin();
                            it_token != token.end(); ++it_token)
                        {
                            file_names << ',' << "cn\\" << *it_token;
                        }
                        ++it;
                    }

                    logger << "file names: " << file_names.str() << std::endl;
                    std::string menu_msg = sess.GetMenuMsg();

                    app.PlayFile(file_names.str(), menu_msg, (bool)flag);
                    if (!app.IsRingIn())
                        break;
                    InputRangeSet input_range_set = sess.GetInputRange();

                    app.SetTimeOut(sess.GetTimeOut(), sess.GetTimeOut2());
                    user_input = app.WaitUserInput(input_range_set, sess.GetEncode());
                    app.SetTimeOut();
                    if (!app.IsRingIn())
                        break;

                    if (user_input == "TIME_OUT")
                    {
                        user_input = "";
                        last_command = "END";
                    }
                }

            } while (last_command != "END");

            if (!app.IsRingIn() || last_command == "END")
            {
                last_command = "END";
                user_input = "";
                sess.DoCommand(last_command, argv[1], caller_id, host_id, user_input);
                last_command = sess.GetLastCommand();

                app.HangUp();
            }

        } catch (const std::string& err) {
            std::cout << err << std::endl;
            app.Reset();
        }
    }
}

int main(int argc, char** argv)
{
	if (argc <= 1)
		return -1;
    try {
	    App app(argv[1]/*channel_id*/);
        app.UpdateActiveFile();

	    init_socket();

	    app.InitChannel();
        MyMethod(app, argv);

    } catch (boost::interprocess::interprocess_exception& err) {
        logger << err.what() << std::endl;
        exit(-1);
    }

	return 0;
}
