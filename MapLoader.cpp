#include "MapLoader.h"
#include <unordered_map>

// Constructor for MapLoader
// Initializes the filename with the given fname.
MapLoader::MapLoader(const std::string& fname) {
    filename = new std::string(fname);
}

// Destructor for MapLoader class
// Cleans up the dynamic memory allocation
MapLoader::~MapLoader() {
    delete filename;
}

// Helper function to trim leading and trailing whitespace from a string
std::string MapLoader::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

// Helper function to convert a string representation of a boolean to its boolean value.
// Here, "yes" is considered as true, anything else as false
bool MapLoader::convertStringToBool(const std::string& str) {
    return str == "yes";
}

//Function to load a map from a file
// Reads from a file and returns a Map object
Map* MapLoader::loadMap() {
    std::ifstream file(*filename);
    std::unordered_map<Territory*, std::vector<std::string>> territoryToAdjacentNames;

    // Check if the file is opened successfully. If not, return nullptr
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return nullptr;
    }

    std::string line;

    //Get basic map data
    std::string mapName = filename->substr(0, filename->find(".map"));

    // Create variable to store this data
    std::string image, scroll, author;
    bool wrap, warn;

    // Parse data until [Continents]. Basically until basic attributes are done. The order of attrbitues doesn't matter.
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;

        if (line == "[Map]") continue;
        if (line == "[Continents]") break;

        std::istringstream ss(line);
        std::string key, value;
        std::getline(ss, key, '=');
        std::getline(ss, value);

        key = trim(key);
        value = trim(value);

        if (key == "image") image = value;
        else if (key == "scroll") scroll = value;
        else if (key == "author") author = value;
        else if (key == "wrap") wrap = convertStringToBool(value);
        else if (key == "warn") warn = convertStringToBool(value);
    }

    //Initialize the map
    Map* map = new Map(image, scroll, author, mapName, wrap, warn);

    // Parse continents until [Territories] is encountered
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;
        if (line == "[Territories]") break;

        std::istringstream ss(line);
        std::string name, numArmiesStr;
        std::getline(ss, name, '=');
        std::getline(ss, numArmiesStr);
        
        name = trim(name);
        int numArmies = std::stoi(numArmiesStr);

        //Add these continents to the map
        Continent* continent = new Continent(name, numArmies);
        map->addContinent(continent);
    }

    //Create an unordered map which associsate each territory name with its corresponding territory object
    std::unordered_map<std::string, Territory*> nameToTerritory;

    //Use a map to find a continent by its name
    std::unordered_map<std::string, Continent*> nameToContinent;

    //populate the continent lookup map using continents from the loaded map
    for (Continent* cont : map->getContinents()) {
        nameToContinent[cont->getName()] = cont;
    }

    // Parse territories until the end of file.
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;

        //Get basic information to instantiate a territory  for each line
        std::istringstream ss(line);
        std::string name, xStr, yStr, continentName;
        std::getline(ss, name, ',');
        std::getline(ss, xStr, ',');
        std::getline(ss, yStr, ',');
        std::getline(ss, continentName, ',');

        name = trim(name);
        int x = std::stoi(xStr);
        int y = std::stoi(yStr);
        continentName = trim(continentName);

        Territory* territory = new Territory(name, x, y);
        //Add the teirrotiry to name-to-territory map for looking up later (to associate with correct continent)
        nameToTerritory[name] = territory;

        //Add territory to the map
        map->addTerritory(territory);

        // Associate territory with its continent and apprpiate numberOfArmies for the territory
        if (nameToContinent.find(continentName) != nameToContinent.end()) {
            Continent* continent = nameToContinent[continentName];
            continent->addTerritory(territory);
            // Now we also set the number of armies for the territory
            territory->setNumberOfArmies(continent->getNumberOfArmies());
        } else {
            //errod handling if territory doesn't exist
            std::cout << "Error: Continent " << continentName << " for territory " << name << " is not found." << std::endl;
        }

        // Parse adjacent territories (just store their names for now, we'll link them in the next step) since they they might not exist now and are create in the next lines
        std::vector<std::string> adjacentNames;
        std::string adjacentName;
        while (std::getline(ss, adjacentName, ',')) {
            adjacentNames.push_back(trim(adjacentName));
        }
        // Store the adjacent territories' names for linking later
        territoryToAdjacentNames[territory] = adjacentNames;
    }

    // Link adjacent territories
    for (auto& pair : territoryToAdjacentNames) {
        Territory* territory = pair.first;
        for (const std::string& adjacentName : pair.second) {
            // If the adjacent territory name exists in the lookup map, create the linkage
            if (nameToTerritory.find(adjacentName) != nameToTerritory.end()) {
                Territory* adjacentTerritory = nameToTerritory[adjacentName];
                territory->addAdjacentTerritory(adjacentTerritory);
            } else {
                //erro handling
                std::cout << "Warning: Adjacent territory " << adjacentName << " for territory " << territory->getName() << " is not defined. Skipping." << std::endl;
            }
        }
    }

    //close file stream
    file.close();
    //return map
    return map;
}
