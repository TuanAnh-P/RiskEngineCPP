#pragma once

#include <memory>
#include <map>
#include <string>

using std::string;

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
        explicit GameState(GameEngine &gameEngine,
                           GameStateType gameStateId,
                           string name);

        virtual ~GameState() = 0;

        GameStateType getGameStateId();

        void enter();

        virtual void update() = 0;
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

        // Get game state instance by ID
        GameState &getGameState(GameStateType gameStateID);

        // Get current GameState
        GameState &getCurrentGameState();

        // Add a new GameState to the game engine
        template <typename S>
        GameState &add(GameStateType gameStateID);

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
        
        ~StartState();

        void update();
    };

    class MapLoadedState : public GameState
    {
    public:
        MapLoadedState(GameEngine &gameEngine);
        
        ~MapLoadedState();

        void update();
    };

    class MapValidatedState : public GameState
    {
    public:
        MapValidatedState(GameEngine &gameEngine);

        ~MapValidatedState();

        void update();
    };

    class PlayersAddedState : public GameState
    {
    public:
        PlayersAddedState(GameEngine &gameEngine);

        ~PlayersAddedState();

        void update();
    };

    class AssignReinforcementState : public GameState
    {
    public:
        AssignReinforcementState(GameEngine &gameEngine);

        ~AssignReinforcementState();

        void update();
    };

    class IssueOrdersState : public GameState
    {
    public:
        IssueOrdersState(GameEngine &gameEngine);

        ~IssueOrdersState();

        void update();
    };

    class ExecuteOrdersState : public GameState
    {
    public:
        ExecuteOrdersState(GameEngine &gameEngine);

        ~ExecuteOrdersState();

        void update();
    };

    class WinState : public GameState
    {
    public:
        WinState(GameEngine &gameEngine);

        ~WinState();

        void update();
    };

    class EndState : public GameState
    {
    public:
        EndState(GameEngine &gameEngine);

        ~EndState();

        void update();
    };
};