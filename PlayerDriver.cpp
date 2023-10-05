#include "Player.h"

// Define the testPlayers function to demonstrate player object features
void testPlayers() {
    // Create a player with the name "John"
    Player* player = new Player("John");

    // Add territories to the player's owned territories
    player->addTerritory(new Territory("New York", 1, 2));
    player->addTerritory(new Territory("London", 3, 4));

    // Get the territories to defend (initially, it returns all owned territories)
    std::vector<Territory*> territoriesToDefend = player->toDefend();

    // Display the territories to defend
    std::cout << "Territories to Defend: ";
    for (const Territory* territory : territoriesToDefend) {
        std::cout << territory->getName() << " - ";
    }
    std::cout << std::endl;

    // Get the territories to attack (initially, it returns an empty list)
    std::vector<Territory*> territoriesToAttack = player->toAttack();

    // Display the territories to attack
    std::cout << "Territories to Attack: ";
    for (const Territory* territory : territoriesToAttack) {
        std::cout << territory->getName() << ", ";
    }
    std::cout << std::endl;

    // Get the player's orders list
    OrdersList& playerOrders = player->getOrdersList();

    // Issue some orders
    player->issueOrder("Airlift");
    player->issueOrder("Bomb");

    // Display the player's orders list
    std::cout << "Displaying player's orders list:" << std::endl;
    playerOrders.print();

    //Use the custom operator<< to print player details
    std::cout << player << std::endl;

    // Clean up the player to prevent memory leaks
    delete player;
}

//int main() {
//    // Call the testPlayers function to demonstrate player object features
//    testPlayers();
//
//    return 0;
//}





