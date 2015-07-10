// ITickable.h

#ifndef __ITICKABLE_H__
#define __ITICKABLE_H__

struct ITickable{
	virtual void tick(float dt) = 0;
};

#endif