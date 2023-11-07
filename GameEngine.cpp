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
using namespace warzone;

namespace warzone
{
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
        if(*_gameStateID == END){
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
        out << "current state" << engine._currentGameState->getGameStateId() << endl;
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
            : GameState(gameEngine, new GameStateType(START), new string("Start")){};

    void StartState::update(){
        Command command = _gameEngine.getCommandProcessor().getCommand();

        if (_gameEngine.getCommandProcessor().validate(command, *_gameStateID)){
            _gameEngine.setCurrentGameState(MAP_LOADED);
        } else {
            printInvalidCommandError();
        }
    }

    // Map Loaded state class implementation
    MapLoadedState::MapLoadedState(GameEngine &gameEngine)
        : GameState(gameEngine, new GameStateType(MAP_LOADED), new string("Map Loaded")){};

    void MapLoadedState::update(){
        Command command = _gameEngine.getCommandProcessor().getCommand();

        if (_gameEngine.getCommandProcessor().validate(command, *_gameStateID)){
            if (command.getCommand() == "validatemap")
            {
                _gameEngine.setCurrentGameState(MAP_VALIDATED);
            }
            else {
                _gameEngine.setCurrentGameState(MAP_LOADED);
            }
        } else {
            printInvalidCommandError();
        }
    }

    // Map Validated state class implementation
    MapValidatedState::MapValidatedState(GameEngine &gameEngine)
        : GameState(gameEngine, new GameStateType(MAP_VALIDATED), new string("Map Validated")) {};

    void MapValidatedState::update(){
        Command command = _gameEngine.getCommandProcessor().getCommand();

        if (_gameEngine.getCommandProcessor().validate(command, *_gameStateID)){
            _gameEngine.setCurrentGameState(PLAYERS_ADDED);
        } else {
            printInvalidCommandError();
        }
    }

   // Players Added state class implementation
    PlayersAddedState::PlayersAddedState(GameEngine &gameEngine)
        : GameState(gameEngine, new GameStateType(PLAYERS_ADDED), new string("Players Added")){};

    void PlayersAddedState::update(){
        Command command = _gameEngine.getCommandProcessor().getCommand();

        if (_gameEngine.getCommandProcessor().validate(command, *_gameStateID)){
            if (command.getCommand() == "gamestart")
            {
                _gameEngine.setCurrentGameState(ASSIGN_REINFORCEMENT);
            }
            else {
                _gameEngine.setCurrentGameState(PLAYERS_ADDED);
            }
        } else {
            printInvalidCommandError();
        }        
    }

    // Assign Reinforcement state class implementation
    AssignReinforcementState::AssignReinforcementState(GameEngine &gameEngine)
        : GameState(gameEngine, new GameStateType(ASSIGN_REINFORCEMENT), new string("Assign Reinforcement")){};

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

        _gameEngine.setCurrentGameState(ISSUE_ORDERS);
    }

    // Issue Orders state class implementation
    IssueOrdersState::IssueOrdersState(GameEngine &gameEngine)
        : GameState(gameEngine, new GameStateType(ISSUE_ORDERS), new string("Issue Orders")){};

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
        _gameEngine.setCurrentGameState(EXECUTE_ORDERS);
    }

    // Execute Orders state class implementation
    ExecuteOrdersState::ExecuteOrdersState(GameEngine &gameEngine)
        : GameState(gameEngine, new GameStateType(EXECUTE_ORDERS), new string("Execute Orders")){};

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

        _gameEngine.setCurrentGameState(WIN);
    }

    // Win state class implementation
    WinState::WinState(GameEngine &gameEngine)
        : GameState(gameEngine, new GameStateType(WIN), new string("Win")){};

    void WinState::update(){
        Command command = _gameEngine.getCommandProcessor().getCommand();

        if (_gameEngine.getCommandProcessor().validate(command, *_gameStateID)){
            if (command.getCommand() == "replay")
            {
                _gameEngine.setCurrentGameState(START);
            }
            else {
                _gameEngine.setCurrentGameState(END);
            }
        } else {
            printInvalidCommandError();
        }
   }

    // End state class implementation
    EndState::EndState(GameEngine &gameEngine)
        : GameState(gameEngine, new GameStateType(END), new string("End")){};

    void EndState::update(){};
};