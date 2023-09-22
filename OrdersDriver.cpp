#include "Orders.h"
#include <iostream>

void testOrdersLists()
{
	// Creates each order type and adds them to a dynamic array
	Deploy* deploy_order = new Deploy(5);
	Advance* advance_order = new Advance;
	Bomb* bomb_order = new Bomb;
	OrdersList* ordersList = new OrdersList;

	ordersList->orders.push_back(deploy_order);
	ordersList->orders.push_back(advance_order);
	ordersList->orders.push_back(bomb_order);

	std::cout << *ordersList->orders.at(0);
	std::cout << *ordersList->orders.at(1);
	
}

