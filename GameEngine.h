#pragma once

#include "CommandProcessing.h"
#include <memory>
#include <map>
#include <string>

using std::string;
using std::ostream;

class Command;

// Enum representing valid game states
enum class GameStateType
{
    START,
    MAP_LOADED,
    MAP_VALIDATED,
    PLAYERS_ADDED,
    ASSIGN_REINFORCEMENT,
    ISSUE_ORDERS,
    EXECUTE_ORDERS,
    WIN,
    END
};

string gameStateTypeToString(GameStateType state);

// functions used for printing game messages and reading use commands from standard in
void printInvalidCommandError();

class GameEngine;
class CommandProcessor;

// represents a base class for game states
class GameState
{
protected:
    // attributes
    string *_name;
    GameStateType * _gameStateID;
    GameEngine &_gameEngine;
public:
    // constructors
    explicit GameState(GameEngine &gameEngine,
                        GameStateType *gameStateId,
                        string *name);

    explicit GameState(GameState &gameState);

    // Assignment operator
    void operator=(const GameState &gameState);

    // destructor
    virtual ~GameState() {};

    // stream ingestion operator
    friend ostream & operator << (ostream &out, GameState &state);
    
    // method that returns the Id of the game state
    GameStateType getGameStateId();
    
    void enter();

    // method for updating the game state
    virtual void update(Command& command) {};
};

// class representing the game engine
class GameEngine
{

protected:
    // All GameStates of the game
    std::map<GameStateType, std::shared_ptr<GameState > > _gameStates;
    // The current GameState.
    GameState *_currentGameState;
    // Command processor 
    CommandProcessor * _commandProcessor;

public:
    // constructor 
    GameEngine();

    GameEngine(CommandProcessor& commandProcessor);

    GameEngine(GameEngine &engine);

    // Stream ingestion operator
    friend ostream & operator << (ostream &out, GameEngine &gameEngine);

    // Assignment operator
    void operator=(const GameEngine &gameEngine);
    
    // Getter for command processor 
    CommandProcessor& getCommandProcessor();

    // Get game state instance by ID
    GameState &getGameState(GameStateType gameStateID);

    // Get current GameState
    GameState &getCurrentGameState();

    // Register a new GameState to the game engine
    // since this is a template function, the implementation can only reside in the header file
    template <typename S>
    void registerGameState(GameStateType gameStateID) {
        _gameStates[gameStateID] = std::unique_ptr<S>(new S(*this));
    };

    // Change the current game state
    void setCurrentGameState(GameStateType gameStateID);

    // Call the update method on the current game state instance
    void update(Command& command);

protected: 
    // Sets the current game state
    void setCurrentGameState(GameState *gameState);
};

// Class representing the State state
class StartState : public GameState
{
public:
    StartState(GameEngine &gameEngine);

    void update(Command& command);
};

// Class MapLoadedState the State state
class MapLoadedState : public GameState
{
public:
    MapLoadedState(GameEngine &gameEngine);

    void update(Command& command);
};

// Class MapValidatedState the State state
class MapValidatedState : public GameState
{
public:
    MapValidatedState(GameEngine &gameEngine);

    void update(Command& command);
};

// Class PlayersAddedState the State state
class PlayersAddedState : public GameState
{
public:
    PlayersAddedState(GameEngine &gameEngine);

    void update(Command& command);
};

// Class AssignReinforcementState the State state
class AssignReinforcementState : public GameState
{
public:
    AssignReinforcementState(GameEngine &gameEngine);

    void update(Command& command);
};

// Class IssueOrdersState the State state
class IssueOrdersState : public GameState
{
public:
    IssueOrdersState(GameEngine &gameEngine);

    void update(Command& command);
};

// Class ExecuteOrdersState the State state
class ExecuteOrdersState : public GameState
{
public:
    ExecuteOrdersState(GameEngine &gameEngine);

    void update(Command& command);
};

// Class WinState the State state
class WinState : public GameState
{
public:
    WinState(GameEngine &gameEngine); 

    void update(Command& command);
};

// Class EndState the State state
class EndState : public GameState
{
public:
    EndState(GameEngine &gameEngine);

    void update(Command& command);
};