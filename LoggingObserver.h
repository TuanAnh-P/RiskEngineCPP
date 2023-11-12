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
    virtual string stringToLog() = 0;
};

//------------------------------------------------------------------------

class Subject {
public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify(ILoggable* loggable);
    Subject();
    ~Subject();
private:
    list<Observer*> *_observers;
};

//------------------------------------------------------------------------

class Observer {
public:
    ~Observer();

    virtual void Update(ILoggable* loggable) = 0;

protected:
    Observer();
};

//------------------------------------------------------------------------

#endif
