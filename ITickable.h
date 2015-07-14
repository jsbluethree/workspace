// ITickable.h
// Chris Bowers

/**
 *	This defines the interface for a tickable - an object updated on each iteration of the main game loop.
 */

#ifndef __ITICKABLE_H__
#define __ITICKABLE_H__

struct ITickable{
	virtual void tick(float dt) = 0;
	
	virtual ~ITickable() {}
};

#endif // __ITICKABLE_H__
