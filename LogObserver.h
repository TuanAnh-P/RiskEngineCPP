#ifndef COMP345A2_LOGOBSERVER_H
#define COMP345A2_LOGOBSERVER_H
#include "LoggingObserver.h"

class LogObserver : public Observer{
    void Update(ILoggable* loggable) override;
};


#endif
