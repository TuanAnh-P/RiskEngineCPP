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
    // Constructor to create a Player instance with a specified name
    Player(const std::string& playerName);

    // Destructor to clean up resources when a Player instance is destroyed
    ~Player();

    // Methods related to managing territories
    void addTerritory(Territory* territory); // Add a territory to the player's owned territories
    bool removeTerritory(Territory* territory); // Remove a territory from the player's owned territories
    std::vector<Territory*> toDefend(); // Get a list of territories to defend
    std::vector<Territory*> toAttack(); // Get a list of territories to attack

    // Methods related to managing cards
    const Hand& getHand() const; // Get the player's hand of cards

    // Methods related to managing orders
    const OrdersList& getOrdersList() const; // Get the player's list of orders
    void issueOrder(const std::string& orderType); // Issue a new order of a specified type

private:
    // Attributes related to a Player's instance
    std::string playerName; // The name of the player
    std::vector<Territory*> ownedTerritories; // List of territories owned by the player
    Hand hand; // The player's hand of cards
    OrdersList ordersList; // The list of orders issued by the player
};


