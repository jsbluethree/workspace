// IEvent.h
// Chris Bowers

/**
 *	This defines the interface for an event to be used with the event dispatcher - see Dispatcher.h
 *	This also contains the enum of all event types used as keys.
 */

#ifndef __IEVENT_H__
#define __IEVENT_H__

#include "typedefs.h"

enum class EventType : u8{
	STATE
};

struct IEvent{
	virtual EventType type() = 0;
	virtual ~IEvent() {}
};


#endif // __IEVENT_H__
