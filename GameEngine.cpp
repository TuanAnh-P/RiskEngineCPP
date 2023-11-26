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
        if (commandStr.rfind("loadmap ", 0) == 0 && stateValidated) {
            //load  map
            string filename = "./maps/" + commandStr.substr(8);
            bool mapLoaded = loadMap(filename);
            if(mapLoaded){
                _currentGameState->update(command);
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
            addPlayer(player);
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
    play();
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
void GameEngine::addPlayer(const std::string& playerName) {
    if (players.size() >= 6) {
        std::cout << "Maximum number of players reached." << std::endl;
    } else {
        players.push_back(new Player(playerName));
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

void GameEngine::play(){
    // tuan you need to encapsulate everything inside here I believe
    cout<< "Playing now" << endl;
    mainGameLoop();
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
    }
}

void GameEngine::issueOrdersPhase() {
    cout << "<----------The orders issuing phase begins---------->" << endl;
    for(Player* player: players) {

        PlayerStrategy* strat = player->getStrategy();
        const StrategyType stratType = player->getStrategyType();

        // Different Strategy Types
        switch (stratType) {
            case StrategyType::HumanPlayer:
                // Player must deploy all his reinforcement pool to proceed with Advance order
                while (player->getReinforcementPool() > 0) {
                    string order;
                    cout << player->getPlayerID() << " enters order: ";
                    cin >> order;
                    if (order == "Deploy"){
                        // Get territories that can deploy to (territories from toDefend())
                        std::cout << "Territories " << player->getPlayerID() << " can deploy army units:" << std::endl;
                        for (Territory* territory : player->toDefend()) {
                            std::cout << territory->getName() << std::endl;
                        }
                        string deployTarget;
                        int numDeploy;
                        cout << player->getPlayerID() << " enters target territory to deploy army units: ";
                        cin >> deployTarget;
                        cout << player->getPlayerID() << " enters number of army units to deploy: ";
                        cin >> numDeploy;
                        Territory* deployTerritory = this->getTerritoryByName(deployTarget);
                        if (deployTerritory == nullptr) cout << "Invalid territory" << endl;
                        else if(numDeploy > player->getReinforcementPool()) cout << "Invalid number of army units to deploy" << endl;
                        else{
                            player->issueOrder("Deploy", nullptr, deployTerritory, new int(numDeploy), nullptr, nullptr, nullptr);
                            player->removeReinforcementPool(numDeploy);
                        }
                        cout << player->getPlayerID() << " has " << player->getReinforcementPool() << " army units left to deploy" << endl;
                    }
                    else cout << "You can only issue 'Deploy' orders when your reinforcement pool is not empty." << endl;
                }

                // Advance order
                cout << player->getPlayerID() << " can make Advance Order" << endl;
                char continueAdvancing;
                do {

                    // Get territories to defend
                    std::cout << "Territories " << player->getPlayerID() << " can Defend:" << std::endl;
                    for (Territory* territory : player->toDefend()) {
                        std::cout << territory->getName() << std::endl;
                    }

                    // Get territories to attack
                    std::cout << "Territories " << player->getPlayerID() << " can Attack:" << std::endl;
                    for (Territory* territory : player->toAttack()) {
                        std::cout << territory->getName() << std::endl;
                    }

                    // Ask the player to make an Advance Order
                    string userSource;
                    string userTarget;
                    int numUnits;
                    cout << player->getPlayerID() << " enters source territory: ";
                    cout << endl;
                    cin >> userSource;
                    cout << player->getPlayerID() << " enters target territory: ";
                    cin >> userTarget;
                    cout << endl;
                    cout << player->getPlayerID() << " enters number of army units to advance: ";
                    cin >> numUnits;
                    cout << endl;

                    // Retrieving source and target territories
                    Territory* sourceTerritory = this->getTerritoryByName(userSource);
                    Territory* targetTerritory = this->getTerritoryByName(userTarget);

                    if (sourceTerritory == nullptr) cout << "Invalid source territory" << endl;
                    else if (targetTerritory == nullptr) cout << "Invalid target territory" << endl;
                    else {
                        player->issueOrder("Advance", sourceTerritory, targetTerritory, new int(numUnits), nullptr, deck, this);
                        // Converting Neutral Player to Aggressive Player if needed
                        for (Player* otherPlayer : getPlayers()){
                            if (otherPlayer->isTerritoryOwned(targetTerritory) && otherPlayer->getStrategyType() == StrategyType::NeutralPlayer){
                                otherPlayer->setPlayerStrategy(new AggressivePlayerStrategy(otherPlayer));
                                cout << otherPlayer->getPlayerID() << " becomes an Aggressive Player" << endl;
                            }
                        }
                    }

                    // Ask if the player wants to make another Advance Order
                    cout << "Do you want to make another Advance Order? (y/n): ";
                    cin >> continueAdvancing;
                } while (continueAdvancing == 'y' || continueAdvancing == 'Y');

                // Player plays a card from their hand
                cout << player->getPlayerID() << " plays a card from their hand contents below" << endl;
                cout << player->getHand() << endl;
                int cardSelection;
                cout << "Enter the card's index you wish to use (1st card has an index of 0): ";
                cin >> cardSelection;
                if (cardSelection>player->getHand().cards.size()-1 || cardSelection<0){
                    cout << "Invalid index ";
                }
                else if (player->getHand().cards[cardSelection]->getType() == CardType::Airlift){
                    string source;
                    string target;
                    int num;
                    cout << "Airlift - Enter the source territory: ";
                    cin >> source;
                    cout << "Airlift - Enter the target territory: ";
                    cin >> target;
                    cout << "Airlift - Enter the number of army units: ";
                    cin >> num;
                    Territory* sourceTerritory = this->getTerritoryByName(source);
                    Territory* targetTerritory = this->getTerritoryByName(target);
                    if (sourceTerritory == nullptr) cout << "Source territory is invalid" << endl;
                    else if (targetTerritory == nullptr) cout << "Source territory is invalid" << endl;
                    else {
                        player->issueOrder("Airlift", sourceTerritory, targetTerritory, new int(num), nullptr, nullptr, nullptr);
                        // Converting Neutral Player to Aggressive Player if needed
                        for (Player* otherPlayer : getPlayers()){
                            if (otherPlayer->isTerritoryOwned(targetTerritory) && otherPlayer->getStrategyType() == StrategyType::NeutralPlayer){
                                otherPlayer->setPlayerStrategy(new AggressivePlayerStrategy(otherPlayer));
                                cout << otherPlayer->getPlayerID() << " becomes an Aggressive Player" << endl;
                            }
                        }
                    }
                }
                else if (player->getHand().cards[cardSelection]->getType() == CardType::Bomb){
                    string targetPlayer;
                    string target;
                    cout << "Bomb - Enter the target player: ";
                    cin >> targetPlayer;
                    cout << "Bomb - Enter the target territory: ";
                    cin >> target;
                    Territory* targetTerritory = this->getTerritoryByName(target);
                    Player* p = this->getPlayerByID(targetPlayer);
                    if (p == nullptr) cout << "Player is invalid" << endl;
                    else if (targetTerritory == nullptr) cout << "Target territory is invalid" << endl;
                    else {
                        player->issueOrder("Bomb", nullptr, targetTerritory, nullptr, p, nullptr, nullptr);
                        // Converting Neutral Player to Aggressive Player if needed
                        for (Player* otherPlayer : getPlayers()){
                            if (otherPlayer->isTerritoryOwned(targetTerritory) && otherPlayer->getStrategyType() == StrategyType::NeutralPlayer){
                                otherPlayer->setPlayerStrategy(new AggressivePlayerStrategy(otherPlayer));
                                cout << otherPlayer->getPlayerID() << " becomes an Aggressive Player" << endl;
                            }
                        }
                    }
                }
                else if (player->getHand().cards[cardSelection]->getType() == CardType::Blockade){
                    string target;
                    cout << "Blockade - Enter the target territory: ";
                    cin >> target;
                    Territory* targetTerritory = this->getTerritoryByName(target);
                    if (targetTerritory == nullptr) cout << "Target territory is invalid" << endl;
                    else player->issueOrder("Blockade", nullptr, targetTerritory, nullptr, nullptr, nullptr, this);
                }
                else if (player->getHand().cards[cardSelection]->getType() == CardType::Diplomacy){
                    string targetPlayer;
                    cout << "Diplomacy/Negotiate - Enter the target player: ";
                    cin >> targetPlayer;
                    Player* p = this->getPlayerByID(targetPlayer);
                    if (p == nullptr) cout << "Player is invalid" << endl;
                    else player->issueOrder("Negotiate", nullptr, nullptr, nullptr, p, nullptr, nullptr);
                }
                break;






















            case StrategyType::AggressivePlayer:
                // Aggressive Player will deploy all of his armies on its strongest territory
                while (player->getReinforcementPool() > 0) {
                    // Get territories he that can deploy to (territories from toDefend())
                    std::cout << "Territories " << player->getPlayerID() << " can deploy army units:" << std::endl;
                    for (Territory* territory : player->toDefend()) {
                        std::cout << territory->getName() << " has " << territory->getNumberOfArmies() << std::endl;
                    }
                    // Get the territory that has the most number of armies
                    Territory* deployTerritory = player->toDefend().at(0);
                    for (Territory* territory : player->toDefend()) {
                        if (territory->getNumberOfArmies() > deployTerritory->getNumberOfArmies()) deployTerritory = territory;
                    }
                    cout << player->getPlayerID() << " enters target territory to deploy army units: " << deployTerritory->getName() << endl;
                    cout << player->getPlayerID() << " enters number of army units to deploy: " << player->getReinforcementPool() << endl;


                    player->issueOrder("Deploy", nullptr, deployTerritory, new int(player->getReinforcementPool()), nullptr, nullptr, nullptr);
                    player->removeReinforcementPool(player->getReinforcementPool());

                    cout << player->getPlayerID() << " has " << player->getReinforcementPool() << " army units left to deploy" << endl;
                }

                // Aggressive Player will then advance from its strongest territory until he can't no longer do so (when toAttack() return an empty vector)
                cout << player->getPlayerID() << " can make Advance Order" << endl;
                while (true) {
                    if (player->toAttack().empty()) break;
                    else{
                        // Get territories to defend
                        std::cout << "Territories " << player->getPlayerID() << " can Defend:" << std::endl;
                        for (Territory* territory : player->toDefend()) {
                            std::cout << territory->getName() << std::endl;
                        }
                        // Get territories to attack
                        std::cout << "Territories " << player->getPlayerID() << " can Attack:" << std::endl;
                        for (Territory* territory : player->toAttack()) {
                            std::cout << territory->getName() << std::endl;
                        }
                        // Get the source territory that has the most number of armies as source territory
                        Territory* sourceTerritory = player->toDefend().empty() ? nullptr : player->toDefend().at(0);
                        for (Territory* territory : player->toDefend()) {
                            if (territory->getNumberOfArmies() > sourceTerritory->getNumberOfArmies()) sourceTerritory = territory;
                        }
                        Territory* targetTerritory = player->toAttack().empty() ? nullptr : player->toAttack().at(0);
                        cout << player->getPlayerID() << " enters source territory: " << sourceTerritory->getName() << endl;
                        cout << player->getPlayerID() << " enters target territory: " << targetTerritory->getName() << endl;
                        cout << player->getPlayerID() << " enters number of army units to advance: " << sourceTerritory->getNumberOfArmies()<< endl;
                        player->issueOrder("Advance", sourceTerritory, targetTerritory, new int(sourceTerritory->getNumberOfArmies()), nullptr, deck, this);
                        // Converting Neutral Player to Aggressive Player if needed
                        for (Player* otherPlayer : getPlayers()){
                            if (otherPlayer->isTerritoryOwned(targetTerritory) && otherPlayer->getStrategyType() == StrategyType::NeutralPlayer){
                                otherPlayer->setPlayerStrategy(new AggressivePlayerStrategy(otherPlayer));
                                cout << otherPlayer->getPlayerID() << " becomes an Aggressive Player" << endl;
                            }
                        }
                    }
                }

                // Aggressive Player will play any cards with an aggressive intent (doing the most damage possible)
                cout << player->getPlayerID() << " plays a card from their hand contents below" << endl;
                cout << player->getHand() << endl;
                if (not player->getHand().cards.empty()){
                    if (player->getHand().cards.at(0)->getType() == CardType::Airlift){
                        // Get the source territory that has the most number of armies as source territory
                        Territory* sourceTerritory = player->toDefend().empty() ? nullptr : player->toDefend().at(0);
                        for (Territory* territory : player->toDefend()) {
                            if (territory->getNumberOfArmies() > sourceTerritory->getNumberOfArmies()) sourceTerritory = territory;
                        }
                        // Get the target territory that has the most number of armies as source territory
                        Territory* targetTerritory = player->toAttack().empty() ? nullptr : player->toAttack().at(0);
                        for (Territory* territory : player->toAttack()) {
                            if (territory->getNumberOfArmies() > targetTerritory->getNumberOfArmies()) targetTerritory = territory;
                        }
                        cout << "Airlift - Enter the source territory: " << sourceTerritory->getName() << endl;
                        cout << "Airlift - Enter the target territory: " << targetTerritory->getName() << endl;
                        cout << "Airlift - Enter the number of army units: " << sourceTerritory->getNumberOfArmies() << endl;
                        player->issueOrder("Airlift", sourceTerritory, targetTerritory, new int(sourceTerritory->getNumberOfArmies()), nullptr, nullptr, nullptr);
                        // Converting Neutral Player to Aggressive Player if needed
                        for (Player* otherPlayer : getPlayers()){
                            if (otherPlayer->isTerritoryOwned(targetTerritory) && otherPlayer->getStrategyType() == StrategyType::NeutralPlayer){
                                otherPlayer->setPlayerStrategy(new AggressivePlayerStrategy(otherPlayer));
                                cout << otherPlayer->getPlayerID() << " becomes an Aggressive Player" << endl;
                            }
                        }
                    }
                    else if (player->getHand().cards.at(0)->getType() == CardType::Bomb){
                        // Get the target territory that has the most number of armies as source territory
                        Territory* targetTerritory = player->toAttack().empty() ? nullptr : player->toAttack().at(0);
                        for (Territory* territory : player->toAttack()) {
                            if (territory->getNumberOfArmies() > targetTerritory->getNumberOfArmies()) targetTerritory = territory;
                        }
                        // Get the player that has that territory
                        Player* targetPlayer = nullptr;
                        for (Player* otherPlayer : getPlayers()){
                            if (otherPlayer->isTerritoryOwned(targetTerritory)) targetPlayer=otherPlayer;
                        }
                        cout << "Bomb - Enter the target player: " << targetPlayer->getPlayerID() << endl;
                        cout << "Bomb - Enter the target territory: " << targetTerritory->getName()<< endl;
                        player->issueOrder("Bomb", nullptr, targetTerritory, nullptr, targetPlayer, nullptr, nullptr);
                        // Converting Neutral Player to Aggressive Player if needed
                        for (Player* otherPlayer : getPlayers()){
                            if (otherPlayer->isTerritoryOwned(targetTerritory) && otherPlayer->getStrategyType() == StrategyType::NeutralPlayer){
                                otherPlayer->setPlayerStrategy(new AggressivePlayerStrategy(otherPlayer));
                                cout << otherPlayer->getPlayerID() << " becomes an Aggressive Player" << endl;
                            }
                        }
                    }
                    else if (player->getHand().cards.at(0)->getType() == CardType::Blockade){
                        cout << player->getPlayerID() << " won't play his Blockade card" << endl;
                    }
                    else if (player->getHand().cards.at(0)->getType() == CardType::Diplomacy){
                        cout << player->getPlayerID() << " won't play his Diplomacy card" << endl;
                    }
                }
                break;



























            case StrategyType::BenevolentPlayer:
                // Benevolent Player will deploy all of his armies on its weakest territory
                while (player->getReinforcementPool() > 0) {
                    // Get territories that he can deploy to (territories from toDefend())
                    std::cout << "Territories " << player->getPlayerID() << " can deploy army units:" << std::endl;
                    for (Territory* territory : player->toDefend()) {
                        std::cout << territory->getName() << " has " << territory->getNumberOfArmies() << std::endl;
                    }
                    // Get the territory that has the least number of armies
                    Territory* deployTerritory = player->toDefend().at(0);
                    for (Territory* territory : player->toDefend()) {
                        if (territory->getNumberOfArmies() < deployTerritory->getNumberOfArmies()) deployTerritory = territory;
                    }
                    cout << player->getPlayerID() << " enters target territory to deploy army units: " << deployTerritory->getName() << endl;
                    cout << player->getPlayerID() << " enters number of army units to deploy: " << player->getReinforcementPool() << endl;


                    player->issueOrder("Deploy", nullptr, deployTerritory, new int(player->getReinforcementPool()), nullptr, nullptr, nullptr);
                    player->removeReinforcementPool(player->getReinforcementPool());

                    cout << player->getPlayerID() << " has " << player->getReinforcementPool() << " army units left to deploy" << endl;
                }

                // Benevolent Player will then make one advance order to move half of the armies from its strongest territory to its weakest territory
                cout << player->getPlayerID() << " can make Advance Order" << endl;
                if (player->toDefend().size()<2) {
                    cout << player->getPlayerID() << " won't make Advance Order" << endl;
                }
                else{
                    // Get territories to defend
                    std::cout << "Territories " << player->getPlayerID() << " can Defend:" << std::endl;
                    for (Territory* territory : player->toDefend()) {
                        std::cout << territory->getName() << std::endl;
                    }
                    // Get territories to attack
                    std::cout << "Territories " << player->getPlayerID() << " can Attack:" << std::endl;
                    for (Territory* territory : player->toAttack()) {
                        std::cout << territory->getName() << std::endl;
                    }
                    // Get the source territory that has the most number of armies
                    Territory* sourceTerritory = player->toDefend().empty() ? nullptr : player->toDefend().at(0);
                    for (Territory* territory : player->toDefend()) {
                        if (territory->getNumberOfArmies() > sourceTerritory->getNumberOfArmies()) sourceTerritory = territory;
                    }
                    // Get the target territory that has the least number of armies
                    Territory* targetTerritory = player->toDefend().empty() ? nullptr : player->toDefend().at(0);
                    for (Territory* territory : player->toDefend()) {
                        if (territory->getNumberOfArmies() < targetTerritory->getNumberOfArmies()) targetTerritory = territory;
                    }
                    cout << player->getPlayerID() << " enters source territory: " << sourceTerritory->getName() << endl;
                    cout << player->getPlayerID() << " enters target territory: " << targetTerritory->getName() << endl;
                    cout << player->getPlayerID() << " enters number of army units to advance: " << static_cast<int>(sourceTerritory->getNumberOfArmies() / 2)<< endl;
                    player->issueOrder("Advance", sourceTerritory, targetTerritory, new int(static_cast<int>(sourceTerritory->getNumberOfArmies() / 2)), nullptr, deck, this);
                }

                // Benevolent Player won't play any cards with an aggressive intent
                cout << player->getPlayerID() << " plays a card from their hand contents below" << endl;
                cout << player->getHand() << endl;
                if (not player->getHand().cards.empty()){
                    // Benevolent Player will use his Blockage card to move half of the armies from its strongest territory to its weakest territory
                    if (player->getHand().cards.at(0)->getType() == CardType::Airlift && player->toDefend().size()<2){
                        // Get the source territory that has the most number of armies as source territory
                        Territory* sourceTerritory = player->toDefend().empty() ? nullptr : player->toDefend().at(0);
                        for (Territory* territory : player->toDefend()) {
                            if (territory->getNumberOfArmies() > sourceTerritory->getNumberOfArmies()) sourceTerritory = territory;
                        }
                        // Get the target territory that has the least number of armies as source territory
                        Territory* targetTerritory = player->toDefend().empty() ? nullptr : player->toDefend().at(0);
                        for (Territory* territory : player->toDefend()) {
                            if (territory->getNumberOfArmies() < targetTerritory->getNumberOfArmies()) targetTerritory = territory;
                        }
                        cout << "Airlift - Enter the source territory: " << sourceTerritory->getName() << endl;
                        cout << "Airlift - Enter the target territory: " << targetTerritory->getName() << endl;
                        cout << "Airlift - Enter the number of army units: " << sourceTerritory->getNumberOfArmies() << endl;
                        player->issueOrder("Airlift", sourceTerritory, targetTerritory, new int(static_cast<int>(sourceTerritory->getNumberOfArmies() / 2)), nullptr, nullptr, nullptr);
                    }
                    else if (player->getHand().cards.at(0)->getType() == CardType::Bomb){
                        cout << player->getPlayerID() << " won't play his Bomb card" << endl;
                    }
                    else if (player->getHand().cards.at(0)->getType() == CardType::Blockade){
                        cout << player->getPlayerID() << " won't play his Blockade card" << endl;
                    }
                    else if (player->getHand().cards.at(0)->getType() == CardType::Diplomacy){
                        cout << player->getPlayerID() << " won't play his Diplomacy card" << endl;
                    }
                }
                else cout << player->getPlayerID() << " won't play any cards" << endl;
                break;

            case StrategyType::NeutralPlayer:
                std::cout << "Territories " << player->getPlayerID() << " can deploy army units:" << std::endl;
                for (Territory* territory : player->toDefend()) {
                    std::cout << territory->getName() << " has " << territory->getNumberOfArmies() << std::endl;
                }
                cout << player->getPlayerID() << " won't make any Deploy orders" << endl;
                cout << player->getPlayerID() << " can make Advance Order" << endl;
                cout << player->getPlayerID() << " won't make Advance Order" << endl;
                cout << player->getPlayerID() << " plays a card from their hand contents below" << endl;
                cout << player->getHand() << endl;
                cout << player->getPlayerID() << " won't play any cards" << endl;
                break;

            case StrategyType::CheaterPlayer:
                std::cout << "Territories " << player->getPlayerID() << " can deploy army units:" << std::endl;
                for (Territory* territory : player->toDefend()) {
                    std::cout << territory->getName() << " has " << territory->getNumberOfArmies() << std::endl;
                }
                cout << player->getPlayerID() << " won't make any Deploy orders" << endl;
                cout << player->getPlayerID() << " can make Advance Order" << endl;
                cout << player->getPlayerID() << " won't make Advance Order" << endl;
                // Cheating algorithm
                for (Territory* territory : player->toAttack()) {
                    player->addTerritory(territory);
                    Player* playerThatOwnedThatTerritory = nullptr;
                    for (Player* otherPlayer : getPlayers()){
                        if (otherPlayer->isTerritoryOwned(territory)) playerThatOwnedThatTerritory=otherPlayer;
                    }
                    playerThatOwnedThatTerritory->removeTerritory(territory);
                    // Converting Neutral Player to Aggressive Player if needed
                    if (playerThatOwnedThatTerritory->getStrategyType() == StrategyType::NeutralPlayer){
                        playerThatOwnedThatTerritory->setPlayerStrategy(new AggressivePlayerStrategy(playerThatOwnedThatTerritory));
                        cout << playerThatOwnedThatTerritory->getPlayerID() << " becomes an Aggressive Player" << endl;
                    }
                }
                cout << player->getPlayerID() << " plays a card from their hand contents below" << endl;
                cout << player->getHand() << endl;
                cout << player->getPlayerID() << " won't play any cards" << endl;
                break;

            default:
                break;
        }
    }
}


void GameEngine::executeOrdersPhase() {
    cout << "<----------The orders executing phase begins---------->" << endl;
    cout << "<----------Deploy orders are executing first---------->" << endl;
    for(Player* player: players) {
        cout << player->getPlayerID() << " is executing orders from his order list" << endl;
        // Display the player's orders list
        std::cout << "Displaying " << player->getPlayerID() << " orders list" << std::endl;
        player->getOrdersList().print();

        cout << "The orders will be executed one by one: " << endl;
        for (Order* order : player->getOrdersList().orders){
            if (order->type == "Deploy") order->execute();
        }
    }

    cout << "<----------Non-deployed orders are executing now---------->" << endl;
    for(Player* player: players) {
        cout << player->getPlayerID() << " is executing orders from his order list" << endl;
        // Display the player's orders list
        std::cout << "Displaying " << player->getPlayerID() << " orders list" << std::endl;
        player->getOrdersList().print();

        cout << "The orders will be executed one by one: " << endl;
        for (Order* order : player->getOrdersList().orders){
            if (order->type != "Deploy")order->execute();
        }
    }
}

void GameEngine::mainGameLoop() {
    int round = 1;
    int numPlayersLeft = players.size();
    while(numPlayersLeft>1){
        cout << "<--------------------Start of round #" << round<< "-------------------->" << endl;
        setCurrentGameState(GameStateType::ASSIGN_REINFORCEMENT);
        reinforcementPhase();
        setCurrentGameState(GameStateType::ISSUE_ORDERS);
        issueOrdersPhase();
        setCurrentGameState(GameStateType::EXECUTE_ORDERS);
        executeOrdersPhase();
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
    setCurrentGameState(GameStateType::WIN);
    Player* winner = players.at(0);
    cout << "Congratulation! " << winner->getPlayerID() << " is the winner";
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
    command.saveEffect("* transitioning to Map Loaded state");
    _gameEngine.setCurrentGameState(GameStateType::MAP_LOADED);
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
