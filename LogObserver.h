#ifndef COMP345A2_LOGOBSERVER_H
#define COMP345A2_LOGOBSERVER_H
#include "LoggingObserver.h"

class LogObserver : public Observer{
    void Update(ILoggable* loggable) override; //method for logging game
    void UpdateTournament(ILoggable* loggable, int game) override; //method for logging tournament games
};

#endif
