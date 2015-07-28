// Input.h
// Chris Bowers

/**
 *	This defines a class that processes SFML events on tick, and dispatches appropriate IEvents.
 */

#ifndef __INPUT_H__
#define __INPUT_H__

#include "SFML.h"
#include "Dispatcher.h"
#include "ITickable.h"
#include "IEvent.h"

struct SFMLEvent : IEvent{
	SFMLEvent(const Event& e);

	EventType type() const;

	Event sf_event;
};

struct Input : ITickable{
	Input(Window& window);

	void tick(float dt);

	Dispatcher events;

private:
	Window& win;
};

#endif // __INPUT_H__
