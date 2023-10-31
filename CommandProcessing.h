#include <list>
#include <string> 
#include <ostream> 
#include "GameEngine.h"

using std::string;

class Command {
private: 
    string *_command;
    string *_effect;

public: 
    // default constructor 
    Command();

    // Non default constructor 
    Command(string *command, string *effect);

    // Copy Constructor
    Command(const Command &cm);

    // Assignment operator 
    Command& operator=(Command &rhs);

    // Stream ingestion operator 
    friend std::ostream& operator<<(std::ostream& out, const Command &cp);

    void saveEffect(string *effect);
};

class CommandProcessor {

private: 
    std::list<Command> _commands;        

    string readCommand();

    string saveCommand();

public: 
    CommandProcessor();
    
    // Copy constructor 
    CommandProcessor(const CommandProcessor &cp);

    // Assignment operator 
    CommandProcessor& operator=(CommandProcessor &rhs);

    // Stream ingestion operator     
    friend std::ostream& operator<<(std::ostream& out, const CommandProcessor &cp); 

    void getCommand();

    bool validate(Command command, warzone::GameStateType gameState);
};