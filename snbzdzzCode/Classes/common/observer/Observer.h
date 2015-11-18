#ifndef __COMMON_OBSERVER_OBSERVER_H__
#define __COMMON_OBSERVER_OBSERVER_H__

#include <map>
#include "data/define/DefinesValue.h"

using namespace std;

class Observer
{
public:
	~Observer();
	ID_OBSERVER idObserverGet() const { return _idObserver; }
	void idObserverSet(ID_OBSERVER val) { _idObserver = val; }
	virtual void updateBySubject(va_list values);

protected:
	Observer();

private:
	ID_OBSERVER _idObserver;
	
};

class Subject
{
public:
	~Subject();
	virtual void attach(Observer *observer);
	virtual void detach(Observer *observer);
	virtual void notify(ID_OBSERVER idObserver, ...);

protected:
	Subject();
	
private:
	map<ID_OBSERVER, Observer *> _map;

};

#endif