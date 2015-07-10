// IEvent.h

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


#endif