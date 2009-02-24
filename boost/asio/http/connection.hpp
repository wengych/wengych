
#ifndef _asio_http_connection_
#define _asio_http_connection_

#include <ifstream>
#include <string>
#include <boost/asio.hpp>

class http_connection
{
public:
	void start()
    {
        boost::asio::async_read_until(socket_, data_, "\r\n",
			boost::bind(&http_connection::handle_request_line, this, _1));
    }

	void handle_request_line(boost::asio::error_code ec)
	{
		if (!ec)
		{
			std::string method, uri, version;
			char sp1, sp2, cr, lf;
			std::istream is(&data_);
		}
	}

private:
	boost::asio::ip::tcp::socket socket_;
	boost::asio::streambuf data_;
};

#endif // _asio_http_connection_
