// IState.h
// Chris Bowers

/**
 *	This defines the interface for a state - see StateMachine.h
 */

#ifndef __ISTATE_H__
#define __ISTATE_H__

struct Dispatcher;

struct IState{
	virtual ~IState() {}

	virtual void enter() {}
	virtual void run() = 0;
	virtual void exit() {}
	virtual Dispatcher& events() = 0;
};

#endif // __ISTATE_H__
