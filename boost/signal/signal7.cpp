#include <iostream>
#include <boost/signals.hpp>

class some_class
{
	boost::signal<void (int)> some_signal;
};

class some_slot_type
{
};

int main(int , char **)
{
	// will cause compile error
	some_class sc1;
	some_class sc2(sc1);

	return 0;
}
