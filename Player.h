#pragma once // Include guard to prevent multiple inclusion of this header

#include <iostream>
#include <vector>
#include <string>

// Including related headers
#include "map.h" // Header for the Territory class
#include "Cards.h"     // Header for the Cards class
#include "Orders.h"    // Header for the Orders class

class Player {
public:
    // Constructor - GOOD
    Player(const std::string& playerName);

    // Copy constructor - GOOD
    Player(Player& other);

    // Assignment operator - GOOD
    Player& operator=(Player& other);

    // Destructor - GOOD
    ~Player();

    friend std::ostream& operator<<(std::ostream& os, Player& player);

    // Methods related to managing territories
    void addTerritory(Territory* territory); // Add a territory to the player's owned territories - GOOD
    std::vector<Territory*> toDefend(); // Get a list of territories to defend - GOOD
    std::vector<Territory*> toAttack(); // Get a list of territories to attack - GOOD

    // Methods related to managing cards
    Hand& getHand(); // Get the player's hand of cards - GOOD

    // Methods related to managing orders
    OrdersList& getOrdersList(); // Get the player's list of orders - GOOD
    void issueOrder(const std::string& orderType); // Issue a new order of a specified type - GOOD

private:
    // Attributes related to a Player's instance
    std::string playerName; // The name of the player - GOOD
    std::vector<Territory*> ownedTerritories; // List of territories owned by the player - GOOD
    Hand* hand; // The player's hand of cards - GOOD
    OrdersList* ordersList; // The list of orders issued by the player - GOOD
};

//    friend std::ostream& operator<<(std::ostream& os, Player& player);
//
//    bool removeTerritory(Territory* territory); // Remove a territory from the player's owned territories

