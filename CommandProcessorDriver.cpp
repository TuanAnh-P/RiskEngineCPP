#include "CommandProcessing.h"
#include <string>
#include <vector>
#include <iostream>
#include "GameEngine.h"

using namespace warzone;
using std::cout;
using std::endl;

void testCommandProcessor(int argc, char* argv[]) {
    CommandProcessor consoleCommandProcessor;
    FileCommandProcessorAdapter *fileCommandProcessorAdapter;

    std::unique_ptr<GameEngine> game(new GameEngine());

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
        Command fileCommand = fileCommandProcessorAdapter->getCommandFromFile();
        // Process the file command as needed
        cout << "Effect of the file command: " << fileCommand.getEffect() << endl;
    } 
    else if (inputMode == "-console") {
        // Read commands from the console
        cout << "Reading commands from the console:\n";
        Command consoleCommand = consoleCommandProcessor.getCommand();
        if(consoleCommandProcessor.validate(consoleCommand, game->getCurrentGameState().getGameStateId())) {
            cout << consoleCommand;
        }
    } else {
        cout << "Invalid option. Usage: ./CommandProcessor -console OR ./CommandProcessor -file <filename>" << endl;
    }
}


int main(int argc, char* argv[]){
    testCommandProcessor(argc, argv);
    return 0;
}