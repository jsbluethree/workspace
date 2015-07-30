// Input.h
// Chris Bowers

/**
 *	This defines a class that processes SFML events on tick, and dispatches appropriate IEvents.
 */

#ifndef __INPUT_H__
#define __INPUT_H__

#include "SFML\Window\Event.hpp"
#include "SFML\Window\Window.hpp"
#include "Dispatcher.h"
#include "ITickable.h"
#include "IEvent.h"

struct SFMLEvent : IEvent{
	explicit SFMLEvent(const sf::Event& e);

	EventType type() const;

	sf::Event sf_event;
};

struct Input : ITickable{
	explicit Input(sf::Window& window);

	void tick(float dt);

	Dispatcher events;

private:
	sf::Window& win;
};

#endif // __INPUT_H__
