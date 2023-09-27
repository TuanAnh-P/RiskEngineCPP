#include "Orders.h"
#include <iostream>

#define LOG(x) std::cout << x << std::endl;
#define DELETE(x) delete x; x = NULL;

void testOrdersLists()
{
	// Creates each order type and adds them to a dynamic array
	Deploy* deploy_order = new Deploy(5);
	Advance* advance_order = new Advance();
	Bomb* bomb_order = new Bomb();
	Blockade* blockade_order = new Blockade();
	Airlift* airlift_order = new Airlift();
	Negotiate* negotiate_order = new Negotiate();

	// Create OrdersList and push orders
	OrdersList* ordersList = new OrdersList;
	ordersList->orders.push_back(deploy_order);
	ordersList->orders.push_back(advance_order);
	ordersList->move(*bomb_order, ordersList->orders.size());
	ordersList->orders.push_back(blockade_order);
	ordersList->orders.push_back(airlift_order);
	ordersList->orders.push_back(negotiate_order);

	

	LOG("Start Test\n ----BEFORE MOVE----");
	ordersList->print();

	LOG("---- AFTER MOVE ----");
	ordersList->move(*deploy_order, 2);

	// Display Order list
	ordersList->print();

	LOG("---- AFTER Remove ----");
	ordersList->remove(*deploy_order);

	// resolve dangling pointer
	DELETE(deploy_order);

	// Display Order list
	ordersList->print();



	
}



