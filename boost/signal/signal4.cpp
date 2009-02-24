#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/signals.hpp>

class parking_lot_guard
{
	typedef
		boost::signal<void (const std::string&)> alarm_type;
	typedef alarm_type::slot_type slot_type;

	boost::shared_ptr<alarm_type> alarm_;

	typedef std::vector<std::string> cars;
	typedef cars::iterator iterator;

	boost::shared_ptr<cars> cars_;

public:
	parking_lot_guard()
		: alarm_(new alarm_type), cars_(new cars) {}

	boost::signals::connection
		connect_to_alarm(const slot_type& a)
	{
		return alarm_->connect(a);
	}

	void operator() (bool is_entering, const std::string& car_id)
	{
		if (is_entering)
			enter(car_id);
		else
			leave(car_id);
	}

private:
	void enter(const std::string& car_id)
	{
		std::cout <<
			"parking_lot_guard::enter(" << car_id << ")\n";

		// If the car already exists here, sound the alarm
		if (std::binary_search(cars_->begin(), cars_->end(), car_id))
			(*alarm_)(car_id);
		else	// Insert the car_id
			cars_->insert(
				std::lower_bound(
					cars_->begin(),
					cars_->end(), car_id), car_id);
	}

	void leave(const std::string& car_id)
	{
		std::cout <<
			"parking_lot_guard::leave(" << car_id << ")\n";

		// If there are no registered cars,
		// or if the car isn't registered, sound the alarm
		std::pair<iterator, iterator> p =
			std::equal_range(cars_->begin(), cars_->end(), car_id);
		if (p.first == cars_->end() || *(p.first) != car_id)\
			(*alarm_)(car_id);
		else
			cars_->erase(p.first);
	}
};

class security_guard
{
private:
	std::string name_;
public:
	security_guard (const char* name) : name_(name) {}

	void do_whatever_it_takes_to_stop_that_car() const
	{
		std::cout <<
			"Stop in the name of ... eh ..." << name_ << '\n';
	}
	void nah_dont_bother() const
	{
		std::cout << name_ <<
			" says: Man, that coffee tastes f i n e fine!\n";
	}

	void operator() (const std::string& car_id) const
	{
		if (car_id.size() && car_id[0] == 'N')
			do_whatever_it_takes_to_stop_that_car();
		else
			nah_dont_bother();
	}
};

class gate
{
private:
	typedef
		boost::signal<void (bool, const std::string&)> signal_type;
	typedef signal_type::slot_type slot_type;

	signal_type enter_or_leave_;
public:
	boost::signals::connection
		connect_to_gate(const slot_type& s)
	{
		return enter_or_leave_.connect(s);
	}
	void enter(const std::string& car_id)
	{
		enter_or_leave_(true, car_id);
	}
	void leave(const std::string& car_id)
	{
		enter_or_leave_(false, car_id);
	}
};

int main(int , char **)
{
	std::vector<security_guard> security_guards;
	security_guards.push_back("Bill");
	security_guards.push_back("Bob");
	security_guards.push_back("Bull");

	// Create two gates
	gate gate1;
	gate gate2;

	// Create the automatic guard
	parking_lot_guard plg;

	// Connect the automatic guard to the gates
	gate1.connect_to_gate(plg);
	gate2.connect_to_gate(plg);

	// Connect the human guards to the automatic guard
	for (unsigned int i = 0; i < security_guards.size(); ++i)
	{
		plg.connect_to_alarm(security_guards.at(i));
	}

	std::cout << "A couple of cars enter...\n";
	gate1.enter("SLN 123");
	gate2.enter("RFD 444");
	gate2.enter("IUY 897");

	std::cout << "\nA couple of cars leave...\n";
	gate1.leave("IUY 897");
	gate1.leave("SLN 123");

	std::cout << "\nSomeone is entering twice - \
or is it a stolen license plate?\n";
	gate1.enter("RFD 444");

	return 0;
}
