// ISceneNode.h
// Chris Bowers

#ifndef __ISCENENODE_H__
#define __ISCENENODE_H__

#include "typedefs.h"
#include "SFML.h"

struct ISceneNode{
	virtual void move(float offsetX, float offsetY) = 0;
	virtual void move(const Vector2f offset) = 0;
	virtual const FloatRect& get_rect() const = 0;
};

#endif // __ISCENENODE_H__
