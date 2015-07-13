// DrawGroup.h
// Chris Bowers

/**
 *	This defines a group of drawables. It is simply an extension of std::vector<Drawable*> that is itself drawable.
 *	See also TickGroup.h
 */

#ifndef __DRAWGROUP_H__
#define __DRAWGROUP_H__

#include "SFML.h"
#include <vector>

struct DrawGroup : std::vector<Drawable*>, Drawable{
protected:
	void draw(RenderTarget& target, RenderStates states) const;
};

#endif // __DRAWGROUP_H__
