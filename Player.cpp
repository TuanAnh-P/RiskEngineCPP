#include "Player.h"

// Constructor
Player::Player(const std::string& playerID)
        : playerID(new std::string(playerID)), hand(new Hand()), ordersList(new OrdersList()), negotiatedPlayers(new std::vector<Player*>()) {
    std::cout << "Player " << *this->playerID << " has arrived!" << std::endl;
}

// Copy constructor
Player::Player(const Player& other)
        : playerID(new std::string(*other.playerID)), hand(new Hand(*other.hand)), ordersList(new OrdersList(*other.ordersList)) {

    // Deep copy owned territories
    for (const Territory* territory : other.ownedTerritories) {
        ownedTerritories.push_back(new Territory(*territory));
    }

    // Deep copy negotiated players
    negotiatedPlayers = new std::vector<Player*>;
    for (const Player* player : *other.negotiatedPlayers) {
        negotiatedPlayers->push_back(new Player(*player));
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
        delete negotiatedPlayers;

        hand = new Hand(*other.hand);
        ordersList = new OrdersList(*other.ordersList);
        negotiatedPlayers = new std::vector<Player*>(*other.negotiatedPlayers);

        // Copy playerID
        delete playerID;
        playerID = new std::string(*other.playerID);
    }
    return *this;
}

Player::~Player() {
    if (playerID) {
        std::cout << "Player " << *playerID << " has been deleted!" << std::endl;
        delete playerID;
    }

    // Delete hand and ordersList
    delete hand;
    delete ordersList;

    // Set the pointers to nullptr after deletion
    playerID = nullptr;
    hand = nullptr;
    ordersList = nullptr;

    // Delete negotiatedPlayers and set the pointer to nullptr
    if (negotiatedPlayers) {
        for (Player* player : *negotiatedPlayers) {
            delete player;
        }
        delete negotiatedPlayers;
        negotiatedPlayers = nullptr;
    }

    // Delete owned territories to prevent memory leaks
    for (Territory* territory : ownedTerritories) {
        delete territory;
    }
    ownedTerritories.clear(); // Handle dangling pointers
}


// Add a territory to the player's ownedTerritories or territories to be defended
void Player::addTerritory(Territory* territory) {
    if (territory) {
        ownedTerritories.push_back(territory);
        std::cout << "Territory " << territory->getName() << " was added!" << std::endl;
    } else {
        std::cout << "Error: Attempted to add a null territory." << std::endl;
    }
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

// Get the list of owned territories
std::vector<Territory*> Player::getOwnedTerritories()
{
    return this->ownedTerritories;
}

void Player::issueOrder(const std::string& orderType) {
    Order* newOrder = nullptr;
    
    Territory* temp = new Territory("TEST", 0, 0); 
    

    // Create an Order object based on the orderType
    if (orderType == "Deploy") {
        // Take user input (Colton)
        newOrder = new Deploy(this, this->ownedTerritories[0], new int(10));
    }
    else if (orderType == "Advance") 
    {
        newOrder = new Advance(this, this->ownedTerritories[0], this->ownedTerritories[1], new int(10));
    }
    else if (orderType == "Bomb") {
        // Take user input (Colton)
        newOrder = new Bomb(this, temp);
    }
    else if (orderType == "Blockade") {
        newOrder = new Blockade(this, this->ownedTerritories[0]);
    }
    else if (orderType == "Airlift") {

        newOrder = new Airlift(this, this->ownedTerritories[0], this->ownedTerritories[1], new int(10));
    }
    else if (orderType == "Negotiate") {
        Player* player = new Player("TEMP_Player"); // TEMP
        newOrder = new Negotiate(this, player);
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

bool Player::isTerritoryOwned(Territory* territory)
{
    for (Territory* var : this->ownedTerritories)
    {
        if (var == territory)
        {
            return true;

        }

    }

    return false;

}

const std::string & Player::getPlayerID()
{
    return *playerID;
}



const std::vector<Player*>& Player::getNegotiatedPlayers()
{
    return *this->negotiatedPlayers;
}

void Player::addToNegotiatedPlayers(Player* player)
{
    if (player != NULL && player != this) this->negotiatedPlayers->push_back(player);
    else std::cout << "NULL player pointer or passing self into parameters, cannot add player to negotiated players' list!" << std::endl;
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Player Name: " << player.playerID << std::endl;
    os << "Owned Territories: " << player.ownedTerritories.size() << " territories" << std::endl;
    os << "Hand Size: " << player.hand->cards.size() << std::endl;
    os << "Orders List Size: " << player.ordersList->orders.size() << std::endl;
    return os;
}



