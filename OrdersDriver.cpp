#include "Orders.h"
#include <iostream>

#define LOG(x) std::cout << x << std::endl;

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

	ordersList->orders.push_back(deploy_order);
	ordersList->orders.push_back(advance_order);
	ordersList->orders.push_back(bomb_order);

	LOG("Start Test\n ----BEFORE MOVE----");


	for (int i = 0; i < ordersList->orders.size(); i++)
	{
		std::cout << i << " - " << *ordersList->orders[i];
	}

	std::cout << "---- AFTER MOVE ----\n";
	ordersList->move(*deploy_order, 2);
	ordersList->move(*advance_order, 1);

	// Display Order list
	for (int i = 0; i < ordersList->orders.size(); i++)
	{
		std::cout << i << " - " << *ordersList->orders[i];
	}

	std::cout << "---- AFTER Delete ----\n";
	ordersList->remove(*deploy_order);
	delete deploy_order;
	deploy_order = NULL; // resolve dangling pointer

	// Display Order list
	for (int i = 0; i < ordersList->orders.size(); i++)
	{
		std::cout << i << " - " << *ordersList->orders[i];
	}
	

	//ordersList->remove(deploy_order);
	//delete deploy_order;
	//deploy_order = NULL; // resolve dangling pointer

	//ordersList->remove(advance_order);



	

	
	
}



