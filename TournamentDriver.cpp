#include "CommandProcessing.h"
#include "LoggingObserverDriver.h"
#include <string>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

void testTournament(){
    LogObserver* logObserver = new LogObserver();//observer for logs
    std::unique_ptr<GameEngine> game(new GameEngine());
    game->Attach(logObserver);//attach observer for logs

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

//int main(){
//   testTournament();
//   return 0;
//}
