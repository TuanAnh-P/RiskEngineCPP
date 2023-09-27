// MapLoader.h
#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "map.h"

class MapLoader {
private:
    std::string* filename;

    //helper methods
    std::string trim(const std::string& str);
    bool convertStringToBool(const std::string& str);

public:
    MapLoader(const std::string& filename);
    ~MapLoader();
    
    Map* loadMap();
};

#endif //MAPLOADER_H