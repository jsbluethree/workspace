// DrawGroup.h

#ifndef __DRAWGROUP_H__
#define __DRAWGROUP_H__

#include "SFML.h"
#include <vector>

struct DrawGroup : std::vector<Drawable*>, Drawable{
protected:
	void draw(RenderTarget& target, RenderStates states) const;
};

#endif