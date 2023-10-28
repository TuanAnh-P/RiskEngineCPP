#include "Orders.h"
#include "map.h"
#include <iostream>
#include "Player.h"

// --------------- Order class ---------------

// Constructors

Order::Order() 
	: m_playerIssuer(NULL), type("Invalid") {}

Order::Order(std::string type, Player* player)
	: m_playerIssuer(player), type(type) {}

// Assignment operator
void Order::operator= (const Order& order) 
{
	m_playerIssuer = order.m_playerIssuer;
	type = order.type;

}

bool Order::validate() { return true;}

void Order::execute() {return;}

Player* Order::getIssuingPlayer()
{
	return this->m_playerIssuer;
}

void Order::setIssuingPlayer(Player* player)
{
	this->m_playerIssuer = player;
}

std::ostream& operator<<(std::ostream& os, Order& order)
{

	if (order.type == "Deploy")
	{
		Deploy* d = dynamic_cast<Deploy*>(&order);

		if (d != nullptr)
		{
			os << d->type << " - Deploys armies to the terrorities" << std::endl;
		}
	}

	else if (order.type == "Advance")
	{
		Advance* d = dynamic_cast<Advance*>(&order);

		if (d != nullptr)
		{
			os << order.type << " - Advance armies to the terrorities" << std::endl;
		}

	}
	else if (order.type == "Bomb")
	{
		Bomb* d = dynamic_cast<Bomb*>(&order);

		if (d != nullptr)
		{
			os << order.type << " - Bomb target terrority" << std::endl;
		}

	}
	else if (order.type == "Blockade")
	{
		Blockade* d = dynamic_cast<Blockade*>(&order);

		if (d != nullptr)
		{
			os << order.type << " - Blockade target terrority" << std::endl;
		}

	}
	else if (order.type == "Airlift")
	{
		Airlift* d = dynamic_cast<Airlift*>(&order);

		if (d != nullptr)
		{
			os << order.type << " - Airlift armies to the terrorities" << std::endl;
		}

	}
	else if (order.type == "Negotiate")
	{
		Negotiate* d = dynamic_cast<Negotiate*>(&order);

		if (d != nullptr)
		{
			os << order.type << " - Negotiate with target player" << std::endl;
		}

	}
	else
	{
		os << "Invalid order!";
	}

	return os;
}

// Destructor

Order::~Order()
{
	std::cout << "Order deconstructor was called!" << std::endl;
};

// --------------- OrdersList class ---------------

// Constructors

OrdersList::OrdersList() {};

OrdersList::OrdersList(OrdersList& other)
{
	if (other.orders.empty()) return;

	else
	{
		this->orders.clear();
		for (int i = 0; i < other.orders.size(); i++)
		{
			this->orders[i] = other.orders[i];
		}
	}
}

// Delete the order from the list of Orders 
void OrdersList::remove(Order& order)
{
	if (this->orders.empty())
	{
		std::cout << "Order List is empty! " << std::endl;
		return;
	}

	for (int i = 0; i < this->orders.size(); i++)
	{
		if (this->orders[i] == &order)
		{
			this->orders.erase(this->orders.begin() + i);
			return;
		}
	}

	std::cout << "Order is not in the Orders List " << std::endl;
}

// Move the order in the list of Orders. Takes Order ptr and target index within the OrdersList array
void OrdersList::move(Order& order, const int target_index)
{
	// Check empty array
	if (this->orders.empty())
	{
		std::cout << "Order List is empty! " << std::endl;
		return;
	}

	// Check if the array has one element
	else if (this->orders.size() < 2)
	{
		std::cout << "Order List only has one element! " << std::endl;
		return;
	}

	// Check if target index is out of bound of the array
	else if (target_index > this->orders.size())
	{
		std::cout << "Index target is out of bounds of the OrdersList " << std::endl;
		return;
	}

	// Swap target index element 

	for (int i = 0; i < this->orders.size(); i++)
	{
		if (this->orders[i] == &order)
		{
			this->orders.erase(this->orders.begin() + i);
			this->orders.insert(this->orders.begin() + target_index, &order);
			return;
		}
	}
}

// Print each order within the OrdersList
void OrdersList::print()
{
	int n = this->orders.size();

	if (this->orders.empty())
	{
		std::cout << "Order List is empty! " << std::endl;
		return;
	}

	for (int i = 0; i < n; i++)
	{
		std::cout << i << " - " << *this->orders[i];
	}

	std::cout << "\n";
}

// Destructor

OrdersList::~OrdersList()
{
	for (Order* order : orders)
	{
		delete order;
	}

	this->orders.clear();
};

// --------------- Deploy class ---------------

// Constructors

Deploy::Deploy()
	: Order("Deploy", NULL), m_targetTerritory(NULL), m_numOfArmyUnits(new int(0)) {}

Deploy::Deploy(Player* player, Territory* target, int* value)
	: Order("Deploy", player), m_targetTerritory(target), m_numOfArmyUnits(value) {}

Deploy::Deploy(Deploy& other) 
	: Order("Deploy", other.getIssuingPlayer()), m_numOfArmyUnits(new int(*other.m_numOfArmyUnits)), m_targetTerritory(other.m_targetTerritory) {}

Deploy::~Deploy()
{
	std::cout << "Deploy deconstructor was called!" << std::endl;
}

// Deploy validate checks if source territory and target territory.
bool Deploy::validate()
{
	std::cout << "Validating " << this->type << " Order.." << std::endl;
	std::vector<Territory*> ownedTerritories = this->getIssuingPlayer()->getOwnedTerritories();

	if (this->getIssuingPlayer()->isTerritoryOwned(m_targetTerritory)) return true;

	return false;
	
}

// Executes Deploy order and begins attack from source territory to target territory
void Deploy::execute()
{
	if (validate())
	{
		std::cout << "Executing Deploy Order.." << std::endl;
		this->print();


		/// Add armies to territory
	}	
	else
	{
		std::cout << "Invalid " << this->type << " - Target territory does not belongs to " << this->getIssuingPlayer()->getPlayerName() << std::endl;
		std::cout << std::endl;
	}

}

void Deploy::print()
{
	std::cout << "-- Deploy Order -- " << std::endl;
	std::string name = m_targetTerritory->getName();
	std::cout << "Target Territory: " << name;
	std::cout << " - Number of armies: " << *m_numOfArmyUnits << std::endl;
	std::cout << std::endl;

}

// --------------- Advance class ---------------

// Constructors

Advance::Advance()
	: Order("Advance", NULL), m_targetTerritory(NULL), m_sourceTerritory(NULL), m_numOfArmyUnits(new int(0)) {};

Advance::Advance(Player* player, Territory* targetTerritory, Territory* sourceTerritory, int* value)
	: Order("Advance", player), m_targetTerritory(targetTerritory), m_sourceTerritory(sourceTerritory),
	m_numOfArmyUnits(value) {};

Advance::Advance(Advance& other)
	: Order("Advance", other.getIssuingPlayer()), m_targetTerritory(other.m_targetTerritory), m_sourceTerritory(other.m_sourceTerritory), 
	m_numOfArmyUnits(new int(*other.m_numOfArmyUnits)) {}

// Advance validate checks if source territory and target territory.  
bool Advance::validate()
{
	std::cout << "Validating " << this->type << " Order.." << std::endl;

	if (!this->getIssuingPlayer()->isTerritoryOwned(m_sourceTerritory)) return false;

	// Check that target territory is adjacent to a player owned territory
	for (Territory* adjacentTerritory : m_targetTerritory->getAdjacentTerritories())
	{
		if (m_sourceTerritory == adjacentTerritory) return true;
	}

	return false;
}

// Executes Advance order and begins attack from source territory to target territory
void Advance::execute()
{
	if (this->validate())
	{
		std::cout << "Executing " << this->type << " order..." << std::endl;

		// Move units
		if (this->getIssuingPlayer()->isTerritoryOwned(m_sourceTerritory) && this->getIssuingPlayer()->isTerritoryOwned(m_targetTerritory))
		{

		}

		// Simulate attack
		else
		{
			float attackerAdvantage = 0.6;
			float defenderAdvantage = 0.7;


		}

		this->print();
		
	}

	else
	{
		/// TODO

	}
	
}

void Advance::print()
{
	std::cout << " -- " << this->type << " Order -- " << std::endl;
	std::string target = m_targetTerritory->getName();
	std::string source = m_sourceTerritory->getName();

	std::cout << "Target Adjacent Territory: " << target << " ----> ";
	std::cout << " Source Territory: " << source;
	std::cout << " - Number of armies: " << *m_numOfArmyUnits << std::endl;
	std::cout << std::endl;


}

// Destructor

Advance::~Advance()
{

}

// --------------- Bomb class ---------------

// Constructors

Bomb::Bomb()
	: Order("Bomb", NULL), m_targetTerritory(NULL) {}

Bomb::Bomb(Player* player, Territory* targetTerritory)
	: Order("Bomb", player), m_targetTerritory(targetTerritory) {}

Bomb::Bomb(Bomb& other)
	: Order("Bomb", other.getIssuingPlayer()), m_targetTerritory(other.m_targetTerritory) {}

// Bomb validate checks if the target territory is validate
bool Bomb::validate()
{
	std::cout << "Validating " << this->type << " order..." << std::endl;

	std::vector<Territory*> ownedTerritories = this->getIssuingPlayer()->getOwnedTerritories();

	// Check if player does not own target territory
	if (!this->getIssuingPlayer()->isTerritoryOwned(m_targetTerritory))
	{
		// Check that target territory is adjacent to a player owned territory
		for (Territory* adjacentTerritory : m_targetTerritory->getAdjacentTerritories())
		{
			this->getIssuingPlayer()->isTerritoryOwned(adjacentTerritory);

			return true;
		}
	}
	
	return false;
}

// Executes Bomb order reducing territory army value by half
void Bomb::execute()
{
	if (this->validate())
	{
		std::cout << "Executing " << this->type << " order..." << std::endl;
		this->print();

		// Reduce target territory armies by half
	}
	else
	{
		std::cout << "Invalid " << this->type << " - " << m_targetTerritory->getName() << " -  belongs to " << this->getIssuingPlayer()->getPlayerName()
			<< " or " << m_targetTerritory->getName() << " territory is not adjacent any to player owned territories" << std::endl;

		std::cout << std::endl;
	}

}

void Bomb::print()
{
	std::cout << " -- " << this->type << " Order-- " << std::endl;
	std::string target = m_targetTerritory->getName();

	std::cout << " Target Territory: " << target << std::endl;
	std::cout << std::endl;

}

// Destructor

Bomb::~Bomb() {}

// --------------- Blockade class ---------------

// Constructors

Blockade::Blockade()
	: Order("Blockade", NULL), m_targetTerritory(NULL) {}

Blockade::Blockade(Player* player, Territory* targetTerritory)
	: Order("Blockade", player), m_targetTerritory(targetTerritory) {}

Blockade::Blockade(Blockade& other)
	: Order("Blockade", other.getIssuingPlayer()), m_targetTerritory(other.m_targetTerritory) {}

// Blockade validate checks if the target territory is validate
bool Blockade::validate()
{
	std::cout << "Validating " << this->type << " order..." << std::endl;

	std::vector<Territory*> ownedTerritories = this->getIssuingPlayer()->getOwnedTerritories();

	if (this->getIssuingPlayer()->isTerritoryOwned(m_targetTerritory)) return true;

	return false;
}

// Executes Blockade which turns target territory into a neutral territory and triple the army value
void Blockade::execute()
{
	if (this->validate())
	{
		std::cout << "Executing " << this->type << " order..." << std::endl;
		this->print();

		// Double target territory armies and transfer the ownership of the territory to the Neutral player.
	}
	else
	{
		std::cout << "Invalid " << this->type << " - " << m_targetTerritory->getName() << " -  does not belongs to " << this->getIssuingPlayer()->getPlayerName() << std::endl;
		std::cout << std::endl;
	}
}

void Blockade::print()
{
	std::cout << " -- " << this->type << " Order-- " << std::endl;
	std::string target = m_targetTerritory->getName();
	std::cout << " Target Territory: " << target << std::endl;

	std::cout << std::endl;
}

// Destructor

Blockade::~Blockade() {}

// --------------- Airlift class ---------------

// Constructors

Airlift::Airlift() 
	: Order("Airlift", NULL), m_targetTerritory(NULL), m_sourceTerritory(NULL), m_numOfArmyUnits(new int(0)) {};

Airlift::Airlift(Player* player, Territory* sourceTerritory, Territory* targetTerritory, int* value)
	: Order("Airlift", player), m_targetTerritory(targetTerritory), m_sourceTerritory(sourceTerritory), m_numOfArmyUnits(value) {};

Airlift::Airlift(Airlift& other)
	: Order("Airlift", other.getIssuingPlayer()), m_sourceTerritory(other.m_sourceTerritory), m_targetTerritory(other.m_targetTerritory), 
	m_numOfArmyUnits(new int(*other.m_numOfArmyUnits)) {}

// Airlift validate checks if the number of armies, target, source territory is validate
bool Airlift::validate()
{
	std::cout << "Validating " << this->type << " Order.." << std::endl;

	std::vector<Territory*> ownedTerritories = this->getIssuingPlayer()->getOwnedTerritories();
	
	if (this->getIssuingPlayer()->isTerritoryOwned(m_sourceTerritory) && this->getIssuingPlayer()->isTerritoryOwned(m_targetTerritory)) return true;

	return false;
}

// Execute Airlift moves number of armies from source to target territory
void Airlift::execute()
{
	if (validate())
	{
		std::cout << "Executing " << this->type << " Order.." << std::endl;
		this->print();
		// Move armies to target territory
	}
	else
	{
		std::cout << "Invalid " << this->type << " - Target or Source territory does not belong to " << this->getIssuingPlayer()->getPlayerName() << std::endl;
		std::cout << std::endl;
	}

}

void Airlift::print()
{

	std::cout << " -- " << this->type << " Order-- " << std::endl;
	std::string target = m_targetTerritory->getName();
	std::string source = m_sourceTerritory->getName();

	std::cout << "Source Territory: " << source << " ----> ";
	std::cout << " Target Territory: " << target;
	std::cout << " - Number of armies: " << *m_numOfArmyUnits << std::endl;

	std::cout << std::endl;
}

// Destructor

Airlift::~Airlift() {}

// --------------- Negotiate class ---------------

// Constructors

Negotiate::Negotiate()
	: Order("Negotiate", NULL), m_targetPlayer(NULL) {}

Negotiate::Negotiate(Player* player, Player* targetPlayer)
	: Order("Negotiate", player), m_targetPlayer(targetPlayer) {}

Negotiate::Negotiate(Negotiate& other)
	: Order("Negotiate", other.getIssuingPlayer()), m_targetPlayer(other.m_targetPlayer) {}

// Negotiate validate checks if the target player is validate
bool Negotiate::validate()
{
	std::cout << "Validating " << this->type << " Order.." << std::endl;

	if (m_targetPlayer != this->getIssuingPlayer()) return true;
	
	return false;
}

// Execute Negotiate disables the target player's ability to attack 
void Negotiate::execute()
{
	if (this->validate())
	{
		std::cout << "Execute "<< this->type <<" order" << std::endl;
		this->print();

		m_targetPlayer->addToNegotiatedPlayers(this->getIssuingPlayer());

	}

	else
	{
		std::cout << "Invalid " << this->type << " : " << m_targetPlayer->getPlayerName() << " is the issuing player" << std::endl;
		std::cout << std::endl;
	}
}

void Negotiate::print()
{
	std::cout << " -- " << this->type << " Order-- " << std::endl;
	std::cout << " Target Player: " << m_targetPlayer->getPlayerName() << std::endl;

	std::cout << std::endl;
}

// Destructor

Negotiate::~Negotiate() {}

