#include <iostream>
#include <cassert>
#include <boost/signals.hpp>
#include <boost/bind.hpp>

class some_class
{
public:
	bool some_function(double d) {
		return d > 3.14;
	}

	bool another_function(double d) {
		return d < 0.0;
	}
};

int main(int , char **)
{
	using namespace boost;
	using namespace std;

	signal<bool (double)> sig0;
	signal<bool (double)> sig1;

	some_class sc;

	sig0.connect(
		bind(&some_class::some_function, &sc, _1));

	sig1.connect(
		bind(&some_class::another_function, &sc, _1));

	assert(sig0(3.1) == false);
	assert(sig1(-12.78) == true);

	return 0;
}
