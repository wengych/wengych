#pragma once

#include <string>
#include <map>

class UserEntity;

struct RoomDataSet {
	std::string _id;
	std::string _serverID;
	std::string _name;
	int _maxBitrate;
	int _maxUsers;
	int _whiteboard;
	int _screencasting;
	int _webcam;
	int _peakConns;
	std::string _messageListBackground;
	std::string _welcomeMessage;
	RoomDataSet(const std::string& id)
		: _id(id),
		_maxBitrate(0),
		_maxUsers(0),
		_whiteboard(0),
		_screencasting(0),
		_webcam(0),
		_peakConns(0)
	{}
};

class RoomEntity
{
public:
	RoomEntity(void);
	~RoomEntity(void);

private:
	RoomDataSet _roomInfo;
	int _userSNSeed;
	std::string _roomSN;
	stdext::hash_map<std::string, UserEntity> _userList;
};

typedef std::map<std::string, RoomEntity> RoomEntitiesType;
typedef RoomEntitiesType::iterator RoomEntitiesIterator;
