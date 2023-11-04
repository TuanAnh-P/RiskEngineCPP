#include "CommandProcessing.h" 
#include <string>
#include <iostream>
#include<vector>

using std::string;

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
            command.saveEffect("transitioning to map loaded state"); 
            return true;
        } 
    case (warzone::MAP_LOADED):
        if(commandValue == "loadmap") {
            command.saveEffect("transitioning to map loaded state"); 
            return true;
        }
        if(commandValue == "validatemap") {
            command.saveEffect("transitioning to map validated state"); 
            return true;
        }
    case warzone::MAP_VALIDATED:
        if(commandValue == "addplayer") {
            command.saveEffect("transitioning to players added state"); 
            return true;
        }
    case warzone::PLAYERS_ADDED:
        if(commandValue == "addplayer") {
            command.saveEffect("transitioning to players added state"); 
            return true;
        }
        if(commandValue == "gamestart") {
            command.saveEffect("transitioning to assign reinforcement state"); 
            return true;
        }
    case warzone::WIN:
        if(commandValue == "replay") {
            command.saveEffect("transitioning to start state"); 
            return true;
        }
        if(commandValue == "quit") {
            command.saveEffect("transitioning to exit state"); 
            return true;
        }
    default:
        command.saveEffect("Command is invalid in the current state"); 
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

