#include <iostream>
#include <string>
#include <cassert>
#include <boost/signals.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/if.hpp>

int main(int , char **)
{
	using namespace boost::lambda;

	boost::signal<void (std::string)> sig;

	sig.connect(var(std::cout)
		<< "Something happened: " << _1 << '\n');
	sig.connect(
		if_(_1=="Signal") [var(std::cout) << "Ok, I've got it\n"]
		.else_[std::cout << constant("Yeah, whatever\n")]);

	sig("Signal");
	sig("Another signal");

	boost::signal<void (int&)> sig2;
	sig2.connect(0, _1 *= 2);	// Double it
	sig2.connect(1, _1 += 3);	// Add 3
	int i = 12;
	sig2(i);
	std::cout << "\ni = " << i << '\n';

	return 0;
}
