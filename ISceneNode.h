// ISceneNode.h
// Chris Bowers

/**
 *	This defines the interface for a scene node. A scene node is generally defined by a rectangle.
 *	May be expanded in the future if necessary.
 */

#ifndef __ISCENENODE_H__
#define __ISCENENODE_H__

#include "SFML\Graphics\Rect.hpp"
#include "SFML\System\Vector2.hpp"

struct ISceneNode{
	virtual ~ISceneNode() = default;

	virtual void move(float offsetX, float offsetY) = 0;
	virtual void move(const sf::Vector2f& offset) = 0;
	virtual sf::FloatRect get_rect() const = 0;	
};

#endif // __ISCENENODE_H__
