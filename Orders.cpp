#include "Orders.h"
#include <iostream>
using namespace std;

// Base Order Class constructor
Order::Order()
{

	

}

// Base Order Class deconstructor
Order::~Order()
{
	// Debugging
	std::cout << "Deconstructor Order base" << std::endl;
}

bool Order::validate()
{
	return true;
}
void Order::execute()
{
	return;
}

// OrdersList class 

/*
	Delete the order from the list of Orders 
*/
void OrdersList::remove(Order* order)
{
	if (this->orders.empty())
	{
		std::cout << "Order List is empty! " << endl;
		return;
	}

	for (int i = 0; i < this->orders.size(); i++)
	{
		if (this->orders[i] == order)
		{
			this->orders.erase(this->orders.begin() + i);
			return;
		}
	}

	std::cout << "Order is not in the Orders List " << endl;
}

/*
	Move the order in the list of Orders. 
	-> Move to top
	-> Move up
	-> Move down 
	-> Move to bottom
*/
void OrdersList::move(Order* order, const int target_index)
{
	// Check empty array
	if (this->orders.empty())
	{
		std::cout << "Order List is empty! " << endl;
		return;
	}

	// Check if the array has one element
	else if (this->orders.size() < 2)
	{
		std::cout << "Order List only has one element! " << endl;
		return;
	}

	// Check if target index is out of bound of the array
	else if (target_index > this->orders.size())
	{
		std::cout << "Index target is out of bounds of the OrdersList " << endl;
		return;
	}

	// Swap target index element 

	for (int i = 0; i < this->orders.size(); i++)
	{
		if (this->orders[i] == order)
		{
			this->orders.erase(this->orders.begin() + i);
			this->orders.insert(this->orders.begin() + target_index, order);
			return;
		}
	}
}

/*
	Override stream insertion operator. Prints the order description when passed dwda
*/
ostream& operator<<(ostream& os, const Order& order)
{

	if (order.type == "Deploy")
	{
		os << order.type << " - Deploys armies to the terrorities\n";
	}
	else if (order.type == "Advance")
	{
		os << order.type << " - Advance armies to the terrorities\n";
	}
	else if (order.type == "Bomb")
	{
		os << order.type << " - Bomb target terrority\n";
	}
	else if (order.type == "Blockade")
	{
		os << order.type << " - Blockade target terrority\n";
	}
	else if (order.type == "Airlift")
	{
		os << order.type << " - Airlift armies to the terrorities\n";
	}
	else if (order.type == "Negotiate")
	{
		os << order.type << " - Negotiate with target player\n";
	}
	else
	{
		os << "Invalid order!";
	}
	
	return os;
}

// Deploy class
/*
	Deploy class constructor. Parameters include number of armies to move, source territory, and target terroritory
*/
Deploy::Deploy(int numOfArmyUnits)
{
	std::cout << "Created Deploy order" << std::endl;
	this->type = "Deploy";
}

/*
	Deploy validate checks if source territory and target territory.
*/
bool Deploy::validate()
{
	std::cout << "validate Deploy order\n";
	return true;
}

/*
	Executes Deploy order and begins attack from source territory to target territory
*/
void Deploy::execute()
{
	if (this->validate())
	{
		std::cout << "execute Deploy order\n";
	}	
}

//  Advance class
/*
	Advance class constructor. Parameters include number of armies to move, source territory, and target terroritory
*/
Advance::Advance()
{
	std::cout << "Created Advance order" << std::endl;
	this->type = "Advance";
}

/*
	Advance validate checks if source territory and target territory. 
*/ 
bool Advance::validate()
{
	std::cout << "validate Advance order\n";
	return true;
}

/*
	Executes Advance order and begins attack from source territory to target territory
*/
void Advance::execute()
{
	if (this->validate())
	{
		std::cout << "execute Advance order\n";
	}
	
}

// Bomb class
/*
	Bomb class constructor. Parameters include target territory to bomb
*/
Bomb::Bomb()
{
	std::cout << "Created Bomb order" << std::endl;
	this->type = "Bomb";
}

/*
	Bomb validate checks if the target territory is validate
*/
bool Bomb::validate()
{
	std::cout << "validate Bomb order\n";
	return true;
}

/*
	Executes Bomb order reducing territory army value by half
*/
void Bomb::execute()
{
	if (this->validate())
	{
		std::cout << "execute Bomb order\n";
	}
}

// Blockade class
/*
	Blockade class constructor. Parameters include target territory
*/
Blockade::Blockade()
{
	std::cout << "Created Blockade order" << std::endl;
	this->type = "Blockade";
}

/*
	Blockade validate checks if the target territory is validate
*/
bool Blockade::validate()
{
	std::cout << "validate Blockade order\n";
	return true;
}

/*
	Executes Blockade which turns target territory into a neutral territory and triple the army value
*/
void Blockade::execute()
{
	if (this->validate())
	{
		std::cout << "execute Blockade order\n";
	}
}

// Airlift class
/*
	Airlift class constructor. Parameters include the number of armies, source territory and target territory
*/
Airlift::Airlift()
{
	std::cout << "Created Airlift order" << std::endl;
	this->type = "Airlift";
}

/*

*/
bool Airlift::validate()
{
	std::cout << "validate Airlift order\n";
	return true;
}

/*

*/
void Airlift::execute()
{
}

// Negotiate class
/*
	Negotiate class constructor. Parameters include target player 
*/
Negotiate::Negotiate()
{
	std::cout << "Created Negotiate order" << std::endl;
	this->type = "Negotiate";
}

/*

*/
bool Negotiate::validate()
{
	std::cout << "validate Negotiate order\n";
	return true;
}

/*

*/
void Negotiate::execute()
{
	if (this->validate())
	{
		std::cout << "execute Negotiate order\n";
	}
}

