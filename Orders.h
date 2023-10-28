#pragma once
#include <iostream>
#include <vector>
#include "map.h"

//Forward declaration
class Player;


// Order base class 
class Order
{
public:
	// Constructor
	Order();

	Order(std::string type, Player* player);
	
	// Override ostream operator
	friend std::ostream& operator<< (std::ostream& os, Order& order);

	// Assignment operator
	void operator=(const Order& order);

	// Class member attributes
	std::string type;

	// Destructor
	virtual ~Order();

	virtual void execute() = 0;

protected:

	// Derived class methods
	virtual bool validate();
	virtual void print() = 0;
	Player* getIssuingPlayer();
	void setIssuingPlayer(Player* player);

private:
	Player* m_playerIssuer;

};

// OrdersList class 
class OrdersList
{
public:
	// Constructor
	OrdersList();

	OrdersList(OrdersList& other);

	void remove(Order& order);
	void move(Order& order, const int target_index);

	// Debug methods
	void print();

	// Class attributes
	std::vector<Order*> orders;

	// Destructor
	~OrdersList();
};

// Deploy Order class 
class Deploy : public Order
{
public:
	// Constructor
	Deploy();
	
	// Parameter constuctor
	Deploy(Player* player, Territory* target, int* value);

	// Copy Constructor
	Deploy(Deploy& other);
	
	// Class methods
	void execute();

	// Helper methods 
	void print();

	// Destructor
	~Deploy();

private: 

	// Members
	Territory* m_targetTerritory;
	int* m_numOfArmyUnits;

	// Methods
	bool validate();
	

};

// Advance Order class 
class Advance : public Order
{
public:
	// Constructor
	Advance();

	//Copy Constructor
	Advance(Advance& other);

	// Parameter Constructor
	Advance(Player* player, Territory* targetTerritory, Territory* sourceTerritory, int* value);

	// Class methods
	void execute();
	void print();

	~Advance();

private:

	// Members
	int* m_numOfArmyUnits;
	Territory* m_sourceTerritory;
	Territory* m_targetTerritory;

	//Methods
	bool validate();
	


};

// Bomb Order class 
class Bomb : public Order
{
public:
	// Constructor 
	Bomb();

	// Parameter constructor 
	Bomb(Player* player, Territory* targetTerritory);

	//Copy Constructor
	Bomb(Bomb& other);

	// Class methods
	void execute();
	void print();

	~Bomb();

private:

	Territory* m_targetTerritory;
	bool validate();

};

// Blockade Order class
class Blockade : public Order
{
public:
	// Constructor
	Blockade();

	Blockade(Player* player, Territory* tagretTerritory);

	//Copy Constructor
	Blockade(Blockade& other);

	// Class methods
	void execute();
	void print();

	~Blockade();

private: 
	Territory* m_targetTerritory;
	bool validate();

};

// Airlift Order class
class Airlift : public Order
{
public:
	// Constructor
	Airlift();

	// Parameter constructor 
	Airlift(Player* player, Territory* sourceTerritory, Territory* targetTerritory, int* value);

	//Copy Constructor
	Airlift(Airlift& other);

	// Class methods
	void execute();
	void print();

	~Airlift();

private:

	int* m_numOfArmyUnits;
	Territory* m_targetTerritory;
	Territory* m_sourceTerritory;
	bool validate();

};

// Negotiate order class
class Negotiate : public Order
{
public:
	// Constructor 
	Negotiate();

	Negotiate(Player* player, Player* targetPlayer);

	//Copy Constructor
	Negotiate(Negotiate& other);

	// Class methods
	void execute();
	void print();

	~Negotiate();

private: 

	Player* m_targetPlayer;
	bool validate();
};






