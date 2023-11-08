#include "Player.h"
#include <cmath>
using namespace std;

void reinforcementPhase(){

}

// Define the testPlayers function to demonstrate player object features
void testMainGameLoop() {

    // Initializing North America
    Continent* northAmerica = new Continent("northAmerica" , 0);
    Territory* canada = new Territory("canada", 0, 0);
    Territory* usa = new Territory("usa", 0, 0);
    Territory* mexico = new Territory("mexico", 0, 0);
    northAmerica->addTerritory(canada);
    northAmerica->addTerritory(usa);
    northAmerica->addTerritory(mexico);


//    // Printing territories in North America
//    const std::vector<Territory*>& northAmericaTerritories = northAmerica->getTerritories();
//    std::cout << "Territories in northAmerica:" << std::endl;
//    for (const Territory* territory : northAmericaTerritories) {
//        std::cout << territory->getName() << std::endl;
//    }

    // Initializing South America
    Continent* southAmerica = new Continent("southAmerica" , 0);
    Territory* colombia = new Territory("colombia", 0, 0);
    Territory* brazil = new Territory("brazil", 0, 0);
    Territory* argentina = new Territory("argentina", 0, 0);
    southAmerica->addTerritory(colombia);
    southAmerica->addTerritory(brazil);
    southAmerica->addTerritory(argentina);

//    // Printing territories in North America
//    const std::vector<Territory*>& southAmericaTerritories = southAmerica->getTerritories();
//    std::cout << "Territories in northAmerica:" << std::endl;
//    for (const Territory* territory : southAmericaTerritories) {
//        std::cout << territory->getName() << std::endl;
//    }

    // Setting adjacency between territories
    canada->addAdjacentTerritory(usa);
    usa->addAdjacentTerritory(canada);
    usa->addAdjacentTerritory(mexico);
    mexico->addAdjacentTerritory(usa);
    mexico->addAdjacentTerritory(colombia);
    colombia->addAdjacentTerritory(mexico);
    colombia->addAdjacentTerritory(brazil);
    brazil->addAdjacentTerritory(colombia);
    brazil->addAdjacentTerritory(argentina);
    argentina->addAdjacentTerritory(brazil);

//    // Testing adjacency territories
//    const std::vector<Territory*>& territoriesAdjacentToUSA = usa->getAdjacentTerritories();
//    std::cout << "Territories adjacent to USA:" << std::endl;
//    for (const Territory* territory : territoriesAdjacentToUSA) {
//        std::cout << territory->getName() << std::endl;
//    }
//    // Testing adjacency territories
//    const std::vector<Territory*>& territoriesAdjacentToColombia = colombia->getAdjacentTerritories();
//    std::cout << "Territories adjacent to Colombia:" << std::endl;
//    for (const Territory* territory : territoriesAdjacentToColombia) {
//        std::cout << territory->getName() << std::endl;
//    }

    // Initializing players
    Player* player1 = new Player("John");
    player1->addTerritory(canada);
    player1->addTerritory(usa);
    player1->addTerritory(mexico);
    Player* player2 = new Player("Jose");
    player2->addTerritory(colombia);
    player2->addTerritory(brazil);
    player2->addTerritory(argentina);
    std::vector<Player*> playerList;
    playerList.push_back(player1);
    playerList.push_back(player2);

    int bonusNorthAmerica = 15;
    int bonusSouthAmerica = 10;

//    cout << player1->isContinentOwned(northAmerica) << endl;
//    cout << player1->isTerritoryOwned(canada) << endl;
//    cout << player1->isTerritoryOwned(colombia) << endl;

    std::cout << "Reinforcement phase: " << std::endl;
    for (Player* player : playerList) {
        int numArmyUnits = std::floor(static_cast<double>(player->getOwnedTerritories().size()) / 3);
        int continentOwned = 0;
        if(player->isContinentOwned(northAmerica)){
            continentOwned++;
            numArmyUnits += bonusNorthAmerica;
        }
        if(player->isContinentOwned(southAmerica)){
            continentOwned++;
            numArmyUnits += bonusSouthAmerica;
        }
        std::cout << "Player " << player->getPlayerID() << " owns " << player->getOwnedTerritories().size() << " territory, " << continentOwned << " continent and gets " << numArmyUnits << " army units." << std::endl;
    }

//    std::cout << "Printing the players stats: " << std::endl;
//    for (Player* player : playerList) {
//        cout << *player << endl;
//    }







//    // Create a player with the name "John"
//    std::cout << "<----------Creating Player---------->" << std::endl;
//    Player* player = new Player("John");
//
//    // Add territories to the player's owned territories
//    std::cout << "<----------Adding Territories---------->" << std::endl;
//    Territory* territory1 = new Territory("New York", 1, 2);
//    Territory* territory2 = new Territory("London", 3, 4);
//    player->addTerritory(territory1);
//    player->addTerritory(territory2);
//
//    // Get the territories to defend (initially, it returns all owned territories)
//    std::vector<Territory*> territoriesToDefend = player->toDefend();
//
//    // Display the territories to defend
//    std::cout << "<----------Displaying Territories To Defend---------->" << std::endl;
//    std::cout << "Territories to Defend: ";
//    for (const Territory* territory : territoriesToDefend) {
//        std::cout << territory->getName() << " - ";
//    }
//    std::cout << std::endl;
//
//    // Get the territories to attack (initially, it returns an empty list)
//    std::vector<Territory*> territoriesToAttack = player->toAttack();
//
//    // Display the territories to attack
//    std::cout << "<----------Displaying Territories To Attack---------->" << std::endl;
//    std::cout << "Territories to Attack: ";
//    for (const Territory* territory : territoriesToAttack) {
//        std::cout << territory->getName() << ", ";
//    }
//    std::cout << std::endl;
//
//    // Get the player's orders list
//    OrdersList& playerOrders = player->getOrdersList();
//
//    // Issue some orders
//    std::cout << "<----------Issuing Orders---------->" << std::endl;
//    player->issueOrder("Airlift");
//    player->issueOrder("Bomb");
//
//    // Display the player's orders list
//    std::cout << "<----------Displaying Orders List---------->" << std::endl;
//    playerOrders.print();
//
//    // Testing reinforcementPool
//    std::cout << "<----------Number of reinforcement pool---------->" << std::endl;
//    player->setReinforcementPool(50);
//    player->addReinforcementPool(100);
//    player->removeReinforcementPool(40);
//    std::cout << player->getReinforcementPool() << std::endl;
//
//    // Testing if a territory is owned by the player
//    std::cout << "<----------Does the player own this territory---------->" << std::endl;
//    std::cout << player->isTerritoryOwned(territory1) << std::endl;
//    Territory* territory3 = new Territory("LA", 6, 7);
//    std::cout << player->isTerritoryOwned(territory3) << std::endl;
//
//    //Use the custom operator<< to print player details
//    std::cout << "<----------Player's Stats---------->" << std::endl;
//    std::cout << *player << std::endl;
//
//    // Clean up the player to prevent memory leaks
//    std::cout << "<----------Deleting Player---------->" << std::endl;
//    delete player;
}

int main() {
    // Call the testPlayers function to demonstrate player object features
    testMainGameLoop();
    return 0;
}