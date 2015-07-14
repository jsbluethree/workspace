// IState.h
// Chris Bowers

/**
 *	This defines the interface for a state - see StateMachine.h
 */

#ifndef __ISTATE_H__
#define __ISTATE_H__

#include "Dispatcher.h"

struct IState{
	virtual ~IState() {}

	virtual void enter() {}
	virtual void run() = 0;
	virtual void exit() {}
	
	Dispatcher events;
};

#endif // __ISTATE_H__
