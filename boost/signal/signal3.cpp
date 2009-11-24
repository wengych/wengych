#include <iostream>
#include <string>
#include <boost/signals.hpp>

class some_slot
{
	std::string s_;
public:
	some_slot(const std::string s) : s_(s) {}
	void operator() () const
	{
		std::cout << s_ << '\n';
	}
};

int main(int , char **)
{
	boost::signal<void (),
		boost::last_value<void>, std::string> sig;

	some_slot s1("I must be called first, you see!");
	some_slot s2("I don't care when you call me, not at all.\
It'll be after those belonging to groups, anyway.");
	some_slot s3("I'd like to be called second, please.");

	sig.connect(s2);
	sig.connect("Last group", s3);
	sig.connect("First group", s1);

	sig();

	return 0;
}
