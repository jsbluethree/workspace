// ISceneNode.h
// Chris Bowers

/**
 *	This defines the interface for a scene node. A scene node is generally defined by a rectangle.
 *	May be expanded in the future if necessary.
 */

#ifndef __ISCENENODE_H__
#define __ISCENENODE_H__

#include "SFML.h"

struct ISceneNode{
	virtual ~ISceneNode() = default;

	virtual void move(float offsetX, float offsetY) = 0;
	virtual void move(const Vector2f& offset) = 0;
	virtual FloatRect get_rect() const = 0;	
};

#endif // __ISCENENODE_H__
