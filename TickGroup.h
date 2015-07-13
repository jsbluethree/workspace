// TickGroup.h
// Chris Bowers

/**
 *	This defines a tickgroup, which is simply a vector of tickables that is itself tickable - see DrawGroup.h
 *	It is probably not necessary to use both this and Ticker.
 */

#ifndef __TICKGROUP_H__
#define __TICKGROUP_H__

#include "ITickable.h"
#include <vector>

struct TickGroup : std::vector<ITickable*>, ITickable{
	void tick(float dt);
};

#endif // __TICKGROUP_H__
