
#pragma once

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "RoomEntity.h"

class AdminCommand;

class connection
	:	public boost::enable_shared_from_this<connection>,
		private boost::noncopyable
{
public:
	explicit connection(boost::asio::io_service& io_service, RoomEntitiesType& roomEntities);

	boost::asio::ip::tcp::socket& socket();

	void start();
private:
	void handle_read(const boost::system::error_code& e,
		std::size_t bytes_transferred);
	void handle_first_read(const boost::system::error_code& e,
		std::size_t bytes_transferred);
	void handle_write(const boost::system::error_code& e);

	void handle_admin_command(AdminCommand& ac);

	boost::asio::io_service::strand _strand;
	boost::asio::ip::tcp::socket _socket;
	boost::array<char, 8192> _buffer;
	RoomEntitiesType& _roomEntities;
};

typedef boost::shared_ptr<connection> connection_ptr;
