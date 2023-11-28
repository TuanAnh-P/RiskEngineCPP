#include "CommandProcessing.h" 
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using std::string;
using std::ifstream;
using std::vector;

// this function gets the first substring of a string split by whitespace
string getFirstSubstring(const string& input) {
    size_t firstSpace = input.find(' ');
    if(firstSpace != string::npos){
        return input.substr(0, firstSpace);
    }

    return input;
}

// Implemenetation of Command class members
Command::Command() {
    _command = new string();
    _effect = new string();
}

// Non default constructor for Command class
Command::Command(string& command) {
    _command = new string(command);
    _effect = new string();
}

// Copy constructor for Command class
Command::Command(const Command& command){
    _command = new string(*command._command);
    _effect = new string(*command._effect);
}

// overloading the assignment operator for Command class
Command& Command::operator=(const Command& rhs){
    if(this != &rhs){
        delete _command;
        delete _effect;

        _command = new string(*rhs._command);
        _effect = new string(*rhs._effect);
    }

    return *this;
}

// Destructor for Command class
Command::~Command() {
    delete _command;
    delete _effect;
}

// getter for the command field 
string& Command::getCommand(){
    return *_command;
}

// save the effect of the command
void Command::saveEffect(const string& effect){
    *_effect = effect;

    Notify(this);
}

// returns a formatted string representing the command effect (used for logging purposes)
string Command::stringToLog(){
    string newCommandEffect = this->getCommandEffect();
    return "Command's Effect: " + newCommandEffect;
};

// Method that returns the command effect
string& Command::getCommandEffect(){
    return *_effect;
}

//  Overriding the stream ingestion operator for Command class
std::ostream& operator <<(std::ostream& out, const Command& command) {
    out << "Command: " << *command._command << ", Effect: " << *command._effect;
    return out;
}

// Implementation of TournamentConfiguration class members

// Non default constructor for TournamentConfiguration class
TournamentConfiguration::TournamentConfiguration(int& numberOfGames, int& maxTurns, vector<string>& mapFiles, vector<string>& playerStrategies) {
    _mapFiles = new vector<string>(mapFiles);
    _playerStrategies = new vector<string>(playerStrategies);
    _numberOfGames = new int(numberOfGames);
    _maxTurns = new int(maxTurns);
}

// Copy constructor for TournamentConfiguration class
TournamentConfiguration::TournamentConfiguration(const TournamentConfiguration& tc) {
    _mapFiles = new vector<string>(*(tc._mapFiles));
    _playerStrategies = new vector<string>(*(tc._playerStrategies));
    _numberOfGames = new int(*(tc._numberOfGames));
    _maxTurns = new int(*(tc._maxTurns));
}

// Overriding the assignment operator for TournamentConfiguration class
TournamentConfiguration& TournamentConfiguration::operator=(const TournamentConfiguration& rhs) {
    if (this != &rhs) {
        delete _mapFiles;
        delete _playerStrategies;
        delete _numberOfGames;
        delete _maxTurns;

        _mapFiles = new vector<string>(*(rhs._mapFiles));
        _playerStrategies = new vector<string>(*(rhs._playerStrategies));
        _numberOfGames = new int(*(rhs._numberOfGames));
        _maxTurns = new int(*(rhs._maxTurns));
    }
    return *this;
}

// Destructor for TournamentConfiguration class
TournamentConfiguration::~TournamentConfiguration() {
    delete _mapFiles;
    delete _playerStrategies;
    delete _numberOfGames;
    delete _maxTurns;
}

// Overriding the stream ingestion operator for the 
ostream& operator<<(std::ostream& out, const TournamentConfiguration& tc) {
    out << "Tournament Configuration Parameters: \n" << endl;
    out << "\tNumber of Games: " << *tc._numberOfGames << endl;
    out << "\tMax Turns: " << *tc._maxTurns << endl;
    out << "\tMap Files: " << endl;
    for (string mapFile : *tc._mapFiles) {
        out << "\t\t" << mapFile << endl;
    }
    out << "\tPlayer Strategies: " << endl;
    for (string playerStrategy : *tc._playerStrategies) {
        out << "\t\t" << playerStrategy << endl;
    }
    return out << "\n";
}

bool TournamentConfiguration::validateCommand(Command& command) {
}

TournamentConfiguration& TournamentConfiguration::parseCommand(Command& command) {
    istringstream commandStream(command.getCommand());
    string parameter;

    vector<std::string> mapFiles;
    vector<std::string> playerStrategies;
    int numberOfGames;
    int maxTurns;

    // Skip the first word "tournament"
    commandStream >> parameter;

    while (commandStream >> parameter) {
        if (parameter == "-M") {
            while (commandStream >> parameter && parameter != "-P") {
                mapFiles.push_back(parameter);
            }
        } else if (parameter == "-P") {
            while (commandStream >> parameter && parameter != "-G") {
                playerStrategies.push_back(parameter);
            }
        } else if (parameter == "-G") {
            commandStream >> numberOfGames;
        } else if (parameter == "-D") {
            commandStream >> maxTurns;
        }
    }

    return *(new TournamentConfiguration(numberOfGames, maxTurns, mapFiles, playerStrategies));
}


// Implementation of CommandProcessor members

// Default constructor for CommandProcessor class
CommandProcessor::CommandProcessor(){
    _commands = new std::vector<Command*>;
}

// Copy constructor for CommandProcessor class
CommandProcessor::CommandProcessor(const CommandProcessor& cp){
    _commands = new std::vector<Command*>;

    for(Command* command: *cp._commands) {
        Command* newCommand = new Command(*command);
        _commands->push_back(newCommand);
    }
}

// Assignment operator for CommandProcessor class
CommandProcessor& CommandProcessor::operator=(const CommandProcessor& other) {
    if (this != &other) {
        for (Command* command : *_commands) {
            delete command;
        }
        delete _commands;
        _commands = new std::vector<Command*>;

        for (Command* command : *other._commands) {
            Command* newCommand = new Command(*command);
            _commands->push_back(newCommand);
        }
    }
    return *this;
}

// Destructor for CommandProcessor class
CommandProcessor::~CommandProcessor() {
    for (Command* command : *_commands) {
        delete command;
    }
    delete _commands;
}

// Method that reads the next console input from the user
string& CommandProcessor::readCommand(){
    std::cout << "\n* Please enter a command: ";
    string command; 
    std::getline(std::cin, command);

    return *(new string(command));
}

// Method that adds a new command to the vector of command in the command processor
Command& CommandProcessor::saveCommand(string& command) {
    // Create a new command and add it to the vector of commands
    Command* newCommand = new Command(command);
    _commands->push_back(newCommand);

    // for logging purposes
    Notify(this);

    // return the newly created command
    return *newCommand;
}

// Method that reads the next input from the user and saves it in the vector of commands and returns it
Command& CommandProcessor::getCommand() {
    string commandValue = readCommand();
    return saveCommand(commandValue);
}

// Method that validates the command based on the current game state
bool CommandProcessor::validate(Command& command, GameStateType gameState) {
    string commandValue = getFirstSubstring(command.getCommand());

    // if the game state is one of the game triggered events, consider the command valid 
    if(gameState == GameStateType::ASSIGN_REINFORCEMENT ||  
       gameState == GameStateType::ISSUE_ORDERS ||
       gameState == GameStateType::EXECUTE_ORDERS) return true;

    // determining if the command is valid based on the game state
    if(gameState == GameStateType::START){
        if(commandValue == "loadmap" || commandValue == "tournament") {
            return true;
        }
        return false;
    }
    else if(gameState == GameStateType::MAP_LOADED){
        if(commandValue == "loadmap" || commandValue == "validatemap") {
            return true;
        }
        return false;
    }
    else if(gameState == GameStateType::MAP_VALIDATED){
        if(commandValue == "addplayer") {
            return true;
        }
        return false;
    }
    else if(gameState == GameStateType::PLAYERS_ADDED){
        if(commandValue == "addplayer" || commandValue == "gamestart") {
            return true;
        }
        return false;
    }
    else if(gameState == GameStateType::WIN){
        if(commandValue == "replay" || commandValue == "quit") {
            return true;
        }
        return false;
    }
    return false;
}

// Method that returns a formatted string representing the last command saved in the command processor (used for logging purposes)
string CommandProcessor::stringToLog(){
    string newCommand = (_commands->back())->getCommand();
    return "Command: " + newCommand;
};

// Overriding the stream ingestion operator for CommandProcessor class
std::ostream& operator<<(std::ostream& os, const CommandProcessor& commandProcessor) {
    os << "Commands in the the command processor: \n" << std::endl;
    for (Command* command : *commandProcessor._commands) {
        os << "\t" << *command << std::endl;
    }
    return os << "\n";
}

// Implemenation of the FileLineReader and FileCommandProcessorAdapter

// Default constructor for FileLineReader class
FileLineReader::FileLineReader() : _fileStream(nullptr) {}

// Non default constructor for FileLineReader class
FileLineReader::FileLineReader(const string& filePath) : _fileStream(new ifstream(filePath)) {}

// Destructor for FileLineReader class
FileLineReader::~FileLineReader() {
    if (_fileStream) {
        _fileStream->close();
        delete _fileStream;
    }
}

// Overriding the stream ingestion operator for FileLineReader class
ostream& operator<<(std::ostream& out, const FileLineReader &flr) {
    out << "FileLineReader";
    return out;
}

// Method that reads the next line from the file and returns it, if the end of file is reached, it returns "EOD"
string& FileLineReader::readLineFromFile() {
    string line;
    if (_fileStream && _fileStream->is_open() && std::getline(*_fileStream, line)) {
        return *(new string(line));
    }
    return *(new string("EOD"));
}

// Default constructor for FileCommandProcessorAdapter class
FileCommandProcessorAdapter::FileCommandProcessorAdapter() : _fileLineReader(nullptr) {}

// Non default constructor for FileCommandProcessorAdapter class
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const string& filePath) : _fileLineReader(new FileLineReader(filePath)) {}

// Copy constructor for FileCommandProcessorAdapter class
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& fcp) : _fileLineReader(fcp._fileLineReader ? new FileLineReader(*(fcp._fileLineReader)) : nullptr) {}

// Destructor for FileCommandProcessorAdapter class
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    delete _fileLineReader;
}

// Overriding the assignment operator for FileCommandProcessorAdapter class
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter &rhs) {
    if (this != &rhs) {
        delete _fileLineReader;
        _fileLineReader = rhs._fileLineReader ? new FileLineReader(*(rhs._fileLineReader)) : nullptr;
    }
    return *this;
}

// Overriding the stream ingestion operator for FileCommandProcessorAdapter class
std::ostream& operator<<(std::ostream& out, const FileCommandProcessorAdapter &fcp) {
    out << "FileCommandProcessorAdapter";
    return out;
}

// Method that reads the next line from the file and returns it, if the end of file is reached, it returns "EOD"
string& FileCommandProcessorAdapter::readCommand() {
    return _fileLineReader ? _fileLineReader->readLineFromFile() : *(new std::string("EOD"));
}
