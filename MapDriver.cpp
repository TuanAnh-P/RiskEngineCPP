#include "map.h"
#include <iostream>
#include "MapLoader.h"



//Function that tests loading of multiple map files.
//For each loaded map, it displays its properties, verifies its validity, 
//and saves the valid maps in a vector.

void testLoadMaps(){

    // List of map files to load
    std::vector<std::string> mapsToLoad = {"./maps/3D.map", "./maps/3D invalid.map", "./maps/003_I72_Fairchild T-31.map", "./maps/003_I72_Fairchild T-31 invalid.map"};
    std::vector<Map*> validMaps;

    for (int i = 0; i < mapsToLoad.size(); i++){
        MapLoader loader(mapsToLoad[i]);
        Map* loadedMap = loader.loadMap();

        // Check if the map was loaded successfully
        if (!loadedMap) {
            std::cerr << "Failed to load the map." << std::endl;
        }


        // Display some map properties for verification
        std::cout << "Map Name: " << loadedMap->getName() << std::endl;

        std::cout << "Map Author: " << loadedMap->getAuthor() << std::endl;
        std::cout << "Map Image: " << loadedMap->getImage() << std::endl;

        if (loadedMap->isValid()){
            std::cout << "The map was valid" << std::endl;
            validMaps.push_back(loadedMap);
        } else {
            std::cout << "The map was invalid" << std::endl;
            delete loadedMap;
            std::cout << "----------------------------------------------------------------------------------" << std::endl;
            std::cout << "----------------------------------------------------------------------------------" << std::endl;
            std::cout << "----------------------------------------------------------------------------------" << std::endl;
            std::cout << "----------------------------------------------------------------------------------" << std::endl;
            std::cout << "----------------------------------------------------------------------------------" << std::endl;
            continue;
        }


        // Display continents and their properties
        for (const Continent* continent : loadedMap->getContinents()) {
            std::cout << "Continent Name: " << continent->getName() << std::endl;
            std::cout << "Number of Armies: " << continent->getNumberOfArmies() << std::endl;

            for (const Territory* territory : continent->getTerritories()) {
                std::cout << "   Territory: " << territory->getName() << " [" << territory->getX() << "," << territory->getY() << "]" << std::endl;

                // Display adjacent territories for each territory
                for (const Territory* adjacentTerritory : territory->getAdjacentTerritories()) {
                    std::cout << "      Adjacent: " << adjacentTerritory->getName() << std::endl;
                }
            }
        }



        std::cout << "----------------------------------------------------------------------------------" << std::endl;
        std::cout << "----------------------------------------------------------------------------------" << std::endl;
        std::cout << "----------------------------------------------------------------------------------" << std::endl;
        std::cout << "----------------------------------------------------------------------------------" << std::endl;
        std::cout << "----------------------------------------------------------------------------------" << std::endl;

    }

    //Display the number of valid maps
    std::cout << "Number of valid Maps are: " << validMaps.size();
}

//calls the testLoadMaps function
/*int main(){

    testLoadMaps();

    return 0;
}*/