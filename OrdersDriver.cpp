#include "Orders.h"
#include <iostream>

void testOrdersLists()
{
	// Creates each order type and adds them to a dynamic array
	Deploy* deploy_order = new Deploy(5);
	Advance* advance_order = new Advance();
	Bomb* bomb_order = new Bomb();
	Blockade* blockade_order = new Blockade();
	Airlift* airlift_order = new Airlift();
	Negotiate* negotiate_order = new Negotiate();



	OrdersList* ordersList = new OrdersList;

	ordersList->remove(*deploy_order);


	ordersList->orders.push_back(deploy_order);
	ordersList->orders.push_back(advance_order);
	ordersList->orders.push_back(bomb_order);

	for (int i = 0; i < ordersList->orders.size(); i++)
	{
		std::cout << i << " - " << *ordersList->orders[i];
	}

	
}

void viewAllOrdersInList(OrdersList* orderList)
{
	
}

