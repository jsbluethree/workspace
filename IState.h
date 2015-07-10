// IState.h

#ifndef __ISTATE_H__
#define __ISTATE_H__

#include "Dispatcher.h"

struct IState{
	Dispatcher events;

	virtual void enter() {}
	virtual void run() = 0;
	virtual void exit() {}
};

#endif