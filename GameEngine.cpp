#include <iostream>
#include <string>
#include <memory>
#include "GameEngine.h"

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

    void printRemainingInStateMessage(string name){
        cout << "\nRemaining in ------------> " << name << " State" << endl;
    }

    string getUserCommand()
    {
        cout << "\nPlease enter command: ";

        string command;
        cin >> command;

        return command;
    };

    // Implementation of the GameEngine class methods
    GameState::GameState(GameEngine &gameEngine, GameStateType gameStateId, string name):
        _name(name), _gameStateID(gameStateId), _gameEngine(gameEngine) {};
    
    ostream & operator << (ostream &out, GameState &state)
    {
        out << state._name << endl;
        return out;
    }


    void GameState::enter(){
        if(_gameStateID == END){
            cout << "\nThe game has finished. Thanks for playing :)\n" << endl;
        }else {
            cout << "\nEntering ------------> " << _name << " State" << endl;
        }
    }

    GameStateType GameState::getGameStateId(){
        return _gameStateID;
    }

    // Implementation of the GameState class methods
    GameEngine::GameEngine() : _currentGameState(nullptr) {};

    ostream & operator << (ostream &out, GameEngine &engine)
    {
        out << "current state" << engine._currentGameState->getGameStateId() << endl;
        return out;
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
            : GameState(gameEngine, START, "Start"){};

    void StartState::update(){
        string input = getUserCommand();

        if (input == "loadmap")
        {
            _gameEngine.setCurrentGameState(MAP_LOADED);
        }
        else
        {
            printInvalidCommandError();
        }
    }

    // Map Loaded state class implementation
    MapLoadedState::MapLoadedState(GameEngine &gameEngine)
        : GameState(gameEngine, MAP_LOADED, "Map Loaded"){};

    void MapLoadedState::update(){
        string input = getUserCommand();

        if (input == "loadmap")
        {
            printRemainingInStateMessage(_name);
        }
        else if (input == "validatemap")
        {
            _gameEngine.setCurrentGameState(MAP_VALIDATED);
        }
        else
        {
            printInvalidCommandError();
        }
    }

    // Map Validated state class implementation
    MapValidatedState::MapValidatedState(GameEngine &gameEngine)
        : GameState(gameEngine, MAP_VALIDATED, "Map Validated"){};

    void MapValidatedState::update(){
        string input = getUserCommand();

            if (input == "addplayer")
            {
                _gameEngine.setCurrentGameState(PLAYERS_ADDED);
            }
            else
            {
                printInvalidCommandError();
            }
    }

    // Players Added state class implementation
    PlayersAddedState::PlayersAddedState(GameEngine &gameEngine)
        : GameState(gameEngine, PLAYERS_ADDED, "Players Added"){};

    void PlayersAddedState::update(){
        string input = getUserCommand();

        if (input == "addplayer")
        {
            printRemainingInStateMessage(_name);
        }
        else if (input == "assigncountries")
        {
            _gameEngine.setCurrentGameState(ASSIGN_REINFORCEMENT);
        }
        else
        {
            printInvalidCommandError();
        }
    }

    // Assign Reinforcement state class implementation
    AssignReinforcementState::AssignReinforcementState(GameEngine &gameEngine)
        : GameState(gameEngine, ASSIGN_REINFORCEMENT, "Assign Reinforcement"){};

    void AssignReinforcementState::update(){
        string input = getUserCommand();

        if (input == "issueorder")
        {
            _gameEngine.setCurrentGameState(ISSUE_ORDERS);
        }
        else
        {
            printInvalidCommandError();
        }
    }


    // Issue Orders state class implementation
    IssueOrdersState::IssueOrdersState(GameEngine &gameEngine)
        : GameState(gameEngine, ISSUE_ORDERS, "Issue Orders"){};

    void IssueOrdersState::update(){
        string input = getUserCommand();

        if (input == "issueorder")
        {
            printRemainingInStateMessage(_name);
        }
        else if (input == "endissueorders")
        {
            _gameEngine.setCurrentGameState(EXECUTE_ORDERS);
        }
        else
        {
            printInvalidCommandError();
        }
    }

    // Execute Orders state class implementation
    ExecuteOrdersState::ExecuteOrdersState(GameEngine &gameEngine)
        : GameState(gameEngine, EXECUTE_ORDERS, "Execute Orders"){};

    void ExecuteOrdersState::update(){
        string input = getUserCommand();

        if (input == "execorder")
        {
            printRemainingInStateMessage(_name);
        }
        else if (input == "endexecorders")
        {
            _gameEngine.setCurrentGameState(ASSIGN_REINFORCEMENT);
        }
        else if (input == "win")
        {
            _gameEngine.setCurrentGameState(WIN);
        }
        else
        {
            printInvalidCommandError();
        }
    }

    // Win state class implementation
    WinState::WinState(GameEngine &gameEngine)
        : GameState(gameEngine, WIN, "Win"){};

    void WinState::update(){
        string input = getUserCommand();

        if (input == "play")
        {
            _gameEngine.setCurrentGameState(START);
        }
        else if (input == "end")
        {
            _gameEngine.setCurrentGameState(END);
        }
        else
        {
            printInvalidCommandError();
        }
    }

    // End state class implementation
    EndState::EndState(GameEngine &gameEngine)
        : GameState(gameEngine, END, "End"){};

    void EndState::update(){};
};