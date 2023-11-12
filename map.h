#ifndef MAP_H
#define MAP_H

#include <string>
#include <unordered_set>
#include <vector>

//Territory class
class Territory {
private:
    //Attributes: Name of territory, x coordinate, y coordinate, vector of adjacent territories
    //All class member are pointers
    std::string* name;
    int* x;
    int* y;
    std::vector<Territory*> adjacentTerritories;
    int* numberOfArmies;

public:
    //constructor
    Territory(const std::string& name, int x, int y);
    
    //Setter: adds adajacent territories of the territory
    void addAdjacentTerritory(Territory* territory);
    
    //Basic Getters
    std::string getName() const;
    int getX() const;
    int getY() const;
    int getNumberOfArmies() const;

    //Basics Setters
    const std::vector<Territory*>& getAdjacentTerritories() const;
    void setName(const std::string& name);
    void setX(int x);
    void setY(int y);
    void setNumberOfArmies(int numOfArmies);

    //Destructor
    ~Territory();

    // Copy constructor
    Territory(const Territory& other); 
    // Assignment operator
    Territory& operator=(const Territory& other); 
};

//Continent class
class Continent {
private:
    //Attributes : number of armies, name of continent, vector of territories linked to the continent
    int* bonus;
    std::string* name;
    std::vector<Territory*> territories;

public:
    //Constructor
    Continent(const std::string& n, int bonus);
    //Setter : add territritory that belongs to the continent
    void addTerritory(Territory* territory);

    //Basic getters
    const std::vector<Territory*>& getTerritories() const;
    int getBonus() const;
    std::string getName() const;

    //Destructor
    ~Continent();

    // Copy constructor
    Continent(const Continent& other);
    // Assignment operator
    Continent& operator=(const Continent& other);

};

//Map class
class Map {
private:

    //Attributes: image file name, scroll, author name, Map name (file name without the ".map"), wrap, warn, vector of territories of the map, vector of continents of the map
    std::string* image;
    std::string* scroll;
    std::string* author;
    std::string* name;
    bool* wrap;
    bool* warn;

    std::vector<Territory*> territories;
    std::vector<Continent*> continents;

    //Helper methods to test validility of the map. A detailed summary on map.cpp 
    void dfs(Territory* start, std::unordered_set<Territory*>& visited) const;
    bool isConnected() const;
    bool areContinentsInterconnected() const;
    bool areTerritoriesUniqueToContinents() const;
    
public:
    //Constrcutor
    Map(const std::string& i, const std::string& s, const std::string& a, const std::string& n, bool wp, bool wn);
    //Setter: add territory to a map
    void addTerritory(Territory* territory);
    //Setter: add continent to a map
    void addContinent(Continent* continent);
    //Getter: gets the continents of the map
    const std::vector<Continent*>& getContinents() const;

    //Basic getters
    std::string getImage() const;
    std::string getScroll() const;
    std::string getAuthor() const;
    std::string getName() const;
    bool getWrap() const;
    bool getWarn() const;
    
    //Check if the map is valid
    bool isValid() const;

    //Destrcutor
    ~Map();

    // Copy constructor
    Map(const Map& other);
    // Assignment operator
    Map& operator=(const Map& other);
};


#endif // MAP_H