#pragma once

#include <vector>
#include <string> 
#include <ostream> 
#include "GameEngine.h"

using std::string;

string getFirstSubstring(const string& string);
class Command {
private: 
    string *_command;
    string *_effect;

public: 
    // default constructor 
    Command();
    
    // constructor that only takes one parameter
    Command(string &command);

    // Non default constructor 
    Command(string &command, string &effect);

    // Copy Constructor
    Command(const Command &cm);

    // destructor
    ~Command();

    // Assignment operator 
    Command& operator=(const Command &rhs);

    // Stream ingestion operator 
    friend std::ostream& operator<<(std::ostream& out, const Command &command);

    string& getCommand();

    void saveEffect(const string &effect);
};

class CommandProcessor {

private: 
    std::vector<Command*> *_commands;        

    string& readCommand();

    Command& saveCommand(string& command);

public: 
    CommandProcessor();
    
    // Copy constructor 
    CommandProcessor(const CommandProcessor &commandProcessor);

    // Destructor 
    ~CommandProcessor();

    // Assignment operator 
    CommandProcessor& operator=(const CommandProcessor &rhs);

    // Stream ingestion operator     
    friend std::ostream& operator<<(std::ostream& out, const CommandProcessor &cp); 

    Command& getCommand();

    bool validate(Command& command, warzone::GameStateType gameState);
};