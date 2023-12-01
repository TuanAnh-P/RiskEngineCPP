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
    virtual void issueOrder(Deck* deck, GameEngine* gameEngine, std::string& orderType) = 0;
    virtual std::vector<Territory*> toAttack() = 0;
    virtual std::vector<Territory*> toDefend() = 0;

    //  Protected class memebers
protected:
    StrategyType m_strategyType = StrategyType::None;
    const Player* getPlayer();
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

    // define abstract methods
    void issueOrder(Deck* deck, GameEngine* gameEngine, std::string& orderType);
    std::vector<Territory*> toAttack();
    std::vector<Territory*> toDefend();

    // Using base class assignment 
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

    // define abstract methods
    void issueOrder(Deck* deck, GameEngine* gameEngine, std::string& orderType);
    std::vector<Territory*> toAttack();
    std::vector<Territory*> toDefend();

    // Using base class assignment 
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

    // define abstract methods
    void issueOrder(Deck* deck, GameEngine* gameEngine, std::string& orderType);
    std::vector<Territory*> toAttack();
    std::vector<Territory*> toDefend();

    // Using base class assignment 
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

    // define abstract methods
    void issueOrder(Deck* deck, GameEngine* gameEngine, std::string& orderType);
    std::vector<Territory*> toAttack();
    std::vector<Territory*> toDefend();

    // Using base class assignment 
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

    // define abstract methods
    void issueOrder(Deck* deck, GameEngine* gameEngine, std::string& orderType);
    std::vector<Territory*> toAttack();
    std::vector<Territory*> toDefend();

    // Using base class assignment 
    using PlayerStrategy::operator=;
};