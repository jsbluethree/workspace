// DrawGroup.cpp
// Chris Bowers

/**
 *	This implements a group of drawables - see DrawGroup.h
 */

#include "DrawGroup.h"

void DrawGroup::draw(sf::RenderTarget& target, sf::RenderStates states) const { for (auto drawable : *this) target.draw(*drawable, states); }
