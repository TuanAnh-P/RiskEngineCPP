#include "PlayerStrategies.h"


#include "map.h"
#include <iostream>
#include "Player.h"
#include "Cards.h"
#include "GameEngine.h"

// --------------- PlayerStrategy class ---------------

// Default Constructor
PlayerStrategy::PlayerStrategy() 
{
	m_strategyType = StrategyType::None;
}

// Params Constructor
PlayerStrategy::PlayerStrategy(Player* player)
	: m_player(player)
{
	m_strategyType = StrategyType::None;
}

// Copy Constructor
PlayerStrategy::PlayerStrategy(PlayerStrategy& other)
{
	m_strategyType = other.m_strategyType;
	m_player = other.m_player;
}

// Assignment operator
PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& other)
{
	m_strategyType = other.m_strategyType;
	m_player = other.m_player;

	return *this;
}

// Player pointer getter
const Player* PlayerStrategy::getPlayer()
{
	return m_player;
}

// Strategy type getter
const StrategyType PlayerStrategy::getStrategyType()
{
	return m_strategyType;
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, const PlayerStrategy& strategy)
{

	// Switch based on the strategy enum type and print 
	switch (strategy.m_strategyType)
	{
	case StrategyType::HumanPlayer:
		os << " this is a Human Player Strategy!";
		break;
	case StrategyType::AggressivePlayer:
		os << " this is a AggressivePlayer Strategy!";
		break;
	case StrategyType::BenevolentPlayer:
		os << " this is a BenevolentPlayer Strategy!";
		break;
	case StrategyType::NeutralPlayer:
		os << " this is a NeutralPlayer Strategy!";
		break;
	case StrategyType::CheaterPlayer:
		os << " this is a CheaterPlayer Strategy!";
		break;

	default:
		os << "ERROR: Invalid strategy type!";
		break;
	}

	return os;
}

// --------------- HumanPlayerStrategy class ---------------

// Constructor
HumanPlayerStrategy::HumanPlayerStrategy(Player* player)
	: PlayerStrategy(player)
{
	m_strategyType = (StrategyType::HumanPlayer);
    m_player = player;
}

void HumanPlayerStrategy::issueOrder(Deck* deck, GameEngine* gameEngine, string& orderType)
{
    if (orderType == "Deploy"){
        // Player must deploy all his reinforcement pool to proceed with Advance order
        while (this->m_player->getReinforcementPool() > 0) {
            string order;
            cout << this->m_player->getPlayerID() << " enters order: ";
            cin >> order;
            if (order == "Deploy" || order == "deploy"){
                // Get territories that can deploy to (territories from toDefend())
                std::cout << "Territories " << this->m_player->getPlayerID() << " can deploy army units:" << std::endl;
                for (Territory* territory : this->m_player->toDefend()) {
                    std::cout << territory->getName() << " has " << territory->getNumberOfArmies() << " army" << std::endl;
                }
                string deployTarget;
                int numDeploy;
                cout << this->m_player->getPlayerID() << " enters target territory to deploy army units: ";
                cin >> deployTarget;
                cout << this->m_player->getPlayerID() << " enters number of army units to deploy: ";
                cin >> numDeploy;
                Territory* deployTerritory = gameEngine->getTerritoryByName(deployTarget);
                if (deployTerritory == nullptr) cout << "Invalid territory" << endl;
                else if(numDeploy > this->m_player->getReinforcementPool()) cout << "Invalid number of army units to deploy" << endl;
                else{
//                            player->issueOrder("Deploy", nullptr, deployTerritory, new int(numDeploy), nullptr, nullptr, nullptr);
                    Order* newOrder = new Deploy(this->m_player, deployTerritory, new int(numDeploy));
                    cout << this->m_player->getPlayerID() << " issued a Deploy order" << std::endl;
                    this->m_player->getOrdersList().orders.push_back(newOrder);
                    this->m_player->removeReinforcementPool(numDeploy);
                }
                cout << this->m_player->getPlayerID() << " has " << this->m_player->getReinforcementPool() << " army units left to deploy" << endl;
            }
            else cout << "You can only issue 'Deploy' orders when your reinforcement pool is not empty." << endl;
        }
    }

    if (orderType == "Else"){
        // Advance order
        cout << this->m_player->getPlayerID() << " can make Advance Order" << endl;
        char continueAdvancing;
        do {

            // Get territories to defend
            std::cout << "Territories " << this->m_player->getPlayerID() << " can Defend:" << std::endl;
            for (Territory* territory : this->m_player->toDefend()) {
                std::cout << territory->getName() << " has " << territory->getNumberOfArmies() << " army" << std::endl;
            }

            // Get territories to attack
            std::cout << "Territories " << this->m_player->getPlayerID() << " can Attack:" << std::endl;
            for (Territory* territory : this->m_player->toAttack()) {
                std::cout << territory->getName() << " has " << territory->getNumberOfArmies() << " army" << std::endl;
            }

            // Ask the player to make an Advance Order
            string userSource;
            string userTarget;
            int numUnits;
            cout << this->m_player->getPlayerID() << " enters source territory: ";
            cout << endl;
            cin >> userSource;
            cout << this->m_player->getPlayerID() << " enters target territory: ";
            cin >> userTarget;
            cout << endl;
            cout << this->m_player->getPlayerID() << " enters number of army units to advance: ";
            cin >> numUnits;
            cout << endl;

            // Retrieving source and target territories
            Territory* sourceTerritory = gameEngine->getTerritoryByName(userSource);
            Territory* targetTerritory = gameEngine->getTerritoryByName(userTarget);

            if (sourceTerritory == nullptr) cout << "Invalid source territory" << endl;
            else if (targetTerritory == nullptr) cout << "Invalid target territory" << endl;
            else {
//                        player->issueOrder("Advance", sourceTerritory, targetTerritory, new int(numUnits), nullptr, deck, this);
                Order* newOrder = new Advance(this->m_player, targetTerritory, sourceTerritory, new int(numUnits), deck, gameEngine);
                cout << this->m_player->getPlayerID() << " issued an Advance order" << std::endl;
                this->m_player->getOrdersList().orders.push_back(newOrder);
                // Converting Neutral Player to Aggressive Player if needed
                for (Player* otherPlayer : gameEngine->getPlayers()){
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
        cout << this->m_player->getPlayerID() << " plays a card from their hand contents below" << endl;
        cout << this->m_player->getHand() << endl;
        int cardSelection;
        cout << "Enter the card's index you wish to use (1st card has an index of 0): ";
        cin >> cardSelection;
        if (cardSelection>this->m_player->getHand().cards.size()-1 || cardSelection<0){
            cout << "Invalid index ";
        }
        else if (this->m_player->getHand().cards[cardSelection]->getType() == CardType::Airlift){
            string source;
            string target;
            int num;
            cout << "Airlift - Enter the source territory: ";
            cin >> source;
            cout << "Airlift - Enter the target territory: ";
            cin >> target;
            cout << "Airlift - Enter the number of army units: ";
            cin >> num;
            Territory* sourceTerritory = gameEngine->getTerritoryByName(source);
            Territory* targetTerritory = gameEngine->getTerritoryByName(target);
            if (sourceTerritory == nullptr) cout << "Source territory is invalid" << endl;
            else if (targetTerritory == nullptr) cout << "Source territory is invalid" << endl;
            else {
//                        player->issueOrder("Airlift", sourceTerritory, targetTerritory, new int(num), nullptr, nullptr, nullptr);
                Order* newOrder = new Airlift(this->m_player, sourceTerritory, targetTerritory, new int(num));
                cout << this->m_player->getPlayerID() << " issued an Airlift order" << std::endl;
                this->m_player->getOrdersList().orders.push_back(newOrder);
                // Converting Neutral Player to Aggressive Player if needed
                for (Player* otherPlayer : gameEngine->getPlayers()){
                    if (otherPlayer->isTerritoryOwned(targetTerritory) && otherPlayer->getStrategyType() == StrategyType::NeutralPlayer){
                        otherPlayer->setPlayerStrategy(new AggressivePlayerStrategy(otherPlayer));
                        cout << otherPlayer->getPlayerID() << " becomes an Aggressive Player" << endl;
                    }
                }
            }
        }
        else if (this->m_player->getHand().cards[cardSelection]->getType() == CardType::Bomb){
            string target;
            cout << "Bomb - Enter the target territory: ";
            cin >> target;
            Territory* targetTerritory = gameEngine->getTerritoryByName(target);
            if (targetTerritory == nullptr) cout << "Target territory is invalid" << endl;
            else {
//                        player->issueOrder("Bomb", nullptr, targetTerritory, nullptr, p, nullptr, nullptr);
                Order* newOrder = new Bomb(this->m_player, targetTerritory);
                cout << this->m_player->getPlayerID() << " issued a Bomb order" << std::endl;
                this->m_player->getOrdersList().orders.push_back(newOrder);
                // Converting Neutral Player to Aggressive Player if needed
                for (Player* otherPlayer : gameEngine->getPlayers()){
                    if (otherPlayer->isTerritoryOwned(targetTerritory) && otherPlayer->getStrategyType() == StrategyType::NeutralPlayer){
                        otherPlayer->setPlayerStrategy(new AggressivePlayerStrategy(otherPlayer));
                        cout << otherPlayer->getPlayerID() << " becomes an Aggressive Player" << endl;
                    }
                }
            }
        }
        else if (this->m_player->getHand().cards[cardSelection]->getType() == CardType::Blockade){
            string target;
            cout << "Blockade - Enter the target territory: ";
            cin >> target;
            Territory* targetTerritory = gameEngine->getTerritoryByName(target);
            if (targetTerritory == nullptr) cout << "Target territory is invalid" << endl;
//                    else player->issueOrder("Blockade", nullptr, targetTerritory, nullptr, nullptr, nullptr, this);
            Order* newOrder = new Blockade(this->m_player, targetTerritory, gameEngine);
            cout << this->m_player->getPlayerID() << " issued a Blockade order" << std::endl;
            this->m_player->getOrdersList().orders.push_back(newOrder);
        }
        else if (this->m_player->getHand().cards[cardSelection]->getType() == CardType::Diplomacy){
            string targetPlayer;
            cout << "Diplomacy/Negotiate - Enter the target player: ";
            cin >> targetPlayer;
            Player* p = gameEngine->getPlayerByID(targetPlayer);
            if (p == nullptr) cout << "Player is invalid" << endl;
//                    else player->issueOrder("Negotiate", nullptr, nullptr, nullptr, p, nullptr, nullptr);
            Order* newOrder = new Negotiate(this->m_player, p);
            cout << this->m_player->getPlayerID() << " issued a Negotiate order" << std::endl;
            this->m_player->getOrdersList().orders.push_back(newOrder);
        }
    }
}

std::vector<Territory*> HumanPlayerStrategy::toAttack()
{
    return m_player->toAttack();
}

std::vector<Territory*> HumanPlayerStrategy::toDefend()
{
    return m_player->toDefend();
}

// --------------- AggressivePlayerStrategy class ---------------

// Constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) 
	: PlayerStrategy(player)
{
	m_strategyType = (StrategyType::AggressivePlayer);
    m_player = player;
}

void AggressivePlayerStrategy::issueOrder(Deck* deck, GameEngine* gameEngine, string& orderType)
{
    if (orderType == "Deploy"){
        // Aggressive Player will deploy all of his armies on its strongest territory
        while (this->m_player->getReinforcementPool() > 0) {
            // Get territories he that can deploy to (territories from toDefend())
            std::cout << "Territories " << this->m_player->getPlayerID() << " can deploy army units:" << std::endl;
            for (Territory* territory : this->m_player->toDefend()) {
                std::cout << territory->getName() << " has " << territory->getNumberOfArmies() << " army" << std::endl;
            }
            // Get the territory that has the most number of armies and making sure that territory has adjacent territories to attack
            Territory* deployTerritory = nullptr;  // Initialize to nullptr
            int maxArmies = 0;
            for (Territory* territory : this->m_player->toDefend()) {
                if (this->m_player->doesHaveAdjacentTerritoriesToAttack(territory)) {
                    if (territory->getNumberOfArmies() >= maxArmies){
                        maxArmies = territory->getNumberOfArmies();  // Update the maxArmies
                        deployTerritory = territory;  // Update only after checking all adjacent territories
                        break;
                    }
                }
            }
            cout << this->m_player->getPlayerID() << " enters target territory to deploy army units: " << deployTerritory->getName() << endl;
            cout << this->m_player->getPlayerID() << " enters number of army units to deploy: " << this->m_player->getReinforcementPool() << endl;
            // Issuing an advance order
            Order* newOrder = new Deploy(this->m_player, deployTerritory, new int(this->m_player->getReinforcementPool()));
            cout << this->m_player->getPlayerID() << " issued a Deploy order" << std::endl;
            // Pushing that order into his orders list
            this->m_player->getOrdersList().orders.push_back(newOrder);
            // Setting his reinforcement pool to be empty
            this->m_player->removeReinforcementPool(this->m_player->getReinforcementPool());
            cout << this->m_player->getPlayerID() << " has " << this->m_player->getReinforcementPool() << " army units left to deploy" << endl;
        }
    }

    if (orderType == "Else"){
        // Aggressive Player will then advance from its strongest territory until he can't no longer do so (when toAttack() return an empty vector)
        cout << this->m_player->getPlayerID() << " can make Advance Order" << endl;
//        std::vector<Territory*> attackTerritories = this->m_player->toAttack();

//        while (true) {
//
//            if (attackTerritories.empty()) break;
//
//            else {
//                // Get territories to defend
//                std::cout << "Territories " << this->m_player->getPlayerID() << " can Defend:" << std::endl;
//                for (Territory* territory : this->m_player->toDefend()) {
//                    std::cout << territory->getName() << " has " << territory->getNumberOfArmies() << " army" << std::endl;
//                }
//                // Get territories to attack
//                std::cout << "Territories " << this->m_player->getPlayerID() << " can Attack:" << std::endl;
//                for (Territory* territory : attackTerritories) {
//                    std::cout << territory->getName() << " has " << territory->getNumberOfArmies() << " army" << std::endl;
//                }
//                // Get the source territory that has the most number of armies as source territory
//                Territory* sourceTerritory = this->m_player->toDefend().empty() ? nullptr : this->m_player->toDefend().at(0);
//                for (Territory* territory : this->m_player->toDefend()) {
//                    if (territory->getNumberOfArmies() > sourceTerritory->getNumberOfArmies()) sourceTerritory = territory;
//                }
//                Territory* targetTerritory = attackTerritories.empty() ? nullptr : attackTerritories.at(0);
//                cout << this->m_player->getPlayerID() << " enters source territory: " << sourceTerritory->getName() << endl;
//                cout << this->m_player->getPlayerID() << " enters target territory: " << targetTerritory->getName() << endl;
//                cout << this->m_player->getPlayerID() << " enters number of army units to advance: " << sourceTerritory->getNumberOfArmies() << endl;
//                Order* newOrder = new Advance(this->m_player, targetTerritory, sourceTerritory, new int(sourceTerritory->getNumberOfArmies()), deck, gameEngine);
//                cout << this->m_player->getPlayerID() << " issued an Advance order" << std::endl;
//                this->m_player->getOrdersList().orders.push_back(newOrder);
//                attackTerritories.erase(std::remove(attackTerritories.begin(), attackTerritories.end(), targetTerritory), attackTerritories.end());
//                // Converting Neutral Player to Aggressive Player if needed
//                for (Player* otherPlayer : gameEngine->getPlayers()) {
//                    if (otherPlayer->isTerritoryOwned(targetTerritory) && otherPlayer->getStrategyType() == StrategyType::NeutralPlayer) {
//                        otherPlayer->setPlayerStrategy(new AggressivePlayerStrategy(otherPlayer));
//                        cout << otherPlayer->getPlayerID() << " becomes an Aggressive Player" << endl;
//                    }
//                }
//            }
//        }

            // Aggressive Player will then attack from all the territories he owns, that source territory must have an adjacent territory to attack and number of armies greater than 0
            // Get territories to defend
            std::cout << "Territories " << this->m_player->getPlayerID() << " can Defend:" << std::endl;
            for (Territory* territory : this->m_player->toDefend()) {
                std::cout << territory->getName() << " has " << territory->getNumberOfArmies() << " army" << std::endl;
            }
            // Get territories to attack
            std::cout << "Territories " << this->m_player->getPlayerID() << " can Attack:" << std::endl;
            for (Territory* territory : this->m_player->toAttack()) {
                std::cout << territory->getName() << " has " << territory->getNumberOfArmies() << " army" << std::endl;
            }

            Territory* sourceTerritory = nullptr;
            Territory* targetTerritory  = nullptr;
            // For each territory he owns, checking if that territory has any territories to attack and has any troops left to advance
            for (Territory* territory : this->m_player->toDefend()){
                if (this->m_player->doesHaveAdjacentTerritoriesToAttack(territory) && territory->getNumberOfArmies() > 0){
                    // Setting that territory as a source territory
                    sourceTerritory = territory;
                    cout << this->m_player->getPlayerID() << " enters source territory: " << sourceTerritory->getName() << endl;
                    // Getting the adjacent territory to attack
                    for (Territory* territoryToAttack : sourceTerritory->getAdjacentTerritories()){
                        if (!this->m_player->isTerritoryOwned(territoryToAttack)){
                            targetTerritory = territoryToAttack;
                            break;
                        }
                    }
                    cout << this->m_player->getPlayerID() << " enters target territory: " << targetTerritory->getName() << endl;
                    // Advancing all of his source territory troops
                    cout << this->m_player->getPlayerID() << " enters number of army units to advance: " << sourceTerritory->getNumberOfArmies() << endl;
                    // Issuing an advance order
                    Order* newOrder = new Advance(this->m_player, targetTerritory, sourceTerritory, new int(sourceTerritory->getNumberOfArmies()), deck, gameEngine);
                    cout << this->m_player->getPlayerID() << " issued an Advance order" << std::endl;
                    // Pushing that order into his orders list
                    this->m_player->getOrdersList().orders.push_back(newOrder);
                    // Converting Neutral Player to Aggressive Player if needed
                    for (Player* otherPlayer : gameEngine->getPlayers()) {
                        if (otherPlayer->isTerritoryOwned(targetTerritory) && otherPlayer->getStrategyType() == StrategyType::NeutralPlayer) {
                            otherPlayer->setPlayerStrategy(new AggressivePlayerStrategy(otherPlayer));
                            cout << otherPlayer->getPlayerID() << " becomes an Aggressive Player" << endl;
                        }
                    }
                }
            }

            if (sourceTerritory == nullptr){
                cout << this->m_player->getPlayerID() << " won't make Advance Order" << endl;
            }

        // Aggressive Player will play any cards with an aggressive intent (doing the most damage possible)
        cout << this->m_player->getPlayerID() << " plays a card from their hand contents below" << endl;
        cout << this->m_player->getHand() << endl;
        if (not this->m_player->getHand().cards.empty()) {
            if (this->m_player->getHand().cards.at(0)->getType() == CardType::Airlift) {
                // Get the source territory that has the most number of armies as source territory
                Territory* sourceTerritory = this->m_player->toDefend().empty() ? nullptr : this->m_player->toDefend().at(0);

                if (sourceTerritory != nullptr)
                {
                    for (Territory* territory : this->m_player->toDefend())
                    {
                        if (territory->getNumberOfArmies() > sourceTerritory->getNumberOfArmies()) sourceTerritory = territory;
                    }
                    // Get the target territory that has the most number of armies as source territory
                    Territory* targetTerritory = this->m_player->toAttack().empty() ? nullptr : this->m_player->toAttack().at(0);
                    for (Territory* territory : this->m_player->toAttack()) {
                        if (territory->getNumberOfArmies() > targetTerritory->getNumberOfArmies()) targetTerritory = territory;
                    }
                    cout << "Airlift - Enter the source territory: " << sourceTerritory->getName() << endl;
                    cout << "Airlift - Enter the target territory: " << targetTerritory->getName() << endl;
                    cout << "Airlift - Enter the number of army units: " << sourceTerritory->getNumberOfArmies() << endl;
                    Order* newOrder = new Airlift(this->m_player, sourceTerritory, targetTerritory, new int(sourceTerritory->getNumberOfArmies()));
                    cout << this->m_player->getPlayerID() << " issued an Airlift order" << std::endl;
                    this->m_player->getOrdersList().orders.push_back(newOrder);
                    // Converting Neutral Player to Aggressive Player if needed
                    for (Player* otherPlayer : gameEngine->getPlayers()) {
                        if (otherPlayer->isTerritoryOwned(targetTerritory) && otherPlayer->getStrategyType() == StrategyType::NeutralPlayer) {
                            otherPlayer->setPlayerStrategy(new AggressivePlayerStrategy(otherPlayer));
                            cout << otherPlayer->getPlayerID() << " becomes an Aggressive Player" << endl;
                        }
                    }
                }                
            }
            else if (this->m_player->getHand().cards.at(0)->getType() == CardType::Bomb) {
                // Get the target territory that has the most number of armies as source territory
                Territory* targetTerritory = this->m_player->toAttack().empty() ? nullptr : this->m_player->toAttack().at(0);
                for (Territory* territory : this->m_player->toAttack()) {
                    if (territory->getNumberOfArmies() > targetTerritory->getNumberOfArmies()) targetTerritory = territory;
                }
                // Get the player that has that territory
                Player* targetPlayer = nullptr;
                for (Player* otherPlayer : gameEngine->getPlayers()) {
                    if (otherPlayer->isTerritoryOwned(targetTerritory)) targetPlayer = otherPlayer;
                }
                cout << "Bomb - Enter the target player: " << targetPlayer->getPlayerID() << endl;
                cout << "Bomb - Enter the target territory: " << targetTerritory->getName() << endl;
                Order* newOrder = new Bomb(this->m_player, targetTerritory);
                cout << this->m_player->getPlayerID() << " issued a Bomb order" << std::endl;
                this->m_player->getOrdersList().orders.push_back(newOrder);
                // Converting Neutral Player to Aggressive Player if needed
                for (Player* otherPlayer : gameEngine->getPlayers()) {
                    if (otherPlayer->isTerritoryOwned(targetTerritory) && otherPlayer->getStrategyType() == StrategyType::NeutralPlayer) {
                        otherPlayer->setPlayerStrategy(new AggressivePlayerStrategy(otherPlayer));
                        cout << otherPlayer->getPlayerID() << " becomes an Aggressive Player" << endl;
                    }
                }
            }
            else if (this->m_player->getHand().cards.at(0)->getType() == CardType::Blockade) {
                cout << this->m_player->getPlayerID() << " won't play his Blockade card" << endl;
            }
            else if (this->m_player->getHand().cards.at(0)->getType() == CardType::Diplomacy) {
                cout << this->m_player->getPlayerID() << " won't play his Diplomacy card" << endl;
            }
        }
    }
}

std::vector<Territory*> AggressivePlayerStrategy::toAttack()
{
    return m_player->toAttack();
}

std::vector<Territory*> AggressivePlayerStrategy::toDefend()
{
    return m_player->toDefend();
}

// --------------- BenevolentPlayerStrategy class ---------------

// Constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player)
{
	m_strategyType = (StrategyType::BenevolentPlayer);
    m_player = player;
}

void BenevolentPlayerStrategy::issueOrder(Deck* deck, GameEngine* gameEngine, string& orderType)
{
    if (orderType == "Deploy"){
        // Benevolent Player will deploy all of his armies on its weakest territory
        while (this->m_player->getReinforcementPool() > 0) 
        {
            // Get territories that he can deploy to (territories from toDefend())
            std::cout << "Territories " << this->m_player->getPlayerID() << " can deploy army units:" << std::endl;
            for (Territory* territory : this->m_player->toDefend()) 
            {
                std::cout << territory->getName() << " has " << territory->getNumberOfArmies() << " army" << std::endl;
            }
            // Get the territory that has the least number of armies
            Territory* deployTerritory = this->m_player->toDefend().at(0);
            for (Territory* territory : this->m_player->toDefend()) {
                if (territory->getNumberOfArmies() < deployTerritory->getNumberOfArmies()) deployTerritory = territory;
            }
            cout << this->m_player->getPlayerID() << " enters target territory to deploy army units: " << deployTerritory->getName() << endl;
            cout << this->m_player->getPlayerID() << " enters number of army units to deploy: " << this->m_player->getReinforcementPool() << endl;
            // Issuing a deploy order
            Order* newOrder = new Deploy(this->m_player, deployTerritory, new int(this->m_player->getReinforcementPool()));
            cout << this->m_player->getPlayerID() << " issued a Deploy order" << std::endl;
            // Pushing that order into his orders list
            this->m_player->getOrdersList().orders.push_back(newOrder);
            // Setting that reinforcement pool to empty
            this->m_player->removeReinforcementPool(this->m_player->getReinforcementPool());
            cout << this->m_player->getPlayerID() << " has " << this->m_player->getReinforcementPool() << " army units left to deploy" << endl;
        }
    }

    if (orderType == "Else"){
        // Benevolent Player will then make an advance order that move half of the armies from its strongest territory to its weakest territory
        cout << this->m_player->getPlayerID() << " can make Advance Order" << endl;
        // Can't make advance order if he only has less than 2 territories
        if (this->m_player->toDefend().size()<2) {
            cout << this->m_player->getPlayerID() << " won't make Advance Order" << endl;
        }
        else{
            // Get territories to defend
            std::cout << "Territories " << this->m_player->getPlayerID() << " can Defend:" << std::endl;
            for (Territory* territory : this->m_player->toDefend()) 
            {
                std::cout << territory->getName() << " has " << territory->getNumberOfArmies() << " army" << std::endl;
            }
            // Get territories to attack
            std::cout << "Territories " << this->m_player->getPlayerID() << " can Attack:" << std::endl;
            for (Territory* territory : this->m_player->toAttack()) {
                std::cout << territory->getName() << " has " << territory->getNumberOfArmies() << " army" << std::endl;
            }
            // Get the source territory that has the most number of armies
            Territory* sourceTerritory = this->m_player->toDefend().empty() ? nullptr : this->m_player->toDefend().at(0);

            if (sourceTerritory != nullptr)
            {
                for (Territory* territory : this->m_player->toDefend()) {
                    if (territory->getNumberOfArmies() > sourceTerritory->getNumberOfArmies()) sourceTerritory = territory;
                }
                // Get the target territory that has the least number of armies
                Territory* targetTerritory = this->m_player->toDefend().empty() ? nullptr : this->m_player->toDefend().at(0);
                for (Territory* territory : this->m_player->toDefend()) {
                    if (territory->getNumberOfArmies() < targetTerritory->getNumberOfArmies()) targetTerritory = territory;
                }
                cout << this->m_player->getPlayerID() << " enters source territory: " << sourceTerritory->getName() << endl;
                cout << this->m_player->getPlayerID() << " enters target territory: " << targetTerritory->getName() << endl;
                cout << this->m_player->getPlayerID() << " enters number of army units to advance: " << static_cast<int>(sourceTerritory->getNumberOfArmies() / 2) << endl;
                // Issuing an advance order
                Order* newOrder = new Advance(this->m_player, targetTerritory, sourceTerritory, new int(static_cast<int>(sourceTerritory->getNumberOfArmies() / 2)), deck, gameEngine);
                cout << this->m_player->getPlayerID() << " issued an Advance order" << std::endl;
                // Pushing that order into his orders list
                this->m_player->getOrdersList().orders.push_back(newOrder);
            }
        }

        // Benevolent Player won't play any cards that card will cause harm to an opponent (Playing them passively)
        cout << this->m_player->getPlayerID() << " plays a card from their hand contents below" << endl;
        cout << this->m_player->getHand() << endl;
        if (not this->m_player->getHand().cards.empty()){
            // Benevolent Player will use his Blockage card to move half of the armies from its strongest territory to its weakest territory (Same principle as with his advance order)
            if (this->m_player->getHand().cards.at(0)->getType() == CardType::Airlift && this->m_player->toDefend().size()<2){
                // Get the source territory that has the most number of armies as source territory
                Territory* sourceTerritory = this->m_player->toDefend().empty() ? nullptr : this->m_player->toDefend().at(0);

                if (sourceTerritory != nullptr)
                {
                    for (Territory* territory : this->m_player->toDefend())
                    {
                        if (territory->getNumberOfArmies() > sourceTerritory->getNumberOfArmies()) sourceTerritory = territory;
                    }
                    // Get the target territory that has the least number of armies as source territory
                    Territory* targetTerritory = this->m_player->toDefend().empty() ? nullptr : this->m_player->toDefend().at(0);
                    for (Territory* territory : this->m_player->toDefend()) {
                        if (territory->getNumberOfArmies() < targetTerritory->getNumberOfArmies()) targetTerritory = territory;
                    }
                    cout << "Airlift - Enter the source territory: " << sourceTerritory->getName() << endl;
                    cout << "Airlift - Enter the target territory: " << targetTerritory->getName() << endl;
                    cout << "Airlift - Enter the number of army units: " << sourceTerritory->getNumberOfArmies() << endl;
                    // Issuing an airlift order
                    Order* newOrder = new Airlift(this->m_player, sourceTerritory, targetTerritory, new int(static_cast<int>(sourceTerritory->getNumberOfArmies() / 2)));
                    cout << this->m_player->getPlayerID() << " issued an Airlift order" << std::endl;
                    // Pushing that order into his orders list
                    this->m_player->getOrdersList().orders.push_back(newOrder);
                }
            }
            else if (this->m_player->getHand().cards.at(0)->getType() == CardType::Bomb){
                cout << this->m_player->getPlayerID() << " won't play his Bomb card" << endl;
            }
            else if (this->m_player->getHand().cards.at(0)->getType() == CardType::Blockade){
                cout << this->m_player->getPlayerID() << " won't play his Blockade card" << endl;
            }
            else if (this->m_player->getHand().cards.at(0)->getType() == CardType::Diplomacy){
                cout << this->m_player->getPlayerID() << " won't play his Diplomacy card" << endl;
            }
        }
        else cout << this->m_player->getPlayerID() << " won't play any cards" << endl;
    }
}

std::vector<Territory*> BenevolentPlayerStrategy::toAttack()
{
    return m_player->toAttack();
}

std::vector<Territory*> BenevolentPlayerStrategy::toDefend()
{
    return m_player->toDefend();
}

// --------------- NeutralPlayerStrategy class ---------------

// Constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player)
{
	m_strategyType = (StrategyType::NeutralPlayer);
    m_player = player;
}

void NeutralPlayerStrategy::issueOrder(Deck* deck, GameEngine* gameEngine, string& orderType)
{
    // Neutral Player won't deploy any troops
    if (orderType == "Deploy"){
        std::cout << "Territories " << this->m_player->getPlayerID() << " can deploy army units:" << std::endl;
        for (Territory* territory : this->m_player->toDefend()) {
            std::cout << territory->getName() << " has " << territory->getNumberOfArmies() << " army" << std::endl;
        }
        cout << this->m_player->getPlayerID() << " won't make any Deploy orders" << endl;
    }
    // Neutral Player won't make any advance orders nor play any cards
    if (orderType == "Else"){
        cout << this->m_player->getPlayerID() << " can make Advance Order" << endl;
        cout << this->m_player->getPlayerID() << " won't make Advance Order" << endl;
        cout << this->m_player->getPlayerID() << " plays a card from their hand contents below" << endl;
        cout << this->m_player->getHand() << endl;
        cout << this->m_player->getPlayerID() << " won't play any cards" << endl;
    }
}

std::vector<Territory*> NeutralPlayerStrategy::toAttack()
{
    return m_player->toAttack();
}

std::vector<Territory*> NeutralPlayerStrategy::toDefend()
{
    return m_player->toDefend();
}

// --------------- CheaterPlayerStrategy class ---------------

// Constructor
CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player)
{
	m_strategyType = (StrategyType::CheaterPlayer);
    m_player = player;
}

void CheaterPlayerStrategy::issueOrder(Deck* deck, GameEngine* gameEngine, string& orderType)
{
    // Cheater Player won't deploy any troops
    if (orderType == "Deploy"){
        std::cout << "Territories " << this->m_player->getPlayerID() << " can deploy army units:" << std::endl;
        for (Territory* territory : this->m_player->toDefend()) {
            std::cout << territory->getName() << " has " << territory->getNumberOfArmies() << " army" << std::endl;
        }
        cout << this->m_player->getPlayerID() << " won't make any Deploy orders" << endl;
    }

    if (orderType == "Else")
    {
        // Cheater Player won't make any advance orders
        cout << this->m_player->getPlayerID() << " can make Advance Order" << endl;
        cout << this->m_player->getPlayerID() << " won't make Advance Order" << endl;

        // Cheating algorithm - Cheater player will automatically conquer all the territories he can attack
        for (Territory* territory : this->m_player->toAttack()) 
        {
            // Adding that territory to the list of territories that he owns
            this->m_player->addTerritory(territory);

            // Finding the player who owned that territory and removing it from the territories that he possesses
            Player* playerThatOwnedThatTerritory = nullptr;
            for (Player* otherPlayer : gameEngine->getPlayers())
            {
                if (otherPlayer->isTerritoryOwned(territory) && otherPlayer != m_player) playerThatOwnedThatTerritory = otherPlayer;
            }
            playerThatOwnedThatTerritory->removeTerritory(territory);

            // Setting Neutral Player to Aggressive Player if needed
            if (playerThatOwnedThatTerritory->getStrategyType() == StrategyType::NeutralPlayer)
            {
                playerThatOwnedThatTerritory->setPlayerStrategy(new AggressivePlayerStrategy(playerThatOwnedThatTerritory));
                cout << playerThatOwnedThatTerritory->getPlayerID() << " becomes an Aggressive Player" << endl;
            }
        }
        // Cheater Player won't play any cards
        cout << this->m_player->getPlayerID() << " plays a card from their hand contents below" << endl;
        cout << this->m_player->getHand() << endl;
        cout << this->m_player->getPlayerID() << " won't play any cards" << endl;
    }
}

std::vector<Territory*> CheaterPlayerStrategy::toAttack()
{
    return m_player->toAttack();
}

std::vector<Territory*> CheaterPlayerStrategy::toDefend()
{
    return m_player->toDefend();
}


