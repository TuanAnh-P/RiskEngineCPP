#include "Player.h" // Include the header file for the Player class

// Constructor -- GOOD
Player::Player(const std::string& playerName) : playerName(playerName) {
    std::cout << playerName << " has arrived!" << std::endl;
}

// Copy constructor - GOOD
Player::Player(Player &other) {
    // Deep copy owned territories
    for (const Territory* territory : other.ownedTerritories) {
        ownedTerritories.push_back(new Territory(*territory));
    }

    // Deep copy hand and orders list
    hand = new Hand(*other.hand);
    ordersList = new OrdersList(*other.ordersList);
}

// Assignment operator - GOOD
Player &Player::operator=(Player &other) {
    if (this != &other) { // Self-assignment check
        // Delete existing owned territories
        for (Territory* territory : ownedTerritories) {
            delete territory;
        }
        ownedTerritories.clear();

        // Deep copy owned territories
        for (const Territory* territory : other.ownedTerritories) {
            ownedTerritories.push_back(new Territory(*territory));
        }

        // Deep copy hand and orders list
        delete hand;
        delete ordersList;
        hand = new Hand(*other.hand);
        ordersList = new OrdersList(*other.ordersList);

        // Copy playerName
        playerName = other.playerName;
    }
    return *this;
}

// Destructor - GOOD
Player::~Player() {
    // Delete hand and ordersList
    delete hand;
    delete ordersList;
    // Delete owned territories to prevent memory leaks
    for (Territory* territory : ownedTerritories) {
        delete territory;
    }
    ownedTerritories.clear();
    std::cout << "Player " << playerName << " was deleted!" << std::endl;
}

// Add a territory to the player's ownedTerritories or territories to be defended - GOOD
void Player::addTerritory(Territory* territory) {
    ownedTerritories.push_back(territory);
    std::cout << territory->getName() << " was added!" << std::endl;
}

// Get a list of territories to be defended (currently returns all owned territories)
std::vector<Territory*> Player::toDefend() {
    // For now, return all owned territories as an arbitrary choice.
    return ownedTerritories;
}

// Get a list of territories to be attacked (currently returns an empty list)
std::vector<Territory*> Player::toAttack() {
    // For now, return an empty list as an arbitrary choice.
    return std::vector<Territory*>();
}

// Get the player's hand of cards
Hand& Player::getHand(){
    return *hand;
}

// <------------------------------------------------------------------------------------>

// Get the player's list of orders
OrdersList& Player::getOrdersList(){
    return *ordersList;
}

void Player::issueOrder(const std::string& orderType) {
    Order* newOrder = nullptr;

    // Create an Order object based on the orderType
    if (orderType == "Deploy") {
        newOrder = new Deploy(5);
    }
    else if (orderType == "Advance") {
        newOrder = new Advance();
    }
    else if (orderType == "Bomb") {
        newOrder = new Bomb();
    }
    else if (orderType == "Blockade") {
        newOrder = new Blockade();
    }
    else if (orderType == "Airlift") {
        newOrder = new Airlift();
    }
    else if (orderType == "Negotiate") {
        newOrder = new Negotiate();
    }

    if (newOrder) {
        // Add the created order to the player's list of orders
        std::cout << orderType << " was added!" << std::endl;
        ordersList->orders.push_back(newOrder);
    }
    else {
        // Handle unsupported order type or invalid parameters
        std::cout << "Invalid order type." << std::endl;
    }
}

// <------------------------------------------------------------------------------------>

//std::ostream &operator<<(std::ostream &os, Player &player) {
//    return <#initializer#>;
//}

//// Remove a territory from ownedTerritories or territories to be defended
//bool Player::removeTerritory(Territory* territory) {
//    // Find the territory in the list of owned territories
//    auto it = std::find(ownedTerritories.begin(), ownedTerritories.end(), territory);
//
//    if (it != ownedTerritories.end()) {
//        // Territory found, erase it from the list
//        ownedTerritories.erase(it);
//        delete territory; // Delete the removed territory to prevent memory leaks
//        std::cout << territory->getName() << " was deleted!" << std::endl;
//        return true; // Territory successfully removed
//    }
//
//    std::cout << "Could not find the territory!" << std::endl;
//    return false; // Territory not found
//}


