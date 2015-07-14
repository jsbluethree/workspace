// Dispatcher.cpp
// Chris Bowers

/**
 * This is an implementation of an event dispatcher - see Dispatcher.h
 */

#include "Dispatcher.h"

Dispatcher::Dispatcher() {}

Dispatcher::Dispatcher(Dispatcher&& other){
	listeners.swap(other.listeners);
	events.swap(other.events);
	defer_add.swap(other.defer_add);
	defer_remove.swap(other.defer_remove);
}

Dispatcher& Dispatcher::operator=(Dispatcher&& other){
	events.clear();
	listeners.swap(other.listeners);
	events.swap(other.events);
	defer_add.swap(other.defer_add);
	defer_remove.swap(other.defer_remove);
	return *this;
}

Dispatcher::~Dispatcher() { for (auto event : events) delete event; events.clear(); }

void Dispatcher::add_listener(EventType type, ICallback* callback) { defer_add.insert(std::make_pair(type, callback)); }

void Dispatcher::remove_listener(EventType type, ICallback* callback) { defer_remove.insert(std::make_pair(type, callback)); }

void Dispatcher::add_event(IEvent* event) { events.push_back(event); }

void Dispatcher::dispatch(IEvent* event){
	// see reference for unordered_multimap::equal_range
	for (auto its = listeners.equal_range(event->type()); its.first != its.second; its.first++){
		// its.first->second is the ICallback*
		its.first->second->execute(event);
	}
	delete event;
}

void Dispatcher::tick(float dt){
	for (const auto& event : events) dispatch(event);
	events.clear();

	listeners.insert(defer_add.begin(), defer_add.end());
	defer_add.clear();
	
	for (const auto& pair : defer_remove){
		auto b_index = listeners.bucket(pair.first);
		for (auto it = listeners.begin(b_index); it != listeners.end(b_index); it++){
			if (it->second == pair.second){
				listeners.erase(it);
				break;
			}
		}
	}
	
	defer_remove.clear();
}
