#ifndef COMP345A2_LOGGINGOBSERVER_H
#define COMP345A2_LOGGINGOBSERVER_H

#include <list>
#include <string>

using namespace std;

//------------------------------------------------------------------------

class Observer;
class Subject;
class ILoggable;

//------------------------------------------------------------------------

class ILoggable{
public:
    virtual string stringToLog() = 0;//method for game logs
    virtual std::string stringToTourLog(int game) = 0;//method for tournament log
};

//------------------------------------------------------------------------

class Subject {
public:
    virtual void Attach(Observer* o);//attach observer
    virtual void Detach(Observer* o);//detach observer
    virtual void Notify(ILoggable* loggable);//notify for game log
    virtual void NotifyTournament(ILoggable* loggable, int game);//notify for tournament log
    Subject();//constructor
    ~Subject()//destructor
private:
    list<Observer*> *_observers;
};

//------------------------------------------------------------------------

class Observer {
public:
    ~Observer();//destructor

    virtual void Update(ILoggable* loggable) = 0;//update for game log
    virtual void UpdateTournament(ILoggable* loggable,int game) = 0;//update for tournament log

protected:
    Observer();//constructor
};

//------------------------------------------------------------------------

#endif
