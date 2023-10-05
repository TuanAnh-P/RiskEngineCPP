#include "Player.h"

// Constructor
Player::Player(const std::string& playerName)
        : playerName(playerName), hand(new Hand()), ordersList(new OrdersList()) {
    std::cout << "Player " << playerName << " has arrived!" << std::endl;
}

// Copy constructor
Player::Player(const Player& other)
        : playerName(other.playerName), hand(new Hand(*other.hand)), ordersList(new OrdersList(*other.ordersList)) {
    for (const Territory* territory : other.ownedTerritories) {
        ownedTerritories.push_back(new Territory(*territory));
    }
}

// Assignment operator
Player& Player::operator=(const Player& other) {
    if (this != &other) { // Self-assignment check
        // Clear existing owned territories
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

// Destructor
Player::~Player() {
    std::cout << "Player " << playerName << " has been deleted!" << std::endl;

    // Delete hand and ordersList
    delete hand;
    delete ordersList;

    // Delete owned territories to prevent memory leaks
    for (Territory* territory : ownedTerritories) {
        delete territory;
    }
    ownedTerritories.clear();
}

// Add a territory to the player's ownedTerritories or territories to be defended
void Player::addTerritory(Territory* territory) {
    ownedTerritories.push_back(territory);
    std::cout << "Territory " << territory->getName() << " was added!" << std::endl;
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
Hand& Player::getHand() {
    return *hand;
}

// Get the player's list of orders
OrdersList& Player::getOrdersList() {
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
        std::cout << "Order " << orderType << " was added to the list of orders!" << std::endl;
        ordersList->orders.push_back(newOrder);
    }
    else {
        // Handle unsupported order type or invalid parameters
        std::cout << "Invalid order type." << std::endl;
    }
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Player Name: " << player.playerName << std::endl;
    os << "Owned Territories: " << player.ownedTerritories.size() << " territories" << std::endl;
    os << "Hand Size: " << player.hand->cards.size() << std::endl;
    os << "Orders List Size: " << player.ordersList->orders.size() << std::endl;
    return os;
}


