#include "PlayerStrategies.h"

// --------------- PlayerStrategy class ---------------

// Default Constructor
PlayerStrategy::PlayerStrategy()
{}

// Copy Constructor
PlayerStrategy::PlayerStrategy(PlayerStrategy& other)
{
	m_strategyType = other.m_strategyType;
}

// Assignment operator
PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& playerStrategy)
{
	m_strategyType = playerStrategy.m_strategyType;
	return *this;
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, const PlayerStrategy& strategy)
{
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

// Strategy type getter
const StrategyType PlayerStrategy::getStrategyType()
{
	return m_strategyType;
}

// --------------- HumanPlayerStrategy class ---------------

// Constructor
HumanPlayerStrategy::HumanPlayerStrategy()
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
AggressivePlayerStrategy::AggressivePlayerStrategy() 
{
	m_strategyType = (StrategyType::AggressivePlayer);
}

void AggressivePlayerStrategy::issueOrder()
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
BenevolentPlayerStrategy::BenevolentPlayerStrategy()
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
NeutralPlayerStrategy::NeutralPlayerStrategy()
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
CheaterPlayerStrategy::CheaterPlayerStrategy()
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


