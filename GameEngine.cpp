#include <iostream>
#include <string>
#include <memory>
#include "GameEngine.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace warzone;

namespace warzone
{
    void printInvalidCommandError()
    {
        cout << "Please enter a valid command..." << endl;
    };

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
    
    void GameState::enter(){
        cout << "\n\tEntered the " << _name << " State" << endl;
    }

    GameStateType GameState::getGameStateId(){
        return _gameStateID;
    }

    // Implementation of the GameState class methods
    GameEngine::GameEngine() : _currentGameState(nullptr) {};

    GameState& GameEngine::getGameState(GameStateType gameStateID){
        return *_gameStates[gameStateID];
    }

    GameState& GameEngine::getCurrentGameState(){
        return *_currentGameState;
    }

    template <typename S> 
    GameState& GameEngine::add(GameStateType gameStateID)
    {
        _gameStates[gameStateID] = std::unique_ptr<S>(new S(*this));
        return *_gameStates[gameStateID];
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

    StartState::~StartState() {};

    void StartState::update(){
        string input = getUserCommand();

        if (input == "loadmap")
        {
            _gameEngine.setCurrentGameState(MAP_LOADED);
        }
        else
        {
            cout << "Please enter a valid command..." << endl;
        }
    }

    // Map Loaded state class implementation
    MapLoadedState::MapLoadedState(GameEngine &gameEngine)
        : GameState(gameEngine, MAP_LOADED, "Map Loaded"){};

    MapLoadedState::~MapLoadedState() {};

    void MapLoadedState::update(){
        string input = getUserCommand();

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

    // Map Validated state class implementation
    MapValidatedState::MapValidatedState(GameEngine &gameEngine)
        : GameState(gameEngine, MAP_VALIDATED, "Map Validated"){};

    MapValidatedState::~MapValidatedState() {};

    void MapValidatedState::update(){
        string input = getUserCommand();

            if (input == "addplayer")
            {
                _gameEngine.setCurrentGameState(PLAYERS_ADDED);
            }
            else
            {
                cout << "Please enter a valid command..." << endl;
            }
    }

    // Players Added state class implementation
    PlayersAddedState::PlayersAddedState(GameEngine &gameEngine)
        : GameState(gameEngine, PLAYERS_ADDED, "Players Added"){};

    PlayersAddedState::~PlayersAddedState() {};

    void PlayersAddedState::update(){
        string input = getUserCommand();

        if (input == "addplayer")
        {
            cout << "Remaining in the " << _name << " State" << endl;
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

    AssignReinforcementState::~AssignReinforcementState() {};

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

    IssueOrdersState::~IssueOrdersState() {};

    void IssueOrdersState::update(){
        string input = getUserCommand();

        if (input == "issueorder")
        {
            cout << "Remaining in the " << _name << " State" << endl;
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

    ExecuteOrdersState::~ExecuteOrdersState() {};

    void ExecuteOrdersState::update(){
        string input = getUserCommand();

        if (input == "execorder")
        {
            cout << "Remaining in the " << _name << " State" << endl;
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

    WinState::~WinState() {};

    void WinState::update(){
        string input = getUserCommand();

        if (input == "play")
        {
            _gameEngine.setCurrentGameState(START);
        }
        else if (input == "end")
        {
            cout << "The game has finished. Thanks for playing :)" << endl;

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

    EndState::~EndState() {};

    void EndState::update(){
        cout << "hello";
    }
};


using namespace warzone;

int main(){
    std::unique_ptr<GameEngine> game(new GameEngine());

    GameState &startState = game->add<StartState>(START);
    GameState &mapLoadedState = game->add<MapLoadedState>(MAP_LOADED);
    GameState &mapValidatedState = game->add<MapValidatedState>(MAP_VALIDATED);
    GameState &playersAddedState = game->add<PlayersAddedState>(PLAYERS_ADDED);
    GameState &assignReinforcementState = game->add<AssignReinforcementState>(ASSIGN_REINFORCEMENT);
    GameState &issueOrdersState = game->add<IssueOrdersState>(ISSUE_ORDERS);
    GameState &executeOrders = game->add<ExecuteOrdersState>(EXECUTE_ORDERS);
    GameState &winState = game->add<WinState>(WIN);
    GameState &endState = game->add<EndState>(END);

    game->setCurrentGameState(START);

    while ((game->getCurrentGameState()).getGameStateId() != END)
    {
        game->update();
    }
};