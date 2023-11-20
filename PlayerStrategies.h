#pragma once

// Player Strategy abstraction base class 
class PlayerStrategy
{
public:
	// Constructor
	PlayerStrategy();

	// Destructor
	virtual ~PlayerStrategy() = default;
	

protected:
	virtual void issueOrder() = 0;
	virtual void toAttack() = 0;
	virtual void toDefend() = 0;

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
};

// Cheater concrete strategy class 
class CheaterPlayerStrategy : public PlayerStrategy
{
public:
	// Destructor
	~CheaterPlayerStrategy() = default;

	// Constructor
	CheaterPlayerStrategy();

	virtual void issueOrder();
	virtual void toAttack();
	virtual void toDefend();
};
