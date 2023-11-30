#include "CommandProcessing.h"
#include <string>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

void testTournament(){
    // Read commands from a file
    string filename = "./commands.txt";

    FileCommandProcessorAdapter *fileCommandProcessorAdapter = new FileCommandProcessorAdapter(filename);
    GameEngine* game = new GameEngine(*fileCommandProcessorAdapter);

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

    while ((game->getCurrentGameState()).getGameStateId() != GameStateType::END)
    {
        Command& command = game->getCommandProcessor().getCommand();

        // if reading from file and no more commands can be read from the file, exit the program
        if(command.getCommand() == "EOD"){
            // cout << "\n\n*** No more commands left in the file, ending game now!\n" << endl;
            break;
        }

        // validate command and transition to another state
        if (game->getCommandProcessor().validate(command, game->getCurrentGameState().getGameStateId())){
            game->update(command);

            // this logic skips the game-triggered events
            if(game->getCurrentGameState().getGameStateId() == GameStateType::ASSIGN_REINFORCEMENT){
                for(int i=0; i < 3; i++){
                    game->update(command);
                }
            }
        } else {
            // if command is invalid, save it in the effect
            command.saveEffect("Invalid command");
            printInvalidCommandError();
        }
    }

    // cout << endl << game->getCommandProcessor();
}

//int main(){
//   testTournament();
//   return 0;
//}
