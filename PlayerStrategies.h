#pragma once

#include <ostream>
#include "map.h"    // Header for the Territory class
#include "Cards.h"  // Header for the Cards class
#include "Orders.h" // Header for the Orders class

class Player; // Forward declaration

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

	const Player& getPlayer();

	// Assignment operator
	PlayerStrategy& operator=(const PlayerStrategy& playerStrategy);

	// Type getter
	const StrategyType getStrategyType();

	// Pure virtual functions
	virtual void issueOrder(const std::string& orderType, Territory* source, Territory* target, int* num, Player* targetPlayer, Deck* deck, GameEngine* gameEngine) = 0;
	virtual void toAttack() = 0;
	virtual void toDefend() = 0;

protected:
	StrategyType m_strategyType = StrategyType::None; 
	Player* m_player = nullptr;

};


// Human concrete strategy class 
class HumanPlayerStrategy : public PlayerStrategy
{
public:
	// Destructor
	~HumanPlayerStrategy() = default;

	// Constructor
	HumanPlayerStrategy(Player* player);

	void issueOrder(const std::string& orderType, Territory* source, Territory* target, int* num, Player* targetPlayer, Deck* deck, GameEngine* gameEngine);
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

	void issueOrder(const std::string& orderType, Territory* source, Territory* target, int* num, Player* targetPlayer, Deck* deck, GameEngine* gameEngine);
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

	void issueOrder(const std::string& orderType, Territory* source, Territory* target, int* num, Player* targetPlayer, Deck* deck, GameEngine* gameEngine);
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

	void issueOrder(const std::string& orderType, Territory* source, Territory* target, int* num, Player* targetPlayer, Deck* deck, GameEngine* gameEngine);
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

	void issueOrder(const std::string& orderType, Territory* source, Territory* target, int* num, Player* targetPlayer, Deck* deck, GameEngine* gameEngine);
	void toAttack();
	void toDefend();

	using PlayerStrategy::operator=;
};
