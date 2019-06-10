#pragma once
#include <vector>

#include "Observer.h"

class Subject {
private:
	std::vector<Observer*> observers;
public:
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
	void notifyObservers();
};