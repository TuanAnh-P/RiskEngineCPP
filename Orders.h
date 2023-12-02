#pragma once
#include <iostream>
#include <vector>
#include "map.h"
#include "LoggingObserver.h"


//Forward declaration
class Player;
class Deck;
class GameEngine;


// Order base class 
class Order : public ILoggable, public Subject
{
public:
    // Constructor
    Order();

    // Parameter constuctor
    Order(std::string type, Player* player);

    // Override ostream operator
    friend std::ostream& operator<< (std::ostream& os, Order& order);

    // Assignment operator
    void operator=(const Order& order);

    // Class member attributes
    std::string type;

    // Destructor
    virtual ~Order();

    // Pure virtual functions
    virtual void execute() = 0;
    virtual void print() = 0;

protected:

    // Derived class methods
    virtual bool validate();
    Player* getIssuingPlayer();
    void setIssuingPlayer(Player* player);

private:

    // Members
    Player* m_playerIssuer;

};

// OrdersList class 
class OrdersList : public ILoggable, public Subject
{
public:
    // Constructor
    OrdersList();

    // Parameter constuctor
    OrdersList(OrdersList& other);

    // Override virtual methods 
    void remove(Order& order);
    void move(Order& order, const int target_index);

    // Debug methods
    void print();

    // Class attributes
    std::vector<Order*> orders;

    // Destructor
    ~OrdersList();

    // Print to log methods
    string stringToLog() override;
    string stringToTourLog(int game) override;

    void addOrder(Order& order);
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

    // Print to log methods
    string stringToLog() override;
    string stringToTourLog(int game) override;

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
    Advance(Player* player, Territory* targetTerritory, Territory* sourceTerritory, int* value, Deck* deck, GameEngine* gameEngine);

    // Class methods
    void execute();
    void print();

    // Destructor
    ~Advance();

    // Print to log methods
    string stringToLog() override;
    string stringToTourLog(int game) override;

private:

    // Members
    int* m_numOfArmyUnits;
    Territory* m_sourceTerritory;
    Territory* m_targetTerritory;
    Deck* m_deckRef;
    GameEngine* m_gameEngineRef;

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

    //Destructor
    ~Bomb();

    // Print to log methods
    string stringToLog() override;
    string stringToTourLog(int game) override;

private:

    // Member 
    Territory* m_targetTerritory;

    bool validate();

};

// Blockade Order class
class Blockade : public Order
{
public:
    // Constructor
    Blockade();

    // Parameter constructor
    Blockade(Player* player, Territory* tagretTerritory, GameEngine* gameEngineRef);

    //Copy Constructor
    Blockade(Blockade& other);

    // Class methods
    void execute();
    void print();

    // Destructor
    ~Blockade();

    // Print to log methods
    string stringToLog() override;
    string stringToTourLog(int game) override;

private:

    // Member
    Territory* m_targetTerritory;
    GameEngine* m_gameEngineRef;

    //Methods
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

    // Destructor
    ~Airlift();

    // Print to log methods
    string stringToLog() override;
    string stringToTourLog(int game) override;

private:

    // Member
    int* m_numOfArmyUnits;
    Territory* m_targetTerritory;
    Territory* m_sourceTerritory;

    //Methods
    bool validate();

};

// Negotiate order class
class Negotiate : public Order
{
public:
    // Constructor
    Negotiate();

    // Parameter constructor
    Negotiate(Player* player, Player* targetPlayer);

    //Copy Constructor
    Negotiate(Negotiate& other);

    // Class methods
    void execute();
    void print();

    // Destructor 
    ~Negotiate();
    
    // Print to log methods
    string stringToLog() override;
    string stringToTourLog(int game) override;

private:

    // Member
    Player* m_targetPlayer;

    // Method
    bool validate();
};