#pragma once

#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

class AdminCommand
{
public:
	explicit AdminCommand(const std::string& msg)
	{
		int index_of_first_tab = msg.find_first_of('\t');
		int index_of_last_tab = msg.find_last_of('\t');
		int room_id_len = index_of_last_tab - index_of_first_tab - 1;
		cmd = msg.substr(0, 2);
		room_id = msg.substr(index_of_first_tab + 1, room_id_len);
		login_name = msg.substr(index_of_last_tab + 1);
	}

	std::string cmd;
	std::string room_id;
	std::string login_name;
};

