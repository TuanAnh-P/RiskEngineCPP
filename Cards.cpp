#include "Cards.h"
#include "Orders.h"
#include <cstdlib>

//---------------------------------------------------CARD---------------------------------------------------------------------------
// Constructor (shallow on purpose)
Card::Card(CardType type, Deck* deck) : type(type), deck(deck) {}

// Copy constructor (shallow on purpose)
Card::Card(Card& other) : type(other.type), deck(other.deck) {}

// Assignment operator (shallow on purpose)
Card& Card::operator=(Card& other) {
    if (this != &other) {
        type = other.type;
        deck = other.deck;
    }
    return *this;
}

// Type getter
CardType Card::getType() {
    return type;
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, Card& card) {
    switch (card.getType()) {
        case CardType::Bomb:
            os << "Card Type: " << "Bomb";
            break;
        case CardType::Reinforcement:
            os << "Card Type: " << "Reinforcement";
            break;
        case CardType::Blockade:
            os << "Card Type: " << "Blockade";
            break;
        case CardType::Airlift:
            os << "Card Type: " << "Airlift";
            break;
        case CardType::Diplomacy:
            os << "Card Type: " << "Diplomacy";
            break;
        default:
            os << "Card Type: " << "Unknown" << std::endl;
            break;
        }
    return os;
}

// Creates order and adds it to orderlist. Card is then put back into the deck.
void Card::play(Hand& hand, int index, OrdersList& ordersList) {
    if (index >= 0 && index < hand.cards.size()) {
        
        Card* playedCard = hand.cards[index];//put card back in deck before removing from hand from 

        if (deck != nullptr) {
            deck->cards.push_back(playedCard);
        }

        switch (playedCard->getType()) {//create order and put into orderlist
        case CardType::Bomb:{
            Bomb* newOrder = new Bomb();
            ordersList.orders.push_back(newOrder);
            break;
        }
        case CardType::Reinforcement: {
            //newOrder = new Reinforcement();
            //ordersList.orders.push_back(newOrder);
            break;
        }
        case CardType::Blockade: {
            Blockade* newOrder = new Blockade();
            ordersList.orders.push_back(newOrder);
            break;
        }
        case CardType::Airlift: {
            Airlift* newOrder = new Airlift();
            ordersList.orders.push_back(newOrder);
            break;
        }
        case CardType::Diplomacy: {
            //newOrder = new Diplomacy();
            //ordersList.orders.push_back(newOrder);
            break;
        }
        default:
            break;
        }


        std::cout << *playedCard << " was played." << std::endl;

        hand.cards[index] = nullptr;
        hand.cards.erase(hand.cards.begin() + index);

    }
    else {
        std::cout << "Invalid index." << std::endl;
    }
}

//---------------------------------------------------DECK---------------------------------------------------------------------------
// Constructor
Deck::Deck() {
    for (int i = 0; i < 20; i++) {
        CardType randomType = static_cast<CardType>(rand() % static_cast<int>(CardType::Diplomacy) + 1); // random CardType
        Card* newCard = new Card(randomType, this); // create the card
        cards.push_back(newCard); // add card to deck
    }
}

// Copy constructor
Deck::Deck(Deck& other) {
    for (Card* card : other.cards) {
        this->cards.push_back(new Card(*card));
    }
}

// Assignment operator
Deck& Deck::operator=(Deck & other) {
    if (this == &other) {
        return *this;
    }

    // Clear cards
    for (Card* card : cards) {
        card = NULL;
        delete card;
    }
    cards.clear();

    // Deep copy of the cards
    for (Card* card : other.cards) {
        this->cards.push_back(new Card(*card));
    }

    return *this;
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, Deck& deck) {
    os << "Deck Contents: \n";
    for (Card* card : deck.cards) {
        os << *card << std::endl;
    }
    return os;
}

// Put card from deck to hand
void Deck::draw(Hand& hand) {
    if (cards.empty()) {//deck is empty
        std::cout << "Deck is empty" << std::endl;
        return;
    }
    Card* drawn = new Card(*cards.front());
    hand.cards.push_back(drawn);//add card to hand before removing from deck
    delete cards[0];
    cards[0] = NULL;
    cards.erase(cards.begin());
}

//-----------------------------------------------------HAND-------------------------------------------------------------------------
// Constructor
Hand::Hand() {

}

// Copy Constructor
Hand::Hand(Hand& other) {
    for (Card* card : other.cards) {
        this->cards.push_back(new Card(*card));
    }
}

// Assignment operator
Hand& Hand::operator=(Hand& other) {
    if (this == &other) {
        return *this;
    }

    // Clear hand cards
    for (Card* card : cards) {
        card = NULL;
        delete card;
    }
    cards.clear();

    // Deep copy
    for (Card* card : other.cards) {
        this->cards.push_back(new Card(*card));
    }

    return *this;
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, Hand& hand) {
    os << "Hand Contents: \n";
    for (Card* card : hand.cards) {
        os << *card << std::endl;
    }
    return os;
}
