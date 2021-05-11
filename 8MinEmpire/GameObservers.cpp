#include "GameObservers.h"

Observer::Observer(std::string oid) {
	this->id = new std::string(oid);
}

Observer::~Observer() {
	delete id;
	id = NULL;
}

std::string Observer::getId() {
	return *id;
}

PhaseObserver::PhaseObserver(std::string pid) : Observer::Observer(pid) {
}

PhaseObserver::~PhaseObserver() {
}

void PhaseObserver::update(std::string playerAction) {

	std::cout << "==============Phase Observer=============" << std::endl;
	std::cout << playerAction << std::endl;
}

Observable::Observable() {
	observers = new std::vector<Observer*>();
}

Observable::~Observable() {

	for (int i = 0; i < observers->size(); i++) {

		if (observers) {
			delete observers->at(i);
			observers->at(i) = NULL;

			delete observers;
			observers = NULL;
		}
	}
}

bool Observable::attach(Observer* ob) {
	for (auto iter = observers->begin(); iter != observers->end(); iter++)
	{
		if ((*iter)->getId() == ob->getId())
		{
			return false;
		}
	}
	observers->emplace_back(ob);
	return true;
}

bool Observable::detach(std::string id) {
	for (auto iter = observers->begin(); iter != observers->end(); iter++)
	{
		if ((*iter)->getId() == id)
		{
			observers->erase(iter);
			return true;
		}
	}
	return false;
}

void Observable::notify(std::string playerAction) {
	for (auto iter = observers->begin(); iter != observers->end(); iter++)
	{
		(*iter)->update(playerAction);
	}
}