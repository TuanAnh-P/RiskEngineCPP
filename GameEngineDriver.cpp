#include "GameEngine.h"

// free function to test the game engine 
void testGameStates(){
    // Create the game engine and add the valid states
    std::unique_ptr<GameEngine> game(new GameEngine());

    // Register valid game states
    game->registerGameState<StartState>(START);
    game->registerGameState<MapLoadedState>(MAP_LOADED);
    game->registerGameState<MapValidatedState>(MAP_VALIDATED);
    game->registerGameState<PlayersAddedState>(PLAYERS_ADDED);
    game->registerGameState<AssignReinforcementState>(ASSIGN_REINFORCEMENT);
    game->registerGameState<IssueOrdersState>(ISSUE_ORDERS);
    game->registerGameState<ExecuteOrdersState>(EXECUTE_ORDERS);
    game->registerGameState<WinState>(WIN);
    game->registerGameState<EndState>(END);

    // Set the starting state
    game->setCurrentGameState(START);

    // loop until the end state has not been reached
    while ((game->getCurrentGameState()).getGameStateId() != END)
    {
        game->update();
    }


};
