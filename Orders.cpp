#include "Orders.h"
#include "map.h"
#include <iostream>
#include "Player.h"
#include "Cards.h"
#include "GameEngine.h"

// --------------- Order class ---------------

// Constructors

Order::Order() 
	: m_playerIssuer(nullptr), type("Invalid") {}

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
{};

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

			// Create an Order object based on the orderType
			if (other.orders[i]->type == "Deploy") 
			{
				this->orders.push_back(new Deploy(*dynamic_cast<Deploy*>(other.orders[i])));
			}

			else if (other.orders[i]->type == "Advance")
			{
				this->orders.push_back(new Advance(*dynamic_cast<Advance*>(other.orders[i])));
			}

			else if (other.orders[i]->type == "Bomb")
			{
				this->orders.push_back(new Bomb(*dynamic_cast<Bomb*>(other.orders[i])));
			}

			else if (other.orders[i]->type == "Blockade")
			{
				this->orders.push_back(new Blockade(*dynamic_cast<Blockade*>(other.orders[i])));
			}

			else if (other.orders[i]->type == "Airlift")
			{
				this->orders.push_back(new Airlift(*dynamic_cast<Airlift*>(other.orders[i])));
			}

			else if (other.orders[i]->type == "Negotiate")
			{
				this->orders.push_back(new Negotiate(*dynamic_cast<Negotiate*>(other.orders[i])));
			}

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
	if (this->orders.size() < 2)
	{
		std::cout << "Order List only has one element! " << std::endl;
		return;
	}

	// Check if target index is out of bound of the array
	if (target_index >= this->orders.capacity())
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
		std::cout << i << " - " << orders[i]->type << std::endl;
	}

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
	: Order("Deploy", nullptr), m_targetTerritory(nullptr), m_numOfArmyUnits(new int(0)) {}

Deploy::Deploy(Player* player, Territory* target, int* value)
	: Order("Deploy", player), m_targetTerritory(target), m_numOfArmyUnits(value) {}

Deploy::Deploy(Deploy& other) 
	: Order("Deploy", other.getIssuingPlayer()), m_numOfArmyUnits(new int(*other.m_numOfArmyUnits)), m_targetTerritory(other.m_targetTerritory) {}

Deploy::~Deploy()
{
	std::cout << this->type << " deconstructor was called!" << std::endl;
}

// Deploy validate checks if source territory and target territory.
bool Deploy::validate()
{
	if (this->getIssuingPlayer() == nullptr) { return false; }

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
		m_targetTerritory->setNumberOfArmies(m_targetTerritory->getNumberOfArmies() + *m_numOfArmyUnits);
		this->print();
        Notify(this);
	}	
	else
	{
		std::cout << "Invalid " << this->type << " - Target territory does not belongs to " << this->getIssuingPlayer()->getPlayerID() << std::endl;
		std::cout << std::endl;
	}

}

void Deploy::print()
{
	if (!validate()) { std::cout << "Cannot print invalid << " << this->type << " Order" << std::endl;  return; }

	std::cout << "-- Deploy Order -- " << std::endl;
	std::string name = m_targetTerritory->getName();
	std::cout << "Target Territory: " << name;
	std::cout << " - Deployed number of armies: " << *m_numOfArmyUnits << std::endl;
	std::cout << " - Territory number of armies: " << m_targetTerritory->getNumberOfArmies() << std::endl;
	std::cout << std::endl;

}

// --------------- Advance class ---------------

// Constructors

Advance::Advance()
	: Order("Advance", nullptr), m_targetTerritory(nullptr), m_sourceTerritory(nullptr), m_numOfArmyUnits(new int(0)), m_deckRef(nullptr), m_gameEngineRef(nullptr) {};

Advance::Advance(Player* player, Territory* targetTerritory, Territory* sourceTerritory, int* value, Deck* deck, GameEngine* gameEngine)
	: Order("Advance", player), m_targetTerritory(targetTerritory), m_sourceTerritory(sourceTerritory),	m_numOfArmyUnits(value), m_deckRef(deck), m_gameEngineRef(gameEngine) {};

Advance::Advance(Advance& other)
	: Order("Advance", other.getIssuingPlayer()), m_targetTerritory(other.m_targetTerritory), m_sourceTerritory(other.m_sourceTerritory), m_numOfArmyUnits(new int(*other.m_numOfArmyUnits)), m_deckRef(other.m_deckRef), m_gameEngineRef(other.m_gameEngineRef) {}

// Advance validate checks if source territory and target territory.  
bool Advance::validate()
{
	if (this->getIssuingPlayer() == nullptr || !this->getIssuingPlayer()->isTerritoryOwned(m_sourceTerritory)) return false;

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
			std::cout << "-- Move Advance order --" << std::endl;

			// Check if the requested move amount is greater then the source territory army amount
			if (*m_numOfArmyUnits > m_sourceTerritory->getNumberOfArmies())
			{
				std::cout << " Reuqest move amount is more then whats on the territory, moving remaining amount thats on the " << m_sourceTerritory->getName();
				m_sourceTerritory->setNumberOfArmies(m_targetTerritory->getNumberOfArmies());
				m_targetTerritory->setNumberOfArmies(0);
			}
			else
			{
				m_sourceTerritory->setNumberOfArmies(m_sourceTerritory->getNumberOfArmies() - *m_numOfArmyUnits);
				m_targetTerritory->setNumberOfArmies(m_targetTerritory->getNumberOfArmies() + *m_numOfArmyUnits);
			}

			
			this->print();
            Notify(this);
		}

		// Simulate attack
		else
		{

			bool attackersTurn = true;
			bool attackersWon = true;
			Player* enemyPlayer = nullptr;


			std::vector<Player*> players = m_gameEngineRef->getPlayers();
			for (Player* player : players)
			{
				for (Territory* territory : player->getOwnedTerritories())
				{
					enemyPlayer = player;
				}
			}

			bool canAttack = true;

			// check if target enemy player is in the issuing Player's negioated players list
			for (Player* negioatedPlayer : this->getIssuingPlayer()->getNegotiatedPlayers())
			{
				if (enemyPlayer == negioatedPlayer)
				{
					canAttack = false;
				}
			}

			if (canAttack)
			{
				m_sourceTerritory->setNumberOfArmies(m_sourceTerritory->getNumberOfArmies() - *m_numOfArmyUnits);

				std::cout << "-- Attack Advance order --" << std::endl;

				bool attackersTurn = true;

				while (*m_numOfArmyUnits != 0 && m_targetTerritory->getNumberOfArmies() != 0)
				{

					int roll;
					switch (attackersTurn)
					{
						// attacker's turn
					case true:
						roll = rand() % 10 + 1;
						if (roll > 6) // Attacker has 60% chance of kill a unit
						{
							*m_numOfArmyUnits -= 1;
							if (*m_numOfArmyUnits == 0) { attackersWon = false; }
						}
						attackersTurn = false;
						break;

						// defender's turn
					case false:
						roll = rand() % 10 + 1;
						if (roll > 7) // Defender has 70% chance of kill a unit
						{
							m_targetTerritory->setNumberOfArmies(m_targetTerritory->getNumberOfArmies() - 1);
							if (m_targetTerritory->getNumberOfArmies() == 0) { attackersWon = true; }
							
						}
						attackersTurn = true;
						break;
					}

					std::cout << m_targetTerritory->getName() << " : " << m_targetTerritory->getNumberOfArmies() << std::endl;
					std::cout << "Attacker armies" << " : " << *m_numOfArmyUnits << std::endl;
				}

				if (attackersWon == true)
				{
					std::cout << "-- Attacker Won --" << std::endl;

					// transfer ownership
					std::vector<Player*> players = m_gameEngineRef->getPlayers();
					for (Player* player : players)
					{
						for (Territory* territory : player->getOwnedTerritories())
						{
							if (territory == m_targetTerritory)
							{
								player->removeTerritory(territory);
								this->getIssuingPlayer()->addTerritory(territory);
								territory->setNumberOfArmies(*m_numOfArmyUnits);
							}
						}
					}

					

					// Check if the issuing player has drawn a card this turn after taking an territory			
					if (!this->getIssuingPlayer()->hasDrawn)
					{
						m_deckRef->draw(this->getIssuingPlayer()->getHand());
						this->getIssuingPlayer()->hasDrawn = true;
					}


				}

				else std::cout << "-- Attacker Lost --" << std::endl;

				this->print();
			}

			else
			{
				std::cout << "Invalid " << this->type << " - Enemy player is a negiaoted player" << std::endl;
				std::cout << std::endl;
			}
			
		}
		
	}

	else
	{
		std::cout << "Invalid " << this->type << " - Source territory does not belongs to " << this->getIssuingPlayer()->getPlayerID() 
			<< "or Source and Target territories are not adjacent territories" << std::endl;
		std::cout << std::endl;

	}
	
}

void Advance::print()
{
	//if (!validate()) { std::cout << "Cannot print invalid << " << this->type << " Order" << std::endl;  return; }

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
	std::cout << this->type << " deconstructor was called!" << std::endl;
}

// --------------- Bomb class ---------------

// Constructors

Bomb::Bomb()
	: Order("Bomb", nullptr), m_targetTerritory(nullptr) {}

Bomb::Bomb(Player* player, Territory* targetTerritory)
	: Order("Bomb", player), m_targetTerritory(targetTerritory) {}

Bomb::Bomb(Bomb& other)
	: Order("Bomb", other.getIssuingPlayer()), m_targetTerritory(other.m_targetTerritory) {}

// Bomb validate checks if the target territory is validate
bool Bomb::validate()
{
	if (this->getIssuingPlayer() == nullptr) { return false; }

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

		std::cout << " Target Territory armies before bombing: " << m_targetTerritory->getNumberOfArmies() << std::endl;

		// Reduce target territory armies by half
		m_targetTerritory->setNumberOfArmies(m_targetTerritory->getNumberOfArmies() / 2);

		std::cout << " Target Territory armies after bombing: " << m_targetTerritory->getNumberOfArmies() << std::endl;

		this->print();

        Notify(this);
	}
	else
	{
		std::cout << "Invalid " << this->type << " - " << m_targetTerritory->getName() << " -  belongs to " << this->getIssuingPlayer()->getPlayerID()
			<< " or " << m_targetTerritory->getName() << " territory is not adjacent any to player owned territories" << std::endl;

		std::cout << std::endl;
	}

}

void Bomb::print()
{
	if (!validate()) { std::cout << "Cannot print invalid << " << this->type << " Order" << std::endl;  return; }

	std::cout << " -- " << this->type << " Order-- " << std::endl;
	std::string target = m_targetTerritory->getName();

	std::cout << " Target Territory: " << target << std::endl;
	std::cout << std::endl;

}

// Destructor

Bomb::~Bomb() 
{
	std::cout << this->type << " deconstructor was called!" << std::endl;
}

// --------------- Blockade class ---------------

// Constructors

Blockade::Blockade()
	: Order("Blockade", nullptr), m_targetTerritory(nullptr), m_gameEngineRef(nullptr) {}

Blockade::Blockade(Player* player, Territory* targetTerritory, GameEngine* gameEngine)
	: Order("Blockade", player), m_targetTerritory(targetTerritory), m_gameEngineRef(gameEngine) {}

Blockade::Blockade(Blockade& other)
	: Order("Blockade", other.getIssuingPlayer()), m_targetTerritory(other.m_targetTerritory), m_gameEngineRef(other.m_gameEngineRef) {}

// Blockade validate checks if the target territory is validate
bool Blockade::validate()
{
	if (this->getIssuingPlayer() == nullptr) { return false; }

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
		std::cout << " Target Territory armies before blockade: " << m_targetTerritory->getNumberOfArmies() << std::endl;

		// Double target territory armies and transfer the ownership of the territory to the Neutral player
		m_targetTerritory->setNumberOfArmies(m_targetTerritory->getNumberOfArmies() * 2);

		std::cout << " Target Territory armies after blockade: " << m_targetTerritory->getNumberOfArmies() << std::endl;

		this->getIssuingPlayer()->removeTerritory(m_targetTerritory);

		// Give the neutral player the territory
		m_gameEngineRef->neutralPlayer->addTerritory(m_targetTerritory);

		this->print();

        Notify(this);
	}
	else
	{
		std::cout << "Invalid " << this->type << " - " << m_targetTerritory->getName() << " -  does not belongs to " << this->getIssuingPlayer()->getPlayerID() << std::endl;
		std::cout << std::endl;
	}
}

void Blockade::print()
{
	//if (!validate()) { std::cout << "Cannot print invalid << " << this->type << " Order" << std::endl;  return; }

	std::cout << " -- " << this->type << " Order-- " << std::endl;
	std::string target = m_targetTerritory->getName();
	std::cout << " Target Territory: " << target << std::endl;
	std::cout << " Target Territory Armies: " << m_targetTerritory->getNumberOfArmies() << std::endl;

	std::cout << std::endl;
}

// Destructor

Blockade::~Blockade() 
{
	std::cout << this->type << " deconstructor was called!" << std::endl;
}

// --------------- Airlift class ---------------

// Constructors

Airlift::Airlift() 
	: Order("Airlift", nullptr), m_targetTerritory(nullptr), m_sourceTerritory(nullptr), m_numOfArmyUnits(new int(0)) {};

Airlift::Airlift(Player* player, Territory* sourceTerritory, Territory* targetTerritory, int* value)
	: Order("Airlift", player), m_targetTerritory(targetTerritory), m_sourceTerritory(sourceTerritory), m_numOfArmyUnits(value) {};

Airlift::Airlift(Airlift& other)
	: Order("Airlift", other.getIssuingPlayer()), m_sourceTerritory(other.m_sourceTerritory), m_targetTerritory(other.m_targetTerritory), 
	m_numOfArmyUnits(new int(*other.m_numOfArmyUnits)) {}

// Airlift validate checks if the number of armies, target, source territory is validate
bool Airlift::validate()
{
	if (this->getIssuingPlayer() == nullptr) { return false; }

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

		// Check if the requested move amount is greater then the source territory army amount
		if (*m_numOfArmyUnits > m_sourceTerritory->getNumberOfArmies())
		{
			std::cout << " Reuqest move amount is more then whats on the territory, moving remaining amount thats on the " << m_sourceTerritory->getName();
			m_sourceTerritory->setNumberOfArmies(m_targetTerritory->getNumberOfArmies());
			m_targetTerritory->setNumberOfArmies(0);
		}
		else
		{
			m_sourceTerritory->setNumberOfArmies(m_sourceTerritory->getNumberOfArmies() - *m_numOfArmyUnits);
			m_targetTerritory->setNumberOfArmies(m_targetTerritory->getNumberOfArmies() + *m_numOfArmyUnits);
		}

		this->print();
        Notify(this);
	}
	else
	{
		std::cout << "Invalid " << this->type << " - Target or Source territory does not belong to " << this->getIssuingPlayer()->getPlayerID() << std::endl;
		std::cout << std::endl;
	}

}

void Airlift::print()
{
	if (!validate()) { std::cout << "Cannot print invalid << " << this->type << " Order" << std::endl;  return; }

	std::cout << " -- " << this->type << " Order-- " << std::endl;
	std::string target = m_targetTerritory->getName();
	std::string source = m_sourceTerritory->getName();

	std::cout << "Source Territory: " << source << " ----> ";
	std::cout << " Target Territory: " << target;
	std::cout << " - Target Territory Number of armies: " << *m_numOfArmyUnits << std::endl;

	std::cout << std::endl;
}

// Destructor

Airlift::~Airlift() 
{
	std::cout << this->type << " deconstructor was called!" << std::endl;
}

// --------------- Negotiate class ---------------

// Constructors

Negotiate::Negotiate()
	: Order("Negotiate", nullptr), m_targetPlayer(nullptr) {}

Negotiate::Negotiate(Player* player, Player* targetPlayer)
	: Order("Negotiate", player), m_targetPlayer(targetPlayer) {}

Negotiate::Negotiate(Negotiate& other)
	: Order("Negotiate", other.getIssuingPlayer()), m_targetPlayer(other.m_targetPlayer) {}

// Negotiate validate checks if the target player is validate
bool Negotiate::validate()
{
	if (this->getIssuingPlayer() == nullptr) { return false; }

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
        Notify(this);
	}

	else
	{
		std::cout << "Invalid " << this->type << " : " << m_targetPlayer->getPlayerID() << " is the issuing player" << std::endl;
		std::cout << std::endl;
	}
}

void Negotiate::print()
{
	if (!validate()) { std::cout << "Cannot print invalid << " << this->type << " Order" << std::endl;  return; }

	std::cout << " -- " << this->type << " Order-- " << std::endl;
	std::cout << " Target Player: " << m_targetPlayer->getPlayerID() << std::endl;

	std::cout << std::endl;
}

// Destructor

Negotiate::~Negotiate() 
{
	std::cout << this->type << " deconstructor was called!" << std::endl;
}

// A2 P5
string OrdersList::stringToLog(){
    Order* newOrder = orders.back();
    const std::type_info& type = typeid(*newOrder);
    std::string typeName = type.name();
    size_t pos = typeName.find_first_not_of("0123456789");
    std::string className = typeName.substr(pos);
    return "Order Issued: " + std::string(className);
};

string Deploy::stringToLog(){
    return "Order Executed: Deploy";
};

string Advance::stringToLog(){
    return "Order Executed: Advance";
};

string Bomb::stringToLog(){
    return "Order Executed: Bomb";
};

string Blockade::stringToLog(){
    return "Order Executed: Blockade";
};

string Airlift::stringToLog(){
    return "Order Executed: Airlift";
};

string Negotiate::stringToLog(){
    return "Order Executed: Negotiate";
};

void OrdersList::addOrder(Order& order)
{
    this->orders.push_back(&order);

    Notify(this);
}

