#include "Orders.h"
#include <iostream>
using namespace std;

// Base Order Class constructor
Order::Order()
{
	std::cout << "Created Order base" << std::endl;

}

// OrdersList class 

void OrdersList::remove()
{
	
}

void OrdersList::move()
{

}

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
	else
	{
		os << "Invalid order!";
	}
	
	return os;
}

// Deploy class constructor

Deploy::Deploy()
{
	std::cout << "Created Deploy order" << std::endl;
	this->type = "Deploy";
}

void Deploy::validate()
{
	std::cout << "validate Deploy order\n";
}

void Deploy::execute()
{
	this->validate();
	std::cout << "execute Deploy order\n";
}

// Advance class constructor

Advance::Advance()
{
	std::cout << "Created Advance order" << std::endl;
	this->type = "Advance";
}

void Advance::validate()
{
	std::cout << "validate Advance order\n";
}

void Advance::execute()
{
	this->validate();
	std::cout << "execute Advance order\n";
}



