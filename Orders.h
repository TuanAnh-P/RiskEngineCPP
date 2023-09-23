#pragma once
#include <iostream>
#include <vector>

/*
	Test free function for Orders

*/
void testOrdersLists();



/*
	Order abstract base class definition
*/
class Order
{
public:
	Order();
	~Order();
	friend std::ostream& operator<< (std::ostream& os, const Order& order);
	

protected:
	std::string type = "Invalid";
	virtual bool validate() = 0;
	virtual void execute() = 0;

	
};

/*
	OrdersList base class definition contains the list of Orders to be executed
*/
class OrdersList
{
public:
	void remove(Order* order);
	void move(Order& order);
	std::vector<Order*> orders;

	

};

/*
	Deploy order class definition. Put a certain number of army units on a target territory
*/
class Deploy : public Order
{
public:
	Deploy(int numOfArmyUnits);
	
	bool validate();
	void execute();

};

/*
	Advance order class definition. Move a certain number of army units from one territory (source territory) to another territory (target
territory)
*/
class Advance : public Order
{
public:
	Advance();

	bool validate();
	void execute();

};

/*
	Bomb order class definition. Destroy half of the army units located on a target territory. This order can only be issued if a player
has the bomb card in their hand. 

*/
class Bomb : public Order
{
public:
	Bomb();

	bool validate();
	void execute();

};

/*
	Blockade order class definition. Triple the number of army units on a target territory and make it a neutral territory. This order can
only be issued if a player has the blockade card in their hand.
*/
class Blockade : public Order
{
public:
	Blockade();

	bool validate();
	void execute();

};

/*
	Airlift order class definition. Advance a certain number of army units from one from one territory (source territory) to another
territory (target territory). This order can only be issued if a player has the airlift card in their hand.
*/
class Airlift : public Order
{
public:
	Airlift();

	bool validate();
	void execute();

};

/*
	Negotiate order class definition. Prevent attacks between the current player and another target player until the end of the turn. This
order can only be issued if a player has the diplomacy card in their hand.
*/
class Negotiate : public Order
{
public:
	Negotiate();

	bool validate();
	void execute();

};






