#include "GameEngine.h"
#include "CommandProcessing.h"
#include <string>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

void testCommandProcessor(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: ./CommandProcessorDriver -console OR ./CommandProcessorDriver file <filename>" << endl;
        return;
    }

    string input = argv[1];

    GameEngine* game;

    if (input == "-file") {
        // Read commands from a file
        if (argc < 3) {
            cout << "Please provide a filename for -file option." << endl;
            return;
        }
        string filename = argv[2];

        cout << "Reading commands from file: " << filename << endl;

        FileCommandProcessorAdapter *fileCommandProcessorAdapter = new FileCommandProcessorAdapter(filename);
        game = new GameEngine(*fileCommandProcessorAdapter);
    } 
    else if (input == "-console") {
        cout << "Reading commands from console: " << endl; 
        
        CommandProcessor * commandProcessor = new CommandProcessor();
        game = new GameEngine(*commandProcessor);
    } else {
        cout << "Invalid option. Usage: ./CommandProcessorDriver -console OR ./CommandProcessorDriver -file <filename>" << endl;
    } 

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
            cout << "\n\n*** No more commands left in the file, ending game now!\n" << endl;
            break;
        }

        // validate command and transition to another state
        if (game->getCommandProcessor().validate(command, game->getCurrentGameState().getGameStateId())){
            game->update(command);

            // this logic skips the game-triggered events
            /*if(game->getCurrentGameState().getGameStateId() == GameStateType::ASSIGN_REINFORCEMENT){
                for(int i=0; i < 3; i++){
                    game->update(command);
                }
            }*/
        } else {
            // if command is invalid, save it in the effect
            command.saveEffect("Invalid command");
            printInvalidCommandError();
        }
    }

    cout << endl << game->getCommandProcessor();
}

/*int main(int argc, char* argv[]){
   testCommandProcessor(argc, argv);
   return 0;
}*/