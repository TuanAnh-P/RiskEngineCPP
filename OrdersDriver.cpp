#include "OrdersDriver.h"
#include "Orders.h"
#include "Player.h"
#include "Cards.h"
#include "MapLoader.h"
#include <iostream>


#define LOG(x) std::cout << x << std::endl;
#define DELETE(x) delete x; x = NULL;

void testOrdersLists()
{
	std::cout << std::endl;
	LOG("-------- Order Lists Test Setup --------")
	std::cout << std::endl;

	Territory* test_territory = new Territory("Test", 0, 0);
	int* armies = new int(10);

	// Creates each order type and adds them to a dynamic array
	Deploy* deploy_order = new Deploy(new Player("Colton"), test_territory, armies);
	Advance* advance_order = new Advance();
	Bomb* bomb_order = new Bomb();
	Blockade* blockade_order = new Blockade();
	Airlift* airlift_order = new Airlift();
	Negotiate* negotiate_order = new Negotiate();

	std::cout << std::endl;
	LOG("Start Test\n ----Poly (Virtual destructor) ----");
	{
		Order* order = new Deploy();
		DELETE(order);

	}
	std::cout << std::endl;


	LOG("Start Test\n ----COPY Constructors----");
	// Test Copy Constructors
	{
		Deploy* deploy_order2 = new Deploy(*deploy_order);
		//Advance* advance_order2(advance_order);
		//Bomb* bomb_order2(bomb_order);
		//Blockade* blockade_order2(blockade_order);
		//Airlift* airlift_order2(airlift_order);
		//Negotiate* negotiate_order2(negotiate_order);
		//DELETE(deploy_order2);
	}

	// Create OrdersList and push orders
	OrdersList* ordersList = new OrdersList;
	ordersList->orders.push_back(deploy_order);
	ordersList->orders.push_back(advance_order);
	ordersList->orders.push_back(bomb_order);
	ordersList->orders.push_back(blockade_order);
	ordersList->orders.push_back(airlift_order);
	ordersList->orders.push_back(negotiate_order);

	OrdersList* ordersList2(ordersList);
	

	LOG("Start Test\n ----BEFORE MOVE----");
	ordersList->print();

	LOG("---- AFTER MOVE ----");
	ordersList->move(*deploy_order, 2);

	// Display Order list
	ordersList->print();

	LOG("---- AFTER Remove ----");
	ordersList->remove(*deploy_order);
	ordersList->print(); 

	//LOG("---- Print copy before remove ----");
	//ordersList2->print();

	// resolve dangling pointer
	DELETE(deploy_order);

	// Display Order list
	ordersList->print();

	/*for(Order* order : ordersList->orders)
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

		
	}*/

	std::cout << std::endl;
	LOG("---- DELETE Orders ----");
	std::cout << std::endl;
	DELETE(test_territory);
	DELETE(ordersList);
	
}

void testOrderExecution()
{
	std::cout << std::endl;
	LOG("-------- Order Execution Test Setup --------")
	std::cout << std::endl;
	std::vector<std::string> mapsToLoad = { "./maps/3D.map" };
	std::vector<Map*> validMaps;

	MapLoader loader(mapsToLoad[0]);
	Map* loadedMap = loader.loadMap();

	if (loadedMap->isValid()) {
		std::cout << "The map was valid" << std::endl;
		validMaps.push_back(loadedMap);
	}
	else {
		std::cout << "The map was invalid" << std::endl;
		delete loadedMap;
		std::cout << "----------------------------------------------------------------------------------" << std::endl;
		std::cout << "----------------------------------------------------------------------------------" << std::endl;
		return;
	}
	
	
	Player* p1 = new Player("Test_Player01");
	Player* p2 = new Player("Test_Player02");
	Player* p3 = new Player("NEUTRAL");

	const std::vector<Continent*> continents = loadedMap->getContinents();
	const std::vector<Territory*> c_territories = continents[0]->getTerritories();
	const std::vector<Territory*> t_territories = continents[1]->getTerritories();

	// Player 1
	p1->addTerritory(c_territories[0]);
	p1->addTerritory(c_territories[1]);

	// Player 2
	p2->addTerritory(c_territories[3]);

	// Neutral player
	p3->addTerritory(c_territories[4]);
	p3->addTerritory(c_territories[5]);
	p3->addTerritory(c_territories[6]);


	// Issue orders
	p1->issueOrder("Deploy");
	p1->issueOrder("Advance");
	p1->issueOrder("Airlift");
	p1->issueOrder("Bomb"); // Need input to validate (at the moment will always be invalid)
	p1->issueOrder("Blockade");
	p1->issueOrder("Negotiate");


	// Execute orders 
	int issueOrderListLength = p1->getOrdersList().orders.size();

	std::cout << std::endl;
	LOG("-------- Order Execution --------")
	std::cout << std::endl;
	for (size_t i = 0; i < issueOrderListLength; i++)
	{
		p1->getOrdersList().orders[i]->execute();
	}


	

	


	
	


	


}



