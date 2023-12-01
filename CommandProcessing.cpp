#include "CommandProcessing.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

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

string Command::stringToTourLog(int game){
    return "";
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

// Method that validates and parses the configuration from the tournament command
TournamentConfiguration* TournamentConfiguration::validateAndParseCommand(string commandStr) {
    // Find the positions of various parameters in the command
    size_t posM = commandStr.find("-M ");
    if (posM == std::string::npos) return nullptr;
    size_t posP = commandStr.find("-P ");
    if (posP == std::string::npos) return nullptr;
    size_t posG = commandStr.find("-G ");
    if (posG == std::string::npos) return nullptr;
    size_t posD = commandStr.find("-D ");
    if (posD == std::string::npos) return nullptr;

    // Extract the lists of map files and player strategies
    std::string mapFilesStr = commandStr.substr(posM + 3, posP - posM - 4);
    std::string playerStrategiesStr = commandStr.substr(posP + 3, posG - posP - 4);

    // Extract the numerical values
    int numberOfGames = std::stoi(commandStr.substr(posG + 2, posD - posG - 2));
    int maxNumberOfTurns = std::stoi(commandStr.substr(posD + 2));

    // Create vectors to store map files and player strategies
    std::vector<std::string> mapFiles;
    std::vector<std::string> playerStrategies;

    // Use stringstream to split comma-separated values into vectors
    std::stringstream mapFilesStream(mapFilesStr);
    std::stringstream playerStrategiesStream(playerStrategiesStr);
    std::string mapFile;
    std::string playerStrategy;

    // Extract map files
    while (std::getline(mapFilesStream, mapFile, ',')) {
        mapFiles.push_back(mapFile);
    }

    // Extract player strategies
    while (std::getline(playerStrategiesStream, playerStrategy, ',')) {
        playerStrategies.push_back(playerStrategy);
    }

    if(numberOfGames < 1 || numberOfGames > 5){
        cout << "Please enter 1-5 Games";
        return nullptr;
    }

    if(maxNumberOfTurns < 10 || maxNumberOfTurns > 50){
        cout << "Please enter 10-50 Turns";
        return nullptr;
    }

    if(mapFiles.size() < 1 || mapFiles.size() > 5){
        cout << "Please enter 1-5 Maps";
        return nullptr;
    }

    if(playerStrategies.size() < 1 || playerStrategies.size() > 4){
        cout << "Please enter 1-4 Players";
        return nullptr;
    }

    for(int i = 0; i < playerStrategies.size(); i++){
        string player = "player" + std::to_string(i);
        std::string strategy = playerStrategies[i];
        if(strategy != "Aggressive" && strategy != "Benevolent" && strategy != "Neutral" && strategy != "Cheater") {
            cout << strategy << " is not a valid Computer";
            return nullptr;
        }
    }

    return new TournamentConfiguration(numberOfGames, maxNumberOfTurns, mapFiles, playerStrategies);
}

int &TournamentConfiguration::getNumberOfGames() {
    return *_numberOfGames;
}

int &TournamentConfiguration::getMaxTurns() {
    return *_maxTurns;
}

vector<string> &TournamentConfiguration::getMapsFiles() {
    return *_mapFiles;
}

vector<string> &TournamentConfiguration::getPlayerStrategies() {
    return *_playerStrategies;
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

string CommandProcessor::stringToTourLog(int game){
    return "";
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