// DrawGroup.h
// Chris Bowers

/**
 *	This defines a group of drawables. It is simply an extension of std::vector<Drawable*> that is itself drawable.
 *	See also TickGroup.h
 */

#ifndef __DRAWGROUP_H__
#define __DRAWGROUP_H__

#include "SFML\Graphics\Drawable.hpp"
#include "SFML\Graphics\RenderTarget.hpp"
#include <vector>

struct DrawGroup : std::vector<sf::Drawable*>, sf::Drawable{
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // __DRAWGROUP_H__
