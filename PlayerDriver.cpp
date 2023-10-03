// PlayerDriver.cpp

#include "Player.h"

// Define the testPlayers function to demonstrate player object features
void testPlayers() {
    // Create a player with the name "Player 1"
    Player player("Player 1");

    // Create some territories
    Territory* territory1 = new Territory("Territory 1", 1, 2);
    Territory* territory2 = new Territory("Territory 2", 3, 4);

    // Add territories to the player's owned territories
    player.addTerritory(territory1);
    player.addTerritory(territory2);

    // Get the territories to defend (initially, it returns all owned territories)
    std::vector<Territory*> territoriesToDefend = player.toDefend();

    // Display the territories to defend
    std::cout << "Territories to Defend: ";
    for (const Territory* territory : territoriesToDefend) {
        std::cout << territory->getName() << "\t";
    }
    std::cout << std::endl;

    // Get the territories to attack (initially, it returns an empty list)
    std::vector<Territory*> territoriesToAttack = player.toAttack();

    // Display the territories to attack
    std::cout << "Territories to Attack: ";
    for (const Territory* territory : territoriesToAttack) {
        std::cout << territory->getName() << "\t";
    }
    std::cout << std::endl;

    // Issue some orders
    player.issueOrder("Deploy");   // Example: Deploy troops to a territory
    player.issueOrder("Advance");  // Example: Advance troops to a neighboring territory

    // Access and test the player's hand
    Hand& playerHand = player.getHand();
    playerHand.cards.size();

    // Access and test the player's orders list
    OrdersList& playerOrders = player.getOrdersList();
    playerOrders.print();

    // Clean up manually by deleting territories to prevent memory leaks
    delete territory1;
    delete territory2;
}

//int main() {
//    // Call the testPlayers function to demonstrate player object features
//    testPlayers();
//
//    return 0;
//}





