#ifndef _MEDIATOR_H_
#define _MEDIATOR_H_

#include <iostream> 
using namespace std;
class Person;

class Mediator
{
	private:
		Person* _landlord;
		Person* _renter;
	public:
		void set_landlord(Person* landlord);

		void set_renter(Person* renter);

		void send(const string& msg, Person* p);
};

#endif
