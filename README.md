# Warzone Game Engine (COMP 345 Project)

This project is a C++ implementation of a game engine for a Risk-style strategy board game, likely developed for the COMP 345 course. It includes modules for map handling, game flow management, player actions, different AI strategies, and game logging.

## Features

* **Map Loading & Validation:** Loads game maps from `.map` files and validates their structure (connectivity, continent subgraphs, territory uniqueness).
* **Game Engine:** Manages the game flow using a state pattern, progressing through phases like Startup, Reinforcement, Issuing Orders, Executing Orders, and Win/End states.
* **Command Processing:** Handles user input either from the console or a file, validating commands based on the current game state. Includes an Adapter pattern for file input.
* **Player Management:** Represents players, tracks their territories, cards, reinforcement pool, and issued orders.
* **Player Strategies:** Implements various player behaviors using the Strategy pattern:
    * Human Player (requires console input)
    * Aggressive Player (focuses on attacking)
    * Benevolent Player (focuses on protecting weak territories)
    * Neutral Player (passive until attacked, then becomes Aggressive)
    * Cheater Player (automatically conquers adjacent territories)
* **Card System:** Implements a deck and hand system for cards like Bomb, Reinforcement, Blockade, Airlift, and Diplomacy. Cards are played to issue corresponding orders.
* **Order System:** Manages different order types (Deploy, Advance, Bomb, Blockade, Airlift, Negotiate) placed by players into an order list for execution.
* **Logging:** Uses the Observer pattern to log game events (state changes, orders issued/executed) to `gamelog.txt`.
* **Tournament Mode:** Allows running multiple games automatically between specified AI players on various maps, logging results to `tournament.txt`.

## Project Structure

The project is divided into several C++ modules:

* `Map`/`MapLoader`: Handles territory, continent, and map representation, loading, and validation.
* `Player`/`PlayerStrategies`: Defines the Player class and different AI/Human behaviors.
* `Cards`: Implements the card, deck, and hand logic.
* `Orders`: Defines the different order types and the player's order list.
* `CommandProcessing`: Handles reading and validating user/file commands.
* `GameEngine`: Orchestrates the game flow and states.
* `LoggingObserver`/`LogObserver`: Implements the logging system.
* Drivers (`*Driver.cpp`): Contain test functions or main execution logic for different modules.

## How to Compile (Example)

(Note: A Makefile or specific build instructions were not provided. This is a general example.)

You can compile the project using a C++ compiler like g++. You'll need to compile all `.cpp` files and link them together. For example, to compile the main driver for command processing:

```bash
g++ -std=c++11 *.cpp -o WarzoneGame
```
