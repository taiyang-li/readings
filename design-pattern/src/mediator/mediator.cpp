#include "person.h"
#include "mediator.h"

void Mediator::set_landlord(Person* landlord)
{
	_landlord = landlord;
	_landlord->set_mediator(this);
}

void Mediator::set_renter(Person* renter)
{
	_renter = renter;
	_renter->set_mediator(this);
}

void Mediator::send(const string& msg, Person* p)
{
	if (p == _landlord)
	{
		_renter->recv_message(msg);
	}
	else if (p == _renter)
	{
		_landlord->recv_message(msg);
	}
}


