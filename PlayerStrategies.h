#pragma once

#include <ostream>

// Strategy enum type
enum class StrategyType
{
	HumanPlayer,
	AggressivePlayer,
	BenevolentPlayer,
	NeutralPlayer,
	CheaterPlayer
};

// Player Strategy abstraction base class 
class PlayerStrategy
{
public:

	// Default Constructor
	PlayerStrategy();

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

protected:
	virtual void issueOrder() = 0;
	virtual void toAttack() = 0;
	virtual void toDefend() = 0;
	StrategyType m_strategyType; 
};


// Human concrete strategy class 
class HumanPlayerStrategy : public PlayerStrategy
{
public:
	// Destructor
	~HumanPlayerStrategy() = default;

	// Constructor
	HumanPlayerStrategy();

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
	AggressivePlayerStrategy();

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
	BenevolentPlayerStrategy();

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
	NeutralPlayerStrategy();

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
	CheaterPlayerStrategy();

	void issueOrder();
	void toAttack();
	void toDefend();

	using PlayerStrategy::operator=;
};
