// ICallback.h
// Chris Bowers

/**
 *	This defines the interface for a callback to be used with the event dispatcher - see Dispatcher.h
 */

#ifndef __ICALLBACK_H__
#define __ICALLBACK_H__

#include "IEvent.h"

struct ICallback{
	virtual void execute(IEvent* event) = 0;
};

#endif // __ICALLBACK_H__
