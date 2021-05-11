#pragma once
#include <iostream>
#include <vector>
class Observer {
private:
	std::string* id;
public:
	Observer(std::string oid);
	~Observer();

	std::string getId();

	virtual void update(std::string playerAction) = 0;
};

class PhaseObserver : public Observer {
private:
public:
	PhaseObserver(std::string pid);
	~PhaseObserver();

	virtual void update(std::string playerAction);
};

class Observable {
private:
	std::vector<Observer*>* observers;
public:
	Observable();
	~Observable();

	bool attach(Observer* ob);
	bool detach(std::string id);

	void notify(std::string playerAction);
};