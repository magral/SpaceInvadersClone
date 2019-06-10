#include <vector>

#include "Subject.h"

void Subject::addObserver(Observer* observer) {
	this->observers.push_back(observer);
}

void Subject::removeObserver(Observer* observer) {
	std::vector<Observer*>::iterator remover = this->observers.begin();
	for (; remover == this->observers.end(); ++remover) {
		if (*remover == observer) {
			this->observers.erase(remover);
			break;
		}
	}
}

void Subject::notifyObservers() {
	for (auto o : this->observers) {
		if (o != nullptr) {
			o->notify();
		}
	}
}