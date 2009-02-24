#pragma once

struct UserEntity
{
	std::string _sn;
	std::string _name;
	std::string _ip;
	std::string _macAddress;
	std::string _version;
	std::string _os;
	std::string _location;

	int _away;
	int _webcam;
	int _typing;
	int _role;
	int _textmute;
	int _audiomute;

	UserEntity(std::string sn, std::string name, int role, int textmute, int audiomute,
		std::string ip, std::string mac, std::string ver, std::string os, std::string location)
		: _sn(sn), _name(name), _role(role), _textmute(textmute), _audiomute(audiomute),
		_ip(ip), _macAddress(mac), _version(ver), _os(os), _location(location)
	{
		
	}
};
