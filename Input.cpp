// Input.cpp
// Chris Bowers

/**
 *	This implements a class that dispatches events based on input - see Input.h
 */

#include "Input.h"

SFMLEvent::SFMLEvent(const sf::Event& e) : sf_event(e) {}

EventType SFMLEvent::type() const{
	switch (sf_event.type){
	case sf::Event::Closed:
		return EventType::SF_CLOSED;
	case sf::Event::Resized:
		return EventType::SF_RESIZED;
	case sf::Event::LostFocus:
		return EventType::SF_LOSTFOCUS;
	case sf::Event::GainedFocus:
		return EventType::SF_GAINEDFOCUS;
	case sf::Event::TextEntered:
		return EventType::SF_TEXTENTERED;
	case sf::Event::KeyPressed:
		return EventType::SF_KEYPRESSED;
	case sf::Event::KeyReleased:
		return EventType::SF_KEYRELEASED;
	case sf::Event::MouseWheelMoved:
		return EventType::SF_MOUSEWHEELMOVED;
	case sf::Event::MouseWheelScrolled:
		return EventType::SF_MOUSEWHEELSCROLLED;
	case sf::Event::MouseButtonPressed:
		return EventType::SF_MOUSEBUTTONPRESSED;
	case sf::Event::MouseButtonReleased:
		return EventType::SF_MOUSEBUTTONRELEASED;
	case sf::Event::MouseMoved:
		return EventType::SF_MOUSEMOVED;
	case sf::Event::MouseEntered:
		return EventType::SF_MOUSEENTERED;
	case sf::Event::MouseLeft:
		return EventType::SF_MOUSELEFT;
	case sf::Event::JoystickButtonPressed:
		return EventType::SF_JOYSTICKBUTTONPRESSED;
	case sf::Event::JoystickButtonReleased:
		return EventType::SF_JOYSTICKBUTTONRELEASED;
	case sf::Event::JoystickMoved:
		return EventType::SF_JOYSTICKMOVED;
	case sf::Event::JoystickConnected:
		return EventType::SF_JOYSTICKCONNECTED;
	case sf::Event::JoystickDisconnected:
		return EventType::SF_JOYSTICKDISCONNECTED;
	case sf::Event::TouchBegan:
		return EventType::SF_TOUCHBEGAN;
	case sf::Event::TouchMoved:
		return EventType::SF_TOUCHMOVED;
	case sf::Event::TouchEnded:
		return EventType::SF_TOUCHENDED;
	case sf::Event::SensorChanged:
		return EventType::SF_SENSORCHANGED;
	default:
		return EventType::INVALID;
	}
}

Input::Input(sf::Window& window) : win{ window } {}

void Input::tick(float dt){
	sf::Event event;
	while (win.pollEvent(event)){
		events.add_event(new SFMLEvent(event));
	}
	events.tick(dt);
}
