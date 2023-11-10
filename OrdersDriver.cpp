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
	// Set up map data
	std::cout << std::endl;
	LOG("-------- Order Lists Test Setup --------")
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

	// Setup player data
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
//	p1->issueOrder("Deploy");
//	p1->issueOrder("Advance");
//	p1->issueOrder("Airlift");
//	p1->issueOrder("Bomb"); // Need input to validate (at the moment will always be invalid)
//	p1->issueOrder("Blockade");
//	p1->issueOrder("Negotiate");

	LOG("\n Start Test ---- Order COPY Constructors---- \n");
	{

		Deploy deploy_order2(*dynamic_cast<Deploy*>(p1->getOrdersList().orders[0]));
		deploy_order2.print();

		Advance advance_order2(*dynamic_cast<Advance*>(p1->getOrdersList().orders[1]));
		advance_order2.print();

		Airlift airlift_order2(*dynamic_cast<Airlift*>(p1->getOrdersList().orders[2]));
		airlift_order2.print();

		Bomb bomb_order2(*dynamic_cast<Bomb*>(p1->getOrdersList().orders[3]));
		bomb_order2.print();

		Blockade blockade_order2(*dynamic_cast<Blockade*>(p1->getOrdersList().orders[4]));
		blockade_order2.print();

		Negotiate negotiate_order2(*dynamic_cast<Negotiate*>(p1->getOrdersList().orders[5]));
		negotiate_order2.print();

	}


	LOG("\n Start test ---- OrderList Copy -----\n");

	OrdersList ordersList(p1->getOrdersList());

	std::cout << "Original OrderList" << std::endl;
	int orderList1Size = p1->getOrdersList().orders.size();

	for (int i = 0; i < orderList1Size; i++)
	{
		std::cout << p1->getOrdersList().orders[i]->type << " - " << &p1->getOrdersList().orders[i] << std::endl;
	}
	std::cout << std::endl;

	int orderList2Size = ordersList.orders.size();
	std::cout << "Copied OrderList" << std::endl;
	for (int i = 0; i < orderList2Size; i++)
	{
		std::cout << ordersList.orders[i]->type << " - " << &ordersList.orders[i] << std::endl;
	}
	std::cout << std::endl;

	LOG("\n Start Test ---- OrderList Methods ----- \n ----BEFORE MOVE----");
	ordersList.print();

	LOG("\n ---- AFTER MOVE ----");
	ordersList.move(*ordersList.orders[0], 2);
	ordersList.print();

	LOG("\n ---- AFTER REMOVE ----");
	ordersList.remove(*ordersList.orders[0]);
	ordersList.print();

	/// Clean Players
	LOG("\n CLEAN ---- Delete Players / OrderList -----\n");
	DELETE(p1);
	DELETE(p2);
	DELETE(p3);
	LOG("\n CLEAN ---- Copy OrderList -----\n");

}

void testOrderExecution()
{
	// Set up map data
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

	// Set up player data
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


//	// Issue orders
//	p1->issueOrder("Deploy");
//	p1->issueOrder("Advance");
//	p1->issueOrder("Airlift");
//	p1->issueOrder("Bomb"); // Need input to validate (at the moment will always be invalid)
//	p1->issueOrder("Blockade"); // TODO - Need to add NEUTRAL player
//	p1->issueOrder("Negotiate");


	// Execute orders
	int issueOrderListLength = p1->getOrdersList().orders.size();

	std::cout << std::endl;
	LOG("-------- Order Execution --------")
	std::cout << std::endl;
	for (size_t i = 0; i < issueOrderListLength; i++)
	{
		p1->getOrdersList().orders[i]->execute();
	}

	/// Clean Players
	DELETE(p1);
	DELETE(p2);
	DELETE(p3)

}



