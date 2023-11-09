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

int main()
{
    //testGameStates();
    testStartupPhase();
    return 0;
};