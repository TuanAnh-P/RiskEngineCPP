//#include "Player.h"
//
//Player::Player(const std::string& playerName) : playerName(playerName) {}
//
//void Player::addTerritory(Territory* territory) {
//    territories.push_back(territory);
//}
//
//bool Player::removeTerritory(Territory* territory) {
//    for (int i = 0; i < territories.size(); ++i) {
//        if (territories[i] == territory) {
//            territories.erase(territories.begin() + i);
//            return true; // Territory successfully removed
//        }
//    }
//    return false; // Territory not found
//}
//
//const std::vector<Territory*>& Player::getTerritories() const {
//    return territories;
//}
//
//void Player::addCard(Card* card) {
//    cards.push_back(card);
//}
//
//bool Player::removeCard(Card* card) {
//    for (int i = 0; i < cards.size(); ++i) {
//        if (cards[i] == card) {
//            cards.erase(cards.begin() + i);
//            return true; // Territory successfully removed
//        }
//    }
//    return false; // Territory not found
//}
//
//const std::vector<Card*>& Player::getCards() const {
//    return cards;
//}
//
//void Player::issueOrder(Order* order) {
//    orders.push_back(order);
//}
//
//std::vector<Territory*> Player::toDefend() {
//    // Return an arbitrary list of territories
//    std::vector<Territory*> defendTerritories;
//    return defendTerritories;
//}
//
//std::vector<Territory*> Player::toAttack() {
//    // Return an arbitrary list of territories
//    std::vector<Territory*> attackTerritories;
//    return attackTerritories;
//}
