
#pragma once 

#include <map>
#include <string>

using namespace std;

class State 
{
    protected:
        string _name;
        GameEngine& _gameEngine;

    public:

        explicit State(GameEngine& gameEngine,
            std::string name = "default")
            : _name(name)
            , _gameEngine(gameEngine)
        {
        }

        virtual ~State() {}
        virtual void enter()
        {
        }
        virtual void exit()
        {
        }
        virtual void update()
        {
        }
};

class GameEngine {

    protected:
        // All states of the game
        std::map<string, std::unique_ptr<State>> _states;
        // The current state.
        State* _currentState;

    public: 
        GameEngine() : _currentState(nullptr) 
        {
        }

        State& getCurrentState()
        {
            return *_currentState;
        }

    protected:
        void setCurrentState(State* state)
        {
            if (_currentState == state)
            {
                return;
            }

            if (_currentState != nullptr)
            {
                _currentState->exit();
            }

            _currentState = state;
            if (_currentState != nullptr)
            {
                _currentState->enter();
            }
        }
}; 









