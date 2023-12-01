#include "LoggingObserver.h"

//void ILoggable::stringToLog(){};

//-------------------------------------------

Subject::Subject(){
    _observers = new list<Observer*>;
}
Subject::~Subject(){
    delete _observers;
}
void Subject::Attach(Observer* o){
    _observers->push_back(o);
};
void Subject::Detach(Observer* o){
    _observers->remove(o);
};
void Subject::Notify(ILoggable* loggable){
    list<Observer *>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->Update(loggable);
};

void Subject::NotifyTournament(ILoggable* loggable, int game){
    list<Observer *>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->UpdateTournament(loggable, game);
};

//--------------------------------------------

Observer::Observer(){
};
Observer::~Observer(){
};

//--------------------------------------------

