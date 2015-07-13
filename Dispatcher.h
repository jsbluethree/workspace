// Dispatcher.h

/**
 *	This defines an event dispatcher. The dispatcher maintains a hashmap of listeners keyed by event type.
 *	On tick, it sends out its events to the appropriate listeners.
 *
 *	TODO: Implement using std::unordered_multimap rather than a map of vectors
 */

#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

#include "ICallback.h"
#include "IEvent.h"
#include "ITickable.h"
#include <unordered_map>
#include <vector>

struct Dispatcher : ITickable{
	std::unordered_map<EventType, std::vector<ICallback*>> listeners;
	std::vector<IEvent*> events;
	std::vector<std::pair<EventType, ICallback*>> defer_add;
	std::vector<std::pair<EventType, ICallback*>> defer_remove;

	Dispatcher();
	~Dispatcher();

	void add_listener(EventType type, ICallback* callback);
	void remove_listener(EventType type, ICallback* callback);
	void add_event(IEvent* event);
	void dispatch(IEvent* event);
	void tick(float dt);

private:
	Dispatcher(const Dispatcher&);
	Dispatcher(Dispatcher&&);
	Dispatcher& operator=(const Dispatcher&);
	Dispatcher& operator=(Dispatcher&&);
};

#endif // __DISPATCHER_H__
