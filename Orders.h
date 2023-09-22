#pragma once
#include <iostream>
#include <vector>

/*
	Test free function for Orders

*/
void testOrdersLists();

/*
	Order abstract base class defintion
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
	OrdersList base class defintion contains the list of Orders to be executed
*/
class OrdersList
{
public:
	void remove();
	void move();
	std::vector<Order*> orders;

private: 
	

};

/*
	Deploy order class defintion
*/
class Deploy : public Order
{
public:
	Deploy();
	
	bool validate();
	void execute();

};

/*
	Advance order class defintion
*/
class Advance : public Order
{
public:
	Advance();

	bool validate();
	void execute();

};

/*
	Bomb order class defintion
*/
class Bomb : public Order
{
public:
	Bomb();

	bool validate();
	void execute();

};

/*
	Blockade order class defintion
*/
class Blockade : public Order
{
public:
	Blockade();

	bool validate();
	void execute();

};

/*
	Airlift order class defintion
*/
class Airlift : public Order
{
public:
	Airlift();

	bool validate();
	void execute();

};

/*
	Negotiate order class defintion
*/
class Negotiate : public Order
{
public:
	Negotiate();

	bool validate();
	void execute();

};






