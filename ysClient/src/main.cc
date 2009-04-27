/*
 * main.cc
 *
 *  Created on: Apr 21, 2009
 *      Author: wengych
 */

#include <gtkmm.h>
#include <glibmm/ustring.h>
#include <windows.h>
#include <iostream>
#include "MainWindow.h"

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

int main(int argc, char* argv[])
{
#ifdef __OS_WIN__
    if (!init_socket()) {
        std::cout << "Win Sock init failed!" << std::endl;
        int err = GetLastError();
        std::cout << "Error num." << err << std::endl;
        return 0;
    }
#endif

    try {
	    Gtk::Main kit(argc, argv);
	    MainWindow window;
	    Gtk::Main::run(window);
    } catch (Glib::ustring& msg) {
        std::cout << msg << std::endl;
    }


    return 0;
}
