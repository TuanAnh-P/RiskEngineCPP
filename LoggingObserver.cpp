#include "LoggingObserver.h"

//void ILoggable::stringToLog(){};

//-------------------------------------------

//constructor
Subject::Subject(){
    _observers = new list<Observer*>;
}
//destructor
Subject::~Subject(){
    delete _observers;
}
//attach observer
void Subject::Attach(Observer* o){
    _observers->push_back(o);
};
//detach observer
void Subject::Detach(Observer* o){
    _observers->remove(o);
};
//notify for game logs
void Subject::Notify(ILoggable* loggable){
    list<Observer *>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->Update(loggable);
};
//notify for tournament logs
void Subject::NotifyTournament(ILoggable* loggable, int game){
    list<Observer *>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->UpdateTournament(loggable, game);
};

//--------------------------------------------
//constructor
Observer::Observer(){
};
//destructor
Observer::~Observer(){
};

//--------------------------------------------

