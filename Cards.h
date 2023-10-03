#ifndef CARDS_H
#define CARDS_H

#include <vector>
#include <string>
#include <iostream>
#include "Orders.h"

class Deck;
class Hand;
class Card;
//------------------------------------------------------------------------------------------------------------------------------
enum class CardType {
    Bomb,
    Reinforcement,
    Blockade,
    Airlift,
    Diplomacy
};
//------------------------------------------------------------------------------------------------------------------------------
class Card {
public:
    Card(CardType type, Deck* deck); // Contructor
    Card(Card& other); // Copy constructor
    Card& operator=(Card& other); // Assignment operator
    Deck* deck;

    CardType getType();
    void play(Hand& hand, int index, OrdersList& ordersList);

    friend std::ostream& operator<<(std::ostream& os, Card& card); // Stream insertion operator

private:
    CardType type;
};
//------------------------------------------------------------------------------------------------------------------------------
class Deck {
public:
    Deck(); // Contructor
    Deck(Deck& other); // Copy constructor
    Deck& operator=(Deck& other); // Assignment operator

    void draw(Hand& hand);

    friend std::ostream& operator<<(std::ostream& os, Deck& deck); // Stream insertion operator

    std::vector<Card*> cards;
};
//------------------------------------------------------------------------------------------------------------------------------
class Hand {
public:
    Hand(); // Contructor
    Hand(Hand& other); // Copy constructor
    Hand& operator=(Hand& other); // Assignment operator

    friend std::ostream& operator<<(std::ostream& os, Hand& hand); // Stream insertion operator

    std::vector<Card*> cards;
};
//------------------------------------------------------------------------------------------------------------------------------
#endif // CARDS_H
