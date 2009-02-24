
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
	// ���캯��������Ϊ��������ַ�������˿ںţ��̳߳ش�С
	explicit server(const std::string& address, const std::string& port, const std::size_t thread_pool_size);
	// ��������
	void run();
	// ֹͣ����
	void stop();


private:
	// �ص���������Ӧ�µĿͻ��˽���
	void handle_accept(const boost::system::error_code& e);

	std::size_t _thread_pool_size;
	boost::asio::io_service _io_service;
	boost::asio::ip::tcp::acceptor _acceptor;

	connection_ptr _new_connection;
	RoomEntitiesType _roomEntities;

	// request_handler _request_handler;
};