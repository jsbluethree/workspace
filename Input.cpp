// Input.cpp
// Chris Bowers

/**
 *	This implements a class that dispatches events based on input - see Input.h
 */

#include "Input.h"

SFMLEvent::SFMLEvent(const Event& e) { sf_event = e; }

EventType SFMLEvent::type() const{
	switch (sf_event.type){
	case Event::Closed:
		return EventType::SF_CLOSED;
	case Event::Resized:
		return EventType::SF_RESIZED;
	case Event::LostFocus:
		return EventType::SF_LOSTFOCUS;
	case Event::GainedFocus:
		return EventType::SF_GAINEDFOCUS;
	case Event::TextEntered:
		return EventType::SF_TEXTENTERED;
	case Event::KeyPressed:
		return EventType::SF_KEYPRESSED;
	case Event::KeyReleased:
		return EventType::SF_KEYRELEASED;
	case Event::MouseWheelMoved:
		return EventType::SF_MOUSEWHEELMOVED;
	case Event::MouseWheelScrolled:
		return EventType::SF_MOUSEWHEELSCROLLED;
	case Event::MouseButtonPressed:
		return EventType::SF_MOUSEBUTTONPRESSED;
	case Event::MouseButtonReleased:
		return EventType::SF_MOUSEBUTTONRELEASED;
	case Event::MouseMoved:
		return EventType::SF_MOUSEMOVED;
	case Event::MouseEntered:
		return EventType::SF_MOUSEENTERED;
	case Event::MouseLeft:
		return EventType::SF_MOUSELEFT;
	case Event::JoystickButtonPressed:
		return EventType::SF_JOYSTICKBUTTONPRESSED;
	case Event::JoystickButtonReleased:
		return EventType::SF_JOYSTICKBUTTONRELEASED;
	case Event::JoystickMoved:
		return EventType::SF_JOYSTICKMOVED;
	case Event::JoystickConnected:
		return EventType::SF_JOYSTICKCONNECTED;
	case Event::JoystickDisconnected:
		return EventType::SF_JOYSTICKDISCONNECTED;
	case Event::TouchBegan:
		return EventType::SF_TOUCHBEGAN;
	case Event::TouchMoved:
		return EventType::SF_TOUCHMOVED;
	case Event::TouchEnded:
		return EventType::SF_TOUCHENDED;
	case Event::SensorChanged:
		return EventType::SF_SENSORCHANGED;
	default:
		return EventType::INVALID;
	}
}

Input::Input(Window& window) : win{ window } {}

void Input::tick(float dt){
	Event event;
	while (win.pollEvent(event)){
		events.add_event(new SFMLEvent(event));
	}
	events.tick(dt);
}
