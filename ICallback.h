// ICallback.h

#ifndef __ICALLBACK_H__
#define __ICALLBACK_H__

#include "IEvent.h"

struct ICallback{
	virtual void execute(IEvent* event) = 0;
};

#endif