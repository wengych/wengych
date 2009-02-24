
#include <boost/asio.hpp>

using namespace boost;

typedef asio::buffers_iterator<
	asio::streambuf::const_buffers_type> iterator;

std::pair<iterator, bool>
match_whitespace(iterator begin, iterator end)
{
	iterator i = begin;
	while (i != end)
	{
		if (std::isspace(*i++)
			return std::make_pair(i, true);
	}
	return std::make_pair(i, false);
}

class match_char
{
public:
	explicit match_char(const char c) : c_(c) {}

	template <typename Iterator>
	std::pair<Iterator, bool> operator() (
		Iterator begin, Iterator end) const
	{
		Iterator i = begin;
		while (i != end)
		{
			if (c_ == *i++)
				return std::make_pair(i, true);
		}
		return std::make_pair(i, false);
	}
private:
	char c_;
};

namespace asio {
	template <> struct is_match_condition<match_char>
		: public boost::true_type {};
}

int main()
{
	asio::streambuf b;
	asio::read_until(s, b, match_whitespace);

	return 0;
}
