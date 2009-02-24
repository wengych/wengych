#include "server.h"
#include <boost/bind.hpp>
#include <boost/thread.hpp>

server::server( const std::string& address, const std::string& port, const std::size_t thread_pool_size )
:	_io_service(),
	_acceptor(_io_service),
	_new_connection(new connection(_io_service, _roomEntities)),
	_thread_pool_size(thread_pool_size)
	//_request_handler()
{
	boost::asio::ip::tcp::resolver resolver(_io_service);
	boost::asio::ip::tcp::resolver::query query(address, port);
	boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);

	_acceptor.open(endpoint.protocol());
	_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	_acceptor.bind(endpoint);
	_acceptor.listen();
	_acceptor.async_accept(_new_connection->socket(),
		boost::bind(&server::handle_accept, this,
		boost::asio::placeholders::error));
}

void server::run()
{
	std::vector<boost::shared_ptr<boost::thread> > threads;
	for (std::size_t i = 0; i < _thread_pool_size; ++i)
	{
		boost::shared_ptr<boost::thread> thread(new boost::thread(
			boost::bind(&boost::asio::io_service::run, &_io_service)));
		threads.push_back(thread);
	}

	for (std::size_t i = 0; i < threads.size(); ++i)
		threads[i]->join();
}

void server::stop()
{
	_io_service.stop();
}

void server::handle_accept(const boost::system::error_code& e)
{
	if (!e)
	{
		_new_connection->start();
		_new_connection.reset(new connection(_io_service, _roomEntities));

		_acceptor.async_accept(_new_connection->socket(),
			boost::bind(&server::handle_accept, this,
			boost::asio::placeholders::error));
	}
}