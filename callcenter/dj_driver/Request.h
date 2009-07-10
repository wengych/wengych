#ifndef __REQUEST_H__
#define __REQUEST_H__
#include <map>
#include <string>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

struct Request {
	typedef std::map<std::string, std::string> ArgMap;
	std::string state;
	size_t recvd_size;
	ArgMap argument_map;
	std::stringstream str_stream;

	Request(const std::string& _state) : state(_state) {}
	Request(const char* buff, size_t buff_size)
	{
		std::string str(buff, buff_size);
		boost::trim(str);
		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
		typedef tokenizer::iterator token_iter;
		boost::char_separator<char> sep(": =\n");
		tokenizer token(str, sep);
		for (token_iter it = token.begin();
			it != token.end(); ++it) {
				if (*it == "Request") {
					++it;
					state = *it;
				} else if (*it != "") {
					token_iter it_next = it;
					if (++it_next == token.end())
						break;
					argument_map[*it] = *it_next;
					it = it_next;
				}
		}
	}
	const std::string str()
	{
		str_stream.str("");

		str_stream << "Request:" << state << ' ';
		for (ArgMap::iterator it = argument_map.begin();
			it != argument_map.end(); ++it)
		{
			str_stream << it->first << ':' << it->second << ' ';
		}
		str_stream << '\n';

		return str_stream.str();
	}
};

#endif
