#include "OrdersDriver.h"
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
	ordersList->orders.push_back(bomb_order);
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

	LOG("---- Validate \\ Execute Orders ----");

	for(Order* order : ordersList->orders)
	{
		if (order->type == "Advance")
		{
			Advance* advance = dynamic_cast<Advance*>(order);
			advance->execute();
		}

		else if (order->type == "Deploy")
		{
			Deploy* temp = dynamic_cast<Deploy*>(order);
			temp->execute();
		}

		else if (order->type == "Bomb")
		{
			Bomb* temp = dynamic_cast<Bomb*>(order);
			temp->execute();
		}

		else if (order->type == "Bomb")
		{
			Bomb* temp = dynamic_cast<Bomb*>(order);
			temp->execute();
		}

		else if (order->type == "Blockade")
		{
			Blockade* temp = dynamic_cast<Blockade*>(order);
			temp->execute();
		}

		else if (order->type == "Airlift")
		{
			Airlift* temp = dynamic_cast<Airlift*>(order);
			temp->execute();
		}

		else if (order->type == "Negotiate")
		{
			Negotiate* temp = dynamic_cast<Negotiate*>(order);
			temp->execute();
		}

		else
		{
			std::cout << "Invalid Order!! Cannot validate / execute!" << std::endl;
		}
	}
	
}



