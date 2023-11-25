#pragma once

#include "map.h"
#include <ostream>

class Player; // Forward declaration
class Deck;
class GameEngine;

// Strategy enum type
enum class StrategyType
{
	HumanPlayer,
	AggressivePlayer,
	BenevolentPlayer,
	NeutralPlayer,
	CheaterPlayer,
	None
};

// Player Strategy abstraction base class 
class PlayerStrategy
{
public:

	// Default Constructor
	PlayerStrategy();

	// Par Constructor
	PlayerStrategy(Player* player);

	// Copy Constructor
	PlayerStrategy(PlayerStrategy& other);

	// Destructor
	virtual ~PlayerStrategy() = default;	

	// Override ostream operator
	friend std::ostream& operator<< (std::ostream& os, const PlayerStrategy& strategy);	

	// Assignment operator
	PlayerStrategy& operator=(const PlayerStrategy& playerStrategy);

	// Type getter
	const StrategyType getStrategyType();

	// Pure virtual functions
	virtual void issueOrder() = 0;
	virtual void toAttack() = 0;
	virtual void toDefend() = 0;	

protected:
	StrategyType m_strategyType = StrategyType::None; 
	const Player* getPlayer();	

private:
	Player* m_player;

};


// Human concrete strategy class 
class HumanPlayerStrategy : public PlayerStrategy
{
public:
	// Destructor
	~HumanPlayerStrategy() = default;

	// Constructor
	HumanPlayerStrategy(Player* player);

	void issueOrder();
	void toAttack();
	void toDefend();

	using PlayerStrategy::operator=;
};

// Aggressive concrete strategy class 
class AggressivePlayerStrategy : public PlayerStrategy
{
public:
	// Destructor
	~AggressivePlayerStrategy() = default;

	// Constructor
	AggressivePlayerStrategy(Player* player);

	void issueOrder();
	void toAttack();
	void toDefend();

	using PlayerStrategy::operator=;
};

// Benevolent concrete strategy class 
class BenevolentPlayerStrategy : public PlayerStrategy
{
public:
	// Destructor
	~BenevolentPlayerStrategy() = default;

	// Constructor
	BenevolentPlayerStrategy(Player* player);

	void issueOrder();
	void toAttack();
	void toDefend();

	using PlayerStrategy::operator=;
};

// Neutral concrete strategy class 
class NeutralPlayerStrategy : public PlayerStrategy
{
public:
	// Destructor
	~NeutralPlayerStrategy() = default;

	// Constructor
	NeutralPlayerStrategy(Player* player);

	void issueOrder();
	void toAttack();
	void toDefend();

	using PlayerStrategy::operator=;
};

// Cheater concrete strategy class 
class CheaterPlayerStrategy : public PlayerStrategy
{
public:
	// Destructor
	~CheaterPlayerStrategy() = default;

	// Constructor
	CheaterPlayerStrategy(Player* player);

	void issueOrder();
	void toAttack();
	void toDefend();

	using PlayerStrategy::operator=;
};
