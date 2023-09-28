#ifndef CARDS_H
#define CARDS_H

#include <vector>
#include <string>
#include <iostream>

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
    Card(CardType type, Deck* deck);
    Card(Card& other); // Copy constructor
    Card& operator=(Card& other); // Assignment operator
    Deck* deck;

    CardType getType();
    //void play(Hand& hand, int index, OrdersList& ordersList);
    void play(Hand& hand, int index);  // Implement this method to create an order and add it to the player's list of orders.

    friend std::ostream& operator<<(std::ostream& os, Card& card); // Stream insertion operator

private:
    CardType type;
};
//------------------------------------------------------------------------------------------------------------------------------
class Deck {
public:
    Deck();
    Deck(Deck& other); // Copy constructor
    Deck& operator=(Deck& other); // Assignment operator

    void draw(Hand& hand);

    friend std::ostream& operator<<(std::ostream& os, Deck& deck); // Stream insertion operator

    std::vector<Card*> cards;
};
//------------------------------------------------------------------------------------------------------------------------------
class Hand {
public:
    Hand();
    Hand(Hand& other); // Copy constructor
    Hand& operator=(Hand& other); // Assignment operator

    friend std::ostream& operator<<(std::ostream& os, Hand& hand); // Stream insertion operator
    std::vector<Card*> cards;
};
//------------------------------------------------------------------------------------------------------------------------------
void testCards();

#endif // CARDS_H
