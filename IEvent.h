// IEvent.h
// Chris Bowers

/**
 *	This defines the interface for an event to be used with the event dispatcher - see Dispatcher.h
 *	This also contains the enum of all event types used as keys.
 */

#ifndef __IEVENT_H__
#define __IEVENT_H__


enum class EventType{
	INVALID,
	STATE,
	// following types refer to sfml event types
	SF_CLOSED,
	SF_RESIZED,
	SF_LOSTFOCUS,
	SF_GAINEDFOCUS,
	SF_TEXTENTERED,
	SF_KEYPRESSED,
	SF_KEYRELEASED,
	SF_MOUSEWHEELMOVED,
	SF_MOUSEWHEELSCROLLED,
	SF_MOUSEBUTTONPRESSED,
	SF_MOUSEBUTTONRELEASED,
	SF_MOUSEMOVED,
	SF_MOUSEENTERED,
	SF_MOUSELEFT,
	SF_JOYSTICKBUTTONPRESSED,
	SF_JOYSTICKBUTTONRELEASED,
	SF_JOYSTICKMOVED,
	SF_JOYSTICKCONNECTED,
	SF_JOYSTICKDISCONNECTED,
	SF_TOUCHBEGAN,
	SF_TOUCHMOVED,
	SF_TOUCHENDED,
	SF_SENSORCHANGED
};

struct IEvent{
	virtual ~IEvent() = default;

	virtual EventType type() const = 0;	
};


#endif // __IEVENT_H__
