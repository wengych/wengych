//
// win_main.cpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>
#include "server.h"

#if defined(_WIN32)

boost::function0<void> console_ctrl_function;

BOOL WINAPI console_ctrl_handler(DWORD ctrl_type)
{
	switch (ctrl_type)
	{
	case CTRL_C_EVENT:
	case CTRL_BREAK_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_SHUTDOWN_EVENT:
		console_ctrl_function();
		return TRUE;
	default:
		return FALSE;
	}
}

int main(int argc, char** argv)
{
	try {
		if (argc != 3) {
			std::cout << "Usage: iVVPubServer <ip> <port> <thread_poll_size>" << std::endl;
			return 1;
		}

		int thread_poll_size = boost::lexical_cast<int>(argv[3]);
		server s(argv[1], argv[2], thread_poll_size);

		console_ctrl_function = boost::bind(&server::stop, &s);
		SetConsoleCtrlHandler(console_ctrl_handler, TRUE);
	} catch (std::exception& e) {
		std::cerr << "exception: " << e.what() << std::endl;
	}

	return 0;
}


#endif // defined(_WIN32)
