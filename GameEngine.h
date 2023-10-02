#pragma once

#include <memory>
#include <map>
#include <string>

using std::string;
using std::ostream;

namespace warzone
{
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

    void printInvalidCommandError();
    string getUserCommand();

    class GameEngine;

    class GameState
    {
    protected:
        string _name;
        GameStateType _gameStateID;
        GameEngine &_gameEngine;
    public:
        friend ostream & operator << (ostream &out, GameState &state);

        explicit GameState(GameEngine &gameEngine,
                           GameStateType gameStateId,
                           string name);

        virtual ~GameState() {};

        GameStateType getGameStateId();

        void enter();

        virtual void update() {};
    };

    class GameEngine
    {

    protected:
        // All GameStates of the game
        std::map<GameStateType, std::unique_ptr<GameState > > _gameStates;
        // The current GameState.
        GameState *_currentGameState;

    public:
        GameEngine();

        friend ostream & operator << (ostream &out, GameEngine &gameEngine);

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
        void update();

    protected:
        void setCurrentGameState(GameState *gameState);
    };

    class StartState : public GameState
    {
    public:
        StartState(GameEngine &gameEngine);

        void update();
    };

    class MapLoadedState : public GameState
    {
    public:
        MapLoadedState(GameEngine &gameEngine);

        void update();
    };

    class MapValidatedState : public GameState
    {
    public:
        MapValidatedState(GameEngine &gameEngine);

        void update();
    };

    class PlayersAddedState : public GameState
    {
    public:
        PlayersAddedState(GameEngine &gameEngine);

        void update();
    };

    class AssignReinforcementState : public GameState
    {
    public:
        AssignReinforcementState(GameEngine &gameEngine);

        void update();
    };

    class IssueOrdersState : public GameState
    {
    public:
        IssueOrdersState(GameEngine &gameEngine);

        void update();
    };

    class ExecuteOrdersState : public GameState
    {
    public:
        ExecuteOrdersState(GameEngine &gameEngine);

        void update();
    };

    class WinState : public GameState
    {
    public:
        WinState(GameEngine &gameEngine); 

        void update();
    };

    class EndState : public GameState
    {
    public:
        EndState(GameEngine &gameEngine);

        void update();
    };
};