#include "GameEngine.h"
#include "CommandProcessing.h"
#include <string>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

void testCommandProcessor(int argc, char* argv[]) {
    CommandProcessor consoleCommandProcessor;
    FileCommandProcessorAdapter *fileCommandProcessorAdapter;

    
    if (argc < 2) {
        cout << "Usage: ./CommandProcessorDriver -console OR ./CommandProcessorDriver file <filename>" << endl;
        return;
    }

    string inputMode = argv[1];

    if (inputMode == "-file") {
        // Read commands from a file
        if (argc < 3) {
            cout << "Please provide a filename for -file option." << endl;
            return;
        }

        string filename = argv[2];
        cout << "Reading commands from file: " << filename << endl;
        fileCommandProcessorAdapter = new FileCommandProcessorAdapter(filename);

        std::unique_ptr<GameEngine> game(new GameEngine(*fileCommandProcessorAdapter));

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
            game->update();
        }
    } 
    else if (inputMode == "-console") {
        // Read commands from the console
        // cout << "Reading commands from the console:\n";
        // Command consoleCommand = consoleCommandProcessor.getCommand();
        // if(consoleCommandProcessor.validate(consoleCommand, game->getCurrentGameState().getGameStateId())) {
        //     cout << consoleCommand;
        // }
    } else {
        cout << "Invalid option. Usage: ./CommandProcessorDriver -console OR ./CommandProcessorDriver -file <filename>" << endl;
    }
}


int main(int argc, char* argv[]){
    testCommandProcessor(argc, argv);
    return 0;
}