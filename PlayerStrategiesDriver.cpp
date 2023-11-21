#include <iostream>
#include "Player.h"
#include "PlayerStrategies.h"

// Test Player Strategies free test function
void testPlayerStrategies()
{
	// Create instance of strategy
	NeutralPlayerStrategy* neutralStrat = new NeutralPlayerStrategy();

	Player player("John", StrategyType::AggressivePlayer);
	

	// Test switch strategy
	std::cout << *player.getStrategy() << std::endl;
	player.setPlayerStrategy(neutralStrat);
	std::cout << *player.getStrategy() << std::endl;


}