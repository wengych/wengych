#define _WIN32_WINNT 0x0501

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void timer1()
{
	boost::asio::io_service io;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
	t.wait();

	std::cout << "timer1()\n";
}

void print1(const boost::system::error_code& /*e*/)
{
	std::cout << "print1()\n";
}
void print2(const boost::system::error_code& /*e*/)
{
	std::cout << "print2()\n";
}

void timer2()
{
	boost::asio::io_service io;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
	t.async_wait(print1);
	t.async_wait(print2);
	std::cout << "timer2()\n";

	io.run();
}

void print3(const boost::system::error_code& /*e*/,
			boost::asio::deadline_timer* t, int* count)
{
	if (*count < 5)
	{
		std::cout << *count << "\n";
		++(*count);

		t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
		t->async_wait(boost::bind(print3,
			boost::asio::placeholders::error, t, count));
	}
}

void timer3()
{
	boost::asio::io_service io;

	int count = 0;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
	t.async_wait(boost::bind(print3,
		boost::asio::placeholders::error, &t, &count));
	std::cout << "timer3()\n";

	io.run();
	std::cout << "Final count is " << count << "\n";
}

class printer4
{
public:
	printer4(boost::asio::io_service& io)
		: timer_(io, boost::posix_time::seconds(1)),
		count_(0)
	{
		timer_.async_wait(boost::bind(&printer4::print, this));
	}

	~printer4()
	{
		std::cout << "Final count is " << count_ << "\n";
	}

	void print()
	{
		if (count_ < 5)
		{
			std::cout << count_ << "\n";
			++count_;

			timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1));
			timer_.async_wait(boost::bind(&printer4::print, this));
		}
	}

private:
	boost::asio::deadline_timer timer_;
	int count_;
};

void timer4()
{
	boost::asio::io_service io;
	printer4 p(io);
	std::cout << "\ntimer4()\n";
	io.run();
}

class printer5
{
public:
	printer5(boost::asio::io_service& io)
		:strand_(io),
		timer1_(io, boost::posix_time::seconds(1)),
		timer2_(io, boost::posix_time::seconds(1)),
		count_(0)
	{
		timer1_.async_wait(strand_.wrap(boost::bind(&printer5::print1, this)));
		timer2_.async_wait(strand_.wrap(boost::bind(&printer5::print2, this)));
	}

	~printer5()
	{
		std::cout << "Final count is " << count_ << "\n";
	}

	void print1()
	{
		if (count_ < 10)
		{
			std::cout << "Timer1: " << count_ << "\n";
			++count_;

			timer1_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));
			timer1_.async_wait(strand_.wrap(boost::bind(&printer5::print1, this)));
		}
	}

	void print2()
	{
		if (count_ < 10)
		{
			std::cout << "Timer 2: " << count_ << "\n";
			++count_;

			timer2_.expires_at(timer2_.expires_at() + boost::posix_time::seconds(1));
			timer2_.async_wait(strand_.wrap(boost::bind(&printer5::print2, this)));
		}
	}

private:
	boost::asio::strand strand_;
	boost::asio::deadline_timer timer1_;
	boost::asio::deadline_timer timer2_;
	int count_;
};

void timer5()
{
	boost::asio::io_service io;
	printer5 p(io);
	boost::thread t(boost::bind(&boost::asio::io_service::run, &io));
	io.run();
	t.join();
}

int main()
{
	timer1();
	timer2();
	timer3();
	timer4();
	timer5();
	return 0;
}
