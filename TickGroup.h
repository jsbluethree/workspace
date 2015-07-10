// TickGroup.h

#ifndef __TICKGROUP_H__
#define __TICKGROUP_H__

#include "ITickable.h"
#include <vector>

struct TickGroup : std::vector<ITickable*>, ITickable{
	void tick(float dt);
};

#endif