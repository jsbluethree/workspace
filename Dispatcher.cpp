// Dispatcher.cpp
// Chris Bowers

/**
 * This is an implementation of an event dispatcher - see Dispatcher.h
 */

#include "Dispatcher.h"

Dispatcher::Dispatcher() {}

Dispatcher::~Dispatcher() { for (auto event : events) delete event; }

void Dispatcher::add_listener(EventType type, ICallback* callback) { defer_add.push_back(std::make_pair(type, callback)); }

void Dispatcher::remove_listener(EventType type, ICallback* callback) { defer_add.push_back(std::make_pair(type, callback)); }

void Dispatcher::add_event(IEvent* event) { events.push_back(event); }

void Dispatcher::dispatch(IEvent* event){
	for (auto callback : listeners[event->type()]) callback->execute(event);
	delete event;
}

void Dispatcher::tick(float dt){
	for (auto event : events) dispatch(event);
	events.clear();

	for (auto pair : defer_add) listeners[pair.first].push_back(pair.second);
	defer_add.clear();

	for (auto pair : defer_remove){
		for (auto it = listeners[pair.first].begin(); it != listeners[pair.first].end(); ++it){
			if (*it == pair.second){
				listeners[pair.first].erase(it);
				break;
			}
		}
	}
	defer_remove.clear();
}

Dispatcher::Dispatcher(const Dispatcher&) {}

Dispatcher::Dispatcher(Dispatcher&&) {}

Dispatcher& Dispatcher::operator=(const Dispatcher&) { return *this; }

Dispatcher& Dispatcher::operator=(Dispatcher&&) { return *this; }
