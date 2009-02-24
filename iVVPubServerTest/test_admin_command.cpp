#define BOOST_TEST_MODULE "test AdminCommand"

#include <boost/test/unit_test.hpp>
#include "../iVVPubServer/AdminCommand.h"

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE(test_admin_command)

BOOST_AUTO_TEST_CASE(test_admin_command)
{
	std::string test_string = "01\t110110\tCharles";
	AdminCommand ac(test_string);
	BOOST_CHECK_EQUAL(ac.cmd, "01");
	BOOST_CHECK_EQUAL(ac.room_id, "110110");
	BOOST_CHECK_EQUAL(ac.login_name, "Charles");

}

BOOST_AUTO_TEST_SUITE_END()