#include "LoggingObserverDriver.h"
using namespace std;

void testLoggingObserver(){
    LogObserver* logObserver = new LogObserver();

    string com = "loadmap";
    Command* command = new Command(com);
    command->Attach(logObserver);
    command->saveEffect("test1");

    CommandProcessor* commandProcessor = new CommandProcessor();
    commandProcessor->Attach(logObserver);
    commandProcessor->getCommand(); //cin in this method

    OrdersList* ordersList = new OrdersList();
    ordersList->Attach(logObserver);

    Player* player = new Player("ryan");
    Territory* territory = new Territory("place", 1, 1);
    player->addTerritory(territory);
    int* num = new int(2);
    Deploy* order = new Deploy(player, territory , num);
    order->Attach(logObserver);

    ordersList->addOrder(*order);
    order->execute();

    GameEngine* gameEngine = new GameEngine();
    gameEngine->Attach(logObserver);
    std::unique_ptr<GameEngine> game(gameEngine);

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
    game->update(*command);

    delete command;
    delete commandProcessor;
    delete order;
    delete ordersList;
    delete territory;
    delete num;
    delete player;
    delete gameEngine;
    delete logObserver;
}

int main(){
    testLoggingObserver();
    return 0;
}