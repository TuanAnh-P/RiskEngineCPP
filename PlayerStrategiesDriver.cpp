#include <iostream>
#include "Player.h"
#include "PlayerStrategies.h"

// Test Player Strategies free test function
void testPlayerStrategies()
{
	// Create instance of strategy
	NeutralPlayerStrategy* neutralStrat = new NeutralPlayerStrategy();
	HumanPlayerStrategy* humanStrat = new HumanPlayerStrategy();
	AggressivePlayerStrategy* aggroStrat = new AggressivePlayerStrategy();

	// Assignment operator test
	*aggroStrat = *humanStrat;


	delete(neutralStrat);
	delete(humanStrat);
	delete(aggroStrat);

	Player player("John", StrategyType::AggressivePlayer);
	Player player2("Sue", StrategyType::NeutralPlayer);
	
	Player player3(player2);

	player2 = player;

	// Test switch strategy
	std::cout << *player.getStrategy() << std::endl;
	player.setPlayerStrategy(new HumanPlayerStrategy());
	std::cout << *player.getStrategy() << std::endl;	

	std::cout << *player2.getStrategy() << std::endl;
	std::cout << *player3.getStrategy() << std::endl;

}