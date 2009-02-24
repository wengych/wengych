#include "connection.h"
#include "AdminCommand.h"
#include <boost/bind.hpp>

connection::connection( boost::asio::io_service& io_service, RoomEntitiesType& roomEntities )
	:	_socket(io_service),
		_roomEntities(roomEntities),
		_strand(io_service)
{
}

boost::asio::ip::tcp::socket& connection::socket()
{
	return _socket;
}

void connection::start()
{
	_socket.async_read_some(boost::asio::buffer(_buffer),
		boost::bind(&connection::handle_first_read, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}

void connection::handle_first_read(const boost::system::error_code& e, std::size_t bytes_transferred)
{
	if (!e) {
		if (bytes_transferred > 0) {
			std::string msg(_buffer.data() + 2);
			assert(_buffer.at(0) == '0');
			switch(_buffer.at(1))
			{
			case '0': // Admin connection
				{
					AdminCommand ac(msg);
					handle_admin_command(ac);
					break;
				}
			case '1': // Room chat connection
				break;
			case '2': // Voice
				break;
			case '3': // Video
				break;
			}
		}
	}
}

void connection::handle_read(const boost::system::error_code& e, std::size_t bytes_transferred)
{
	if (!e)
	{
	}

}

void connection::handle_write(const boost::system::error_code& e)
{

}

void connection::handle_admin_command( AdminCommand& ac )
{
	RoomEntitiesIterator itRoom = _roomEntities.find(ac.room_id);
	if (itRoom == _roomEntities.end()) // no room has been found.
		return ;

	switch (ac.cmd.at(1))
	{
	case '0': // Kick
		
		break;
	case '1': // Ban
		break;
	}
}