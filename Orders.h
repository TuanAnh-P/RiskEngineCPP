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
	friend std::ostream& operator<< (std::ostream& os, const Order& order);
	


protected:
	std::string type = "Invalid";
	virtual void validate() = 0;
	virtual void execute() = 0;

	
};

/*
	OrdersList base class defintion
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
	
	void validate();
	void execute();

};

/*
	Advance order class defintion
*/
class Advance : public Order
{
public:
	Advance();

	void validate();
	void execute();

};






