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
    string command; 
    std::getline(std::cin, command);

    return command;
}

Command& CommandProcessor::saveCommand(string& command) {
    Command* newCommand = new Command(command);
    _commands->push_back(newCommand);

    return *newCommand;
}

Command& CommandProcessor::getCommand() {
    string command = readCommand();
    return saveCommand(command);
}

bool CommandProcessor::validate(Command& command, warzone::GameStateType gameState) {
    string commandValue = getFirstSubstring(command.getCommand());

    switch (gameState)
    {
    case (warzone::START):
        if(commandValue == "loadmap") {
            return true;
        } 
    case (warzone::MAP_LOADED):
        if(commandValue == "loadmap" || commandValue == "validatemap") {
            return true;
        }
    case warzone::MAP_VALIDATED:
        if(commandValue == "addplayer") {
            return true;
        }
    case warzone::PLAYERS_ADDED:
        if(commandValue == "addplayer" || commandValue == "gamestart") {
            return true;
        }
    case warzone::WIN:
        if(commandValue == "replay" || commandValue == "quit") {
            return true;
        }
    default:
        return false;
    }
}

std::ostream& operator<<(std::ostream& os, const CommandProcessor& commandProcessor) {
    os << "Commands in the processor: " << std::endl;
    for (Command* command : *commandProcessor._commands) {
        os << *command << std::endl;
    }
    return os;
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
        return line;
    }
    return *(new string(""));
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
    return _fileLineReader ? _fileLineReader->readLineFromFile() : *(new std::string(""));
}