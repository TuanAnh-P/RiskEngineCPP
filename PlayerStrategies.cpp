#include "PlayerStrategies.h"

// --------------- PlayerStrategy class ---------------

// Default Constructor
PlayerStrategy::PlayerStrategy() 
{
	m_strategyType = StrategyType::None;
}

// Params Constructor
PlayerStrategy::PlayerStrategy(Player* player)
	: m_player(player)
{
	m_strategyType = StrategyType::None;
}

// Copy Constructor
PlayerStrategy::PlayerStrategy(PlayerStrategy& other)
{
	m_strategyType = other.m_strategyType;
	m_player = other.m_player;
}

// Assignment operator
PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& other)
{
	m_strategyType = other.m_strategyType;
	m_player = other.m_player;

	return *this;
}

// Player pointer getter
const Player& PlayerStrategy::getPlayer()
{
	return *m_player;
}

// Strategy type getter
const StrategyType PlayerStrategy::getStrategyType()
{
	return m_strategyType;
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, const PlayerStrategy& strategy)
{

	// Switch based on the strategy enum type and print 
	switch (strategy.m_strategyType)
	{
	case StrategyType::HumanPlayer:
		os << " this is a Human Player Strategy!";
		break;
	case StrategyType::AggressivePlayer:
		os << " this is a AggressivePlayer Strategy!";
		break;
	case StrategyType::BenevolentPlayer:
		os << " this is a BenevolentPlayer Strategy!";
		break;
	case StrategyType::NeutralPlayer:
		os << " this is a NeutralPlayer Strategy!";
		break;
	case StrategyType::CheaterPlayer:
		os << " this is a CheaterPlayer Strategy!";
		break;

	default:
		os << "ERROR: Invalid strategy type!";
		break;
	}

	return os;
}

// --------------- HumanPlayerStrategy class ---------------

// Constructor
HumanPlayerStrategy::HumanPlayerStrategy(Player* player)
	: PlayerStrategy(player)
{
	m_strategyType = (StrategyType::HumanPlayer);	
}

void HumanPlayerStrategy::issueOrder(const std::string& orderType, Territory* source, Territory* target, int* num, Player* targetPlayer, Deck* deck, GameEngine* gameEngine)
{
	Order* newOrder = nullptr;

	if (orderType == "Deploy") newOrder = new Deploy(m_player, target, num);
	else if (orderType == "Advance") newOrder = new Advance(m_player, target, source, num, deck, gameEngine);
	else if (orderType == "Bomb") newOrder = new Bomb(m_player, target);
	else if (orderType == "Blockade") newOrder = new Blockade(m_player, target, gameEngine);
	else if (orderType == "Airlift") newOrder = new Airlift(m_player, source, target, num);
	else if (orderType == "Negotiate") newOrder = new Negotiate(m_player, targetPlayer);

	if (newOrder) {
		// Add the created order to the player's list of orders
		/*std::cout << m_player->getPlayerID() << " issued a " << orderType << " order" << std::endl;
		m_player->getOrdersList().orders.push_back(newOrder);*/
	}
	else std::cout << "Invalid order type." << std::endl;
}

void HumanPlayerStrategy::toAttack()
{

}

void HumanPlayerStrategy::toDefend()
{

}

// --------------- AggressivePlayerStrategy class ---------------

// Constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) 
{
	m_strategyType = (StrategyType::AggressivePlayer);
}

void AggressivePlayerStrategy::issueOrder(const std::string& orderType, Territory* source, Territory* target, int* num, Player* targetPlayer, Deck* deck, GameEngine* gameEngine)
{

}

void AggressivePlayerStrategy::toAttack()
{

}

void AggressivePlayerStrategy::toDefend()
{

}

// --------------- BenevolentPlayerStrategy class ---------------

// Constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player)
{
	m_strategyType = (StrategyType::BenevolentPlayer);
}

void BenevolentPlayerStrategy::issueOrder(const std::string& orderType, Territory* source, Territory* target, int* num, Player* targetPlayer, Deck* deck, GameEngine* gameEngine)
{

}

void BenevolentPlayerStrategy::toAttack()
{

}

void BenevolentPlayerStrategy::toDefend()
{

}


// --------------- NeutralPlayerStrategy class ---------------

// Constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player)
{
	m_strategyType = (StrategyType::NeutralPlayer);
}

void NeutralPlayerStrategy::issueOrder(const std::string& orderType, Territory* source, Territory* target, int* num, Player* targetPlayer, Deck* deck, GameEngine* gameEngine)
{

}

void NeutralPlayerStrategy::toAttack()
{

}

void NeutralPlayerStrategy::toDefend()
{

}

// --------------- CheaterPlayerStrategy class ---------------

// Constructor
CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player)
{
	m_strategyType = (StrategyType::CheaterPlayer);
}

void CheaterPlayerStrategy::issueOrder(const std::string& orderType, Territory* source, Territory* target, int* num, Player* targetPlayer, Deck* deck, GameEngine* gameEngine)
{

}

void CheaterPlayerStrategy::toAttack()
{

}

void CheaterPlayerStrategy::toDefend()
{

}


