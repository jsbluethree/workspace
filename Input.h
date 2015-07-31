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

struct SizeEvent : IEvent, sf::Event::SizeEvent{
	explicit SizeEvent(const sf::Event& e);
};

struct KeyPressedEvent : IEvent, sf::Event::KeyEvent{
	explicit KeyPressedEvent(const sf::Event& e);
};

struct KeyReleasedEvent : IEvent, sf::Event::KeyEvent{
	explicit KeyReleasedEvent(const sf::Event& e);
};

struct TextEvent : IEvent, sf::Event::TextEvent{
	explicit TextEvent(const sf::Event& e);
};

struct MouseMoveEvent : IEvent, sf::Event::MouseMoveEvent{
	explicit MouseMoveEvent(const sf::Event& e);
};

struct MouseButtonPressedEvent : IEvent, sf::Event::MouseButtonEvent{
	explicit MouseButtonPressedEvent(const sf::Event& e);
};

struct MouseButtonReleasedEvent : IEvent, sf::Event::MouseButtonEvent{
	explicit MouseButtonReleasedEvent(const sf::Event& e);
};

struct MouseWheelScrollEvent : IEvent, sf::Event::MouseWheelScrollEvent{
	explicit MouseWheelScrollEvent(const sf::Event& e);
};

struct JoystickConnectEvent : IEvent, sf::Event::JoystickConnectEvent{
	explicit JoystickConnectEvent(const sf::Event& e);
};

struct JoystickDisconnectEvent : IEvent, sf::Event::JoystickConnectEvent{
	explicit JoystickDisconnectEvent(const sf::Event& e);
};

struct JoystickMoveEvent : IEvent, sf::Event::JoystickMoveEvent{
	explicit JoystickMoveEvent(const sf::Event& e);
};

struct JoystickButtonPressedEvent : IEvent, sf::Event::JoystickButtonEvent{
	explicit JoystickButtonPressedEvent(const sf::Event& e);
};

struct JoystickButtonReleasedEvent : IEvent, sf::Event::JoystickButtonEvent{
	explicit JoystickButtonReleasedEvent(const sf::Event& e);
};

struct TouchBeganEvent : IEvent, sf::Event::TouchEvent{
	explicit TouchBeganEvent(const sf::Event& e);
};

struct TouchMovedEvent : IEvent, sf::Event::TouchEvent{
	explicit TouchMovedEvent(const sf::Event& e);
};

struct TouchEndedEvent : IEvent, sf::Event::TouchEvent{
	explicit TouchEndedEvent(const sf::Event& e);
};

struct SensorEvent : IEvent, sf::Event::SensorEvent{
	explicit SensorEvent(const sf::Event& e);
};

struct ClosedEvent : IEvent{};

struct LostFocusEvent : IEvent{};

struct GainedFocusEvent : IEvent{};

struct MouseEnteredEvent : IEvent{};

struct MouseLeftEvent : IEvent{};

struct Input : ITickable{
	explicit Input(sf::Window& window);

	void tick(float dt);

	Dispatcher events;

private:
	sf::Window& win;
};

#endif // __INPUT_H__
