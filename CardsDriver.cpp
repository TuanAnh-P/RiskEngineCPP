#include "CardsDriver.h"
#include "Cards.h"
#include "Orders.h"

void testCards() {
    Deck* deck1 = new Deck();
    Hand* hand1 = new Hand();
    OrdersList* ordersList1 = new OrdersList();

    int deckSize = deck1->cards.size();
    std::cout << "Deck size: " << deckSize << std::endl;

    int handSize1 = hand1->cards.size();
    std::cout << "Hand size: " << handSize1 << std::endl;

    int orderListSize = ordersList1->orders.size();
    std::cout << "OrdersList size: " << orderListSize << std::endl;

    for (int i = 0; i < 7; i++) {
        deck1->draw(*hand1);
    }

    deckSize = deck1->cards.size();
    std::cout << "Deck size: " << deckSize << std::endl;

    handSize1 = hand1->cards.size();
    std::cout << "Hand size: " << handSize1 << std::endl;

    orderListSize = ordersList1->orders.size();
    std::cout << "OrdersList size: " << orderListSize << std::endl;

    for (int i = 0; i < 7; i++) {
        hand1->cards[0]->play(*hand1, 0, *ordersList1);
        //hand1->cards[0]->play(*hand1, 0);
    }

    deckSize = deck1->cards.size();
    std::cout << "Deck size: " << deckSize << std::endl;

    handSize1 = hand1->cards.size();
    std::cout << "Hand size: " << handSize1 << std::endl;

    orderListSize = ordersList1->orders.size();
    std::cout << "OrdersList size: " << orderListSize << std::endl;

    
    for (Card* card : deck1->cards) {
        delete card;
    }
    deck1->cards.clear();
    
    
    for (Card* card : hand1->cards) {
        delete card;
    }
    hand1->cards.clear();

    for (Order* order : ordersList1->orders) {
        delete order;
    }
    ordersList1->orders.clear();
    

    delete deck1;
    delete hand1;
    delete ordersList1;

}


/*int main()
{
    testCards();
}*/
