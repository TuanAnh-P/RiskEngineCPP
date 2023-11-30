#!/bin/bash

clear
g++ -w -std=c++17 ./MapLoader.cpp ./Player.cpp ./Orders.cpp ./LoggingObserver.cpp ./Cards.cpp ./map.cpp ./PlayerStrategies.cpp ./GameEngine.cpp ./CommandProcessing.cpp ./TournamentDriver.cpp -o game
./game -file ./commands.txt 
