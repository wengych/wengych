#include <iostream>
#include <boost/signals.hpp>

bool always_return_true() {
	return true;
}

bool always_return_false() {
	return false;
}

int main(int , char **)
{
	boost::signal<bool ()> sig;

	sig.connect(&always_return_true);
	sig.connect(&always_return_false);

	std::cout << std::boolalpha << "True or false? " << sig();

	return 0;
}
