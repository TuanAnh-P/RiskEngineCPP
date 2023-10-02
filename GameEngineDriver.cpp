#include "GameEngine.h"

using namespace warzone;

void testGameStates(){
    // Create the game engine and add the valid states

    std::unique_ptr<GameEngine> game(new GameEngine());

    GameState &startState = game->add<StartState>(START);
    GameState &mapLoadedState = game->add<MapLoadedState>(MAP_LOADED);
    GameState &mapValidatedState = game->add<MapValidatedState>(MAP_VALIDATED);
    GameState &playersAddedState = game->add<PlayersAddedState>(PLAYERS_ADDED);
    GameState &assignReinforcementState = game->add<AssignReinforcementState>(ASSIGN_REINFORCEMENT);
    GameState &issueOrdersState = game->add<IssueOrdersState>(ISSUE_ORDERS);
    GameState &executeOrders = game->add<ExecuteOrdersState>(EXECUTE_ORDERS);
    GameState &winState = game->add<WinState>(WIN);
    GameState &endState = game->add<EndState>(END);

    game->setCurrentGameState(START);

    while ((game->getCurrentGameState()).getGameStateId() != END)
    {
        game->update();
    }
};

int main() {
    testGameStates();
};

