#include <iostream>
#include <boost/signals.hpp>

bool step0() {
	std::cout << "step0 is ok\n";
	return true;
}

bool step1() {
	std::cout << "step1 is not ok. This won't do at all!\n";
	return false;
}

bool step2() {
	std::cout << "step2 is ok\n";
	return true;
}

class stop_on_failure
{
public:
	typedef bool result_type;

	template <typename InputIterator>
	bool operator() (InputIterator begin, InputIterator end) const
	{
		while (begin != end)
		{
			if (!*begin)
				return false;
			++begin;
		}
		return true;
	}
};

int main(int , char **)
{
	boost::signal<bool (), stop_on_failure> sig;
	sig.connect(0, &step0);
	sig.connect(1, &step1);
	sig.connect(2, &step2);

	bool ok = sig();

	if (ok)
		std::cout << "All system tests clear\n";
	else
		std::cout << "At least one test failed. Aborting.\n";

	return 0;
}
