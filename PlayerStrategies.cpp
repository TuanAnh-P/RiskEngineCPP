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
    m_player = player;
}

void HumanPlayerStrategy::issueOrder()
{
}

std::vector<Territory*> HumanPlayerStrategy::toAttack()
{
    return m_player->toAttack();
}

std::vector<Territory*> HumanPlayerStrategy::toDefend()
{
    return m_player->toDefend();
}

int HumanPlayerStrategy::execute(int a, int b) {
    return 0;
}

// --------------- AggressivePlayerStrategy class ---------------

// Constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) 
	: PlayerStrategy(player)
{
	m_strategyType = (StrategyType::AggressivePlayer);
    m_player = player;
}

void AggressivePlayerStrategy::issueOrder()
{
}

std::vector<Territory*> AggressivePlayerStrategy::toAttack()
{
    return m_player->toAttack();
}

std::vector<Territory*> AggressivePlayerStrategy::toDefend()
{
    return m_player->toDefend();
}

int AggressivePlayerStrategy::execute(int a, int b) {
    return 0;
}

// --------------- BenevolentPlayerStrategy class ---------------

// Constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player)
{
	m_strategyType = (StrategyType::BenevolentPlayer);
    m_player = player;
}

// Shouldn't be able to issue a Bomb order so remove Bomb order as an option
void BenevolentPlayerStrategy::issueOrder()
{
}

std::vector<Territory*> BenevolentPlayerStrategy::toAttack()
{
    return m_player->toAttack();
}

std::vector<Territory*> BenevolentPlayerStrategy::toDefend()
{
    return m_player->toDefend();
}

int BenevolentPlayerStrategy::execute(int a, int b) {
    return 0;
}


// --------------- NeutralPlayerStrategy class ---------------

// Constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player)
{
	m_strategyType = (StrategyType::NeutralPlayer);
    m_player = player;
}

void NeutralPlayerStrategy::issueOrder()
{
    std::cout << "Territories " << this->m_player->getPlayerID() << " can deploy army units:" << std::endl;
    for (Territory* territory : this->m_player->toDefend()) {
        std::cout << territory->getName() << " has " << territory->getNumberOfArmies() << std::endl;
    }
    cout << this->m_player->getPlayerID() << " won't make any Deploy orders" << endl;
    cout << this->m_player->getPlayerID() << " can make Advance Order" << endl;
    cout << this->m_player->getPlayerID() << " won't make Advance Order" << endl;
    cout << this->m_player->getPlayerID() << " plays a card from their hand contents below" << endl;
    cout << this->m_player->getHand() << endl;
    cout << this->m_player->getPlayerID() << " won't play any cards" << endl;
}

std::vector<Territory*> NeutralPlayerStrategy::toAttack()
{
    return m_player->toAttack();
}

std::vector<Territory*> NeutralPlayerStrategy::toDefend()
{
    return m_player->toDefend();
}

int NeutralPlayerStrategy::execute(int a, int b) {
    return a+b;
}

// --------------- CheaterPlayerStrategy class ---------------

// Constructor
CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player)
{
	m_strategyType = (StrategyType::CheaterPlayer);
    m_player = player;
}

void CheaterPlayerStrategy::issueOrder()
{
}

std::vector<Territory*> CheaterPlayerStrategy::toAttack()
{
    return m_player->toAttack();
}

std::vector<Territory*> CheaterPlayerStrategy::toDefend()
{
    return m_player->toDefend();
}

int CheaterPlayerStrategy::execute(int a, int b) {
    return 0;
}


