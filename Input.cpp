// Input.cpp
// Chris Bowers

/**
 *	This implements a class that dispatches events based on input - see Input.h
 */

#include "Input.h"

SizeEvent::SizeEvent(const sf::Event& e) : sf::Event::SizeEvent(e.size) {}

KeyPressedEvent::KeyPressedEvent(const sf::Event& e) : sf::Event::KeyEvent(e.key) {}

KeyReleasedEvent::KeyReleasedEvent(const sf::Event& e) : sf::Event::KeyEvent(e.key) {}

TextEvent::TextEvent(const sf::Event& e) : sf::Event::TextEvent(e.text) {}

MouseMoveEvent::MouseMoveEvent(const sf::Event& e) : sf::Event::MouseMoveEvent(e.mouseMove) {}

MouseButtonPressedEvent::MouseButtonPressedEvent(const sf::Event& e) : sf::Event::MouseButtonEvent(e.mouseButton) {}

MouseButtonReleasedEvent::MouseButtonReleasedEvent(const sf::Event& e) : sf::Event::MouseButtonEvent(e.mouseButton) {}

MouseWheelScrollEvent::MouseWheelScrollEvent(const sf::Event& e) : sf::Event::MouseWheelScrollEvent(e.mouseWheelScroll) {}

JoystickConnectEvent::JoystickConnectEvent(const sf::Event& e) : sf::Event::JoystickConnectEvent(e.joystickConnect) {}

JoystickDisconnectEvent::JoystickDisconnectEvent(const sf::Event& e) : sf::Event::JoystickConnectEvent(e.joystickConnect) {}

JoystickMoveEvent::JoystickMoveEvent(const sf::Event& e) : sf::Event::JoystickMoveEvent(e.joystickMove) {}

JoystickButtonPressedEvent::JoystickButtonPressedEvent(const sf::Event& e) : sf::Event::JoystickButtonEvent(e.joystickButton) {}

JoystickButtonReleasedEvent::JoystickButtonReleasedEvent(const sf::Event& e) : sf::Event::JoystickButtonEvent(e.joystickButton) {}

TouchBeganEvent::TouchBeganEvent(const sf::Event& e) : sf::Event::TouchEvent(e.touch) {}

TouchMovedEvent::TouchMovedEvent(const sf::Event& e) : sf::Event::TouchEvent(e.touch) {}

TouchEndedEvent::TouchEndedEvent(const sf::Event& e) : sf::Event::TouchEvent(e.touch) {}

SensorEvent::SensorEvent(const sf::Event& e) : sf::Event::SensorEvent(e.sensor) {}

Input::Input(sf::Window& window) : win{ window } {}

void Input::tick(float dt){
	sf::Event event;
	while (win.pollEvent(event)){
		switch (event.type){
		case sf::Event::Closed:
			events.add_event(new ClosedEvent);
			break;
		case sf::Event::Resized:
			events.add_event(new SizeEvent(event));
			break;
		case sf::Event::LostFocus:
			events.add_event(new LostFocusEvent);
			break;
		case sf::Event::GainedFocus:
			events.add_event(new GainedFocusEvent);
			break;
		case sf::Event::TextEntered:
			events.add_event(new TextEvent(event));
			break;
		case sf::Event::KeyPressed:
			events.add_event(new KeyPressedEvent(event));
			break;
		case sf::Event::KeyReleased:
			events.add_event(new KeyReleasedEvent(event));
			break;
		case sf::Event::MouseWheelScrolled:
			events.add_event(new MouseWheelScrollEvent(event));
			break;
		case sf::Event::MouseButtonPressed:
			events.add_event(new MouseButtonPressedEvent(event));
			break;
		case sf::Event::MouseButtonReleased:
			events.add_event(new MouseButtonReleasedEvent(event));
			break;
		case sf::Event::MouseEntered:
			events.add_event(new MouseEnteredEvent);
			break;
		case sf::Event::MouseLeft:
			events.add_event(new MouseLeftEvent);
			break;
		case sf::Event::JoystickButtonPressed:
			events.add_event(new JoystickButtonPressedEvent(event));
			break;
		case sf::Event::JoystickButtonReleased:
			events.add_event(new JoystickButtonReleasedEvent(event));
			break;
		case sf::Event::JoystickMoved:
			events.add_event(new JoystickMoveEvent(event));
			break;
		case sf::Event::JoystickConnected:
			events.add_event(new JoystickConnectEvent(event));
			break;
		case sf::Event::JoystickDisconnected:
			events.add_event(new JoystickDisconnectEvent(event));
			break;
		case sf::Event::TouchBegan:
			events.add_event(new TouchBeganEvent(event));
			break;
		case sf::Event::TouchMoved:
			events.add_event(new TouchMovedEvent(event));
			break;
		case sf::Event::TouchEnded:
			events.add_event(new TouchEndedEvent(event));
			break;
		case sf::Event::SensorChanged:
			events.add_event(new SensorEvent(event));
			break;
		}
	}
	events.tick(dt);
}
