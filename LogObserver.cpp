#include <fstream>
#include "LogObserver.h"


void LogObserver::Update(ILoggable* loggable) {
    string line = loggable->stringToLog();
    std::fstream gamelog("gamelog.txt", std::ios::app);
    gamelog << line << std::endl;
    gamelog.close();
};

void LogObserver::UpdateTournament(ILoggable* loggable, int game) {
    string line = loggable->stringToTourLog(game);
    std::fstream gamelog("tournament.txt", std::ios::app);
    gamelog << line << std::endl;
    gamelog.close();
};