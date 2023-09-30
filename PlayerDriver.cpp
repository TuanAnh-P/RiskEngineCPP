#include "Player.h"

int main() {
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

    // Get the territories to attack (initially, it returns an empty list)
    std::vector<Territory*> territoriesToAttack = player.toAttack();

    // Issue some orders
    player.issueOrder("Deploy");   // Example: Deploy troops to a territory
    player.issueOrder("Advance");  // Example: Advance troops to a neighboring territory

    // Access and test the player's hand
    const Hand& playerHand = player.getHand();
    playerHand.print();

    // Access and test the player's orders list
    const OrdersList& playerOrders = player.getOrdersList();
    playerOrders.print();

    // Clean up manually by deleting territories to prevent memory leaks
    delete territory1;
    delete territory2;

    return 0;
}




