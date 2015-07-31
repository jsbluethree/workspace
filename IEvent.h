// IEvent.h
// Chris Bowers

/**
 *	This defines the base class for all events to be used with the event dispatcher - see Dispatcher.h
 *	TODO: Pool allocation
 */

#ifndef __IEVENT_H__
#define __IEVENT_H__

struct IEvent{
	virtual ~IEvent() = default;
};

#endif // __IEVENT_H__
