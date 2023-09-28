// Cards.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Cards.h"
#include "Orders.cpp"
#include <cstdlib>

//---------------------------------------------------CARD---------------------------------------------------------------------------
// Constructor
Card::Card(CardType type, Deck* deck) : type(type), deck(deck) {}

// Copy constructor
Card::Card(Card& other) : type(other.type), deck(other.deck) {}

// Assignment operator
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

//void Card::play(Hand& hand, int index, OrdersList& ordersList) {
void Card::play(Hand& hand, int index) {
    // Check if the index is valid
    if (index >= 0 && index < hand.cards.size()) {
        
        Card* playedCard = hand.cards[index];

        if (deck != nullptr) {
            deck->cards.push_back(playedCard);
        }



        /*
        Order* newOrder = nullptr;
        switch (playedCard->getType()) {
        case CardType::Bomb:
            newOrder = new Bomb();
            ordersList.move(newOrder, ordersList.orders.size() - 1);
            break;
        case CardType::Reinforcement:
            //newOrder = new Reinforcement();
            //ordersList.move(newOrder, ordersList.orders.size() - 1);
            break;
        case CardType::Blockade:
            newOrder = new Blockade();
            ordersList.move(newOrder, ordersList.orders.size() - 1);
            break;
        case CardType::Airlift:
            newOrder = new Airlift();
            ordersList.move(newOrder, ordersList.orders.size() - 1);
            break;
        case CardType::Diplomacy:
            //newOrder = new Diplomacy();
            //ordersList.move(newOrder, ordersList.orders.size() - 1);
            break;
        default:
            
            break;
        }
        std::cout << *playedCard << " was played." << std::endl;
        */
        std::cout << *playedCard << " was played." << std::endl;




        hand.cards[index] = nullptr;
        delete hand.cards[index];

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
        CardType randomType = static_cast<CardType>(rand() % static_cast<int>(CardType::Diplomacy) + 1); // Generate a random CardType
        Card* newCard = new Card(randomType, this); // Create a new Card with random type and the current deck pointer
        cards.push_back(newCard); // Add the new card to the deck
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
        return *this; // Self-assignment, no need to do anything
    }

    // Clear the current cards
    for (Card* card : cards) {
        card = NULL;
        delete card;
    }
    cards.clear();

    // Perform a deep copy of the cards
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

void Deck::draw(Hand& hand) {
    if (cards.empty()) {
        std::cout << "Deck is empty" << std::endl;
        return;
    }
    Card* drawn = new Card(*cards.front());
    hand.cards.push_back(drawn);
    cards[0] = NULL;
    delete cards[0];
    cards.erase(cards.begin());
}

//-----------------------------------------------------HAND-------------------------------------------------------------------------
// Constructor
Hand::Hand() {

}

// Copy Constructor
Hand::Hand(Hand& other) {
    // Copy the contents of 'other' to this 'Hand'
    for (Card* card : other.cards) {
        // Assuming Card has a copy constructor, if not, you might need to implement it.
        this->cards.push_back(new Card(*card));
    }
}

// Assignment operator
Hand& Hand::operator=(Hand& other) {
    if (this == &other) {
        return *this; // Self-assignment, no need to do anything
    }

    // Clear the current contents of this 'Hand'
    for (Card* card : cards) {
        card = NULL;
        delete card;
    }
    cards.clear();

    // Copy the contents of 'other' to this 'Hand'
    for (Card* card : other.cards) {
        this->cards.push_back(new Card(*card));
    }

    return *this;
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, Hand& hand) {
    os << "Hand Contents: \n";
    for (Card* card : hand.cards) {
        os << *card << std::endl; // Assuming Card has an overload for the << operator
    }
    return os;
}

//------------------------------------------------------------------------------------------------------------------------------
void testCards() {
    Deck* deck1 = new Deck();
    Hand* hand1 = new Hand();
    //OrdersList* ordersList1 = new OrdersList();

    int deckSize = deck1->cards.size();
    std::cout << "Deck size: " << deckSize << std::endl;

    int handSize1 = hand1->cards.size();
    std::cout << "Hand size: " << handSize1 << std::endl;

    /*
    int orderListSize = ordersList1->orders.size();
    std::cout << "OrdersList size: " << orderListSize << std::endl;
    */

    for (int i = 0; i < 7; i++) {
        deck1->draw(*hand1);
    }

    deckSize = deck1->cards.size();
    std::cout << "Deck size: " << deckSize << std::endl;

    handSize1 = hand1->cards.size();
    std::cout << "Hand size: " << handSize1 << std::endl;

    for (int i = 0; i < 7; i++) {
        //hand1->cards[0]->play(*hand1, 0, *ordersList1);
        hand1->cards[0]->play(*hand1, 0);
    }

    deckSize = deck1->cards.size();
    std::cout << "Deck size: " << deckSize << std::endl;

    handSize1 = hand1->cards.size();
    std::cout << "Hand size: " << handSize1 << std::endl;

    for (Card* card : deck1->cards) {
        delete card;
    }
    deck1->cards.clear();

    for (Card* card : hand1->cards) {
        delete card;
    }
    hand1->cards.clear();

    /*
    for (Order* order : ordersList1->orders) {
        delete order;
    }
    ordersList1->orders.clear();
    */

    delete deck1;
    delete hand1;
    //delete ordersList1;
}


int main()
{
    testCards();
}
