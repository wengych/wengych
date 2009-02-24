
#pragma once

#include <hash_map>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include "RoomEntity.h"
#include "connection.h"

class server
	:	private boost::noncopyable
{
public:
	// 构造函数，参数为服务器地址，监听端口号，线程池大小
	explicit server(const std::string& address, const std::string& port, const std::size_t thread_pool_size);
	// 启动服务
	void run();
	// 停止服务
	void stop();


private:
	// 回调函数，响应新的客户端接入
	void handle_accept(const boost::system::error_code& e);

	std::size_t _thread_pool_size;
	boost::asio::io_service _io_service;
	boost::asio::ip::tcp::acceptor _acceptor;

	connection_ptr _new_connection;
	RoomEntitiesType _roomEntities;

	// request_handler _request_handler;
};