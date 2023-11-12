#include "GameEngine.h"
#include <iostream>
using namespace std;


// free function to test the game engine 
void testGameStates(){
    // Create the game engine and add the valid states
    std::unique_ptr<GameEngine> game(new GameEngine());

    // Register valid game states
    game->registerGameState<StartState>(GameStateType::START);
    game->registerGameState<MapLoadedState>(GameStateType::MAP_LOADED);
    game->registerGameState<MapValidatedState>(GameStateType::MAP_VALIDATED);
    game->registerGameState<PlayersAddedState>(GameStateType::PLAYERS_ADDED);
    game->registerGameState<AssignReinforcementState>(GameStateType::ASSIGN_REINFORCEMENT);
    game->registerGameState<IssueOrdersState>(GameStateType::ISSUE_ORDERS);
    game->registerGameState<ExecuteOrdersState>(GameStateType::EXECUTE_ORDERS);
    game->registerGameState<WinState>(GameStateType::WIN);
    game->registerGameState<EndState>(GameStateType::END);

    // Set the starting state
    game->setCurrentGameState(GameStateType::START);


    // loop until the end state has not been reached
    while ((game->getCurrentGameState()).getGameStateId() != GameStateType::END)
    {
        cout << "status is " << ((game->getCurrentGameState()).getGameStateId() != GameStateType::END) ;
        
        Command& command = game->getCommandProcessor().getCommand();

        cout << "reach 1";
        if (game->getCommandProcessor().validate(command, game->getCurrentGameState().getGameStateId())){
            game->update(command);
        } else {
            printInvalidCommandError();
        }
    }
};

void testStartupPhase(){
    // Create the game engine and add the valid states
    std::unique_ptr<GameEngine> game(new GameEngine());

    // Register valid game states
    game->registerGameState<StartState>(GameStateType::START);
    game->registerGameState<MapLoadedState>(GameStateType::MAP_LOADED);
    game->registerGameState<MapValidatedState>(GameStateType::MAP_VALIDATED);
    game->registerGameState<PlayersAddedState>(GameStateType::PLAYERS_ADDED);
    game->registerGameState<AssignReinforcementState>(GameStateType::ASSIGN_REINFORCEMENT);
    game->registerGameState<IssueOrdersState>(GameStateType::ISSUE_ORDERS);
    game->registerGameState<ExecuteOrdersState>(GameStateType::EXECUTE_ORDERS);
    game->registerGameState<WinState>(GameStateType::WIN);
    game->registerGameState<EndState>(GameStateType::END);

    // Set the starting state
    game->setCurrentGameState(GameStateType::START);
    game->startupPhase();
}

// free function to test the main game loop
void testMainGameLoop(){

    // Create the game engine
    std::unique_ptr<GameEngine> game(new GameEngine());

    // Initializing North America
    Continent* northAmerica = new Continent("northAmerica" , 5);
    Territory* usa = new Territory("usa", 0, 0);
    Territory* mexico = new Territory("mexico", 0, 0);
    northAmerica->addTerritory(usa);
    northAmerica->addTerritory(mexico);

    // Initializing South America
    Continent* southAmerica = new Continent("southAmerica" , 10);
    Territory* colombia = new Territory("colombia", 0, 0);
    Territory* brazil = new Territory("brazil", 0, 0);
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
    game->gameMap=map;

    // Initializing 2 players
    Player* player1 = new Player("John");
    Player* player2 = new Player("Jose");
    std::vector<Player*> playerList;
    playerList.push_back(player1);
    playerList.push_back(player2);
    game->players=playerList;

    // Manually assigning territories to players
    player1->addTerritory(usa);
    player1->addTerritory(mexico);
    player2->addTerritory(colombia);
    player2->addTerritory(brazil);

    // Manually setting reinforcement pool to 50 for each player
    player1->setReinforcementPool(50);
    player2->setReinforcementPool(50);

    // Manually drawing 2 cards for each player
    game->deck = new Deck();
    game->deck->draw(player1->getHand());
    game->deck->draw(player1->getHand());
    game->deck->draw(player2->getHand());
    game->deck->draw(player2->getHand());

    // Calling the mainGameLoop()
    game->mainGameLoop();
}

/*int main()
{
//    testGameStates();
//    testStartupPhase();
    testMainGameLoop();
    return 0;
};*/