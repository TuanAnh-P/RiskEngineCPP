#include "Player.h"

// Constructor
Player::Player(const std::string& playerID)
        : playerID(new std::string(playerID)), hand(new Hand()), ordersList(new OrdersList()), negotiatedPlayers(new std::vector<Player*>()), reinforcementPool(new int(0)) {
//    std::cout << "Player " << *this->playerID << " has arrived!" << std::endl;
}

// Copy constructor
Player::Player(const Player& other)
        : playerID(new std::string(*other.playerID)), hand(new Hand(*other.hand)), ordersList(new OrdersList(*other.ordersList)), reinforcementPool(new int(*other.reinforcementPool)) {

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

        // Copy reinforcementPool
        delete reinforcementPool;
        reinforcementPool = new int(*other.reinforcementPool);
    }
    return *this;
}

Player::~Player() {
    if (playerID) {
//        std::cout << "Player " << *playerID << " has been deleted!" << std::endl;
        delete playerID;
    }

    // Delete reinforcementPool
    delete reinforcementPool;

    // Delete hand and ordersList
    delete hand;
    delete ordersList;

    // Set the pointers to nullptr after deletion
    playerID = nullptr;
    reinforcementPool = nullptr;
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

// Remove a territory from the player's ownedTerritories
void Player::removeTerritory(Territory* territory) {
    if (ownedTerritories.empty()) { std::cout << "Player does not own any territories!" << std::endl; return;}
    for (size_t i = 0; i < ownedTerritories.size(); i++) {
        if (ownedTerritories[i] == territory) {
            ownedTerritories.erase(ownedTerritories.begin() + i);
            std::cout << "Territory " << territory->getName() << " was removed!" << std::endl;
            return; // Exit the function once the territory is found and removed
        }
    }
    // If the loop completes without finding the territory, it means the player does not own it.
    std::cout << "Error: Attempted to remove a territory that the player does not own." << std::endl;
}

// Custom function to swap two territories
void swapTerritories(Territory*& a, Territory*& b) {
    Territory* temp = a;
    a = b;
    b = temp;
}

// Custom comparison function for sorting territories by decreasing numberOfArmies
bool compareTerritoriesByArmies(const Territory* a, const Territory* b) {
    return a->getNumberOfArmies() > b->getNumberOfArmies();
}

std::vector<Territory*> Player::toDefend() {
    // Sort owned territories by decreasing numberOfArmies (bubble sort)
    int n = ownedTerritories.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (compareTerritoriesByArmies(ownedTerritories[j], ownedTerritories[j + 1])) {
                swapTerritories(ownedTerritories[j], ownedTerritories[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;  // If no two elements were swapped, the array is already sorted
        }
    }
    return ownedTerritories;
}

std::vector<Territory*> Player::toAttack() {
    std::vector<Territory*> toAttack;
    for (Territory* territory : ownedTerritories) {
        std::vector<Territory*> adjacentTerritories = territory->getAdjacentTerritories();

        // Sort adjacent territories by decreasing numberOfArmies (bubble sort)
        int n = adjacentTerritories.size();
        bool swapped;
        for (int i = 0; i < n - 1; i++) {
            swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (compareTerritoriesByArmies(adjacentTerritories[j], adjacentTerritories[j + 1])) {
                    swapTerritories(adjacentTerritories[j], adjacentTerritories[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) {
                break;  // If no two elements were swapped, the array is already sorted
            }
        }

        for (Territory* adjacentTerritory : adjacentTerritories) {
            if (!isTerritoryOwned(adjacentTerritory)) {
                toAttack.push_back(adjacentTerritory);
            }
        }
    }
    return toAttack;
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

void Player::issueOrder(const std::string& orderType, Territory* source, Territory* target, int* num, Player* targetPlayer) {
    Order* newOrder = nullptr;

    if (orderType == "Deploy") newOrder = new Deploy(this, target, num);
    else if (orderType == "Advance") newOrder = new Advance(this, target, source, num);
    else if (orderType == "Bomb") newOrder = new Bomb(this, target);
    else if (orderType == "Blockade") newOrder = new Blockade(this, target);
    else if (orderType == "Airlift") newOrder = new Airlift(this, source, target, num);
    else if (orderType == "Negotiate") newOrder = new Negotiate(this, targetPlayer);

    if (newOrder) {
        // Add the created order to the player's list of orders
        std::cout << this->getPlayerID() << " issued a " << orderType << " order" << std::endl;
        ordersList->orders.push_back(newOrder);
    }
    else std::cout << "Invalid order type." << std::endl;
}

bool Player::isTerritoryOwned(Territory* territory)
{
    if (this->ownedTerritories.empty()) return false;
  
    for (Territory* var : this->ownedTerritories)
    {
        if (var == territory) return true;
    }
    return false;
}

bool Player::isContinentOwned(Continent* continent) {
    std::vector<Territory*>& continentTerritories = const_cast<std::vector<Territory *> &>(continent->getTerritories());
    for (Territory* territory : continentTerritories) {
        if (!isTerritoryOwned(territory)) {
            return false; // Player doesn't own all territories in the continent
        }
    }
    return true; // Player owns all territories in the continent
}

std::string Player::getPlayerID() const {
    return *playerID;
}

const std::vector<Player*>& Player::getNegotiatedPlayers() {
    return *this->negotiatedPlayers;
}

int Player::getReinforcementPool() const {
    return *reinforcementPool;
}

void Player::setReinforcementPool(const int& amount) {
    if (reinforcementPool != nullptr) {
        delete reinforcementPool;
    }
    reinforcementPool = new int(amount);
}

void Player::addReinforcementPool(const int &amount) {
    if (reinforcementPool != nullptr) {
        *reinforcementPool += amount;
    }
}

void Player::removeReinforcementPool(const int &amount) {
    if (reinforcementPool != nullptr) {
        *reinforcementPool -= amount;
        if (*reinforcementPool < 0) {
            // Ensure the reinforcement pool does not go negative.
            *reinforcementPool = 0;
        }
    }
}

void Player::addToNegotiatedPlayers(Player* player)
{
    if (player != NULL && player != this) this->negotiatedPlayers->push_back(player);
    else std::cout << "NULL player pointer or passing self into parameters, cannot add player to negotiated players' list!" << std::endl;
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Player Name: " << *player.playerID << std::endl;
    os << "Owned Territories: " << player.ownedTerritories.size() << " territories" << std::endl;
    os << "Hand Size: " << player.hand->cards.size() << std::endl;
    os << "Orders List Size: " << player.ordersList->orders.size() << std::endl;
    os << "Reinforcement Pool: " << *player.reinforcementPool << std::endl;
    return os;
}



