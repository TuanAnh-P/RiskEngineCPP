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

    string com2 = "validatemap";
    Command* command2 = new Command(com2);
    command2->Attach(logObserver);
    command2->saveEffect("test end");

    game->update(*command2);


    delete command;
    delete command2;
    delete commandProcessor;
    delete order;
    delete ordersList;
    delete territory;
    delete num;
    delete player;
    delete gameEngine;
    delete logObserver;

    ILoggable* log = nullptr;
    Subject* sub = new Subject();
    OrdersList* proof1 = dynamic_cast<OrdersList*>(log);
    OrdersList* proof2 = dynamic_cast<OrdersList*>(sub);
    Order* proof3 = dynamic_cast<Order*>(log);
    Order* proof4 = dynamic_cast<Order*>(sub);
    Command* proof5 = dynamic_cast<Command*>(log);
    Command* proof6 = dynamic_cast<Command*>(sub);
    CommandProcessor* proof7 = dynamic_cast<CommandProcessor*>(log);
    CommandProcessor* proof8 = dynamic_cast<CommandProcessor*>(sub);
    GameEngine* proof9 = dynamic_cast<GameEngine*>(log);
    GameEngine* proof10 = dynamic_cast<GameEngine*>(sub);
    delete log;
    delete sub;
    delete proof1;
    delete proof2;
    delete proof3;
    delete proof4;
    delete proof5;
    delete proof6;
    delete proof7;
    delete proof8;
    delete proof9;
    delete proof10;
}

/*int main(){
    testLoggingObserver();
    return 0;
}*/
