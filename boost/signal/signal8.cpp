#include <iostream>
#include <string>
#include <boost/signals.hpp>

class some_slot_type
{
	std::string s_;
public:
	some_slot_type(const char* s) : s_(s) {}

	void operator() (const std::string& s) const
	{
		std::cout << s_ << ": " << s << '\n';
	}
};

int main(int , char **)
{
	using namespace boost::signals;

	boost::signal<void (const std::string&)> sig;

	some_slot_type sc1("sc1");
	some_slot_type sc2("sc2");

	connection c1 = sig.connect(sc1);
	connection c2 = sig.connect(sc2);

	// Comparison
	std::cout << "c1==c2: " << (c1==c2) << '\n';
	std::cout << "c1<c2:  " << (c1<c2)  << '\n';

	// Testing the connection
	if (c1.connected())
		std::cout << "c1 is connected to a signal\n";

// Swapping and disconnecting
	sig("Hello there");

	c1.swap(c2);
	sig("We've swapped the connections");
	c1.disconnect();
	sig("Disconnected c1, which referred to sc2 after the swap");

	return 0;
}
