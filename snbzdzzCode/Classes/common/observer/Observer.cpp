#include "Observer.h"
#include <iostream>
#include <algorithm>
#include <stdarg.h>

using namespace std;

Observer::Observer()
{
}

Observer::~Observer()
{
}

void Observer::updateBySubject(va_list values)
{
	
}

Subject::Subject()
{

}

Subject::~Subject()
{

}

void Subject::attach(Observer *observer)
{
	auto iter = _map.find(observer->idObserverGet());
	if (iter != _map.end() && iter->second != nullptr)
	{
		return;
	}
	_map.insert(map<ID_OBSERVER, Observer *>::value_type(observer->idObserverGet(), observer));
}

void Subject::detach(Observer *observer)
{
	auto iter = _map.find(observer->idObserverGet());
	if (iter == _map.end())
	{
		return;
	}
	_map.erase(iter);
}

void Subject::notify(ID_OBSERVER idObserver, ...)
{
	if (_map.find(idObserver) == _map.end())
	{
		return;
	}
	auto observer = _map[idObserver];
	if (observer == nullptr)
	{
		return;
	}
	va_list values;
	va_start(values, idObserver);
	observer->updateBySubject(values);
	va_end(values);
}

/*void Subject::notifyAll(void *data / *= nullptr* /)
{
	for (auto iter = _map.begin(); iter != _map.end(); iter++)
	{
		iter->second->updateBySubject(data);
	}
}*/
