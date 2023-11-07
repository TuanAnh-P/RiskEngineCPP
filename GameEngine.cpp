#include <iostream>
#include <string>
#include <memory>
#include "GameEngine.h"
#include "CommandProcessing.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;

string gameStateTypeToString(GameStateType state) {
    switch (state) {
        case GameStateType::START:
            return "START";
        case GameStateType::MAP_LOADED:
            return "MAP_LOADED";
        case GameStateType::MAP_VALIDATED:
            return "MAP_VALIDATED";
        case GameStateType::PLAYERS_ADDED:
            return "PLAYERS_ADDED";
        case GameStateType::ASSIGN_REINFORCEMENT:
            return "ASSIGN_REINFORCEMENT";
        case GameStateType::ISSUE_ORDERS:
            return "ISSUE_ORDERS";
        case GameStateType::EXECUTE_ORDERS:
            return "EXECUTE_ORDERS";
        case GameStateType::WIN:
            return "WIN";
        case GameStateType::END:
            return "END";
        default:
            return "UNKNOWN";
    }
}

void printInvalidCommandError()
{
    cout << "\nCommand not recognized! Please try again ..." << endl;
};

void printRemainingInStateMessage(string &name){
    cout << "\nRemaining in ------------> " << name << " State" << endl;
}

string getUserCommand()
{
    cout << "\nPlease enter command: ";

    string command;
    cin >> command;

    return command;
};

// Implementation of the GameEngine class methods / constructors
GameState::GameState(GameEngine &gameEngine, GameStateType *gameStateId, string *name):
    _name(name), _gameStateID(gameStateId), _gameEngine(gameEngine) {};

GameState::GameState(GameState &gameState):
    _name(gameState._name), _gameStateID(gameState._gameStateID), _gameEngine(gameState._gameEngine) {};

void GameState::operator= (const GameState &gameState){
    _gameEngine = gameState._gameEngine;
    _gameStateID = gameState._gameStateID;
    _name = gameState._name;
} 

ostream & operator << (ostream &out, GameState &state)
{
    out << state._name << endl;
    return out;
}

void GameState::enter(){
    if(*_gameStateID == GameStateType::END){
        cout << "\nThe game has finished. Thanks for playing :)\n" << endl;
    }else {
        cout << "\nEntering ------------> " << *_name << " State" << endl;
    }
}

GameStateType GameState::getGameStateId(){
    return *_gameStateID;
}

// Implementation of the GameState class methods / constructors
GameEngine::GameEngine() : _currentGameState(nullptr) {};

GameEngine::GameEngine(CommandProcessor& commandProcessor): _commandProcessor(&commandProcessor) {};

GameEngine::GameEngine(GameEngine &engine) : 
    _currentGameState(engine._currentGameState), _gameStates(engine._gameStates) {};

ostream & operator << (ostream &out, GameEngine &engine)
{
    out << "current state" << gameStateTypeToString(engine._currentGameState->getGameStateId())<< endl;
    return out;
}

void GameEngine::operator= (const GameEngine &gameEngine){
    _gameStates = gameEngine._gameStates;
    _currentGameState = gameEngine._currentGameState;
}   

CommandProcessor& GameEngine::getCommandProcessor() {
    return *_commandProcessor;
}

GameState& GameEngine::getGameState(GameStateType gameStateID){
    return *_gameStates[gameStateID];
}

GameState& GameEngine::getCurrentGameState(){
    return *_currentGameState;
}

void GameEngine::setCurrentGameState(GameStateType gameStateID)
{
    GameState *gameState = &getGameState(gameStateID);
    setCurrentGameState(gameState);
}

void GameEngine::update(){
    if (_currentGameState != nullptr)
    {
        _currentGameState->update();
    }
}

void GameEngine::setCurrentGameState(GameState *gameState)
{
    if (_currentGameState == gameState)
    {
        return;
    }

    _currentGameState = gameState;
    if (_currentGameState != nullptr)
    {
        _currentGameState->enter();
    }
}

// Start state class implementation
StartState::StartState(GameEngine &gameEngine)
        : GameState(gameEngine, new GameStateType(GameStateType::START), new string("Start")){};

void StartState::update(){
    Command command = _gameEngine.getCommandProcessor().getCommand();

    if (_gameEngine.getCommandProcessor().validate(command, *_gameStateID)){
        command.saveEffect("* transitioning to Map Loaded state");
        _gameEngine.setCurrentGameState(GameStateType::MAP_LOADED);
    } else {
        printInvalidCommandError();
    }
}

// Map Loaded state class implementation
MapLoadedState::MapLoadedState(GameEngine &gameEngine)
    : GameState(gameEngine, new GameStateType(GameStateType::MAP_LOADED), new string("Map Loaded")){};

void MapLoadedState::update(){
    Command command = _gameEngine.getCommandProcessor().getCommand();

    if (_gameEngine.getCommandProcessor().validate(command, *_gameStateID)){
        if (command.getCommand() == "validatemap")
        {
            command.saveEffect("* transitioning to Map Validated state");
            _gameEngine.setCurrentGameState(GameStateType::MAP_VALIDATED);
        }
        else {
            command.saveEffect("* transitioning to Map Loaded state");
            _gameEngine.setCurrentGameState(GameStateType::MAP_LOADED);
        }
    } else {
        printInvalidCommandError();
    }
}

// Map Validated state class implementation
MapValidatedState::MapValidatedState(GameEngine &gameEngine)
    : GameState(gameEngine, new GameStateType(GameStateType::MAP_VALIDATED), new string("Map Validated")) {};

void MapValidatedState::update(){
    Command command = _gameEngine.getCommandProcessor().getCommand();

    if (_gameEngine.getCommandProcessor().validate(command, *_gameStateID)){
        command.saveEffect("* transitioning to Players Added state");
        _gameEngine.setCurrentGameState(GameStateType::PLAYERS_ADDED);
    } else {
        printInvalidCommandError();
    }
}

// Players Added state class implementation
PlayersAddedState::PlayersAddedState(GameEngine &gameEngine)
    : GameState(gameEngine, new GameStateType(GameStateType::PLAYERS_ADDED), new string("Players Added")){};

void PlayersAddedState::update(){
    Command command = _gameEngine.getCommandProcessor().getCommand();

    if (_gameEngine.getCommandProcessor().validate(command, *_gameStateID)){
        if (command.getCommand() == "gamestart")
        {
            command.saveEffect("* transitioning to Assign Reinforcement state");
            _gameEngine.setCurrentGameState(GameStateType::ASSIGN_REINFORCEMENT);
        }
        else {
            command.saveEffect("* transitioning to Players Added state");
            _gameEngine.setCurrentGameState(GameStateType::PLAYERS_ADDED);
        }
    } else {
        printInvalidCommandError();
    }        
}

// Assign Reinforcement state class implementation
AssignReinforcementState::AssignReinforcementState(GameEngine &gameEngine)
    : GameState(gameEngine, new GameStateType(GameStateType::ASSIGN_REINFORCEMENT), new string("Assign Reinforcement")){};

void AssignReinforcementState::update(){
    // string input = getUserCommand();

    // if (input == "issueorder")
    // {
    //     _gameEngine.setCurrentGameState(ISSUE_ORDERS);
    // }
    // else
    // {
    //     printInvalidCommandError();
    // }

    _gameEngine.setCurrentGameState(GameStateType::ISSUE_ORDERS);
}

// Issue Orders state class implementation
IssueOrdersState::IssueOrdersState(GameEngine &gameEngine)
    : GameState(gameEngine, new GameStateType(GameStateType::ISSUE_ORDERS), new string("Issue Orders")){};

void IssueOrdersState::update(){
//     string input = getUserCommand();

//     if (input == "issueorder")
//     {
//         printRemainingInStateMessage(*_name);
//     }
//     else if (input == "endissueorders")
//     {
//         _gameEngine.setCurrentGameState(EXECUTE_ORDERS);
//     }
//     else
//     {
//         printInvalidCommandError();
//     }
    _gameEngine.setCurrentGameState(GameStateType::EXECUTE_ORDERS);
}

// Execute Orders state class implementation
ExecuteOrdersState::ExecuteOrdersState(GameEngine &gameEngine)
    : GameState(gameEngine, new GameStateType(GameStateType::EXECUTE_ORDERS), new string("Execute Orders")){};

void ExecuteOrdersState::update(){
    // string input = getUserCommand();

    // if (input == "execorder")
    // {
    //     printRemainingInStateMessage(*_name);
    // }
    // else if (input == "endexecorders")
    // {
    //     _gameEngine.setCurrentGameState(ASSIGN_REINFORCEMENT);
    // }
    // else if (input == "win")
    // {
    //     _gameEngine.setCurrentGameState(WIN);
    // }
    // else
    // {
    //     printInvalidCommandError();
    // }

    _gameEngine.setCurrentGameState(GameStateType::WIN);
}

// Win state class implementation
WinState::WinState(GameEngine &gameEngine)
    : GameState(gameEngine, new GameStateType(GameStateType::WIN), new string("Win")){};

void WinState::update(){
    Command command = _gameEngine.getCommandProcessor().getCommand();

    if (_gameEngine.getCommandProcessor().validate(command, *_gameStateID)){
        if (command.getCommand() == "replay")
        {
            command.saveEffect("* transitioning to Start state");
            _gameEngine.setCurrentGameState(GameStateType::START);
        }
        else {
            cout << _gameEngine.getCommandProcessor();
            command.saveEffect("* transitioning to End state");
            _gameEngine.setCurrentGameState(GameStateType::END);
        }
    } else {
        printInvalidCommandError();
    }
}

// End state class implementation
EndState::EndState(GameEngine &gameEngine)
    : GameState(gameEngine, new GameStateType(GameStateType::END), new string("End")){};

void EndState::update(){};