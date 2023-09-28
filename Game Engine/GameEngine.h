#pragma once

#include <memory>
#include <map>
#include <string>
#include <assert.h>

using std::string;
using std::cout;
using std::endl;

namespace warzone
{
    void printStateEnterMessage();

    template <typename T>
    class GameEngine;

    template <typename T>
    class GameState
    {
    protected:
        string _name;
        T _gameStateID;
        GameEngine<T>& _gameEngine;

    public:
        explicit GameState(GameEngine<T> &gameEngine,
                           T gameStateId,
                           string name)
            : _name(name),
              _gameStateID(gameStateId),
              _gameEngine(gameEngine)
        {
        }

        virtual void enter()
        {
        }

        virtual void update()
        {
        }

        virtual void exit()
        {
        }
    };

    template <typename T>
    class GameEngine
    {

    protected:
        // All GameStates of the game
        std::map<T, std::unique_ptr<GameState<T> > > _gameStates;
        // The current GameState.
        GameState<T> *_currentGameState;

    public:
        GameEngine() : _currentGameState(nullptr)
        {
        }

        GameState<T> &getGameState(T gameStateID)
        {
            return *_gameStates[gameStateID];
        }

        // Get current GameState
        GameState<T> &getCurrentGameState()
        {
            return *_currentGameState;
        }

        // Add a new GameState to the game engine
        template <class S>
        GameState<T> &add(T gameStateID)
        {
            // static_assert(not std::is_same<GameState<T>, S>());
            _gameStates[gameStateID] = std::unique_ptr<S>(new S(*this));
            return *_gameStates[gameStateID];
        }

        void setCurrentGameState(T gameStateID)
        {
            GameState<T> *gameState = &getGameState(gameStateID);
            setCurrentGameState(gameState);
        }

        void update()
        {
            if (_currentGameState != nullptr)
            {
                _currentGameState->update();
            }
        }

    protected:
        void setCurrentGameState(GameState<T>* gameState)
        {
            if (_currentGameState == gameState)
            {
                return;
            }

            if (_currentGameState != nullptr)
            {
                _currentGameState->exit();
            }

            _currentGameState = gameState;
            if (_currentGameState != nullptr)
            {
                _currentGameState->enter();
            }
        }
    };
}