#include <iostream>
#include <string>
#include "person.h"
#include "mediator.h"

int main()
{
	Person* renter = new Renter();
	Person* landlord= new Landlord();
	Mediator* mediator = new Mediator();

	mediator->set_landlord(landlord);
	mediator->set_renter(renter);

	landlord->send_message("I have a house to be rented");
	renter->send_message("I will rent your house");

	return 0;		
}
