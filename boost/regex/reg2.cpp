#include <iostream>
#include <string>
#include <boost/regex.hpp>

int main(int , char **)
{
	// Are there equally many occurrences of
	// "new" and "delete"?
	boost::regex reg("(new)|(delete)");
	boost::smatch m;
	std::string s =
		"Calls to new must be followed by delete. \
		Calling simply new results in a leak!";
	
	int new_counter = 0;
	int delete_counter = 0;

	std::string::const_iterator it = s.begin();
	std::string::const_iterator end = s.end();

	while (boost::regex_search(it, end, m, reg))
	{
		// New or delete ?
		m[1].matched ? ++new_counter : ++ delete_counter;
		it = m[0].second;
	}

	if (new_counter != delete_counter)
	{
		std::cout << "Leak deleted!\n";
	}
	else 
	{
		std::cout << "Seams ok...\n";
	}

	return 0;
}
