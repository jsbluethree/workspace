// Dispatcher.h
// Chris Bowers

/**
 *	This defines an event dispatcher. The dispatcher maintains a hashmap of listeners keyed by event type.
 *	On tick, it sends out its events to the appropriate listeners.
 */

#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

#include "ICallback.h"
#include "IEvent.h"
#include "ITickable.h"
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>

struct Dispatcher : ITickable{
	Dispatcher() = default;
	Dispatcher(Dispatcher&& other);
	Dispatcher& operator=(Dispatcher&& other);
	~Dispatcher();

	Dispatcher(const Dispatcher&) = delete;
	Dispatcher& operator=(const Dispatcher&) = delete;

	template<typename event_type>
	void add_listener(ICallback& callback);
	template<typename event_type>
	void remove_listener(ICallback& callback);
	void add_event(IEvent* event);
	void dispatch(IEvent* event);
	void tick(float dt);

private:
	std::unordered_multimap<std::type_index, ICallback*> listeners;
	std::unordered_multimap<std::type_index, ICallback*> defer_add;
	std::unordered_multimap<std::type_index, ICallback*> defer_remove;
	std::vector<IEvent*> events;
};

// NEED IMPLEMENTATION FOR TEMPLATE FUNCTIONS HERE:

template<typename event_type>
void Dispatcher::add_listener(ICallback& callback) { defer_add.insert(std::make_pair(std::type_index(typeid(event_type)), &callback)); }

template<typename event_type>
void Dispatcher::remove_listener(ICallback& callback) { defer_remove.insert(std::make_pair(std::type_index(typeid(event_type)), &callback)); }

#endif // __DISPATCHER_H__
