#include "Orders.h"
#include <iostream>

void testOrdersLists()
{
	// Creates each order type and adds them to a dynamic array
	Deploy* order1 = new Deploy;
	Advance* order2 = new Advance;
	OrdersList* ordersList = new OrdersList;

	ordersList->orders.push_back(order1);
	ordersList->orders.push_back(order2);

	std::cout << *ordersList->orders.at(0);
	std::cout << *ordersList->orders.at(1);
	
}

