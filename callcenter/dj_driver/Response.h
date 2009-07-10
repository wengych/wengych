#ifndef __RESPONSE_H__
#define __RESPONSE_H__
#include <map>
#include <string>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

struct Response {
	typedef std::map<std::string, std::string> ArgMap;
	std::string state;
	size_t recvd_size;
	ArgMap argument_map;
	std::stringstream str_stream;

	Response(const std::string& _state) : state(_state) {}
	Response(const Response& rhs) : state(rhs.state),
		recvd_size(rhs.recvd_size),
		argument_map(rhs.argument_map)
	{}
	Response(const char* buff, size_t buff_size)
	{
		std::string str(buff, buff_size);
		boost::trim(str);
		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
		typedef tokenizer::iterator token_iter;
		boost::char_separator<char> sep(": =\n");
		tokenizer token(str, sep);
		for (token_iter it = token.begin();
			it != token.end(); ++it) {
				if (*it == "Response") {
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

	Response& operator=(const Response& rhs)
	{
		this->argument_map = rhs.argument_map;
		this->recvd_size = rhs.recvd_size;
		this->state = rhs.state;
		this->str_stream.str("");

		return *this;
	}
	const std::string str()
	{
		str_stream.str("");

		str_stream << "Response:" << state << '\n';
		for (ArgMap::iterator it = argument_map.begin();
			it != argument_map.end(); ++it)
		{
			str_stream << it->first << ':' << it->second << '\n';
		}
		str_stream << '\n';

		return str_stream.str();
	}

};


#endif
