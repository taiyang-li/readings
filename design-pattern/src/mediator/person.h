#ifndef _PERSON_H_
#define _PERSON_H_

#include "mediator.h"
class Person 
{
	protected:
		Mediator* _mediator;

	public:
		virtual void set_mediator(Mediator* mediator)
		{
			_mediator = mediator;
		}

		virtual void send_message(const string& msg) {
			_mediator->send(msg, this);
		}

		virtual void recv_message(const string& msg) {}
};

class Landlord : public Person
{
	public:
		virtual void recv_message(const string& msg)
		{
			cout << "Landlord receive message: " << msg << endl;
		}
};

class Renter : public Person
{
	public:
		virtual void recv_message(const string& msg)
		{
			cout << "Renter receive message: " << msg << endl;
		}
};

#endif
