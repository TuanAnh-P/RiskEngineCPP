#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Territory.h"
#include "Order.h"
#include "Card.h"

class Player {
public:
    Player(const std::string& playerName);

    // Methods to manage territories
    void addTerritory(Territory* territory);
    bool removeTerritory(Territory* territory);
    const std::vector<Territory*>& getTerritories() const;

    // Methods to manage cards
    void addCard(Card* card);
    bool removeCard(Card* card);
    const std::vector<Card*>& getCards() const;

    // Methods for issuing orders
    void issueOrder(Order* order);

    // Methods to decide which territories to defend and attack
    std::vector<Territory*> toDefend();
    std::vector<Territory*> toAttack();

private:
    std::string playerName;
    std::vector<Territory*> territories;
    std::vector<Card*> cards;
    std::vector<Order*> orders;
};

#endif
