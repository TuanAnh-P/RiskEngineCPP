#include <iostream>
#include "Player.h"
#include "PlayerStrategies.h"
#include "GameEngine.h"

// Test Player Strategies free test function
void testPlayerStrategies()
{
	// Create instance of strategy
	/*NeutralPlayerStrategy* neutralStrat = new NeutralPlayerStrategy();
	HumanPlayerStrategy* humanStrat = new HumanPlayerStrategy();
	AggressivePlayerStrategy* aggroStrat = new AggressivePlayerStrategy();*/

	// Assignment operator test
	//*aggroStrat = *humanStrat;


	//delete(neutralStrat);
	//delete(humanStrat);
	//delete(aggroStrat);

	//Player* player = new Player("John", StrategyType::AggressivePlayer);
	//Player* player2 = new Player("Sue", StrategyType::NeutralPlayer);
	//
	//Player player3(*player2);

	//player2 = player;

	//// Test switch strategy
	//std::cout << player->getStrategy() << std::endl;
	//player->setPlayerStrategy(new HumanPlayerStrategy(player));
	//std::cout << *player->getStrategy() << std::endl;	

	//std::cout << *player2->getStrategy() << std::endl;
	//std::cout << *player3.getStrategy() << std::endl;


    // Create the game engine
    std::unique_ptr<GameEngine> game(new GameEngine());

    // Initializing North America
    Continent* northAmerica = new Continent("northAmerica", 5);
    Territory* usa = new Territory("usa", 0, 0);
    usa->setNumberOfArmies(0);
    Territory* mexico = new Territory("mexico", 0, 0);
    mexico->setNumberOfArmies(0);
    northAmerica->addTerritory(usa);
    northAmerica->addTerritory(mexico);

    // Initializing South America
    Continent* southAmerica = new Continent("southAmerica", 10);
    Territory* colombia = new Territory("colombia", 0, 0);
    colombia->setNumberOfArmies(0);
    Territory* brazil = new Territory("brazil", 0, 0);
    brazil->setNumberOfArmies(0);
    southAmerica->addTerritory(colombia);
    southAmerica->addTerritory(brazil);

    // Setting adjacency between territories
    usa->addAdjacentTerritory(mexico);
    mexico->addAdjacentTerritory(usa);
    mexico->addAdjacentTerritory(colombia);
    colombia->addAdjacentTerritory(mexico);
    colombia->addAdjacentTerritory(brazil);
    brazil->addAdjacentTerritory(colombia);

    // Initializing temporary map
    Map* map = new Map("test", "test", "test", "test", true, true);
    map->addTerritory(usa);
    map->addTerritory(mexico);
    map->addTerritory(colombia);
    map->addTerritory(brazil);
    map->addContinent(northAmerica);
    map->addContinent(southAmerica);
    game->gameMap = map;

    // Initializing players for each Strategy
    Player* aggressive_Player = new Player("AGGRO_PLAYER", StrategyType::AggressivePlayer);
    Player* benevolent_Player = new Player("BENE_PLAYER", StrategyType::BenevolentPlayer);
    Player* neutral_Player = new Player("NEUT_PLAYER", StrategyType::NeutralPlayer);
    Player* cheater_Player = new Player("CHEAT_PLAYER", StrategyType::CheaterPlayer);
    Player* human_Player = new Player("HUMAN_PLAYER", StrategyType::HumanPlayer);

    //  -----------------------  Game 1   -----------------------  // 

    std::vector<Player*> playerList;
    playerList.push_back(aggressive_Player);
    playerList.push_back(benevolent_Player);
    game->players = playerList;

    // Manually assigning territories to players
    aggressive_Player->addTerritory(usa);
    aggressive_Player->addTerritory(mexico);
    benevolent_Player->addTerritory(colombia);
    benevolent_Player->addTerritory(brazil);

    // Manually setting reinforcement pool to 50 for each player
    aggressive_Player->setReinforcementPool(50);
    benevolent_Player->setReinforcementPool(50);

    // Manually drawing 2 cards for each player
    game->deck = new Deck();
    game->deck->draw(aggressive_Player->getHand());
    game->deck->draw(aggressive_Player->getHand());
    game->deck->draw(benevolent_Player->getHand());
    game->deck->draw(benevolent_Player->getHand());

    // Start game loop
    game->mainGameLoop(5);

    // Reset the player list and territories 
    playerList.clear();
    usa->setNumberOfArmies(0);
    mexico->setNumberOfArmies(0);
    colombia->setNumberOfArmies(0);
    brazil->setNumberOfArmies(0);


    //  -----------------------  Game 2   -----------------------  // 

    playerList.push_back(neutral_Player);
    playerList.push_back(cheater_Player);
    game->players = playerList;

    neutral_Player->addTerritory(usa);
    neutral_Player->addTerritory(mexico);
    cheater_Player->addTerritory(colombia);
    cheater_Player->addTerritory(brazil);

    // Manually setting reinforcement pool to 50 for each player
    neutral_Player->setReinforcementPool(50);
    cheater_Player->setReinforcementPool(50);

    // Manually drawing 2 cards for each player
    game->deck = new Deck();
    game->deck->draw(neutral_Player->getHand());
    game->deck->draw(neutral_Player->getHand());
    game->deck->draw(cheater_Player->getHand());
    game->deck->draw(cheater_Player->getHand());

    // Start game loop
    game->mainGameLoop(5);

    playerList.clear();
    usa->setNumberOfArmies(0);
    mexico->setNumberOfArmies(0);
    colombia->setNumberOfArmies(0);
    brazil->setNumberOfArmies(0);

    //  -----------------------  Game 3   -----------------------  // 

    playerList.push_back(neutral_Player);
    playerList.push_back(aggressive_Player);
    game->players = playerList;

    neutral_Player->addTerritory(usa);
    neutral_Player->addTerritory(mexico);
    aggressive_Player->addTerritory(colombia);
    aggressive_Player->addTerritory(brazil);

    // Manually setting reinforcement pool to 50 for each player
    neutral_Player->setReinforcementPool(50);
    aggressive_Player->setReinforcementPool(50);

    // Manually drawing 2 cards for each player
    game->deck = new Deck();
    game->deck->draw(neutral_Player->getHand());
    game->deck->draw(neutral_Player->getHand());
    game->deck->draw(aggressive_Player->getHand());
    game->deck->draw(aggressive_Player->getHand());

    // Start game loop
    game->mainGameLoop(2);

    playerList.clear();
    usa->setNumberOfArmies(0);
    mexico->setNumberOfArmies(0);
    colombia->setNumberOfArmies(0);
    brazil->setNumberOfArmies(0);
}

int main()
{
    //    testGameStates();
    //    testStartupPhase();
    testPlayerStrategies();
    return 0;
};