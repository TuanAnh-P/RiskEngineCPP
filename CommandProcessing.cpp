#include "CommandProcessing.h" 
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using std::string;
using std::ifstream;

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

Command::Command(string& command) {
    _command = new string(command);
    _effect = new string();
}

Command::Command(const Command& command){
    _command = new string(*command._command);
    _effect = new string(*command._effect);
}

Command& Command::operator=(const Command& rhs){
    if(this != &rhs){
        delete _command;
        delete _effect;

        _command = new string(*rhs._command);
        _effect = new string(*rhs._effect);
    }

    return *this;
}

Command::~Command() {
    delete _command;
    delete _effect;
}

string& Command::getCommand(){
    return *_command;
}

void Command::saveEffect(const string& effect){
    *_effect = effect;

    Notify(this);
}

std::ostream& operator <<(std::ostream& out, const Command& command) {
    out << "Command: " << *command._command << ", Effect: " << *command._effect;
    return out;
}


// Implementation of CommandProcessor members

CommandProcessor::CommandProcessor(){
    _commands = new std::vector<Command*>;
}

CommandProcessor::CommandProcessor(const CommandProcessor& cp){
    _commands = new std::vector<Command*>;

    for(Command* command: *cp._commands) {
        Command* newCommand = new Command(*command);
        _commands->push_back(newCommand);
    }
}

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

CommandProcessor::~CommandProcessor() {
    for (Command* command : *_commands) {
        delete command;
    }
    delete _commands;
}

string& CommandProcessor::readCommand(){
    std::cout << "\n* Please enter a command: ";
    string command; 
    std::getline(std::cin, command);

    return *(new string(command));
}

Command& CommandProcessor::saveCommand(string& command) {
    Command* newCommand = new Command(command);
    _commands->push_back(newCommand);

    Notify(this);

    return *newCommand;
}

Command& CommandProcessor::getCommand() {
    string commandValue = readCommand();
    return saveCommand(commandValue);
}

bool CommandProcessor::validate(Command& command, GameStateType gameState) {
    string commandValue = getFirstSubstring(command.getCommand());

    if(gameState == GameStateType::ASSIGN_REINFORCEMENT ||  
       gameState == GameStateType::ISSUE_ORDERS ||
       gameState == GameStateType::EXECUTE_ORDERS) return true;

    switch (gameState)
    {
        case GameStateType::START:
            if(commandValue == "loadmap") {
                return true;
            } 
            return false;
        case GameStateType::MAP_LOADED:
            if(commandValue == "loadmap" || commandValue == "validatemap") {
                return true;
            }
            return false;
        case GameStateType::MAP_VALIDATED:
            if(commandValue == "addplayer") {
                return true;
            }
            return false;
        case GameStateType::PLAYERS_ADDED:
            if(commandValue == "addplayer" || commandValue == "gamestart") {
                return true;
            }
            return false;
        case GameStateType::WIN:
            if(commandValue == "replay" || commandValue == "quit") {
                return true;
            }
            return false;
        default:
            return false;
        }
}

std::ostream& operator<<(std::ostream& os, const CommandProcessor& commandProcessor) {
    os << "Commands in the the command processor: \n" << std::endl;
    for (Command* command : *commandProcessor._commands) {
        os << "\t" << *command << std::endl;
    }
    return os << "\n";
}

// Implemenation of the FileLineReader and FileCommandProcessorAdapter
FileLineReader::FileLineReader() : _fileStream(nullptr) {}

FileLineReader::FileLineReader(const string& filePath) : _fileStream(new ifstream(filePath)) {}

FileLineReader::~FileLineReader() {
    if (_fileStream) {
        _fileStream->close();
        delete _fileStream;
    }
}

ostream& operator<<(std::ostream& out, const FileLineReader &flr) {
    out << "FileLineReader";
    return out;
}

string& FileLineReader::readLineFromFile() {
    string line;
    if (_fileStream && _fileStream->is_open() && std::getline(*_fileStream, line)) {
        return *(new string(line));
    }
    return *(new string("EOD"));
}


FileCommandProcessorAdapter::FileCommandProcessorAdapter() : _fileLineReader(nullptr) {}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const string& filePath) : _fileLineReader(new FileLineReader(filePath)) {}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& fcp) : _fileLineReader(fcp._fileLineReader ? new FileLineReader(*(fcp._fileLineReader)) : nullptr) {}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    delete _fileLineReader;
}

FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter &rhs) {
    if (this != &rhs) {
        delete _fileLineReader;
        _fileLineReader = rhs._fileLineReader ? new FileLineReader(*(rhs._fileLineReader)) : nullptr;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, const FileCommandProcessorAdapter &fcp) {
    out << "FileCommandProcessorAdapter";
    return out;
}

string& FileCommandProcessorAdapter::readCommand() {
    return _fileLineReader ? _fileLineReader->readLineFromFile() : *(new std::string("EOD"));
}

// A2 P5
string Command::stringToLog(){
    string newCommandEffect = this->getCommandEffect();
    return "Command's Effect: " + newCommandEffect;
};

string CommandProcessor::stringToLog(){
    string newCommand = (_commands->back())->getCommand();
    return "Command: " + newCommand;
};

string& Command::getCommandEffect(){
    return *_effect;
}