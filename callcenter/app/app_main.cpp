#include <iostream>
#include <string>
#include <ysdef.h>
#include <boost/lexical_cast.hpp>

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

int main(int argc, char** argv)
{
	if (argc <= 1)
		return -1;

	App app(argv[1]/*channel_id*/);
	Dict dict;

	init_socket();

	app.InitChannel();
	while (app.RingIn()) {
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
					file_names << *it;
					++it;
					while (it != menu.end()) {
						file_names << ',' << *it;
						++it;
					}

                    app.PlayFile(file_names.str(), (bool)flag);
					if (!app.IsRingIn())
						break;
                    InputRangeSet input_range_set = sess.GetInputRange();

					user_input = app.WaitUserInput(input_range_set);
					if (!app.IsRingIn())
						break;
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

	return 0;
}
