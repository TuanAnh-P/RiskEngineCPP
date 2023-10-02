#include "GameEngine.h"

using namespace warzone;

void testGameStates(){
    // Create the game engine and add the valid states
    std::unique_ptr<GameEngine> game(new GameEngine());

    game->registerGameState<StartState>(START);
    game->registerGameState<MapLoadedState>(MAP_LOADED);
    game->registerGameState<MapValidatedState>(MAP_VALIDATED);
    game->registerGameState<PlayersAddedState>(PLAYERS_ADDED);
    game->registerGameState<AssignReinforcementState>(ASSIGN_REINFORCEMENT);
    game->registerGameState<IssueOrdersState>(ISSUE_ORDERS);
    game->registerGameState<ExecuteOrdersState>(EXECUTE_ORDERS);
    game->registerGameState<WinState>(WIN);
    game->registerGameState<EndState>(END);

    game->setCurrentGameState(START);

    while ((game->getCurrentGameState()).getGameStateId() != END)
    {
        game->update();
    }
};

int main() {
    testGameStates();
};

