#include "Player.h"

// Constructor implementation
Player::Player(string &playerName, vector<&Territory> territoriesList, vector<&Card> handOfCards, OrdersList &ordersList) {
    this->playerName = &playerName;
    this->territoriesList = territoriesList;
    this->handOfCards = handOfCards;
    this->ordersList = &ordersList;
}

void Player::issueOrder() {
    
}

vector<Territory*> Player::toDefend() {
    vector<Territory*> territoriesToDefend;
    return territoriesToDefend;
}

vector<Territory*> Player::toAttack() {
    vector<Territory*> territoriesToAttack;
    return territoriesToAttack;
}

