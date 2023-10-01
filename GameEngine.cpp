#include <iostream>
#include <string>
#include <memory>
#include "GameEngine.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using namespace warzone; 

namespace warzone{

enum GameStateType
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

void printStateEnterMessage(string stateName){
    cout << "Entered the " << stateName << " State" << endl;
};

void printInvalidCommandError(){
    cout << "Please enter a valid command..." << endl;
};

string getUserCommand(){
  cout <<  "\nPlease enter command: "; 

  string command;
  cin >> command;

  return command; 
};

class StartState : public GameState<GameStateType>
{
public:
    StartState(GameEngine<GameStateType> &gameEngine)
        : GameState<GameStateType>(gameEngine,
                                   START,
                                   "Start")
    {
        
    }

    void enter(){
        printStateEnterMessage(_name);
    }

    void update()
    {
        string input =  getUserCommand();

        if (input == "loadmap")
        {
            _gameEngine.setCurrentGameState(MAP_LOADED);
        }
        else
        {
            cout << "Please enter a valid command..." << endl;
        }
    }
};

class MapLoadedState : public GameState<GameStateType>
{
public:
    MapLoadedState(GameEngine<GameStateType> &gameEngine)
        : GameState<GameStateType>(gameEngine,
                                    MAP_LOADED,
                                   "Map Loaded")
    {
    }

    void enter() {
        printStateEnterMessage(_name);
    }

    void update()
    {
        string input =  getUserCommand();

        if (input == "loadmap")
        {
            cout << "Remaining in the " << _name << " State" << endl;
        }
        else if (input == "validatemap")
        {
            _gameEngine.setCurrentGameState(MAP_VALIDATED);
        }
        else
        {
            cout << "Please enter a valid command..." << endl;
        }
    }
};

class MapValidatedState : public GameState<GameStateType>
{
public:
    MapValidatedState(GameEngine<GameStateType> &gameEngine)
        : GameState<GameStateType>(gameEngine,
                                   MAP_VALIDATED,
                                   "Map Validated")
    {
    }

    void enter() {
        printStateEnterMessage(_name);
    }

    void update()
    {
        string input =  getUserCommand();

        if (input == "addplayer") {
            _gameEngine.setCurrentGameState(PLAYERS_ADDED);
        } else {
            cout << "Please enter a valid command..." << endl;
        }
    }
};

class PlayersAddedState : public GameState<GameStateType>
{
public:
    PlayersAddedState(GameEngine<GameStateType> &gameEngine)
        : GameState<GameStateType>(gameEngine,
                                   PLAYERS_ADDED,
                                   "Players Added")
    {
    }

    void enter() {
        printStateEnterMessage(_name);
    }

    void update()
    {
        string input =  getUserCommand();

        if(input == "addplayer"){
           cout << "Remaining in the " <<  _name << " State" << endl;
        } else if (input == "assigncountries") {
            _gameEngine.setCurrentGameState(ASSIGN_REINFORCEMENT);
        } else {
            printInvalidCommandError();
        }
    }
};

class AssignReinforcementState : public GameState<GameStateType>
{
public:
    AssignReinforcementState(GameEngine<GameStateType> &gameEngine)
        : GameState<GameStateType>(gameEngine,
                                   ASSIGN_REINFORCEMENT,
                                   "Assign Reinforcement")
    {
    }

    void enter() {
        printStateEnterMessage(_name);
    }

    void update()
    {
        string input =  getUserCommand();

        if(input == "issueorder"){
           _gameEngine.setCurrentGameState(ISSUE_ORDERS);
        } else {
            printInvalidCommandError();
        }
    }
};

class IssueOrdersState : public GameState<GameStateType>
{
public:
    IssueOrdersState(GameEngine<GameStateType> &gameEngine)
        : GameState<GameStateType>(gameEngine,
                                   ISSUE_ORDERS,
                                   "Issue Orders")
    {
    }

    void enter() {
        printStateEnterMessage(_name);
    }

    void update()
    {
        string input =  getUserCommand();

        if(input == "issueorder"){
           cout << "Remaining in the " <<  _name << " State" << endl;
        } else if (input == "endissueorders") {
            _gameEngine.setCurrentGameState(EXECUTE_ORDERS);
        } else {
            printInvalidCommandError();
        }
    }
};

class ExecuteOrdersState : public GameState<GameStateType>
{
public:
    ExecuteOrdersState(GameEngine<GameStateType> &gameEngine)
        : GameState<GameStateType>(gameEngine,
                                   EXECUTE_ORDERS,
                                   "Execute Orders")
    {
    }

    void enter() {
        printStateEnterMessage(_name);
    }

    void update()
    {
        string input =  getUserCommand();

        if(input == "execorder"){
           cout << "Remaining in the " <<  _name << " State" << endl;
        } else if (input == "endexecorders") {
            _gameEngine.setCurrentGameState(ASSIGN_REINFORCEMENT);
        } 
        else if (input == "win") {
            _gameEngine.setCurrentGameState(WIN);
        }else {
            printInvalidCommandError();
        }
    }
};

class WinState : public GameState<GameStateType>
{
public:
    WinState(GameEngine<GameStateType> &gameEngine)
        : GameState<GameStateType>(gameEngine,
                                   WIN,
                                   "Win")
    {
    }

    void enter() {
        printStateEnterMessage(_name);
    }

    void update()
    {
        string input =  getUserCommand();

        if (input == "play") {
            _gameEngine.setCurrentGameState(START);
        } else if (input == "end") {
            _gameEngine.setCurrentGameState(END);
        } else {
            printInvalidCommandError();
        }
    }
};

class EndState : public GameState<GameStateType>
{
public:
    EndState(GameEngine<GameStateType> &gameEngine)
        : GameState<GameStateType>(gameEngine,
                                   END,
                                   "End")
    {
    }

    void enter() {
        cout << "The game has finished. Thanks for playing :)" << endl;
    }
};

};

int main()
{
    // Create the game engine and add the valid states

    std::unique_ptr<GameEngine<GameStateType> > game(new GameEngine<GameStateType>());

    GameState<GameStateType> &startState = game->add<StartState>(START);
    GameState<GameStateType> &mapLoadedState = game->add<MapLoadedState>(MAP_LOADED);
    GameState<GameStateType> &mapValidatedState = game->add<MapValidatedState>(MAP_VALIDATED);
    GameState<GameStateType> &playersAddedState = game->add<PlayersAddedState>(PLAYERS_ADDED);
    GameState<GameStateType> &assignReinforcementState = game->add<AssignReinforcementState>(ASSIGN_REINFORCEMENT);
    GameState<GameStateType> &issueOrdersState = game->add<IssueOrdersState>(ISSUE_ORDERS);
    GameState<GameStateType> &executeOrders = game->add<ExecuteOrdersState>(EXECUTE_ORDERS);
    GameState<GameStateType> &winState = game->add<WinState>(WIN);
    GameState<GameStateType> &endState = game->add<EndState>(END);


    game->setCurrentGameState(START);

    while ((game->getCurrentGameState()).getGameStateId() != END)
    {
        game->update();
    }
}