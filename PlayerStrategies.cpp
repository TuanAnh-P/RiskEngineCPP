#include "PlayerStrategies.h"


#include "map.h"
#include <iostream>
#include "Player.h"
#include "Cards.h"
#include "GameEngine.h"

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
const Player* PlayerStrategy::getPlayer()
{
	return m_player;
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

void HumanPlayerStrategy::issueOrder()
{
	
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
	: PlayerStrategy(player)
{
	m_strategyType = (StrategyType::AggressivePlayer);
}

void AggressivePlayerStrategy::issueOrder()
{
	// Deploy
	

	// Advance 

	
	
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

void BenevolentPlayerStrategy::issueOrder()
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

void NeutralPlayerStrategy::issueOrder()
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

void CheaterPlayerStrategy::issueOrder()
{

}

void CheaterPlayerStrategy::toAttack()
{

}

void CheaterPlayerStrategy::toDefend()
{

}


