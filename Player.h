#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
// #include <Territory.h>
// #include <Card.h>
// #include <OrdersList.h>

using namespace std;

class Player {

public:
    Player(string &playerName, vector<&Territory> territoriesList, vector<&Card> handOfCards, OrdersList &ordersList);
    void issueOrder();
    vector<Territory*> toDefend();
    vector<Territory*> toAttack();

private:
    string *playerName;
    vector<Territory*> territoriesList;
    vector<Card*> handOfCards;
    OrdersList *ordersList;

};

#endif PLAYER_H
