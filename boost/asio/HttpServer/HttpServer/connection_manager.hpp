#ifndef HTTP_CONNECTION_MANAGER_HPP
#define HTTP_CONNECTION_MANAGER_HPP

#include <set>
#include <boost/noncopyable.hpp>
#include "connection.hpp"

namespace http {
	namespace server {

		class connection_manager
			:	private boost::noncopyable
		{
		public:
			void start(connection_ptr c);
			void stop(connection_ptr c);
			void stop_all();

		private:
			std::set<connection_ptr> connections_;
		};
	}
}

#endif // HTTP_CONNECTION_MANAGER_HPP