# Risk Engine - C++ Game Implementation

A comprehensive C++ implementation of a Risk-style strategy board game engine. This project demonstrates advanced object-oriented programming concepts, design patterns, and game development architecture in C++.

## Overview

This game engine provides a complete framework for playing Risk-style board games with support for multiple AI strategies, map loading and validation, turn-based gameplay, and comprehensive logging. The implementation showcases several key design patterns including Strategy, Observer, State, and Adapter patterns.

## Contributors

| Contributor        | GitHub Profile                               |
| ------------------ | -------------------------------------------- |
| **Colton Leblond** | [@coltcodess](https://github.com/coltcodess) |
| **Tuan Anh Pham**  | [@TuanAnh-P](https://github.com/TuanAnh-P)   |
| **Khash Azad**     | [@khashazad](https://github.com/khashazad)   |
| **Ryan Li**        | [@Ryan2Li](https://github.com/Ryan2Li)       |
| **Abdullah Amir**  | [@AA789-ai](https://github.com/AA789-ai)     |

## Features

### Core Game Systems

- **Map Loading & Validation:** Loads game maps from `.map` files with complete structural validation including connectivity checks, continent subgraph verification, and territory uniqueness validation
- **Game State Management:** Implements a robust state machine that manages game flow through distinct phases: Startup, Reinforcement, Order Issuing, Order Execution, and Win/End conditions
- **Command Processing:** Flexible input system supporting both interactive console commands and batch file processing with comprehensive command validation and state-aware parsing
- **Multi-Player Support:** Full player management system tracking territories, card collections, reinforcement pools, and order queues

### AI and Strategy System

The engine implements multiple AI personalities using the Strategy pattern:

- **Human Player:** Interactive gameplay requiring user input for all decisions
- **Aggressive Player:** Focuses on territorial expansion and aggressive attacking strategies
- **Benevolent Player:** Defensive-oriented strategy that protects vulnerable territories
- **Neutral Player:** Passive behavior that switches to aggressive mode when attacked
- **Cheater Player:** Automated conquest of adjacent territories for testing purposes

### Game Mechanics

- **Card System:** Complete implementation of special ability cards including Bomb, Reinforcement, Blockade, Airlift, and Diplomacy with deck management
- **Order Management:** Comprehensive order system supporting Deploy, Advance, Bomb, Blockade, Airlift, and Negotiate commands with proper validation and execution
- **Tournament Mode:** Automated tournament system for running multiple games between AI players with statistical analysis and result logging

### Technical Features

- **Logging System:** Observer pattern implementation for comprehensive game event logging
- **Memory Management:** Proper C++ resource management with copy constructors and assignment operators
- **Modular Architecture:** Clean separation of concerns across multiple specialized modules

## Requirements

- C++ compiler with C++11 support or later (GCC 4.9+, Clang 3.4+, or MSVC 2015+)
- Standard C++ library
- No external dependencies required

## Building the Project

### Quick Build

To compile all components together:

```bash
g++ -std=c++11 -Wall -Wextra *.cpp -o RiskEngine
```

### Modular Build

For better compilation control, you can build specific components:

```bash
# Compile main game
g++ -std=c++11 -Wall MainDriver.cpp GameEngine.cpp Player.cpp Cards.cpp Orders.cpp map.cpp MapLoader.cpp CommandProcessing.cpp PlayerStrategies.cpp LoggingObserver.cpp LogObserver.cpp -o RiskEngine

# Compile individual test drivers
g++ -std=c++11 CardsDriver.cpp Cards.cpp -o CardTest
g++ -std=c++11 MapDriver.cpp map.cpp MapLoader.cpp -o MapTest
g++ -std=c++11 PlayerDriver.cpp Player.cpp Cards.cpp Orders.cpp map.cpp -o PlayerTest
```

### Build Options

Add these flags for different build configurations:

- Debug build: `-g -DDEBUG`
- Release build: `-O2 -DNDEBUG`
- Verbose warnings: `-Wall -Wextra -Wpedantic`

## Getting Started

### Running the Main Game

```bash
./RiskEngine
```

### Testing Individual Components

The project includes dedicated test drivers for each module:

```bash
./CardTest      # Test card system
./MapTest       # Test map loading and validation
./PlayerTest    # Test player mechanics
```

### Using Tournament Mode

For automated tournaments between AI players:

```bash
./RiskEngine -tournament
```

### Sample Maps

The `maps/` directory contains several example map files:

- `003_I72_Fairchild T-31.map` - Standard gameplay map
- `3D.map` - Alternative map layout
- `test.map` - Simple map for testing

## Project Architecture

The codebase is organized into focused modules with clear responsibilities:

### Core Components

- **Map/MapLoader** (`map.cpp`, `MapLoader.cpp`) - Territory and continent management with file parsing
- **Player/PlayerStrategies** (`Player.cpp`, `PlayerStrategies.cpp`) - Player representation and AI behaviors
- **GameEngine** (`GameEngine.cpp`) - State management and game flow orchestration
- **Orders** (`Orders.cpp`) - Command pattern implementation for player actions
- **Cards** (`Cards.cpp`) - Special ability system with deck management

### Supporting Systems

- **CommandProcessing** (`CommandProcessing.cpp`) - Input parsing and validation
- **LoggingObserver** (`LoggingObserver.cpp`) - Event logging and game state tracking
- **Driver Files** (`*Driver.cpp`) - Testing and demonstration programs

## Usage Examples

### Loading a Custom Map

```cpp
MapLoader loader;
Map* gameMap = loader.loadMap("maps/custom.map");
if (gameMap && gameMap->validate()) {
    // Map is ready for gameplay
}
```

### Setting Up Players

```cpp
std::vector<Player*> players;
players.push_back(new Player("Human", new HumanPlayerStrategy()));
players.push_back(new Player("AI_Aggressive", new AggressivePlayerStrategy()));
```

## File Formats

### Map File Structure

Map files use a specific format with sections for continents and territories. Each territory must specify its connections to adjacent territories, and all territories within a continent must form a connected subgraph.

### Command File Format

Command files contain one command per line and support all interactive commands including map loading, player setup, and game control.

## Technical Notes

- The game engine uses dynamic memory allocation for game objects - ensure proper cleanup
- Map validation includes checks for connected graphs and valid continent structures
- All AI strategies implement the same interface for consistent behavior
- The logging system captures all significant game events for analysis and debugging
- Tournament mode supports statistical analysis across multiple game sessions
