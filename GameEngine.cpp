#include <iostream>
#include <string>
#include <memory>
#include "GameEngine.h"
#include "CommandProcessing.h"

#include <algorithm>
#include <random>
#include <chrono>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;

string gameStateTypeToString(GameStateType state) {
    switch (state) {
        case GameStateType::START:
            return "START";
        case GameStateType::MAP_LOADED:
            return "MAP_LOADED";
        case GameStateType::MAP_VALIDATED:
            return "MAP_VALIDATED";
        case GameStateType::PLAYERS_ADDED:
            return "PLAYERS_ADDED";
        case GameStateType::ASSIGN_REINFORCEMENT:
            return "ASSIGN_REINFORCEMENT";
        case GameStateType::ISSUE_ORDERS:
            return "ISSUE_ORDERS";
        case GameStateType::EXECUTE_ORDERS:
            return "EXECUTE_ORDERS";
        case GameStateType::WIN:
            return "WIN";
        case GameStateType::END:
            return "END";
        default:
            return "UNKNOWN";
    }
}

void printInvalidCommandError()
{
    cout << "\nInvalid Command entered..." << endl;
};



// Implementation of the GameEngine class methods / constructors
GameState::GameState(GameEngine &gameEngine, GameStateType *gameStateId, string *name):
        _name(name), _gameStateID(gameStateId), _gameEngine(gameEngine) {};

GameState::GameState(GameState &gameState):
        _name(gameState._name), _gameStateID(gameState._gameStateID), _gameEngine(gameState._gameEngine) {};

GameState::~GameState(){
    delete _name;
}

void GameState::operator= (const GameState &gameState){
    _gameEngine = gameState._gameEngine;
    _gameStateID = gameState._gameStateID;
    _name = gameState._name;
}

ostream & operator << (ostream &out, GameState &state)
{
    out << state._name << endl;
    return out;
}

void GameState::enter(){
    if(*_gameStateID == GameStateType::END){
        cout << "\nThe game has finished. Thanks for playing :)\n" << endl;
    }else {
        cout << "\nEntering ------------> " << *_name << " State" << endl;
    }
}

GameStateType GameState::getGameStateId(){
    return *_gameStateID;
}

//Startuphase
void GameEngine::startupPhase() {
    CommandProcessor commandProcessor;

    while (true) {
        // Get a command from the command processor
        Command& command = commandProcessor.getCommand();

        // Retrieve the command string
        string commandStr = command.getCommand();

        //Retrive the game state
        GameStateType gameState = getCurrentGameState().getGameStateId();
        bool stateValidated = commandProcessor.validate(command, gameState);

        //do the appropriate sequence
        if (commandStr.rfind("tournament", 0) == 0 && stateValidated) { //TODO wrong tournament format, and valids
            // Find the positions of various parameters in the command
            size_t posM = commandStr.find("-M");
            if (posM == std::string::npos) continue;
            size_t posP = commandStr.find("-P");
            if (posP == std::string::npos) continue;
            size_t posG = commandStr.find("-G");
            if (posG == std::string::npos) continue;
            size_t posD = commandStr.find("-D");
            if (posD == std::string::npos) continue;

            // Extract the lists of map files and player strategies
            std::string mapFilesStr = commandStr.substr(posM + 3, posP - posM - 4);
            std::string playerStrategiesStr = commandStr.substr(posP + 3, posG - posP - 4);

            // Extract the numerical values
            int numberOfGames = std::stoi(commandStr.substr(posG + 2, posD - posG - 2));
            int maxNumberOfTurns = std::stoi(commandStr.substr(posD + 2));

            // Create vectors to store map files and player strategies
            std::vector<std::string> mapFiles;
            std::vector<std::string> playerStrategies;

            // Use stringstream to split comma-separated values into vectors
            std::stringstream mapFilesStream(mapFilesStr);
            std::stringstream playerStrategiesStream(playerStrategiesStr);
            std::string mapFile;
            std::string playerStrategy;

            // Extract map files
            while (std::getline(mapFilesStream, mapFile, ',')) {
                mapFiles.push_back(mapFile);
            }

            // Extract player strategies
            while (std::getline(playerStrategiesStream, playerStrategy, ',')) {
                playerStrategies.push_back(playerStrategy);
            }

            // Now you have the extracted information in vectors
            // Loop through and print the values
//            std::cout << "Map Files: ";
//            for (const auto& mapFile : mapFiles) {
//                std::cout << mapFile << " ";
//            }
//            std::cout << "\nPlayer Strategies: ";
//            for (const auto& strategy : playerStrategies) {
//                std::cout << strategy << " ";
//            }
//            std::cout << "\nNumber of Games: " << numberOfGames << "\nMax Number of Turns: " << maxNumberOfTurns << std::endl;

            if(numberOfGames < 1 || numberOfGames > 5){
                cout << "Please enter 1-5 Games";
                continue;
            }

            if(maxNumberOfTurns < 10 || maxNumberOfTurns > 50){
                cout << "Please enter 10-50 Turns";
                continue;
            }

            if(mapFiles.size() < 1 || mapFiles.size() > 5){
                cout << "Please enter 1-5 Maps";
                continue;
            }

            if(playerStrategies.size() < 1 || playerStrategies.size() > 4){
                cout << "Please enter 1-4 Players";
                continue;
            }

            for(int k = 0; k < mapFiles.size(); k++){
                for(int i = 0; i < numberOfGames; i++){
                    setCurrentGameState(GameStateType::START);
                    //loadmap Phase
                    string filename = "./maps/" + mapFiles[k];
                    bool mapLoaded = loadMap(filename);
                    if(mapLoaded){
                        _currentGameState->update(command);
                        Notify(this);
                    }

                    //validatemap Phase
                    bool mapValidated = validateMap();
                    if (mapValidated){
                        _currentGameState->update(command);
                        Notify(this);
                    }

                    //add player Phase
                    players.clear();
                    for(int j = 0; j < playerStrategies.size(); j++){
                        string player = "player" + std::to_string(j);
                        std::string strategy = playerStrategies[j];

                        if(strategy == "Aggressive") {
                            addPlayer(player, StrategyType::AggressivePlayer);
                        }
                        else if(strategy == "Benevolent") {
                            addPlayer(player, StrategyType::BenevolentPlayer);
                        }
                        else if(strategy == "Neutral") {
                            addPlayer(player, StrategyType::NeutralPlayer);
                        }
                        else if(strategy == "Cheater") {
                            addPlayer(player, StrategyType::CheaterPlayer);
                        }
                        _currentGameState->update(command);
                        Notify(this);
                    }

                    //start game Phase
                    gameStart();
                    play(maxNumberOfTurns);

                }

            }
            delete &command;
            delete &mapFiles;
            delete &playerStrategies;
            return;

        }
        else if (commandStr.rfind("loadmap ", 0) == 0 && stateValidated) {
            //load  map
            string filename = "./maps/" + commandStr.substr(8);
            bool mapLoaded = loadMap(filename);
            if(mapLoaded){
                //_currentGameState->update(command);
                setCurrentGameState(GameStateType::MAP_LOADED);
                Notify(this);
            }
        } else if (commandStr == "validatemap" && stateValidated) {
            // Validate the map
            bool mapValidated = validateMap();
            if (mapValidated){
                _currentGameState->update(command);
                Notify(this);
            }
        } else if (commandStr.rfind("addplayer ", 0) == 0 && stateValidated) {
            // Add a player
            string player = commandStr.substr(9);
            addPlayer(player, StrategyType::HumanPlayer);
            _currentGameState->update(command);
            Notify(this);
        } else if (commandStr == "gamestart" && stateValidated) {
            //starts game
            if (players.size() >= 2){
                delete &command;
                gameStart();
                break;
            } else {
                cout << "Please enter at least 2 players";
            }
        } else {
            std::cout << "Invalid command for the current state." << std::endl;
        }

        delete &command;
    }
    play(-10);
}

//loads map
bool GameEngine::loadMap(const std::string& filename) {
    MapLoader loader(filename);
    Map* newMap = loader.loadMap();

    cout << "opening map: " << filename << endl;
    if (!newMap) {
        std::cout << "Failed to load the map." << std::endl;
        return false;
    } else {
        delete gameMap;
        gameMap = newMap;
        std::cout << "Map: " << filename.substr(7) << " loaded successfully." << std::endl;
        return true;
    }
}

//validates map
bool GameEngine::validateMap() {
    if (gameMap == nullptr) {
        std::cout << "No map loaded to validate." << std::endl;
        return false;
    }
    if (gameMap->isValid()) {
        std::cout << "The map is valid." << std::endl;
        return true;
    } else {
        std::cout << "The map is invalid." << std::endl;
        return false;
    }
}

//just addsplayers
void GameEngine::addPlayer(const std::string& playerName, StrategyType strat) {
    if (players.size() >= 6) {
        std::cout << "Maximum number of players reached." << std::endl;
    } else {
        players.push_back(new Player(playerName, strat));
        std::cout << "Player " << playerName << " added." << std::endl;
    }
}

void GameEngine::distributeTerritories() {
    // Get all territories from the map
    std::vector<Territory*> allTerritories;
    for (const Continent* continent : gameMap->getContinents()) {
        const auto& territories = continent->getTerritories();
        allTerritories.insert(allTerritories.end(), territories.begin(), territories.end());
    }

    // Shuffle territories
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(allTerritories.begin(), allTerritories.end(), std::default_random_engine(seed));

    // Distribute territories among players
    size_t playerIndex = 0;
    for (Territory* territory : allTerritories) {
        players[playerIndex]->addTerritory(territory);

        cout << "Player " << players[playerIndex]->getPlayerID() << " has been assigned territory " << territory->getName() << endl;
        playerIndex = (playerIndex + 1) % players.size();
    }
}

void GameEngine::randomizePlayerOrder() {
    std::cout << "Player order before randomizing:" << std::endl;
    for (const auto& player : players) {
        std::cout << player->getPlayerID() << std::endl;
    }

    // shuffle players list order
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(players.begin(), players.end(), std::default_random_engine(seed));

    std::cout << "Player order after randomizing:" << std::endl;
    for (const auto& player : players) {
        std::cout << player->getPlayerID() << std::endl;
    }
}


void GameEngine::initializeReinforcementPools() {
    for (Player* player : players) {
        player->setReinforcementPool(50);
    }
}

void GameEngine::drawInitialCards() {
    for (Player* player : players) {
        for(int i = 0; i < 2; i++){
            deck->draw(player->getHand());
        }
        cout << "Player "<< player->getPlayerID() << "'s cards: " << player->getHand() << endl ;
    }
}

void GameEngine::gameStart(){
    cout << "distribituing territories" << endl;
    distributeTerritories();
    cout << "rendomizing order" << endl;
    randomizePlayerOrder();
    cout << "initialize reinforcement pool" << endl;
    initializeReinforcementPools();
    cout << "drawing initial cards" << endl;
    deck = new Deck();
    drawInitialCards();
}

void GameEngine::play(int turns){
    // tuan you need to encapsulate everything inside here I believe
    cout<< "Playing now" << endl;
    mainGameLoop(turns);
}

void GameEngine::reinforcementPhase() {
    cout << "<----------The reinforcement phase begin---------->" << endl;
    for(Player* player: players){
        int numReinforcement = std::floor(static_cast<double>(player->getOwnedTerritories().size()) / 3);
        int continentOwned = 0;
        for(Continent* continent : gameMap->getContinents()){
            if (player->isContinentOwned(continent)){
                numReinforcement += continent->getBonus();
                continentOwned++;
            }
        }
        int finalNumReinforcement = std::max(3, numReinforcement);
        player->addReinforcementPool(finalNumReinforcement);
        cout << player->getPlayerID() << " owns " << player->getOwnedTerritories().size() << " territories and " << continentOwned << " continents" << endl;
        cout << player->getPlayerID() << " receives " << finalNumReinforcement << " army units and now has " << player->getReinforcementPool() << " army units" << endl;
        cout << endl;
    }
}

void GameEngine::issueOrdersPhase(string orderType) {
    if (orderType == "Deploy"){
        cout << "<----------The Deploy orders issuing phase begins---------->" << endl;
        for(Player* player: players) {
            player->issueOrder(deck, this, orderType);
        }
    }

    if (orderType == "Else"){
        cout << "<----------The Non-deploy orders issuing phase begins---------->" << endl;
        for(Player* player: players) {
            player->issueOrder(deck, this, orderType);
        }
    }
}


void GameEngine::executeOrdersPhase(string orderType) {

    if (orderType == "Deploy"){
        cout << "<----------The Deploy orders executing phase begins---------->" << endl;
        for(Player* player: players) {
            cout << player->getPlayerID() << " is executing orders from his order list" << endl;
            // Display the player's orders list
            std::cout << "Displaying " << player->getPlayerID() << " orders list" << std::endl;
            player->getOrdersList().print();

            cout << "The orders will be executed one by one: " << endl;
            for (Order* order : player->getOrdersList().orders){
                if (order->type == "Deploy") {
                    order->execute();
                    player->getOrdersList().orders.erase(std::remove(player->getOrdersList().orders.begin(), player->getOrdersList().orders.end(), order), player->getOrdersList().orders.end());
                }
            }
            cout << endl;
        }
    }

    if (orderType == "Else"){
        cout << "<----------The Non-Deploy orders executing phase begins---------->" << endl;
        for(Player* player: players) {
            cout << player->getPlayerID() << " is executing orders from his order list" << endl;
            // Display the player's orders list
            std::cout << "Displaying " << player->getPlayerID() << " orders list" << std::endl;
            player->getOrdersList().print();

            cout << "The orders will be executed one by one: " << endl;
            for (Order* order : player->getOrdersList().orders){
                if (order->type != "Deploy") {
                    order->execute();
                    player->getOrdersList().orders.erase(std::remove(player->getOrdersList().orders.begin(), player->getOrdersList().orders.end(), order), player->getOrdersList().orders.end());
                }
            }
            cout << endl;
        }
    }
}

void GameEngine::mainGameLoop(int turns) {
    int round = 1;
    int numPlayersLeft = players.size();

    while(numPlayersLeft>1 && (round <= turns || turns == -10)){
        cout << "<--------------------Start of round #" << round<< "-------------------->" << endl;
        setCurrentGameState(GameStateType::ASSIGN_REINFORCEMENT);
        reinforcementPhase();
        setCurrentGameState(GameStateType::ISSUE_ORDERS);
        issueOrdersPhase("Deploy");
        setCurrentGameState(GameStateType::EXECUTE_ORDERS);
        executeOrdersPhase("Deploy");
        setCurrentGameState(GameStateType::ISSUE_ORDERS);
        issueOrdersPhase("Else");
        setCurrentGameState(GameStateType::EXECUTE_ORDERS);
        executeOrdersPhase("Else");
        round++;
        for(Player* player: getPlayers()){
            if (player->getOwnedTerritories().size() == 0) {
                cout << player->getPlayerID() << " is be kicked out of the game because he doesn't own territories" << endl;
                players.erase(std::remove(players.begin(), players.end(), player), players.end());
                numPlayersLeft--;
            }
        }
        std::cout << "Press Enter to continue...";
        std::string dummy;
        std::getline(std::cin, dummy);  // Wait for the user to press Enter
    }
    if(numPlayersLeft>1){
        setCurrentGameState(GameStateType::END);
        cout << "Game is a DRAW!";
    }
    else{
        setCurrentGameState(GameStateType::WIN);
        Player* winner = players.at(0);
        cout << "Congratulation! " << winner->getPlayerID() << " is the winner";
    }
}

Player* GameEngine::getPlayerByID(const string& playerID) {
    for (Player* player : players) {
        if (player->getPlayerID() == playerID) {
            return player;
        }
    }
    return nullptr;  // Player with the specified ID not found
}

Territory* GameEngine::getTerritoryByName(const string& territoryName){
    for (const Territory* territory : getAllTerritories()) {
        if (territory->getName() == territoryName) {
            return const_cast<Territory*>(territory); // Use const_cast if territories is a member variable
        }
    }
    return nullptr;  // Territory with the specified name not found
}

const std::vector<Player*>& GameEngine::getPlayers() const {
    return players;
}

const std::vector<Territory*>& GameEngine::getAllTerritories() const {
    std::vector<Territory*>* allTerritories = new std::vector<Territory*>();
    for (const Continent* continent : gameMap->getContinents()) {
        const auto& territories = continent->getTerritories();
        allTerritories->insert(allTerritories->end(), territories.begin(), territories.end());
    }
    return *allTerritories;
}


//New constructor
GameEngine::GameEngine() : gameMap(nullptr), _currentGameState(nullptr), neutralPlayer(new Player("Neutral Player")) {};

//Need destructor
GameEngine::~GameEngine() {
    delete gameMap;
    for (auto player : players) {
        delete player;
    }
    delete deck;

    _gameStates.clear();

    delete _currentGameState;

    delete _commandProcessor;

    delete neutralPlayer;
}

GameEngine::GameEngine(CommandProcessor& commandProcessor): _commandProcessor(&commandProcessor) {};

GameEngine::GameEngine(GameEngine &engine) :
        _currentGameState(engine._currentGameState), _gameStates(engine._gameStates) {};

ostream & operator << (ostream &out, GameEngine &engine)
{
    out << "current state" << gameStateTypeToString(engine._currentGameState->getGameStateId())<< endl;
    return out;
}

void GameEngine::operator= (const GameEngine &gameEngine){
    _gameStates = gameEngine._gameStates;
    _currentGameState = gameEngine._currentGameState;
}

CommandProcessor& GameEngine::getCommandProcessor() {
    return *_commandProcessor;
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

void GameEngine::update(Command& command){
    if (_currentGameState != nullptr)
    {
        _currentGameState->update(command);
        Notify(this);
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
        : GameState(gameEngine, new GameStateType(GameStateType::START), new string("Start")){};

void StartState::update(Command& command){
    if(command.getCommand() == "loadmap")
    {
        command.saveEffect("* transitioning to Map Loaded state");
        _gameEngine.setCurrentGameState(GameStateType::MAP_LOADED);
    }
    if(command.getCommand() == "tournament") {

    }
}

// Map Loaded state class implementation
MapLoadedState::MapLoadedState(GameEngine &gameEngine)
        : GameState(gameEngine, new GameStateType(GameStateType::MAP_LOADED), new string("Map Loaded")){};

void MapLoadedState::update(Command& command){

    if (command.getCommand() == "validatemap")
    {
        command.saveEffect("* transitioning to Map Validated state");
        _gameEngine.setCurrentGameState(GameStateType::MAP_VALIDATED);
    }
    else {
        command.saveEffect("* transitioning to Map Loaded state");
        _gameEngine.setCurrentGameState(GameStateType::MAP_LOADED);
    }
}

// Map Validated state class implementation
MapValidatedState::MapValidatedState(GameEngine &gameEngine)
        : GameState(gameEngine, new GameStateType(GameStateType::MAP_VALIDATED), new string("Map Validated")) {};

void MapValidatedState::update(Command& command){
    command.saveEffect("* transitioning to Players Added state");
    _gameEngine.setCurrentGameState(GameStateType::PLAYERS_ADDED);
}

// Players Added state class implementation
PlayersAddedState::PlayersAddedState(GameEngine &gameEngine)
        : GameState(gameEngine, new GameStateType(GameStateType::PLAYERS_ADDED), new string("Players Added")){};

void PlayersAddedState::update(Command& command){
    if (command.getCommand() == "gamestart")
    {
        command.saveEffect("* transitioning to Assign Reinforcement state");
        _gameEngine.setCurrentGameState(GameStateType::ASSIGN_REINFORCEMENT);
    }
    else {
        command.saveEffect("* transitioning to Players Added state");
        _gameEngine.setCurrentGameState(GameStateType::PLAYERS_ADDED);
    }
}

// Assign Reinforcement state class implementation
AssignReinforcementState::AssignReinforcementState(GameEngine &gameEngine)
        : GameState(gameEngine, new GameStateType(GameStateType::ASSIGN_REINFORCEMENT), new string("Assign Reinforcement")){};

void AssignReinforcementState::update(Command& command){
    _gameEngine.setCurrentGameState(GameStateType::ISSUE_ORDERS);
}

// Issue Orders state class implementation
IssueOrdersState::IssueOrdersState(GameEngine &gameEngine)
        : GameState(gameEngine, new GameStateType(GameStateType::ISSUE_ORDERS), new string("Issue Orders")){};

void IssueOrdersState::update(Command& command){
    _gameEngine.setCurrentGameState(GameStateType::EXECUTE_ORDERS);
}

// Execute Orders state class implementation
ExecuteOrdersState::ExecuteOrdersState(GameEngine &gameEngine)
        : GameState(gameEngine, new GameStateType(GameStateType::EXECUTE_ORDERS), new string("Execute Orders")){};

void ExecuteOrdersState::update(Command &command){
    _gameEngine.setCurrentGameState(GameStateType::WIN);
}

// Win state class implementation
WinState::WinState(GameEngine &gameEngine)
        : GameState(gameEngine, new GameStateType(GameStateType::WIN), new string("Win")){};

void WinState::update(Command& command){
    if (command.getCommand() == "replay")
    {
        command.saveEffect("* transitioning to Start state");
        _gameEngine.setCurrentGameState(GameStateType::START);
    }
    else {
        command.saveEffect("* transitioning to End state");
        _gameEngine.setCurrentGameState(GameStateType::END);
    }
}

// End state class implementation
EndState::EndState(GameEngine &gameEngine)
        : GameState(gameEngine, new GameStateType(GameStateType::END), new string("End")){};

void EndState::update(Command& command){};

//A2 P5
string GameEngine::stringToLog(){
    string currentState = (this->getCurrentGameState()).getGameStateName();
    return "Game Engine New State: " + currentState;
};

string GameState::getGameStateName(){
    return *_name;
}
