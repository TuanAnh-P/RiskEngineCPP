#include <iostream>
#include <string>
#include <memory>
#include "GameEngine.h"

using namespace warzone;
using namespace std;

enum class GameStateType
{
    START,
    MAP_LOADED,
    MAP_VALIDATED,
    PLAYERS_ADDED,
    ASSIGN_REINFORCEMENT,
    ISSUE_ORDERS,
    EXECUTE_ORDERS,
    WIN
};

class StartState : public GameState<GameStateType>
{
public:
    StartState(GameEngine<GameStateType> &gameEngine)
        : GameState<GameStateType>(gameEngine,
                                   GameStateType::START,
                                   "Start")
    {
    }
    void enter()
    {
        GameState<GameStateType>::enter();
        cout << "Entered the " << _name << " State" << endl;
    }

    void update()
    {
        GameState<GameStateType>::update();

        string input;
        cin >> input;

        if (input == "loadmap")
        {
            _gameEngine.setCurrentGameState(GameStateType::MAP_LOADED);
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
                                   GameStateType::MAP_LOADED,
                                   "Map Loaded")
    {
    }
    void enter()
    {
        GameState<GameStateType>::enter();
        cout << "Entered the " << _name << " State" << endl;
    }

    void update()
    {
        GameState<GameStateType>::update();

        string input;
        cin >> input;

        if (input == "loadmap")
        {
            cout << "Remaining in the " << _name << " State" << endl;
        }
        else if (input == "validatemap")
        {
            _gameEngine.setCurrentGameState(GameStateType::MAP_VALIDATED);
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
                                   GameStateType::MAP_VALIDATED,
                                   "Map Validated")
    {
    }
    void enter()
    {
        GameState<GameStateType>::enter();
        cout << "Entered the " << _name << " State" << endl;
    }

    void update()
    {
        GameState<GameStateType>::update();

        string input;
        cin >> input;

        // if(input == "loadmap"){
        //    cout << "Remaining in the " <<  _name << " State" << endl;
        // } else if (input == "validatemap") {
        //     _gameEngine.setCurrentGameState(GameStateType::MAP_VALIDATED);
        // } else {
        //     cout << "Please enter a valid command..." << endl;
        // }
    }
};

class WinState : public GameState<GameStateType>
{
public:
    WinState(GameEngine<GameStateType> &gameEngine)
        : GameState<GameStateType>(gameEngine,
                                   GameStateType::WIN,
                                   "Win")
    {
    }
    void enter()
    {
        GameState<GameStateType>::enter();
        cout << "Entered the " << _name << " State" << endl;
    }

    void update()
    {
        GameState<GameStateType>::update();

        string input;
        cin >> input;

        // if(input == "loadmap"){
        //    cout << "Remaining in the " <<  _name << " State" << endl;
        // } else if (input == "validatemap") {
        //     _gameEngine.setCurrentGameState(GameStateType::MAP_VALIDATED);
        // } else {
        //     cout << "Please enter a valid command..." << endl;
        // }
    }
};

int main()
{
    // Create the game engine and add the valid states

    unique_ptr<GameEngine<GameStateType> > game = make_unique<GameEngine<GameStateType> >();

    GameState<GameStateType> &startState = game->add<GameStateType>(GameStateType::START);
    GameState<GameStateType> &mapLoadedState = game->add<GameStateType>(GameStateType::MAP_LOADED);
    GameState<GameStateType> &mapValidatedState = game->add<GameStateType>(GameStateType::MAP_VALIDATED);

    GameState<GameStateType> &winState = game->add<GameStateType>(GameStateType::MAP_VALIDATED);


    game->setCurrentGameState(GameStateType::START);

    bool done = false;
    while (true)
    {
        game->update();
    }
}
