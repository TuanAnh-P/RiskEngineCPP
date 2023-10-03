// PlayerDriver.cpp

#include "Player.h"

// Define the testPlayers function to demonstrate player object features
void testPlayers() {
    // Create a player with the name "John" - GOOD
    Player* player = new Player("John");

    // Create some territories - GOOD
    Territory* territory1 = new Territory("Territory 1", 1, 2);
    Territory* territory2 = new Territory("Territory 2", 3, 4);

    // Add territories to the player's owned territories - GOOD
    player->addTerritory(territory1);
    player->addTerritory(territory2);

    // Get the territories to defend (initially, it returns all owned territories) - GOOD
    std::vector<Territory*> territoriesToDefend = player->toDefend();

    // Display the territories to defend - GOOD
    std::cout << "Territories to Defend: ";
    for (const Territory* territory : territoriesToDefend) {
        std::cout << territory->getName() << "\t";
    }
    std::cout << std::endl;

    // Get the territories to attack (initially, it returns an empty list) - GOOD
    std::vector<Territory*> territoriesToAttack = player->toAttack();

    // Display the territories to attack - GOOD
    std::cout << "Territories to Attack: ";
    for (const Territory* territory : territoriesToAttack) {
        std::cout << territory->getName() << "\t";
    }
    std::cout << std::endl;

    // <------------------------------------------------------------------------------------>

    // Issue some orders
    player->issueOrder("Airlift");  // Example: Advance troops to a neighboring territory

    // Get the player's orders list
    OrdersList& playerOrders = player->getOrdersList();

    // Display the player's orders list
    playerOrders.print();

    // <------------------------------------------------------------------------------------>

    // Clean up manually by deleting territories and the player to prevent memory leaks
    delete territory1;
    delete territory2;
    delete player;
}

//int main() {
//    // Call the testPlayers function to demonstrate player object features
//    testPlayers();
//    std::cout << "Break point" << std::endl;
//
//    return 0;
//}





