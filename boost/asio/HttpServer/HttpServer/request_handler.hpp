#ifndef HTTP_REQUEST_HANDLER_HPP
#define HTTP_REQUEST_HANDLER_HPP

#include <string>
#include <boost/noncopyable.hpp>

namespace http {
	namespace server {
		struct reply;
		struct request;

		class request_handler
			:	private boost::noncopyable
		{
		public:
			explicit request_handler(const std::string& doc_root);
			void handle_request(const request& req, reply& rep);

		private:
			std::string doc_root_;
			static bool url_decode(const std::string& in, std::string& out);
		};
	}
}

#endif //HTTP_REQUEST_HANDLER_HPP